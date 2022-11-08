#include "mydatastore.h"
#include "datastore.h"
#include "util.h"
#include <set>
#include <map>
#include <vector>
#include <sstream>
#include <algorithm>
#include <iomanip>
#include <iostream>

using namespace std;

MyDataStore::MyDataStore() : DataStore()
{

}

void MyDataStore::addProduct(Product* p)
{
	vecProducts.push_back(p);
	std::set<std::string> keyWords = p->keywords();
	std::set<std::string>::iterator it;

	for (it = keyWords.begin(); it != keyWords.end(); ++it){
		if (mapProduct.find(*it) == mapProduct.end()){
			std::set<Product*> newSet;
			newSet.insert(p);
			mapProduct.insert(std::make_pair(*it, newSet));
		}
		else{
			mapProduct[*it].insert(p);
		}
	}
}

void MyDataStore::dump(std::ostream& ofile)
{
	ofile << "<products>" << std::endl;
	for (unsigned int i = 0; i < vecProducts.size(); ++i){
		vecProducts[i]->dump(ofile);
	}
	ofile << "</products>" << std::endl;
	ofile << "<users>" << std::endl;
	std::map<std::string, User*>::iterator it;
	for (it = mapUsers.begin(); it != mapUsers.end(); ++it){
		((it)->second)->dump(ofile);
	}
	ofile << "</users>" << std::endl;
}

void MyDataStore::addUser(User* u)
{
	std::vector<Product*> userProd;
	mapCart.insert(std::make_pair(u, userProd));
	mapUsers.insert(std::make_pair(u->getName(), u));
}

void MyDataStore::addCart(std::string user, string search, std::vector<Product*> hits)
{
	User* u;
	unsigned int search_hit_number = stoi(search);
	if (hits.empty()){
		cout << "No products avaliable. Search for a product!" << endl;
		return;
	}
	if (search_hit_number > hits.size())
	{
		cout << "Invalid request" << endl;
		return;
	}
	if (mapUsers.find(user) == mapUsers.end())
	{
		cout << "Invalid request" << endl;
		return;
	}
	else{
		u = mapUsers.find(user)->second;
		mapCart[u].push_back(hits[search_hit_number - 1]);
		return;
	}
}

void MyDataStore::viewCart(std::string user)
{
	User* u;
	if (mapUsers.find(user) == mapUsers.end()){
		cout << "Invalid username" << endl;
		return;
	}
	u = mapUsers.find(user)->second;
	vector<Product*> products = mapCart[u];
	if (products.begin() == products.end())
	{
		cout << "Cart is empty!" << endl;
		return;
	}
	int prodNum = 1;
	vector<Product*>::iterator it;
	for (it = products.begin(); it != products.end(); ++it)
	{
		cout << "Item" << prodNum << endl;
		cout << (*it)->displayString() << endl;
		cout << endl;
		prodNum++;
	}
}

void MyDataStore::buyCart(std::string user)
{
	User* u;
	if (mapUsers.find(user) == mapUsers.end())
	{
		cout << "Invalid username" << endl;
		return;
	}
	u = mapUsers.find(user)->second;
	vector<Product*> items = mapCart[u];
	if (items.begin() == items.end())
	{
		cout << "Cart is empty!" << endl;
		return;
	}
	vector<Product*> leftOver;
	vector<Product*>::iterator it;
	for (it = items.begin(); it != items.end(); ++it)
	{
		if ((*it)->getPrice() > u->getBalance())
		{
			cout << u->getName() << " doesn't have enough money for: " << (*it)->getName() << " (" << (*it)->getPrice() << ")" << endl;
			leftOver.push_back(*it);
		}
		else if ((*it)->getQty() == 0)
		{
			cout << "We are currently out of stock of: " << (*it)->getName() << endl;
		}
		else
		{
			u->deductAmount((*it)->getPrice());
			(*it)->subtractQty(1);
			cout << u->getName() << " has $" << u->getBalance() << " left." << endl;
		}
	}
	mapCart[u] = leftOver;
	return;
}

std::vector<Product*> MyDataStore::search(std::vector<std::string>& terms, int type)
{
	std::vector<Product*> vecProducts;
	std::set<Product*> setProduct;
	std::set<Product*> setTerm;
	if (type != 0 && type != 1)
	{
		vector<Product*> nothing;
		cout << "Invalid" << endl;
		return nothing;
	}
	for (unsigned int i = 0; i < terms.size(); ++i)
	{
		if (type == 0)
		{
			setTerm = mapProduct[terms[0]];
			setProduct = mapProduct[terms[i]];
			setTerm = setIntersection(setTerm, setProduct);
		}
		else if (type == 1)
		{
			setProduct = mapProduct[terms[i]];
			setTerm = setUnion(setTerm, setProduct);
		}
	}
	std::set<Product*>::iterator it;
	for (it = setTerm.begin(); it != setTerm.end(); ++it)
	{
		vecProducts.push_back(*it);
	}
	return vecProducts;
}


