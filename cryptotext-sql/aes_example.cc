//
// $Id: aes_example.cc 33 2010-08-22 22:33:05Z df2417 $
//

#include <string>
#include <cstdio>
#include <cstdlib>
#include <openssl/evp.h>
#include <openssl/aes.h>

int aes_init(unsigned char * key_data, int key_data_len, EVP_CIPHER_CTX * e_ctx, EVP_CIPHER_CTX * d_ctx) {
   int i, nrounds = 5;
   unsigned char key[32], iv[32];
   i = EVP_BytesToKey(EVP_aes_256_cbc(), EVP_sha1(), NULL, key_data, key_data_len, nrounds, key, iv);
   if (i != 32) {
      printf("Key size is %d bits - should be 256 bits\n", i);
      return EXIT_FAILURE;
   }

   EVP_CIPHER_CTX_init(e_ctx);
   EVP_EncryptInit_ex(e_ctx, EVP_aes_256_cbc(), NULL, key, iv);
   EVP_CIPHER_CTX_init(d_ctx);
   EVP_DecryptInit_ex(d_ctx, EVP_aes_256_cbc(), NULL, key, iv);

   return EXIT_SUCCESS;
}

unsigned char * aes_encrypt(EVP_CIPHER_CTX * e, unsigned char * plaintext, int * len) {
   int c_len = *len + AES_BLOCK_SIZE, f_len = 0;
   unsigned char *ciphertext = (unsigned char *)malloc(c_len);

   EVP_EncryptInit_ex(e, NULL, NULL, NULL, NULL);
   EVP_EncryptUpdate(e, ciphertext, &c_len, plaintext, *len);
   EVP_EncryptFinal_ex(e, ciphertext+c_len, &f_len);

   *len = c_len + f_len;
   return ciphertext;
}

unsigned char * aes_decrypt(EVP_CIPHER_CTX * e, unsigned char * ciphertext, int * len) {
   int p_len = *len, f_len = 0;
   unsigned char *plaintext = (unsigned char *)malloc(p_len);
  
   EVP_DecryptInit_ex(e, NULL, NULL, NULL, NULL);
   EVP_DecryptUpdate(e, plaintext, &p_len, ciphertext, *len);
   EVP_DecryptFinal_ex(e, plaintext+p_len, &f_len);

   *len = p_len + f_len;
   return plaintext;
}

int do_aesOPS(char * inputText, char * inputKey) {
   EVP_CIPHER_CTX en, de;

   unsigned char * key_data;
   int key_data_len;

   // key_data = (unsigned char *)inputKey;
   // key_data_len = strlen(inputKey);
   key_data = (unsigned char *)'cuenctest1';
   key_data_len = strlen(key_data);
  
   if (aes_init(key_data, key_data_len, &en, &de)) {
      printf("Couldn't initialize AES cipher\n");
      return EXIT_FAILURE;
   }
   char *plaintext;
   unsigned char *ciphertext;
   int olen, len;
    
   olen = len = strlen(inputText)+1;
    
   ciphertext = aes_encrypt(&en, (unsigned char *)inputText, &len);
   plaintext = (char *)aes_decrypt(&de, ciphertext, &len);

   if (strncmp(plaintext, inputText, olen)) { 
      printf("FAIL: enc/dec failed for \"%s\"\n", inputText);
   }
   else { 
	  printf("AES Encrypted: \"%s\"\n", (char *)ciphertext);
	  printf("AES Decrypted: \"%s\"\n", plaintext);
   }    
   free(ciphertext);
   free(plaintext);
   EVP_CIPHER_CTX_cleanup(&en);
   EVP_CIPHER_CTX_cleanup(&de);

   return EXIT_SUCCESS;
}