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
    std::vector<int> sortedVector;
    clock_t start = clock();

    sortedVector = fordJohnsonSort(numbersVector);

    clock_t end = clock();
    double vectorSortTime = double(end - start) / CLOCKS_PER_SEC;

    // Sort using std::deque
    std::deque<int> sortedDeque;
    start = clock();

    sortedDeque = fordJohnsonSort(numbersDeque);

    end = clock();
    double dequeSortTime = double(end - start) / CLOCKS_PER_SEC;

//------------------------------ Print --------------------------------------------//
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

//------------------------------ Algorithm -----------------------------//
//------------------- Helper Functions Implementation ------------------//

// Simple insertion sort for small segments
template <typename Container>
void insertionSort(Container &container, int left, int right) {
    for (int i = left + 1; i <= right; ++i) {
        int key = container[i];
        int j = i - 1;
        while (j >= left && container[j] > key) {
            container[j + 1] = container[j];
            --j;
        }
        container[j + 1] = key;
    }
}

// Binary search to find the index where to insert 'item' in a sorted container
template <typename Container>
int binarySearch(const Container &container, int item, int left, int right) {
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (container[mid] == item)
            return mid;
        else if (container[mid] < item)
            left = mid + 1;
        else
            right = mid - 1;
    }
    return left;
}

// Insert value into sorted container at the correct position
template <typename Container>
void binaryInsert(Container &container, int value) {
    int pos = binarySearch(container, value, 0, container.size() - 1);
    container.insert(container.begin() + pos, value);
}

// Ford-Johnson (merge-insert) sort implementation
template <typename Container>
Container fordJohnsonSort(Container &input) {
    int n = input.size();
    if (n <= 1)
        return input;

    // Step 1: Pair up elements and split into A (max) and B (min)
    Container A, B;
    int i = 0;
    for (; i + 1 < n; i += 2) {
        if (input[i] > input[i + 1]) {
            A.push_back(input[i]);
            B.push_back(input[i + 1]);
        } else {
            A.push_back(input[i + 1]);
            B.push_back(input[i]);
        }
    }
    // If odd, keep last element for later
    int oddElement = -1;
    bool hasOdd = (n % 2 != 0);
    if (hasOdd) {
        oddElement = input[n - 1];
    }

    // Step 2: Sort A recursively (or with insertionSort for small size)
    if (A.size() <= 16) {
        insertionSort(A, 0, A.size() - 1);
    } else {
        A = fordJohnsonSort(A);
    }

    // Step 3: Insert B elements into A using Jacobsthal order
    std::vector<int> jacobOrder = generateJacobsthalSequence(B);
    std::vector<bool> inserted(B.size(), false);
    // Insert B[jacobsthal[k] - 1] if in range and not already inserted
    for (size_t k = 1; k < jacobOrder.size(); ++k) {
        int idx = jacobOrder[k] - 1;
        if (idx >= 0 && idx < (int)B.size() && !inserted[idx]) {
            binaryInsert(A, B[idx]);
            inserted[idx] = true;
        }
    }
    // Insert remaining B elements in order
    for (size_t j = 0; j < B.size(); ++j) {
        if (!inserted[j]) {
            binaryInsert(A, B[j]);
            inserted[j] = true;
        }
    }
    // Step 4: Insert odd element if needed
    if (hasOdd) {
        binaryInsert(A, oddElement);
    }
    return A;
}

// Explicit instantiation for std::vector<int> and std::deque<int>
template std::vector<int> fordJohnsonSort(std::vector<int> &input);
template std::deque<int> fordJohnsonSort(std::deque<int> &input);