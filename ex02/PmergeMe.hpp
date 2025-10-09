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

//Simple insertion sort for small segments
template <typename Container>
void insertionSort(Container &container, int left, int right);

//Search in a sorted container where to insert the item 
template <typename Container>
int binarySearch(const Container &container, int item, int left, int right);

//Insert the item of the b container into the a container at the found position by binary search
template <typename Container>
void binaryInsert(Container &container, int value);

//Generate the Jacobsthal sequence up to the size of the container
template <typename Container>
std::vector<int> generateJacobsthalSequence(const Container &container) {
    std::vector<int> jacobsthal;
    size_t n = container.size();
    if (n == 0)
        return jacobsthal;
    jacobsthal.push_back(0); // J(0)
    if (n == 1)
        return jacobsthal;
    jacobsthal.push_back(1); // J(1)
    for (size_t i = 2; jacobsthal.size() < n; ++i) {
        int next = jacobsthal[i - 1] + 2 * jacobsthal[i - 2];
        jacobsthal.push_back(next);
    }
    return jacobsthal;
}


#endif // PMERGEME_HPP