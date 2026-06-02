#ifndef PMERGEME_HPP
# define PMERGEME_HPP

# include <vector>
# include <deque>
# include <string>

// Sorts a sequence of positive integers using the Ford-Johnson
// (merge-insertion) algorithm. The algorithm is implemented twice, once on a
// std::vector and once on a std::deque, so we can compare their timings.
class PmergeMe
{
	public:
		PmergeMe();
		PmergeMe(const PmergeMe& other);
		PmergeMe& operator=(const PmergeMe& other);
		~PmergeMe();

		// Parses argv into the internal containers.
		// Throws std::invalid_argument on any non positive-integer token.
		void parse(int argc, char** argv);

		// Runs both sorts, printing the before/after sequences and timings.
		void run();

	private:
		std::vector<int> _vec;
		std::deque<int>  _deq;

		void sortVector(std::vector<int>& v);
		void sortDeque(std::deque<int>& d);

		template <typename Container>
		void printSequence(const std::string& label, const Container& c) const;
};

#endif
