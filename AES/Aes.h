#ifndef AES_H
#define AES_H

#include <iostream>
#include <vector>
#include <string>

using byte = unsigned char;
using word = unsigned int;

class Aes
{
    int Nk{},   //  key length in 32-bit words. Depending on the key length, Nk = 4, 6, 8.
        Nr{},   //  the number of rounds of encryption. Depending on the key length, Nr = 10, 12 or 14.
        Nb{};   //  the number of columns (32-bit words) that make up State.
    std::vector<word> ExpandedKey{};
    static const byte SBox[256];
    static const byte InvSBox[256];
    static const byte Rcon[10];
    static const byte MixColMatrix[4][4];
    static const byte InvMixColMatrix[4][4];
    byte state[4][4];
    std::string cipherText{};
    std::string decryptText{};

    byte Mul(byte a, byte b);

    void SubBytes();
    void ShiftRows();
    void MixColumns();

    void InvSubBytes();
    void InvShiftRows();
    void InvMixColumns();

    void AddRoundKey(int round);

    word SubWord(word sw);
    word RotWord(word rw);
    void KeyExpansion(std::string& key);
    
    std::string ToStringState();

public:
    enum KeySize{
        AES128 = 128,
        AES192 = 192,
        AES256 = 256
    };
    Aes(std::string key, int bitSize);
    ~Aes();
    std::string GetCipherText();
    std::string GetDecryptedText();
    void Encrypt(std::string plainText);
    void Decrypt(std::string cipherText);

};

#endif