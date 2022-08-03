/*
 * AES_CBC_Mode.h
 *
 * Created: 8/2/2022 11:37:53 PM
 *  Author: phamh
 */ 


#ifndef AES_CBC_MODE_H_
#define AES_CBC_MODE_H_

#include "aes128.h"

void aes128_CBC_encrypt(uint8 iv[], uint8* plaintext, uint32 plaintext_size, const uint8* key);
void aes128_CBC_decrypt(uint8 iv[], uint8* ciphertext, uint32 ciphertext_size, const uint8* key);

#endif /* AES_CBC_MODE_H_ */