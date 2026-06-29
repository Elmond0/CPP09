#ifndef PMERGEME_HPP
# define PMERGEME_HPP

# include <vector>
# include <deque>
# include <string>

class PmergeMe
{
	public:
		PmergeMe();
		PmergeMe(const PmergeMe& other);
		PmergeMe& operator=(const PmergeMe& other);
		~PmergeMe();

		void parse(int argc, char** argv);
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
