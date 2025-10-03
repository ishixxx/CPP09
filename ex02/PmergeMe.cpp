#include "PmergeMe.hpp"

//------------------- Constructors & Destructors ------------------//

PmergeMe::PmergeMe() {}

PmergeMe::PmergeMe(const PmergeMe &other) {
    numbersVector = other.numbersVector;
    numbersDeque = other.numbersDeque;
}

PmergeMe &PmergeMe::operator=(const PmergeMe &other) {
    if (this != &other) {
        numbersVector = other.numbersVector;
        numbersDeque = other.numbersDeque;
    }
    return *this;
}

PmergeMe::~PmergeMe() {}

//------------------- Utility Functions ------------------//

void PmergeMe::addNumber(int num) {
    if (num < 0) {
        throw std::invalid_argument("Negative numbers are not allowed");
    }
    numbersVector.push_back(num);
    numbersDeque.push_back(num);
}

void PmergeMe::sort() {

    // Sort using std::vector
    std::vector<int> sortedVector = numbersVector;
    clock_t start = clock();
    
    //fordJohnsonSort(sortedVector);
    std::sort(sortedVector.begin(), sortedVector.end());

    clock_t end = clock();
    double vectorSortTime = double(end - start) / CLOCKS_PER_SEC;

    // Sort using std::deque
    std::deque<int> sortedDeque = numbersDeque;
    start = clock();

    //fordJohnsonSort(sortedDeque);
    std::sort(sortedDeque.begin(), sortedDeque.end());

    end = clock();
    double dequeSortTime = double(end - start) / CLOCKS_PER_SEC;

//------------------------------Print--------------------------------------------//
    std::cout << "Before: ";
    for (size_t i = 0; i < numbersVector.size(); ++i) {
        std::cout << numbersVector[i] << " ";
    }
    std::cout << std::endl;

    std::cout << "After: ";
    for (size_t i = 0; i < sortedVector.size(); ++i) {
        std::cout << sortedVector[i] << " ";
    }
    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << "Time to process a range of " <<  numbersVector.size() << " elements with std::vector : " 
              << vectorSortTime << " seconds" << std::endl;
    std::cout << "Time to process a range of " <<  numbersDeque.size() << " elements with std::deque : " 
              << dequeSortTime << " seconds" << std::endl;
}
