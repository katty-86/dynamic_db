//============================================================================
// Name        : Dynamic_db.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <vector>
#include "IntegerField.h"
#include "Field.h"
#include "Record.h"
#include <memory>
#include "Table.h"

/*TODO:brakuje obsługi błedów
 *
 *
 *
 * */
using namespace std;

struct Table_config_t {
	std::string name;
	int count;
};

struct Row_config_t {
	std::string name;
	std::string type;
};

int main() {
	int i;
	Table ta();
	cout << "how many field do you want to store in table" << endl;
	cin>>i;
	ta->setFieldCounter(i);
	cout << "give name type(int, varchar)" << endl;
	for (int i = 0; i < tc.count; i++) {
		Row_config_t rc;
		cin >> rc.name;
		cin >> rc.type;
		r.addField(rc.name, rc.type);
	}
	cout << r << endl;

	cout << "!!!Hello World!!!" << endl; // prints !!!Hello World!!!
	return 0;
}
