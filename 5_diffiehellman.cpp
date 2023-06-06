#include <iostream>
#include <vector>
#include <cmath>

int prime_checker(int p) {
    if (p < 1) {
        return -1;
    } else if (p > 1) {
        if (p == 2) {
            return 1;
        }
        for (int i = 2; i < p; ++i) {
            if (p % i == 0) {
                return -1;
            }
        }
        return 1;
    }
    return -1;
}

int primitive_check(int g, int p, std::vector<int>& L) {
    for (int i = 1; i < p; ++i) {
        int result = g;
        for (int j = 1; j < i; ++j) {
            result = (result * g) % p;
        }
        L.push_back(result);
    }
    for (int i = 1; i < p; ++i) {
        if (std::count(L.begin(), L.end(), i) > 1) {
            L.clear();
            return -1;
        }
    }
    return 1;
}

int main() {
    std::vector<int> L;
    int P;
    while (true) {
        std::cout << "Enter P: ";
        std::cin >> P;
        if (prime_checker(P) == -1) {
            std::cout << "Number Is Not Prime, Please Enter Again!" << std::endl;
            continue;
        }
        break;
    }

    int G;
    while (true) {
        std::cout << "Enter The Primitive Root Of " << P << ": ";
        std::cin >> G;
        if (primitive_check(G, P, L) == -1) {
            std::cout << "Number Is Not A Primitive Root Of " << P << ", Please Try Again!" << std::endl;
            continue;
        }
        break;
    }

    int x1, x2;
    while (true) {
        std::cout << "Enter The Private Key Of User 1: ";
        std::cin >> x1;
        std::cout << "Enter The Private Key Of User 2: ";
        std::cin >> x2;
        if (x1 >= P || x2 >= P) {
            std::cout << "Private Key Of Both The Users Should Be Less Than " << P << "!" << std::endl;
            continue;
        }
        break;
    }

    int y1 = 1;
    int y2 = 1;
    for (int i = 0; i < x1; ++i) {
        y1 = (y1 * G) % P;
    }
    for (int i = 0; i < x2; ++i) {
        y2 = (y2 * G) % P;
    }

    int k1 = 1;
    int k2 = 1;
    for (int i = 0; i < x1; ++i) {
        k1 = (k1 * y2) % P;
    }
    for (int i = 0; i < x2; ++i) {
        k2 = (k2 * y1) % P;
    }

    std::cout << "\nSecret Key For User 1 Is " << k1 << std::endl;
    std::cout << "Secret Key For User 2 Is " << k2 << std::endl;

    if (k1 == k2) {
        std::cout << "Keys Have Been Exchanged Successfully" << std::endl;
    } else {
        std::cout << "Keys Have Not Been Exchanged Successfully" << std::endl;
    }

    return 0;
}
