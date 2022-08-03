/*
 * aes128.c
 *
 * Created: 7/19/2022 1:32:46 AM
 *  Author: ThoPH
 */ 

#include <aes128.h>

#define getSBoxInvert(num) (Inv_S_Box[(num)])

static void GetState(uint8* plaintext, uint8* state, uint8 mode);
static void RotWord(uint8* word);
static void KeyExpansion128(const uint8* key);
static void AddRoundKey(uint8* state, const uint8* key, uint8 mode);
static void ShiftRows(uint8* state, const uint8* key, uint8 mode);
static void SubByte(uint8* state, const uint8* key, uint8 mode);
static void SubMixcolumn(uint8* SubState);
static void Mixcolumns(uint8* state, const uint8* key, uint8 mode);
static void aes128_encrypt_sub(uint8* plaintext);
static void aes128_decrypt_sub(uint8* state);
static void InvMixColumns(uint8* state);
static void InvSubBytes(uint8* state);
static void InvShiftRows(uint8* state);
static uint8 Multiply(uint8 x, uint8 y);
static uint8 xtime(uint8 x);
static const funcEncryption EncryptionFuncTbl[2][4] =
{
    {
        &SubByte,
        &ShiftRows,
        &Mixcolumns,
        &AddRoundKey
    },
    {
        &SubByte,
        &ShiftRows,
        NULL_PTR,
        &AddRoundKey
    }
};
static const uint8 S_Box[256] = {
    0x63, 0x7c, 0x77, 0x7b, 0xf2, 0x6b, 0x6f, 0xc5, 0x30, 0x01, 0x67, 0x2b, 0xfe, 0xd7, 0xab, 0x76,
    0xca, 0x82, 0xc9, 0x7d, 0xfa, 0x59, 0x47, 0xf0, 0xad, 0xd4, 0xa2, 0xaf, 0x9c, 0xa4, 0x72, 0xc0,
    0xb7, 0xfd, 0x93, 0x26, 0x36, 0x3f, 0xf7, 0xcc, 0x34, 0xa5, 0xe5, 0xf1, 0x71, 0xd8, 0x31, 0x15,
    0x04, 0xc7, 0x23, 0xc3, 0x18, 0x96, 0x05, 0x9a, 0x07, 0x12, 0x80, 0xe2, 0xeb, 0x27, 0xb2, 0x75,
    0x09, 0x83, 0x2c, 0x1a, 0x1b, 0x6e, 0x5a, 0xa0, 0x52, 0x3b, 0xd6, 0xb3, 0x29, 0xe3, 0x2f, 0x84,
    0x53, 0xd1, 0x00, 0xed, 0x20, 0xfc, 0xb1, 0x5b, 0x6a, 0xcb, 0xbe, 0x39, 0x4a, 0x4c, 0x58, 0xcf,
    0xd0, 0xef, 0xaa, 0xfb, 0x43, 0x4d, 0x33, 0x85, 0x45, 0xf9, 0x02, 0x7f, 0x50, 0x3c, 0x9f, 0xa8,
    0x51, 0xa3, 0x40, 0x8f, 0x92, 0x9d, 0x38, 0xf5, 0xbc, 0xb6, 0xda, 0x21, 0x10, 0xff, 0xf3, 0xd2,
    0xcd, 0x0c, 0x13, 0xec, 0x5f, 0x97, 0x44, 0x17, 0xc4, 0xa7, 0x7e, 0x3d, 0x64, 0x5d, 0x19, 0x73,
    0x60, 0x81, 0x4f, 0xdc, 0x22, 0x2a, 0x90, 0x88, 0x46, 0xee, 0xb8, 0x14, 0xde, 0x5e, 0x0b, 0xdb,
    0xe0, 0x32, 0x3a, 0x0a, 0x49, 0x06, 0x24, 0x5c, 0xc2, 0xd3, 0xac, 0x62, 0x91, 0x95, 0xe4, 0x79,
    0xe7, 0xc8, 0x37, 0x6d, 0x8d, 0xd5, 0x4e, 0xa9, 0x6c, 0x56, 0xf4, 0xea, 0x65, 0x7a, 0xae, 0x08,
    0xba, 0x78, 0x25, 0x2e, 0x1c, 0xa6, 0xb4, 0xc6, 0xe8, 0xdd, 0x74, 0x1f, 0x4b, 0xbd, 0x8b, 0x8a,
    0x70, 0x3e, 0xb5, 0x66, 0x48, 0x03, 0xf6, 0x0e, 0x61, 0x35, 0x57, 0xb9, 0x86, 0xc1, 0x1d, 0x9e,
    0xe1, 0xf8, 0x98, 0x11, 0x69, 0xd9, 0x8e, 0x94, 0x9b, 0x1e, 0x87, 0xe9, 0xce, 0x55, 0x28, 0xdf,
    0x8c, 0xa1, 0x89, 0x0d, 0xbf, 0xe6, 0x42, 0x68, 0x41, 0x99, 0x2d, 0x0f, 0xb0, 0x54, 0xbb, 0x16 
};
static const uint8 Inv_S_Box[256] = {
    0x52, 0x09, 0x6a, 0xd5, 0x30, 0x36, 0xa5, 0x38, 0xbf, 0x40, 0xa3, 0x9e, 0x81, 0xf3, 0xd7, 0xfb,
    0x7c, 0xe3, 0x39, 0x82, 0x9b, 0x2f, 0xff, 0x87, 0x34, 0x8e, 0x43, 0x44, 0xc4, 0xde, 0xe9, 0xcb,
    0x54, 0x7b, 0x94, 0x32, 0xa6, 0xc2, 0x23, 0x3d, 0xee, 0x4c, 0x95, 0x0b, 0x42, 0xfa, 0xc3, 0x4e,
    0x08, 0x2e, 0xa1, 0x66, 0x28, 0xd9, 0x24, 0xb2, 0x76, 0x5b, 0xa2, 0x49, 0x6d, 0x8b, 0xd1, 0x25,
    0x72, 0xf8, 0xf6, 0x64, 0x86, 0x68, 0x98, 0x16, 0xd4, 0xa4, 0x5c, 0xcc, 0x5d, 0x65, 0xb6, 0x92,
    0x6c, 0x70, 0x48, 0x50, 0xfd, 0xed, 0xb9, 0xda, 0x5e, 0x15, 0x46, 0x57, 0xa7, 0x8d, 0x9d, 0x84,
    0x90, 0xd8, 0xab, 0x00, 0x8c, 0xbc, 0xd3, 0x0a, 0xf7, 0xe4, 0x58, 0x05, 0xb8, 0xb3, 0x45, 0x06,
    0xd0, 0x2c, 0x1e, 0x8f, 0xca, 0x3f, 0x0f, 0x02, 0xc1, 0xaf, 0xbd, 0x03, 0x01, 0x13, 0x8a, 0x6b,
    0x3a, 0x91, 0x11, 0x41, 0x4f, 0x67, 0xdc, 0xea, 0x97, 0xf2, 0xcf, 0xce, 0xf0, 0xb4, 0xe6, 0x73,
    0x96, 0xac, 0x74, 0x22, 0xe7, 0xad, 0x35, 0x85, 0xe2, 0xf9, 0x37, 0xe8, 0x1c, 0x75, 0xdf, 0x6e,
    0x47, 0xf1, 0x1a, 0x71, 0x1d, 0x29, 0xc5, 0x89, 0x6f, 0xb7, 0x62, 0x0e, 0xaa, 0x18, 0xbe, 0x1b,
    0xfc, 0x56, 0x3e, 0x4b, 0xc6, 0xd2, 0x79, 0x20, 0x9a, 0xdb, 0xc0, 0xfe, 0x78, 0xcd, 0x5a, 0xf4,
    0x1f, 0xdd, 0xa8, 0x33, 0x88, 0x07, 0xc7, 0x31, 0xb1, 0x12, 0x10, 0x59, 0x27, 0x80, 0xec, 0x5f,
    0x60, 0x51, 0x7f, 0xa9, 0x19, 0xb5, 0x4a, 0x0d, 0x2d, 0xe5, 0x7a, 0x9f, 0x93, 0xc9, 0x9c, 0xef,
    0xa0, 0xe0, 0x3b, 0x4d, 0xae, 0x2a, 0xf5, 0xb0, 0xc8, 0xeb, 0xbb, 0x3c, 0x83, 0x53, 0x99, 0x61,
    0x17, 0x2b, 0x04, 0x7e, 0xba, 0x77, 0xd6, 0x26, 0xe1, 0x69, 0x14, 0x63, 0x55, 0x21, 0x0c, 0x7d 
};
static const uint8 Rcon[10] = {0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80, 0x1B, 0x36};
static uint8 ExpandsionKey[11][16];
static void GetState(uint8* plaintext, uint8* state, uint8 mode)
{
    uint8 uint8a_row;
    uint8 uint8a_wordCnt;
    uint8 uint8a_elementCnt = 0U;

    /* Check mode get state or plain text */
    if (mode == 1U) {
        for (uint8a_row = 0U; uint8a_row < 4U; uint8a_row++) {
            for (uint8a_wordCnt = 0U; uint8a_wordCnt < 4U; uint8a_wordCnt++) {
                /* rearrange the position of each element in plaintext*/
                *(state + uint8a_row + (uint8a_wordCnt << 2U)) = *(plaintext + uint8a_elementCnt);
                uint8a_elementCnt += 1U;
            }
        }
    } else {
        for (uint8a_wordCnt = 0U; uint8a_wordCnt < 4U; uint8a_wordCnt++) {
            for (uint8a_row = 0U; uint8a_row < 4U; uint8a_row++) {
                /* revert to position of the original plain text  */
                *(plaintext + uint8a_elementCnt) = *(state + uint8a_wordCnt + (uint8a_row << 2U));
                uint8a_elementCnt += 1U;
            }
        }
    }

    return;
}
static void RotWord(uint8* word)
{
    uint8 uint8a_wordTmp;
    uint8 uint8a_elementCnt;

    uint8a_wordTmp = *(word);

    /* Rotate the position of byte in word */
    for (uint8a_elementCnt = 0U; uint8a_elementCnt < 3U; uint8a_elementCnt++) {
        *(word + uint8a_elementCnt) = *(word + uint8a_elementCnt + 1U);
    }

    *(word + 3U) = uint8a_wordTmp;

    return;
}
static void KeyExpansion128(const uint8* key)
{
    uint8 uint8a_keyCnt;
    uint8 uint8a_roundCnt;
    uint8 uint8a_elementCnt;
    uint8 uint8a_wordGKey[4];

    for (uint8a_keyCnt = 0U; uint8a_keyCnt < 16U; uint8a_keyCnt++) {
        /* Get 16 bytes of the original key to expansion key */
        ExpandsionKey[0][uint8a_keyCnt] = *(key + uint8a_keyCnt);
    }

    for (uint8a_roundCnt = 1U; uint8a_roundCnt < 11U; uint8a_roundCnt++) {

        /* Get the fourth word in state */
        uint8a_wordGKey[3] = ExpandsionKey[uint8a_roundCnt - 1U][15];
        uint8a_wordGKey[2] = ExpandsionKey[uint8a_roundCnt - 1U][14];
        uint8a_wordGKey[1] = ExpandsionKey[uint8a_roundCnt - 1U][13];
        uint8a_wordGKey[0] = ExpandsionKey[uint8a_roundCnt - 1U][12];

        /* one-byte circular left shift on a word */
        RotWord(uint8a_wordGKey);
        /* a byte substitution on each byte of its input word */
        SubByte(uint8a_wordGKey, key, 0U);

        /* Update all bytes in state from the first word */
        ExpandsionKey[uint8a_roundCnt][0] = uint8a_wordGKey[0] ^ ExpandsionKey[uint8a_roundCnt - 1U][0] ^ Rcon[uint8a_roundCnt - 1U];
        ExpandsionKey[uint8a_roundCnt][1] = uint8a_wordGKey[1] ^ ExpandsionKey[uint8a_roundCnt - 1U][1];
        ExpandsionKey[uint8a_roundCnt][2] = uint8a_wordGKey[2] ^ ExpandsionKey[uint8a_roundCnt - 1U][2];
        ExpandsionKey[uint8a_roundCnt][3] = uint8a_wordGKey[3] ^ ExpandsionKey[uint8a_roundCnt - 1U][3];

        /* Update all bytes in state from the second word */
        for (uint8a_elementCnt = 4U; uint8a_elementCnt < 16U; uint8a_elementCnt++) {
            ExpandsionKey[uint8a_roundCnt][uint8a_elementCnt] = ExpandsionKey[uint8a_roundCnt][uint8a_elementCnt - 4U] ^ ExpandsionKey[uint8a_roundCnt - 1U][uint8a_elementCnt];
        }
    }

    return;
}
static void AddRoundKey(uint8* state, const uint8* key, uint8 mode)
{
    uint8 uint8a_elementCnt;
    uint8 uint8a_wordCnt;
    uint8 uint8a_row;

    uint8a_elementCnt = 0U;

    /* Trace all bytes in state */
    for (uint8a_wordCnt = 0U; uint8a_wordCnt < 4U; uint8a_wordCnt++) {
        for (uint8a_row = 0U; uint8a_row < 4U; uint8a_row++) {
            /* XOR each byte between state and key */
            *(state + (uint8a_row << 2U) + uint8a_wordCnt) ^= *(key + uint8a_elementCnt);
            uint8a_elementCnt += 1U;
        }
    }

    return;
}
static void ShiftRows(uint8* state, const uint8* key, uint8 mode)
{
    uint8 uint8a_row;
    uint8 uint8a_col;
    uint8 uint8a_elementCnt;
    uint8 uint8a_stateTemp;

    for (uint8a_row = 0U; uint8a_row < 4U; uint8a_row++) {
        for (uint8a_col = 0U; uint8a_col < uint8a_row; uint8a_col++) {
            /* Get byte of the first word */
            uint8a_stateTemp = *(state + (uint8a_row << 2U));
            for (uint8a_elementCnt = 0U; uint8a_elementCnt < 3U; uint8a_elementCnt++) {
                state[uint8a_elementCnt + (uint8a_row << 2U)] = state[uint8a_elementCnt + 1U + (uint8a_row << 2U)];
            }
            /* Update byte of the fourth word */
             *(state + 3U + (uint8a_row << 2U)) = uint8a_stateTemp;
        }
    }

    return;
}
static void SubByte(uint8* state, const uint8* key, uint8 mode)
{
    uint8 uint8a_modeStatus;
    uint8 uint8a_elementCnt;

    /* Check the number of byte need to substitute */
    if (mode == 1U) {
        uint8a_modeStatus = 16U;
    } else {
        uint8a_modeStatus = 4U;
    }

    for (uint8a_elementCnt = 0U; uint8a_elementCnt < uint8a_modeStatus; uint8a_elementCnt++) {
        /* Update state according to S_Box */
        *(state + uint8a_elementCnt) = S_Box[*(state + uint8a_elementCnt)];
    }

    return;
}
static void SubMixcolumn(uint8* SubState) {
    uint8 uint8a_mixcol[4];
    uint8 uint8a_elementCnt[4];
    uint8 uint8a_row;
    uint8 uint8a_highBit;

    /* Check and get all byte in word */
    for (uint8a_row = 0U; uint8a_row < 4U; uint8a_row++) {
        uint8a_mixcol[uint8a_row] = SubState[uint8a_row];
        uint8a_highBit = (uint8)(SubState[uint8a_row] >> 7U);
        uint8a_elementCnt[uint8a_row] = SubState[uint8a_row] << 1U;
        uint8a_elementCnt[uint8a_row] ^= uint8a_highBit * 0x1BU;
    }

    SubState[0] = uint8a_elementCnt[0] ^ uint8a_mixcol[3] ^ uint8a_mixcol[2] ^ uint8a_elementCnt[1] ^ uint8a_mixcol[1];
    SubState[1] = uint8a_elementCnt[1] ^ uint8a_mixcol[0] ^ uint8a_mixcol[3] ^ uint8a_elementCnt[2] ^ uint8a_mixcol[2];
    SubState[2] = uint8a_elementCnt[2] ^ uint8a_mixcol[1] ^ uint8a_mixcol[0] ^ uint8a_elementCnt[3] ^ uint8a_mixcol[3];
    SubState[3] = uint8a_elementCnt[3] ^ uint8a_mixcol[2] ^ uint8a_mixcol[1] ^ uint8a_elementCnt[0] ^ uint8a_mixcol[0];

    return;
}
static void Mixcolumns(uint8* state, const uint8* key, uint8 mode)
{
    uint8 uint8a_wordCnt;
    uint8 uint8a_row;
    uint8 uint8a_elementTmp[4];

    for (uint8a_wordCnt = 0U; uint8a_wordCnt < 4U; uint8a_wordCnt++) {
        /* Get each word in state */
        for (uint8a_row = 0U; uint8a_row < 4U; uint8a_row++) {
            uint8a_elementTmp[uint8a_row] = *(state + (uint8a_row << 2U) + uint8a_wordCnt);
        }

        /* Excute mix column */
        SubMixcolumn(uint8a_elementTmp);

        /* Update state */
        for (uint8a_row = 0U; uint8a_row < 4U; uint8a_row++) {
            *(state + (uint8a_row << 2U) + uint8a_wordCnt) = uint8a_elementTmp[uint8a_row];
        }
    }

    return;
}
static void aes128_encrypt_sub(uint8* plaintext)
{
    uint8 uint8a_state[16];
    uint8 uint8a_roundCnt;
    uint8 uint8a_stepCnt;

    /* Get state from plain text */
    GetState(plaintext, uint8a_state, 1U);
    /* Add round key */
    EncryptionFuncTbl[0][3](uint8a_state, ExpandsionKey[0], 1U);

    for (uint8a_roundCnt = 1U; uint8a_roundCnt < 11U; uint8a_roundCnt++) {
        for (uint8a_stepCnt = 0U; uint8a_stepCnt < 4U; uint8a_stepCnt++) {
            /* Check Round being executed */
            if (uint8a_roundCnt < 10U) {
                /* SubByte -> ShiftRowns -> Mixcolumns -> AddRoundKey */
                EncryptionFuncTbl[0][uint8a_stepCnt](uint8a_state, ExpandsionKey[uint8a_roundCnt], 1U);
            } else {
                /* Check NULL */
                if (NULL_PTR != EncryptionFuncTbl[1][uint8a_stepCnt]) {
                    /* SubByte -> ShiftRowns -> AddRoundKey */
                    EncryptionFuncTbl[1][uint8a_stepCnt](uint8a_state, ExpandsionKey[uint8a_roundCnt], 1U);
                } else {
                    /* Do nothing */
                }
            }
        }
    }

    /* Get plaintext from state */
    GetState(plaintext, uint8a_state, 0U);

    return;
}
void aes128_encrypt(uint8* state, const uint8* key)
{
    /* Expand key */
    KeyExpansion128(key);

    /* Excute encryption */
    aes128_encrypt_sub(state);

    return;
}

