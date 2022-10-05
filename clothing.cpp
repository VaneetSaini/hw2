#include "clothing.h"
#include "util.h"

using namespace std;

Clothing::Clothing(const std::string category, const std::string name, double price, int qty, std::string size, std::string brand) :
	Product(category, name, price, qty)
	
{
	name_ = name;
	price_ = price;
	size_ = size;
	brand_ = brand;
	qty_ = qty;

}

Clothing::~Clothing()
{
	
}

std::set<std::string> Clothing::keywords() const
{
	std::set<std::string> result;
	std::set<std::string> keyName;
	std::set<std::string> keyBrand;

	keyName = parseStringToWords(name_);
	keyBrand = parseStringToWords(brand_);
	result = setUnion(keyName, keyBrand);

	return result;
}

std::string Clothing::displayString() const
{
	return name_ + "\n" + "Size: " + size_ + " Brand: " + brand_ + "\n" + std::to_string(price_) + " " + std::to_string(qty_) + " left.";
}

void Clothing::dump(std::ostream& os) const
{
	os << category_ << "\n" << name_ << "\n" << price_ << "\n" << qty_ << "\n" << size_ << "\n" << brand_ << endl;
}
