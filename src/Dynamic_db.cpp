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
#include "Table.h"
#include "Serializer.h"
#include <algorithm>
#include <regex>
#include "Utils.h"
using namespace std;

void displayManu();
void DMLMenu();
void createTable(shared_ptr<Table> &t);
void saveBDtoFile(shared_ptr<Table> &t);
void readDBfromFile(shared_ptr<Table> &t);
void insert(shared_ptr<Table> &t);
void select(shared_ptr<Table> &t);
std::string acceptable_type = ("INT VAR TIME FLOAT");

int main() {

	char choose;
	shared_ptr<Table> t = make_shared<Table>();
	do {
		displayManu();
		cin >> choose;
		if (choose == 'b') {
			createTable(t);
		} else if (choose == 'c') {
			saveBDtoFile(t);
		} else if (choose == 'd') {
			readDBfromFile(t);
		} else if (choose == 'e') {
			if (!t->checkIfListDataEmpty()) {
				DMLMenu();
				cin >> choose;
				if (choose == 'i') {
					insert(t);
				} else if (choose == 's') {
					//basic select *
					//t->printTable();
				   select(t);
				} else if (choose == 'd') {
					t->findRow("IMIE", "krzys");
				} else if (choose == 'u') {
					t->findRow("imieiiii", "krzys");
				}

				else {

				}
			} else {
				cout << "list is empty -task is not possible" << endl;
			}

		} else if (choose == 'f') {
			t->describeTable();
		} else {

		}
	} while (choose != 'q');

//printing table

	return 0;
}

void displayManu() {
	cout << "what you want to do?\n";
	cout << "config_db_file - config db_file \n";
	cout << "b- create db \n";
	cout << "c- commit db\n";
	cout << "d- load db\n";
	cout << "f- describe table\n";
	cout << "e- write dml statement (select, update.....)\n";
	cout << "q- quit\n";
	cout << ">";
}

void DMLMenu() {
	cout << "i- insert \n";
	cout << "d- delete\n";
	cout << "u- update\n";
	cout << "s- select\n";
	cout << ">";
}

void createTable(shared_ptr<Table> &t) {

	int n;
	string name;
	cout << "Set name of table" << endl;
	cin >> name;
	std::transform(name.begin(), name.end(), name.begin(), ::toupper);
	t->setName(name);
	cout << "how many field do you want to store in table" << endl;
	cin >> n;
	cout << "creating tables...." << endl;
	for (int i = 0; i < n; i++) {
		//checking function for type
		string name, type;
		do {
			cout << "Write type from [" << acceptable_type << "]" << endl;
			cin >> type;
			std::transform(type.begin(), type.end(), type.begin(), ::toupper);
		} while (acceptable_type.find(type) == std::string::npos);

		cout << "Write name: ";
		cin >> name;
		std::transform(name.begin(), name.end(), name.begin(), ::toupper);
		t->addConfigField(type, name);
	}
}

void saveBDtoFile(shared_ptr<Table> &t) {
	string filename;
	cout << "Set name of the file" << endl;
	cin >> filename;
	Serializer helper;
	helper.writaData(t, filename);
}
void readDBfromFile(shared_ptr<Table> &t) {
	t->clearTable();
	string filename;
	cout << "Set name of the file" << endl;
	cin >> filename;
	Serializer helper;
	helper.readData(t, filename);
}

void insert(shared_ptr<Table> &t) {
	cout << "How many rows you want to add" << endl;
	int rows;
	cin >> rows;
	for (int i = 0; i < rows; ++i) {
		t->addRow();
	}
	t->printTable();
}


void select(shared_ptr<Table> &t){

	//checking if correct line!



	cout<<"Write select"<<endl;
	string select_input, phrase;
	cin.ignore(256, '\n');
	getline(cin, select_input);
	std::transform(select_input.begin(), select_input.end(), select_input.begin(), ::toupper);
	phrase="SELECT * FROM ";
	phrase.append(t->getName());
	phrase.append(" WHERE ");
	cout<<phrase<<endl;

	int pos=select_input.find("=");
	int pos_where=select_input.find(" WHERE ");
			string name=select_input.substr(phrase.size(),pos-phrase.size());
		    string value=select_input.substr(pos+1,select_input.size()-pos);
	//select * from from $table_name  where value=name
	if((select_input.find("COUNT(*)"))!=std::string::npos){

	    cout<<"--"<<value<<"---"<<name<<endl;
	    list<Record> lis_result= t->findMatchingRow(name, value);
	    for(auto i =lis_result.begin(); i!=lis_result.end(); ++i){
	    	cout<<*i;
	    }
	}
	if((select_input.find(" * "))!=std::string::npos){
			int pos=select_input.find("=");
			string name=select_input.substr(phrase.size(),pos-phrase.size());
		    string value=select_input.substr(pos+1,select_input.size()-pos);
		    cout<<"--"<<value<<"---"<<name<<endl;
		    cout<< t->countMatchingRow(name, value);

		}

}
