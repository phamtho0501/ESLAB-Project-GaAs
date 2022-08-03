/*
 * aes128.h
 *
 * Created: 7/19/2022 1:33:10 AM
 *  Author: ThoPH
 */ 


#ifndef AES128_H_
#define AES128_H_

#include "Std_Type.h"

typedef void (*funcEncryption)(uint8* state, const uint8* key, uint8 mode);

void aes128_encrypt(uint8 *state, const uint8 *key);
void aes128_decrypt(uint8* cipher, const uint8* key);


#endif /* AES128_H_ */