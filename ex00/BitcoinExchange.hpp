#ifndef BITCOINEXCHANGE_HPP
# define BITCOINEXCHANGE_HPP

# include <map>
# include <string>

// Holds the historical BTC price database (date -> exchange rate) and
// evaluates an input file of "date | value" lines against it.
class BitcoinExchange
{
	public:
		BitcoinExchange();
		BitcoinExchange(const BitcoinExchange& other);
		BitcoinExchange& operator=(const BitcoinExchange& other);
		~BitcoinExchange();

		// Loads the price database from a csv file ("date,rate").
		// Throws std::runtime_error if the file cannot be read.
		void loadDatabase(const std::string& path);

		// Reads the input file line by line and prints the result for each.
		// Throws std::runtime_error if the file cannot be opened.
		void processInput(const std::string& path) const;

	private:
		std::map<std::string, float> _rates;

		// Returns the rate for the given date, or the closest earlier date.
		// Throws std::out_of_range if no date in the db is <= the asked one.
		float getRate(const std::string& date) const;
};

// Validation helpers (free functions, reusable and easy to test).
bool isValidDate(const std::string& date);
bool parseValue(const std::string& str, float& out);

#endif
