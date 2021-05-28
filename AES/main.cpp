#include "Aes.h"

int main(){
    std::string cipherKey{};
    std::string plainText{};

    Aes obj(cipherKey, Aes::KeySize::AES128);

    std::cout << "Enter key text. \n";
    std::cin >> cipherKey;

    std::cout << "Enter text to encrypt. \n";
    std::cin >> plainText;

    obj.Encrypt(plainText);

    std::cout << "Encrypted Text \n" << "----------------- \n";
	std::cout << obj.GetCipherText() << std::endl << std::endl;

    obj.Decrypt( obj.GetCipherText() )  ;
	std::cout << "Decrypted Text \n" << "----------------- \n";
	std::cout << obj.GetDecryptedText() << std::endl << std::endl;
}