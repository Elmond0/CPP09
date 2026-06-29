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

static std::vector<size_t> buildInsertionOrder(size_t pendCount)
{
	std::vector<size_t> order;
	size_t prev = 0;
	size_t curr = 1;
	size_t jacobPrev = 1;
	size_t jacobPrevPrev = 0;

	while (prev < pendCount)
	{
		size_t upper = curr;
		if (upper > pendCount)
			upper = pendCount;
		for (size_t idx = upper; idx > prev; --idx)
			order.push_back(idx - 1);
		prev = curr;

		size_t next = jacobPrev + 2 * jacobPrevPrev;
		jacobPrevPrev = jacobPrev;
		jacobPrev = curr;
		curr = next;
	}
	return order;
}

template <typename Container>
static void fordJohnson(Container& data)
{
	typedef typename Container::iterator Iter;

	size_t n = data.size();
	if (n < 2)
		return;

	bool hasStraggler = (n % 2 != 0);
	int straggler = 0;
	if (hasStraggler)
		straggler = data[n - 1];

	Container winners;
	Container losers;

	for (size_t i = 0; i + 1 < n; i += 2)
	{
		int a = data[i];
		int b = data[i + 1];
		if (a > b)
			std::swap(a, b);
		losers.push_back(a);
		winners.push_back(b);
	}

	fordJohnson(winners);
	Container main = winners;

	std::vector<size_t> order = buildInsertionOrder(losers.size());

	for (size_t o = 0; o < order.size(); ++o)
	{
		int value = losers[order[o]];
		Iter pos = std::upper_bound(main.begin(), main.end(), value);
		main.insert(pos, value);
	}
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

	std::clock_t startVec = std::clock();
	sortVector(_vec);
	std::clock_t endVec = std::clock();

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
