#ifndef MYDATASTORE_H
#define MYDATASTORE_H
#include <string>
#include <set>
#include <vector>
#include <map>
#include <algorithm>
#include "user.h"
#include "datastore.h"

class MyDataStore : public DataStore{
public:
	MyDataStore();
	void addProduct(Product* p);
	void addUser(User* u);
	std::vector<Product*> search(std::vector<std::string>& terms, int type);
	void dump(std::ostream& ofile);
	void addCart(std::string user, Product* p);
	void viewCart(std::string user);
	void buyCart(std::string user);

	private:
		std::vector<Product*> Products;
		std::map<std::string, User*> users;
		std::map<std::string, std::vector<Product*>> usersCart;
		std::map<std::string, std::set<Product*>> mapOfProducts;

};
#endif

