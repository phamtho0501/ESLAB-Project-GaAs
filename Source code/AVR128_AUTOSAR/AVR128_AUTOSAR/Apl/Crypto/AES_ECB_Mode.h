/*
 * AES_ECB_Mode.h
 *
 * Created: 8/2/2022 11:31:54 PM
 *  Author: phamh
 */ 


#ifndef AES_ECB_MODE_H_
#define AES_ECB_MODE_H_

#include "aes128.h"

void aes128_ECB_encrypt(uint8* plaintext, uint32 plaintext_size, const uint8* key);
void aes128_ECB_decrypt(uint8* Ciphertext, uint32 Ciphertext_size, const uint8* key);


#endif /* AES_ECB_MODE_H_ */