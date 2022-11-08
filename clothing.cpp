#include "clothing.h"
#include "util.h"
#include <iostream>
#include <algorithm>
#include <vector>
#include <string> 
#include <sstream>
#include <iomanip> 

using namespace std;

Clothing::Clothing(const std::string category, const std::string name, double price, int qty, std::string size, std::string brand) :
	Product(category, name, price, qty)
	
{
	size_ = size;
	brand_ = brand;

}

Clothing::~Clothing()
{
	
}

std::set<std::string> Clothing::keywords() const
{
	std::set<std::string> result;
	std::set<std::string> brand;
	result = parseStringToWords(name_);
	brand = parseStringToWords(brand_);
	std::set<std::string>::iterator it;
	for (it = brand.begin(); it != brand.end(); ++it)
	{
		result.insert(*it);
	}
	result.insert(to_string(price_));
	result.insert(to_string(qty_));
	result.insert(size_);

	return result;
}

std::string Clothing::displayString() const
{
	stringstream ss;
	ss << name_ << "\n" << "Size: " << size_ << " " << "Brand: " << brand_ << "\n" << price_  << " " << qty_ << " " << "left." << "\n" << std::endl;
	return ss.str();
}

void Clothing::dump(std::ostream& os) const
{
	os << category_ << "\n" << name_ << "\n" << price_ << "\n" << qty_ << "\n" << size_ << "\n" << brand_ << endl;
}