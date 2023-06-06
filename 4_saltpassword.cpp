#include <iostream>
#include <fstream>
#include <string>
#include <random>
#include <algorithm>
#include <functional>
#include <cctype>
#include <unordered_map>


std::string generate_salt(std::size_t length = 8) {
    std::string salt_characters = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!@#$%^&*";
    std::random_device rd;
    std::mt19937 generator(rd());
    std::shuffle(salt_characters.begin(), salt_characters.end(), generator);
    salt_characters.resize(length);
    return salt_characters;
}


std::string hash_password(const std::string& password, const std::string& salt) {
    std::string salted_password = password + salt;
    std::hash<std::string> hash_fn;
    std::size_t hashed_password = hash_fn(salted_password);
    return std::to_string(hashed_password);
}


bool check_password(const std::string& password, const std::string& hashed_password, const std::string& salt) {
    std::string salted_password = password + salt;
    std::hash<std::string> hash_fn;
    std::size_t hashed_input_password = hash_fn(salted_password);
    return hashed_password == std::to_string(hashed_input_password);
}

int main() {
    std::size_t num_users;
    std::cout << "Enter the number of users: ";
    std::cin >> num_users;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    std::ofstream file("hashed_passwords.txt");
    if (!file) {
        std::cerr << "Failed to open the file." << std::endl;
        return 1;
    }

    std::unordered_map<std::string, std::string> password_file;
    for (std::size_t i = 1; i <= num_users; ++i) {
        std::string username, password;
        std::cout << "Enter the username for User" << i << ": ";
        std::getline(std::cin, username);
        std::cout << "Enter the password for User" << i << ": ";
        std::getline(std::cin, password);
        password_file[username] = password;
    }

    std::unordered_map<std::string, std::pair<std::string, std::string> > hashed_password_file;
    for (std::pair<const std::string, std::string>& pair : password_file) {
        const std::string& username = pair.first;
        std::string& password = pair.second;
        const std::string salt = generate_salt();
        const std::string hashed_password = hash_password(password, salt);
        hashed_password_file.insert(std::make_pair(username, std::make_pair(hashed_password, salt)));
        file << username << ':' << hashed_password << ':' << salt << '\n';
    }
    file.close();

    std::string input_username, input_password;
    std::cout << "Enter username: ";
    std::getline(std::cin, input_username);
    std::cout << "Enter password: ";
    std::getline(std::cin, input_password);

    std::ifstream hashed_passwords_file("hashed_passwords.txt");
    if (!hashed_passwords_file) {
        std::cerr << "Failed to open the file." << std::endl;
        return 1;
    }

    std::string line;
    bool login_successful = false;
    while (std::getline(hashed_passwords_file, line)) {
        std::size_t delimiter_pos_1 = line.find(':');
        std::size_t delimiter_pos_2 = line.find(':', delimiter_pos_1 + 1);
        if (delimiter_pos_1 != std::string::npos && delimiter_pos_2 != std::string::npos) {
            std::string stored_username = line.substr(0, delimiter_pos_1);
            std::string stored_hashed_password = line.substr(delimiter_pos_1 + 1, delimiter_pos_2 - delimiter_pos_1 - 1);
            std::string stored_salt = line.substr(delimiter_pos_2 + 1);
            if (stored_username == input_username &&
                check_password(input_password, stored_hashed_password, stored_salt)) {
                login_successful = true;
                break;
            }
        }
    }
    hashed_passwords_file.close();

    if (login_successful) {
        std::cout << "Login successful." << std::endl;
    } else {
        std::cout << "Login failed. Invalid username or password." << std::endl;
    }

    return 0;
}
