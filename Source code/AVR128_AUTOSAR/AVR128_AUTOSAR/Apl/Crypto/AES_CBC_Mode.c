/*
 * AES_CBC_Mode.c
 *
 * Created: 8/2/2022 11:37:46 PM
 *  Author: phamh
 */ 

#include "AES_CBC_Mode.h"

void aes128_CBC_encrypt(uint8 iv[], uint8* plaintext, uint32 plaintext_size, const uint8* key)
{
	uint8 uint8a_cbc[16];
	uint32 uint32a_byteIdx;
	uint32 uint32a_blockIdx;
	uint32 uint32a_blocks;

	for (uint32a_byteIdx = 0U; uint32a_byteIdx < 16U; uint32a_byteIdx++) {
		uint8a_cbc[uint32a_byteIdx] = iv[uint32a_byteIdx];
	}

	uint32a_blocks = plaintext_size / 16U;
	
	/* Loop through all blocks */
	for (uint32a_blockIdx = 0U; uint32a_blockIdx < uint32a_blocks; uint32a_blockIdx++) {
		/* XOR: Combining of the plaintext block with the previous ciphertext block */
		for (uint32a_byteIdx = 0U; uint32a_byteIdx < 16U; uint32a_byteIdx++) {
			uint8a_cbc[uint32a_byteIdx] ^= plaintext[uint32a_byteIdx];
		}
		
		/* Create ciphertext */
		aes128_encrypt(uint8a_cbc, key);
		
		for (uint32a_byteIdx = 0U; uint32a_byteIdx < 16U; uint32a_byteIdx++) {
			plaintext[uint32a_byteIdx] = uint8a_cbc[uint32a_byteIdx];
		}
		
		plaintext += 16U;
	}

	/* Store new IV for next call */
	for (uint32a_byteIdx = 0U; uint32a_byteIdx < 16U; uint32a_byteIdx++) {
		iv[uint32a_byteIdx] = uint8a_cbc[uint32a_byteIdx];
	}

	return;
}

void aes128_CBC_decrypt(uint8 iv[], uint8* ciphertext, uint32 ciphertext_size, const uint8* key)
{
	uint8 uint8a_cbc[16];
	uint8 uint8a_temp[16];
	uint32 uint32a_byteIdx;
	uint32 uint32a_blockIdx;
	uint32 uint32a_blocks;


	/* uint8a_cbc is the output of previous ciphertext block */
	for (uint32a_byteIdx = 0U; uint32a_byteIdx < 16U; uint32a_byteIdx++) {
		uint8a_cbc[uint32a_byteIdx] = iv[uint32a_byteIdx];
	}

	uint32a_blocks = ciphertext_size / 16U;
	
	/* Loop through all blocks */
	for (uint32a_blockIdx = 0U; uint32a_blockIdx < uint32a_blocks; uint32a_blockIdx++) {
		/* Get previous ciphertext block */
		for (uint32a_byteIdx = 0U; uint32a_byteIdx < 16U; uint32a_byteIdx++) {
			uint8a_temp[uint32a_byteIdx] = ciphertext[uint32a_byteIdx];
		}
		
		/* Create output from decryption */
		aes128_decrypt(ciphertext, key);
		
		/* Create plaintext: XOR output decryption with previous ciphertext */
		for (uint32a_byteIdx = 0U; uint32a_byteIdx < 16U; uint32a_byteIdx++) {
			ciphertext[uint32a_byteIdx] ^= uint8a_cbc[uint32a_byteIdx];
			uint8a_cbc[uint32a_byteIdx] = uint8a_temp[uint32a_byteIdx];
		}
		
		ciphertext += 16U;
	}

	/* Store new IV for next call */
	for (uint32a_byteIdx = 0U; uint32a_byteIdx < 16U; uint32a_byteIdx++) {
		iv[uint32a_byteIdx] = uint8a_cbc[uint32a_byteIdx];
	}

	return;
}