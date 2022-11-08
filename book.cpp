#include "book.h"
#include "util.h"
#include <iostream>
#include <algorithm>
#include <vector>
#include <string> 
#include <sstream>
#include <iomanip> 

using namespace std;

Book::Book(const std::string category, const std::string name, double price, int qty, std::string isbn, std::string author) :
	Product(category, name, price, qty)
	
{
	author_ = author;
	isbn_ = isbn;

}

Book::~Book()
{
	
}

std::set<std::string> Book::keywords() const
{
	std::set<std::string> result;
	std::set<std::string> author;
	result = parseStringToWords(name_);
	author = parseStringToWords(author_);
	std::set<std::string>::iterator it;
	for (it = author.begin(); it != author.end(); ++it)
	{
		result.insert(*it);
	}
	result.insert(to_string(price_));
	result.insert(to_string(qty_));
	result.insert(isbn_);

	return result;
}

std::string Book::displayString() const
{
	stringstream ss;
	ss << name_ << "\n" << "Author: " << author_ << " " << "ISBN: " << isbn_ << price_ << " " << qty_ << " " << "left." << "\n" << std::endl;
	return ss.str();
}

void Book::dump(std::ostream& os) const
{
	os << category_ << "\n" << name_ << "\n" << price_ << "\n" << qty_ << "\n" << isbn_ << "\n" << author_ << endl;
}