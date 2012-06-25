//
// $Id: misc_text_tools.h 78 2010-09-05 01:22:56Z df2417 $
//

#ifndef MISC_TEXT_TOOLS_H
#define MISC_TEXT_TOOLS_H

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
#include "GeneralHashFunctions.h"
#include "base64.h"

#define BLOOM_SIZE 128           // 128 bits to represent 1024 bytes

using namespace std;

int aes_init(unsigned char *key_data, int key_data_len,
        unsigned char *salt, EVP_CIPHER_CTX * e_ctx);

unsigned char *aes_encrypt(EVP_CIPHER_CTX * e, unsigned char *plaintext,
        int *len);

vector < string > body_to_words(string);

char *encrypt_word(string, char *, int *);

void dump_bloom(unsigned char *bloom);

bool
test_bloom_membership(unsigned char *haystack_bloom,
        unsigned char *needle_bloom);

void
hash_encrypted_word_to_bloom(char *ciphertext, unsigned char *bloom);


#endif                          /* end of include guard */
