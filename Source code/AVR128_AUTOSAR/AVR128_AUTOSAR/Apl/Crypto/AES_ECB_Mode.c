/*
 * AES_ECB_Mode.c
 *
 * Created: 8/2/2022 11:32:03 PM
 *  Author: phamh
 */ 

#include "AES_ECB_Mode.h"

void aes128_ECB_encrypt(uint8* plaintext, uint32 plaintext_size, const uint8* key)
{
	uint32 uint32a_idx;
	uint32 uint32a_blocks;

	/* Get the number of block */
	uint32a_blocks = plaintext_size / 16U;

	for (uint32a_idx = 0U; uint32a_idx < uint32a_blocks; uint32a_idx++) {
		aes128_encrypt(plaintext, key);
		plaintext += 16U;
	}

	return;
}


void aes128_ECB_decrypt(uint8* Ciphertext, uint32 Ciphertext_size, const uint8* key)
{
	uint32 uint32a_idx;
	uint32 uint32a_blocks;

	/* Get the number of block */
	uint32a_blocks = Ciphertext_size / 16U;

	for (uint32a_idx = 0U; uint32a_idx < uint32a_blocks; uint32a_idx++) {
		aes128_decrypt(Ciphertext, key);
		Ciphertext += 16U;
	}

	return;
}