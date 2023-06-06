#include <iostream>
#include <string>
#include <random>

int custom_hash(const std::string& message) {
    std::hash<std::string> hash_fn;  // Instantiate the hash function object
    std::size_t hash_value = hash_fn(message);  // Compute the hash value
    return static_cast<int>(hash_value & 0xFFFF);  // Extract the lower 16 bits
}

int main() {
    std::string message;

    std::cout << "Enter the message: ";
    std::getline(std::cin, message);

    int hash_value = custom_hash(message);

    std::cout << "Original Message: " << message << std::endl;
    std::cout << "Hash value: " << hash_value << std::endl;

    // Simulate receiver computing the hash again
    std::string received_message;
    std::cout << "Enter the received message: ";
    std::getline(std::cin, received_message);

    int received_hash_value = custom_hash(received_message);

    std::cout << "Received Message: " << received_message << std::endl;
    std::cout << "Received Hash value: " << received_hash_value << std::endl;

    // Verify integrity
    if (received_hash_value == hash_value) {
        std::cout << "Integrity: The message has not been modified." << std::endl;
    } else {
        std::cout << "Integrity: The message has been modified." << std::endl;
    }

    return 0;
}