static uint8 xtime(uint8 x)
{
    return ((x<<1U) ^ ((x>>7U) * 0x1BU));
}

static uint8 Multiply(uint8 x, uint8 y)
{
    return (((y & 1U) * x) ^
    ((y>>1U & 1U) * xtime(x)) ^
    ((y>>2U & 1U) * xtime(xtime(x))) ^
    ((y>>3U & 1U) * xtime(xtime(xtime(x)))) ^
    ((y>>4U & 1U) * xtime(xtime(xtime(xtime(x)))))); /* this last call to xtime() can be omitted */
}

static void InvShiftRows(uint8* state)
{
    uint8 temp;
    /* Rotate first row 1 columns to right */
    temp = state[7];
    state[7] = state[6];
    state[6] = state[5];
    state[5] = state[4];
    state[4] = temp;

    /* Rotate second row 2 columns to right */
    temp = state[11];
    state[11] = state[9];
    state[9] = temp;

    temp = state[10];
    state[10] = state[8];
    state[8] = temp;

    /* Rotate third row 3 columns to right */
    temp = state[15];
    state[15] = state[12];
    state[12] = state[13];
    state[13] = state[14];
    state[14] = temp;

    return;
}

static void InvSubBytes(uint8* state)
{
    uint8 uint8a_idx;

    for (uint8a_idx = 0U; uint8a_idx < 16U; ++uint8a_idx) {
        state[uint8a_idx] = getSBoxInvert(state[uint8a_idx]);
    }

    return;
}

