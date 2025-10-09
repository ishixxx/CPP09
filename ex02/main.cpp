#include "PmergeMe.hpp"

int main(int argc, char **argv) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <numbers...>" << std::endl;
        return 1;
    }

    PmergeMe pmergeMe;

    for (int i = 1; i < argc; ++i) {
        char *end;
        long num = std::strtol(argv[i], &end, 10);
        if (*end != '\0' || num < 0 || num > INT_MAX) {
            std::cerr << "Error: Invalid number '" << argv[i] << "'" << std::endl;
            return 1;
        }
        pmergeMe.addNumber(static_cast<int>(num));
    }

    clock_t start = clock();
    pmergeMe.sort();
    clock_t end = clock();

    std::cout << std::endl;
    //number * 10^-6 so if 5e-06 seconds = 5 * 10^6 = 0,000005
    double elapsed = double(end - start) / CLOCKS_PER_SEC;
    std::cout << "Time taken to sort: " << std::fixed << std::setprecision(6) << elapsed << " seconds" << std::endl;

    return 0;
}