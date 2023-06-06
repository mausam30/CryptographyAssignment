#include <iostream>
#include <string>
#include <cctype>

std::string affine_encrypt(const std::string& plain_text, int a, int b) {
    std::string alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    std::string encrypted_text = "";

    for (size_t i = 0; i < plain_text.length(); i++) {
        char ch = plain_text[i];
        if (std::isalpha(ch)) {
            char uppercase_ch = std::toupper(ch);
            int index = alphabet.find(uppercase_ch);
            int encrypted_index = (a * index + b) % 26;
            char encrypted_char = alphabet[encrypted_index];
            encrypted_text += encrypted_char;
        } else {
            encrypted_text += ch;
        }
    }

    return encrypted_text;
}

std::string affine_decrypt(const std::string& cipher_text, int a, int b) {
    std::string alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    std::string decrypted_text = "";
    int a_inverse = 0;

    for (int i = 0; i < 26; i++) {
        if ((a * i) % 26 == 1) {
            a_inverse = i;
            break;
        }
    }

    for (size_t i = 0; i < cipher_text.length(); i++) {
        char ch = cipher_text[i];
        if (std::isalpha(ch)) {
            char uppercase_ch = std::toupper(ch);
            int index = alphabet.find(uppercase_ch);
            int decrypted_index = (a_inverse * (index - b + 26)) % 26;
            char decrypted_char = alphabet[decrypted_index];
            decrypted_text += decrypted_char;
        } else {
            decrypted_text += ch;
        }
    }

    return decrypted_text;
}

int main() {
    std::string plain_text;
    int a, b;

    std::cout << "Enter the plain text: ";
    std::getline(std::cin, plain_text);
    std::cout << "Enter the multiplicative value: ";
    std::cin >> a;
    std::cout << "Enter the additive value: ";
    std::cin >> b;
    std::cin.ignore(); // Ignore the newline character after reading 'b'.

    std::string encrypted_text = affine_encrypt(plain_text, a, b);
    std::cout << "Encrypted text: " << encrypted_text << std::endl;

    std::string decrypted_text = affine_decrypt(encrypted_text, a, b);
    std::cout << "Decrypted text: " << decrypted_text << std::endl;

    return 0;
}
