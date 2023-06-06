#include <iostream>
#include <stdexcept>

struct ExtendedEuclideanResult {
    int gcd;
    int x;
    int y;
};

ExtendedEuclideanResult extended_euclidean_algorithm(int a, int b) {
    if (b == 0) {
        ExtendedEuclideanResult result;
        result.gcd = a;
        result.x = 1;
        result.y = 0;
        return result;
    }

    ExtendedEuclideanResult prev_result = extended_euclidean_algorithm(b, a % b);
    ExtendedEuclideanResult result;
    result.gcd = prev_result.gcd;
    result.x = prev_result.y;
    result.y = prev_result.x - (a / b) * prev_result.y;

    return result;
}

int find_modular_inverse(int a, int m) {
    ExtendedEuclideanResult result = extended_euclidean_algorithm(a, m);
    if (result.gcd != 1) {
        throw std::runtime_error("Inverse does not exist.");
    }

    int inverse = (result.x % m + m) % m;
    return inverse;
}

int main() {
    int a, m;

    std::cout << "Enter a number to find inverse: ";
    std::cin >> a;
    std::cout << "Enter the number whose modulus is to be found: ";
    std::cin >> m;

    int inverse;
    try {
        inverse = find_modular_inverse(a, m);
        std::cout << "Modular inverse of " << a << " mod " << m << " is: " << inverse << std::endl;
    } catch (const std::runtime_error& e) {
        std::cout << e.what() << std::endl;
    }

    return 0;
}
