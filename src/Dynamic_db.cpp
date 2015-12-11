/*
//============================================================================
// Name        : Dynamic_db.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <vector>
#include <memory>
//#include "Field.h"
//#include "Record.h"
#include "Table.h"


TODO:brakuje obsługi błedów
 *
 *
 *
 *
using namespace std;
//
//struct Table_config_t {
//	std::string name;
//	int count;
//};
//
//struct Row_config_t {
//	std::string name;
//	std::string type;
//};



int main() {
	int n;
	string name;
	//creating table
	shared_ptr <Table> t = make_shared<Table>();
	cout<<"Set name of table"<<endl;
	cin>>name;
	t->setName(name);
	cout << "how many field do you want to store in table" << endl;
	cin>>n;
	cout<<"creating tables...."<<endl;
	for(int i=0; i<n; i++){
	//checking function for type
		string name, type;
		cout<<"type(VAR, INT, FLOAT, TIME): ";
		cin>>type;
		cout<<"name: ";
		cin>>name;
		t->addConfigField(type, name);
	}

	//printing table
	t->describeTable();
	Record


	return 0;
}



*/

#include <iostream>
#include <memory>
#include <vector>

class Property
{
public:
    Property(const std::string& name) //note: we don't lightly copy strings in C++
      : m_name(name) {}
    virtual ~Property() {}
private:
    std::string m_name;
};

template< typename T >
class TypedProperty : public Property
{
public:
    TypedProperty (const std::string& name, const T& data): Property(name), m_data(data){}
private:
    T m_data;
};


typedef std::vector< std::shared_ptr<Property> > property_list_type;

int main(){

std::vector< std::shared_ptr<Property> > a;




}



