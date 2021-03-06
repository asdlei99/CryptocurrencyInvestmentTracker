#include "stdafx.h"

/*!
* @brief Prints help message
*/
void printHelp() {
	std::cout << "[q] = Quit the application\n" << "[r] = Refresh and print the wallet\n[c] = Query information for a specific cryptocurrency\n[s] = Setup wallet\n[h] = Prints this message" << std::endl;
}

/*!
* @brief Queries and prints information for a single cryptocurrency
* @param[in] query PriceQuery object for querying information about the required cryptocurrency
*/
void querySingleCurrency(PriceQuery &query) {
	Currency currency;
	std::cout << "Input the name of the cryptocurrency to query: ";
	std::string name;
	std::getline(std::cin, name);
	if (query.queryCurrency(currency, name)) {
		std::cout << "Name: " << currency.name << "\nPrice in BTC: " << currency.price[BTC] << "\nPrice in USD: " << currency.price[USD]
			<< "\nPrice in EUR: " << currency.price[EUR] << "\nChange percent in 24h: " << currency.changePercentInDay << "\n";
	}
	else {
		std::cout << "Failed to query: " << name << std::endl;
	}
}

/*!
* @brief Runs a loop and asks for users commands
* @param[in] query PriceQuery object for querying information about cryptocurrencies
* @param[in] Wallet Wallet object that contains information about the users investments
*/
void run(PriceQuery &query, Wallet &wallet) {
	printHelp();
	int action;
	while (true) {
		std::cout << "> ";
		action = _getch();
		std::cout << "\n";
		switch (action) {
		case 'q':
			return;
		case 'h':
			printHelp();
			break;
		case 'r':
			if (!wallet.loadWallet())
				std::cout << "Failed to load wallet. Check the syntax" << std::endl;
			else
				std::cout << wallet << std::endl;
			break;
		case 'c':
			querySingleCurrency(query);
			break;
		case 's':
			if (wallet.createWallet()) {
				std::cout << "Wallet created!" << std::endl;
				if (!wallet.loadWallet())
					std::cout << "Failed to load wallet. Check the syntax" << std::endl;
				else
					std::cout << wallet << std::endl;
			}
			else {
				std::cout << "Failed to create wallet" << std::endl;
			}
			break;
		default:
			std::cout << "Unknown action \'" << (char)action << "\'. Press \'h\' for help" << std::endl;
		}
	}
}

int main(int argc, char *argv[])
{
	std::string walletFile = "wallet.txt";
	if (argc > 1) {
		walletFile = (argv[1]);
	}
	PriceQuery query;
	Wallet wallet(query, walletFile);
	run(query, wallet);
	return 0;
}

