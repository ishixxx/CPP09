#ifndef PMERGEME_HPP
# define PMERGEME_HPP

#include <iostream>
#include <vector>
#include <deque>
#include <algorithm>
#include <stdexcept>
#include <ctime>
#include <iomanip>
#include <sstream>
#include <cstdlib>
#include <climits>
#include <cstring>
#include <cctype>
#include <cmath>


class PmergeMe {
    public:
        PmergeMe();
        PmergeMe(const PmergeMe &other);
        PmergeMe &operator=(const PmergeMe &other);
        ~PmergeMe();

        void addNumber(int num);
        void sort();

    private:
        std::vector<int> numbersVector;
        std::deque<int> numbersDeque;
};

//-------------------Main Sorting Algorithm------------------//
template <typename Container>
Container fordJohnsonSort(Container &input);

//-------------------Helper Functions-------------------//
template <typename Container>
void insertionSort(Container &container, int left, int right);

template <typename Container>
int binarySearch(const Container &container, int item, int left, int right);

template <typename Container>
void binaryInsertionSort(Container &container, int value);

template <typename Container>
std::vector<int> generateJacobsthalSequence(const Container &container);

#endif // PMERGEME_HPP