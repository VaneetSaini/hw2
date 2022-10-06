#include "mydatastore.h"
#include "datastore.h"
#include "util.h"
#include "book.h"
#include "clothing.h"
#include "movie.h"
#include "user.h"
#include <set>
#include <map>
#include <vector>
#include <sstream>
#include <algorithm>
#include <iomanip>

MyDataStore::MyDataStore() : DataStore()
{

}

void MyDataStore::addProduct(Product* p)
{
	Products.push_back(p);
	std::set<std::string> keyWords = p->keywords();
	std::set<std::string>::iterator it;
	for (it = keyWords.begin(); it != keyWords.end(); ++it){
		if (users.find(*it) == users.end()){
			std::set<Product*> newSet;
			newSet.insert(p);
			mapOfProducts.insert(std::make_pair(*it, newSet));
		}
		else{
			mapOfProducts[*it].insert(p);
		}
	}
}

void MyDataStore::dump(std::ostream& ofile)
{
	ofile << "<products>" << std::endl;
	for (unsigned int i = 0; i < Products.size(); ++i){
		Products[i]->dump(ofile);
	}
	ofile << "</products>" << std::endl;
	ofile << "<users>" << std::endl;
	std::map<std::string, User*>::iterator it;
	for (it = users.begin(); it != users.end(); ++it){
		it->second->dump(ofile);
	}
	ofile << "</users>" << std::endl;
}

void MyDataStore::addUser(User* u)
{
	users.insert(std::make_pair(u->getName(), u));
}

void MyDataStore::addCart(std::string user, Product* p)
{
	usersCart[user].push_back(p);
}

void MyDataStore::viewCart(std::string user)
{
	if (usersCart.find(user) != usersCart.end()){
		std::vector<Product*> x = usersCart[user];
		for (unsigned int i = 0; i < x.size(); ++i){
			x[i]->displayString();

		}
	}
}

void MyDataStore::buyCart(std::string user)
{
	std::vector<Product*> notEnoughMoney;
	std::vector<Product*> purchaseCurrentCart;
	std::vector<Product*>::iterator it;
	if (usersCart.find(user) != usersCart.end()){
		purchaseCurrentCart = usersCart[user];
		for (it = purchaseCurrentCart.begin(); it != purchaseCurrentCart.end(); ++it){
			if ((*it)->getQty() == 0 || users[user]->getBalance() < (*it)->getPrice()){
				notEnoughMoney.push_back(*it);
			}
			else{
				users[user]->deductAmount((*it)->getPrice());
				(*it)->subtractQty(1);
			}
		}
		purchaseCurrentCart = notEnoughMoney;
	}
}

std::vector<Product*> MyDataStore::search(std::vector<std::string>& terms, int type)
{
	std::vector<std::string>::iterator it1;
	std::vector<std::string>::iterator it2; 
	std::set<Product*> setProducts = mapOfProducts[terms[0]];
	if (type == 0){
		for (it1 = terms.begin(); it1 != terms.end(); ++it1){
			setProducts = setIntersection(setProducts, mapOfProducts[*it1]);
		}
	}
	else if(type == 1){
		for (it2 = terms.begin(); it2 != terms.end(); ++it2){
			setProducts = setUnion(setProducts, mapOfProducts[*it2]);

		}
	}
	std::vector<Product*> convToVec(setProducts.begin(), setProducts.end());
	return convToVec;
}


