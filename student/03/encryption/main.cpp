#include <iostream>
#include <string>
#include <cctype>

char encrypt(std::string encryption, char c) {
    std::string alphabet = "abcdefghijklmnopqrstuvwxyz";
    std::string::size_type encrypted = alphabet.find(c);
    return encryption[encrypted];
}

int main()
{
    std::cout << "Enter the encryption key: ";
    std::string key = "";
    std::getline(std::cin, key);

    if (key.length() != 26) {
        std::cout << "Error! The encryption key must contain 26 characters." << std::endl;
        return EXIT_FAILURE;
    }

    for (const char& c : key) {
        if (isupper(c)) {
           std::cout << "Error! The encryption key must contain only lower case characters." << std::endl;
           return EXIT_FAILURE;
        }
    }

    for (char a = 'a'; a < 'z'; a++) {
        if (key.find(a) == std::string::npos) {
            std::cout << "Error! The encryption key must contain all alphabets a-z." << std::endl;
            return EXIT_FAILURE;
        }
    }

    std::cout << "Enter the text to be encrypted: ";
    std::string msg;
    getline(std::cin, msg);

    std::string encrypted = "";

    for (char& c : msg) {
        encrypted += encrypt(key, c);
    }

    std::cout << "Encrypted text: " << encrypted << std::endl;

    return 0;
}
