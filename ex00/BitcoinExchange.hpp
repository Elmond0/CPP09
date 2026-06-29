#ifndef BITCOINEXCHANGE_HPP
# define BITCOINEXCHANGE_HPP

# include <map>
# include <string>

class BitcoinExchange
{
	public:
		BitcoinExchange();
		BitcoinExchange(const BitcoinExchange& other);
		BitcoinExchange& operator=(const BitcoinExchange& other);
		~BitcoinExchange();

		void loadDatabase(const std::string& path);
		void processInput(const std::string& path) const;

	private:
		std::map<std::string, float> _rates;
		float getRate(const std::string& date) const;
};

bool isValidDate(const std::string& date);
bool parseValue(const std::string& str, float& out);

#endif