static void InvMixColumns(uint8* state)
{
    uint8 output[16];

    output[0] = state[0];
    output[1] = state[1];
    output[2] = state[2];
    output[3] = state[3];
    output[4] = state[4];
    output[5] = state[5];
    output[6] = state[6];
    output[7] = state[7];
    output[8] = state[8];
    output[9] = state[9];
    output[10] = state[10];
    output[11] = state[11];
    output[12] = state[12];
    output[13] = state[13];
    output[14] = state[14];
    output[15] = state[15];

    state[0]  = Multiply(output[0], 0x0e) ^ Multiply(output[4], 0x0b) ^ Multiply(output[8], 0x0d) ^ Multiply(output[12], 0x09);
    state[4]  = Multiply(output[0], 0x09) ^ Multiply(output[4], 0x0e) ^ Multiply(output[8], 0x0b) ^ Multiply(output[12], 0x0d);
    state[8]  = Multiply(output[0], 0x0d) ^ Multiply(output[4], 0x09) ^ Multiply(output[8], 0x0e) ^ Multiply(output[12], 0x0b);
    state[12] = Multiply(output[0], 0x0b) ^ Multiply(output[4], 0x0d) ^ Multiply(output[8], 0x09) ^ Multiply(output[12], 0x0e);

    state[1]  = Multiply(output[1], 0x0e) ^ Multiply(output[5], 0x0b) ^ Multiply(output[9], 0x0d) ^ Multiply(output[13], 0x09);
    state[5]  = Multiply(output[1], 0x09) ^ Multiply(output[5], 0x0e) ^ Multiply(output[9], 0x0b) ^ Multiply(output[13], 0x0d);
    state[9]  = Multiply(output[1], 0x0d) ^ Multiply(output[5], 0x09) ^ Multiply(output[9], 0x0e) ^ Multiply(output[13], 0x0b);
    state[13] = Multiply(output[1], 0x0b) ^ Multiply(output[5], 0x0d) ^ Multiply(output[9], 0x09) ^ Multiply(output[13], 0x0e);

    state[2]  = Multiply(output[2], 0x0e) ^ Multiply(output[6], 0x0b) ^ Multiply(output[10], 0x0d) ^ Multiply(output[14], 0x09);
    state[6]  = Multiply(output[2], 0x09) ^ Multiply(output[6], 0x0e) ^ Multiply(output[10], 0x0b) ^ Multiply(output[14], 0x0d);
    state[10] = Multiply(output[2], 0x0d) ^ Multiply(output[6], 0x09) ^ Multiply(output[10], 0x0e) ^ Multiply(output[14], 0x0b);
    state[14] = Multiply(output[2], 0x0b) ^ Multiply(output[6], 0x0d) ^ Multiply(output[10], 0x09) ^ Multiply(output[14], 0x0e);

    state[3]  = Multiply(output[3], 0x0e) ^ Multiply(output[7], 0x0b) ^ Multiply(output[11], 0x0d) ^ Multiply(output[15], 0x09);
    state[7]  = Multiply(output[3], 0x09) ^ Multiply(output[7], 0x0e) ^ Multiply(output[11], 0x0b) ^ Multiply(output[15], 0x0d);
    state[11] = Multiply(output[3], 0x0d) ^ Multiply(output[7], 0x09) ^ Multiply(output[11], 0x0e) ^ Multiply(output[15], 0x0b);
    state[15] = Multiply(output[3], 0x0b) ^ Multiply(output[7], 0x0d) ^ Multiply(output[11], 0x09) ^ Multiply(output[15], 0x0e);

    return;
}

static void aes128_decrypt_sub(uint8* state)
{
    uint8 uint8a_round;
    /* Add the First round key to the state before starting the rounds. */
    AddRoundKey(state, ExpandsionKey[10], 1U);
    /* The loop to calculate AddRoundKey from 9th to 1st   */
    for (uint8a_round = 9U; 0U < uint8a_round ; --uint8a_round) {
        InvShiftRows(state);
        InvSubBytes(state);
        AddRoundKey(state, ExpandsionKey[uint8a_round], 1U);
        InvMixColumns(state);
    }
    /*Add the final round key to the state */
    InvShiftRows(state);
    InvSubBytes(state);
    AddRoundKey(state, ExpandsionKey[0], 1U);

    return;
}

void aes128_decrypt(uint8* cipher, const uint8* key)
{
    uint8 invCipher[16];
    KeyExpansion128(key);

    /* Get state from cipher text */
    GetState(cipher, invCipher, 1U);
    aes128_decrypt_sub(invCipher);

    /* InvGet state */
    GetState(cipher, invCipher, 0U);
    
    return;
}