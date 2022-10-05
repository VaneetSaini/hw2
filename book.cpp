#include "book.h"
#include "util.h"

using namespace std;

Book::Book(const std::string category, const std::string name, double price, int qty, std::string isbn, std::string author) :
	Product(category, name, price, qty)
	
{
	name_ = name;
	price_ = price;
	author_ = author;
	isbn_ = isbn;
	qty_ = qty;

}

Book::~Book()
{
	
}

std::set<std::string> Book::keywords() const
{
	std::set<std::string> result;
	std::set<std::string> keyAuth;
	std::set<std::string> keyISBN;
	std::set<std::string> keyName;

	keyAuth = parseStringToWords(author_);
	keyISBN = parseStringToWords(isbn_);
	keyName = parseStringToWords(name_);
	std::set<std::string> temp = setUnion(keyName, keyAuth);
	result = setUnion(temp, keyISBN);

	return result;
}

std::string Book::displayString() const
{
	return name_ + "\n" + "Author: " + author_ + " ISBN: " + isbn_ + "\n" + std::to_string(price_) + " " + std::to_string(qty_) + " left.";
}

void Book::dump(std::ostream& os) const
{
	os << category_ << "\n" << name_ << "\n" << price_ << "\n" << qty_ << "\n" << isbn_ << "\n" << author_ << endl;
}