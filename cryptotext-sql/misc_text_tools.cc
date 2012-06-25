//
// Miscellaneous text tools
//
// $Id: misc_text_tools.cc 82 2010-09-16 14:23:36Z df2417 $
//


#include <iostream>
#include <vector>
#include <string>
#include <cstring>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <iterator>
#include <openssl/evp.h>
#include <openssl/aes.h>
#include "base64.h"
#include "GeneralHashFunctions.h"
#include "misc_text_tools.h"

using namespace std;


typedef unsigned int (*hash_func) (const string &);

void dump_bloom(unsigned char *bloom) {
    for (int i = 0; i < BLOOM_SIZE; ++i) {
        printf("%02x", bloom[i]);
    }
    printf("\n");

}

// true if found, false if not found

bool
test_bloom_membership(unsigned char *haystack_bloom,
        unsigned char *needle_bloom) {
    for (int idx = 0; idx < BLOOM_SIZE; ++idx) {
        if ((needle_bloom[idx] & haystack_bloom[idx]) != needle_bloom[idx])
            return true;
    }
    return false;
}

void
hash_encrypted_word_to_bloom(char *ciphertext, unsigned char *bloom) {
    // hash_func hashes[] = {RSHash, JSHash, PJWHash, ELFHash, BKDRHash, SDBMHash,
    //     DJBHash, DEKHash, BPHash, FNVHash, APHash};

	string b64_cipher = base64_encode(reinterpret_cast<const unsigned char *>(ciphertext), strlen(ciphertext));

	// DEBUG
	cout << "b64_cipher = " << b64_cipher << endl;

    //for (unsigned int idx = 0; idx < sizeof (hashes) / sizeof (*hashes); ++idx) {
        unsigned int hash;
        unsigned char hash_index;

        // Get the bloom filter hash index
        // hash = hashes[idx] (b64_cipher);
		hash = RSHash(b64_cipher);
        hash_index =
                (hash >> 24) & 0xFF ^
                (hash >> 16) & 0xFF ^ (hash >> 8) & 0xFF ^ (hash) & 0xFF;

        // Find the bit offset in the bloom filter
        int byte_offset, bit_offset;
        byte_offset = hash_index / 8;
        bit_offset = hash_index % 8;

        // Set it
        bloom[byte_offset] |= 1<<bit_offset;
    //} // end for
}

/*
 body_to_words:

        Split `body' into word components.
 */
vector < string > body_to_words(string body) {
    vector < string > words;
    istringstream word_stream(body);

    copy(istream_iterator < string > (word_stream),
            istream_iterator < string > (),
            back_inserter < vector < string > >(words));

    return words;
}

// args in: word, key
// args out: len

char *encrypt_word(string word, char *key, int *len) {
    EVP_CIPHER_CTX en;

    // Initialize AES
    unsigned char salt[] = "U2FsdGVkX1";
    unsigned char *key_data;
    int key_data_len, i;

    key_data = reinterpret_cast<unsigned char *> (key);
    key_data_len = strlen(key);

    if (aes_init(key_data, key_data_len, reinterpret_cast<unsigned char *> (&salt), &en)) {
        printf("Couldn't initialize AES cipher\n");
        return NULL;
    }
    // Encrypt word
    unsigned char *encrypted_word;
    unsigned char *plaintext_word;
    *len = word.length();

    const char *x = word.c_str(); // needed for proper const below

    plaintext_word = (unsigned char *) x;
    encrypted_word = aes_encrypt(&en, plaintext_word, len);

    return (char *)encrypted_word;

}

string convertInt(int number) {
    stringstream ss; //create a stringstream
    ss << number; //add number to the stream
    return ss.str(); //return a string with the contents of the stream
}



// 
// Create an 256 bit key and IV using the supplied key_data. salt can be added for taste.
// Fills in the encryption and decryption ctx objects and returns 0 on success
//

int aes_init(unsigned char *key_data, int key_data_len,
        unsigned char *salt, EVP_CIPHER_CTX * e_ctx) {
    int i, nrounds = 5;
    unsigned char key[32], iv[32];

    //     
    // Gen key & IV for AES 256 CBC mode. A SHA1 digest is used to hash the supplied key material.
    // nrounds is the number of times the we hash the material. More rounds are more secure but
    // slower.
    // 
    i = EVP_BytesToKey(EVP_aes_256_cbc(), EVP_sha1(), salt, key_data,
            key_data_len, nrounds, key, iv);
    if (i != 32) {
        printf("Key size is %d bits - should be 256 bits\n", i);
        return -1;
    }

    EVP_CIPHER_CTX_init(e_ctx);
    EVP_EncryptInit_ex(e_ctx, EVP_aes_256_cbc(), NULL, key, iv);

    return EXIT_SUCCESS;
}

unsigned char *aes_encrypt(EVP_CIPHER_CTX * e, unsigned char *plaintext,
        int *len) {
    /* max ciphertext len for a n bytes of plaintext is n + AES_BLOCK_SIZE -1 bytes */
    int c_len = *len + AES_BLOCK_SIZE, f_len = 0;
    unsigned char *ciphertext = reinterpret_cast<unsigned char *> (malloc(c_len));

    /* allows reusing of 'e' for multiple encryption cycles */
    EVP_EncryptInit_ex(e, NULL, NULL, NULL, NULL);

    /* update ciphertext, c_len is filled with the length of ciphertext generated,
     *len is the size of plaintext in bytes */
    EVP_EncryptUpdate(e, ciphertext, &c_len, plaintext, *len);

    /* update ciphertext with the final remaining bytes */
    EVP_EncryptFinal_ex(e, ciphertext + c_len, &f_len);

    *len = c_len + f_len;
    return ciphertext;
}

// DEBUG

int main(int argc, char *argv[]) {
    char *cipher;		// unsigned to preserve bitwise ops
    int len;
    unsigned char bloom_body[BLOOM_SIZE] = {'\0'};

    for (int i = 1; i < 5049; i++) {
        string inFileName = "files/body-" + convertInt(i) + ".txt";

        ifstream infile;
        infile.open(inFileName.c_str(), ifstream::in);

        string line, body_words;
        while (getline(infile, line)) {
            body_words += line; // read the lines from the SQL file into a single statement
        }
        infile.close();

        // build message bloom filter
		// Clear the filter first
		for(size_t i = 0; i < BLOOM_SIZE; ++i) {
			bloom_body[i] = 0;
		}

        vector<string> words = body_to_words(body_words); // Fill with files of plaintext words per message
        for (vector<string>::iterator iter = words.begin(); iter != words.end(); iter++) {
            cout << "Word: [" << *iter << "]" <<  endl;
            cipher = encrypt_word(*iter, (char*) "cuenctest1", &len);
            hash_encrypted_word_to_bloom(cipher, bloom_body);

            dump_bloom(bloom_body);               // for debugging

            //string outfile = "files/body-" + convertInt(i) + ".bin";
            //ofstream out(outfile.c_str(), ios::binary);
            //out.write((char*) bloom_body, sizeof (bloom_body));
            //out.close();

        }
    }
    // create a word bloom for debugging
   unsigned char bloom_word[BLOOM_SIZE] = {'\0'};
   cipher = encrypt_word("ueheiu", (char*)"cuenctest1", &len);
   hash_encrypted_word_to_bloom(cipher, bloom_word);

   // test membership
   cout << test_bloom_membership(bloom_body, bloom_word) << endl;

   return 0;
}
