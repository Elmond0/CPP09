#include "PmergeMe.hpp"

#include <iostream>
#include <sstream>
#include <stdexcept>
#include <algorithm>
#include <ctime>
#include <cstdlib>
#include <climits>
#include <cctype>

PmergeMe::PmergeMe() {}

PmergeMe::PmergeMe(const PmergeMe& other) : _vec(other._vec), _deq(other._deq) {}

PmergeMe& PmergeMe::operator=(const PmergeMe& other)
{
	if (this != &other)
	{
		_vec = other._vec;
		_deq = other._deq;
	}
	return *this;
}

PmergeMe::~PmergeMe() {}

// ----- parsing --------------------------------------------------------------

// Parses a single argument as a strictly positive integer (> 0) that fits
// in an int. Throws std::invalid_argument otherwise.
static int parseToken(const std::string& token)
{
	if (token.empty())
		throw std::invalid_argument("empty token");

	for (size_t i = 0; i < token.size(); ++i)
		if (!std::isdigit(static_cast<unsigned char>(token[i])))
			throw std::invalid_argument("not a positive integer");

	char* end = 0;
	long value = std::strtol(token.c_str(), &end, 10);
	if (*end != '\0' || value <= 0 || value > INT_MAX)
		throw std::invalid_argument("out of range");

	return static_cast<int>(value);
}

void PmergeMe::parse(int argc, char** argv)
{
	for (int i = 1; i < argc; ++i)
	{
		int value = parseToken(argv[i]);
		_vec.push_back(value);
		_deq.push_back(value);
	}
	if (_vec.empty())
		throw std::invalid_argument("no input");
}

// ----- Jacobsthal -----------------------------------------------------------

// Builds the order in which pending elements should be inserted, following the
// Jacobsthal sequence (1, 3, 5, 11, 21, ...). Within each Jacobsthal "group"
// we insert from the highest index down to the previous boundary; this keeps
// the number of comparisons close to the theoretical minimum.
//
// The groups tile [0, pendCount) without gaps or overlaps, so the returned
// vector contains every index in [0, pendCount) exactly once.
static std::vector<size_t> buildInsertionOrder(size_t pendCount)
{
	std::vector<size_t> order;
	size_t prev = 0;       // start of the current group
	size_t curr = 1;       // current Jacobsthal number
	size_t jacobPrev = 1;  // J(k-1)
	size_t jacobPrevPrev = 0; // J(k-2)

	while (prev < pendCount)
	{
		size_t upper = curr;
		if (upper > pendCount)
			upper = pendCount;
		for (size_t idx = upper; idx > prev; --idx)
			order.push_back(idx - 1);
		prev = curr;

		// Next Jacobsthal number: J(k) = J(k-1) + 2 * J(k-2).
		size_t next = jacobPrev + 2 * jacobPrevPrev;
		jacobPrevPrev = jacobPrev;
		jacobPrev = curr;
		curr = next;
	}
	return order;
}

// ----- generic Ford-Johnson -------------------------------------------------
//
// Templated on the container type so the exact same logic runs for both the
// vector and the deque, while each call still operates on its own container
// (the subject only asks that two different containers are used).

template <typename Container>
static void fordJohnson(Container& data)
{
	typedef typename Container::iterator Iter;

	size_t n = data.size();
	if (n < 2)
		return;

	// 1. Split into pairs and order each pair (first <= second).
	//    `straggler` is the leftover element when n is odd.
	bool hasStraggler = (n % 2 != 0);
	int straggler = 0;
	if (hasStraggler)
		straggler = data[n - 1];

	Container winners;  // larger element of each pair (the "main chain" seeds)
	Container losers;   // smaller element of each pair (the "pend")

	for (size_t i = 0; i + 1 < n; i += 2)
	{
		int a = data[i];
		int b = data[i + 1];
		if (a > b)
			std::swap(a, b);
		losers.push_back(a);   // smaller
		winners.push_back(b);  // larger
	}

	// 2. Recursively sort the winners: this becomes our sorted "main chain".
	fordJohnson(winners);
	Container main = winners;

	// 3. Binary-insert every loser into the main chain, in Jacobsthal order.
	//    Each loser is <= its own winner, so searching the whole chain is safe
	//    and always finds the correct spot.
	std::vector<size_t> order = buildInsertionOrder(losers.size());

	for (size_t o = 0; o < order.size(); ++o)
	{
		int value = losers[order[o]];
		Iter pos = std::upper_bound(main.begin(), main.end(), value);
		main.insert(pos, value);
	}

	// 4. Finally, binary-insert the straggler if there was one.
	if (hasStraggler)
	{
		Iter pos = std::upper_bound(main.begin(), main.end(), straggler);
		main.insert(pos, straggler);
	}

	data = main;
}

void PmergeMe::sortVector(std::vector<int>& v)
{
	fordJohnson(v);
}

void PmergeMe::sortDeque(std::deque<int>& d)
{
	fordJohnson(d);
}

// ----- output ---------------------------------------------------------------

template <typename Container>
void PmergeMe::printSequence(const std::string& label, const Container& c) const
{
	std::cout << label;
	for (typename Container::const_iterator it = c.begin(); it != c.end(); ++it)
		std::cout << " " << *it;
	std::cout << std::endl;
}

void PmergeMe::run()
{
	printSequence("Before:", _vec);

	// Time the vector sort.
	std::clock_t startVec = std::clock();
	sortVector(_vec);
	std::clock_t endVec = std::clock();

	// Time the deque sort.
	std::clock_t startDeq = std::clock();
	sortDeque(_deq);
	std::clock_t endDeq = std::clock();

	printSequence("After: ", _vec);

	double usVec = static_cast<double>(endVec - startVec) / CLOCKS_PER_SEC * 1e6;
	double usDeq = static_cast<double>(endDeq - startDeq) / CLOCKS_PER_SEC * 1e6;

	std::cout << "Time to process a range of " << _vec.size()
			  << " elements with std::vector : " << usVec << " us" << std::endl;
	std::cout << "Time to process a range of " << _deq.size()
			  << " elements with std::deque  : " << usDeq << " us" << std::endl;
}
