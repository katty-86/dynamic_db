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
void deleteRow(shared_ptr<Table> &t);
void updateRow(shared_ptr<Table> &t);
string acceptable_type = ("INT VAR TIME FLOAT");

int main() {

	string choose;
	shared_ptr<Table> t = make_shared<Table>();
	displayManu();
	do {
		cout << "\n >";
		getline(cin, choose);
		cin >> choose;
		if (choose == "b") {
			createTable(t);
		} else if (choose == "c") {
			saveBDtoFile(t);
		} else if (choose == "d") {
			readDBfromFile(t);
		} else if (choose == "h") {
			displayManu();
		} else if (choose == "e") {
			if (!t->checkIfListDataEmpty()) {
				DMLMenu();
				cin >> choose;
				if (choose == "i") {
					insert(t);
				} else if (choose == "s") {
					select(t);
				} else if (choose == "d") {
					deleteRow(t);
				} else if (choose == "u") {
					updateRow(t);
				}

				else {

				}
			} else {
				cout << "list is empty -task is not possible" << endl;
			}

		} else if (choose == "f") {
			t->describeTable();
		} else {

		}
	} while (choose != "q");

//printing table

	return 0;
}

void displayManu() {
	cout << "b- create db \n";
	cout << "c- commit db\n";
	cout << "d- load db\n";
	cout << "f- describe table\n";
	cout << "e- write dml statement (select, update.....)\n";
	cout << "q- quit\n";
	cout << "h- print help\n";
	cout << "\n\n or write dml statement for existing table \n";
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

void select(shared_ptr<Table> &t) {

	cout << "Write select" << endl;
	string select_input;
	cin.ignore(256, '\n');
	getline(cin, select_input);
	std::transform(select_input.begin(), select_input.end(),
			select_input.begin(), ::toupper);
	regex reg_input(
			"select[[:s:]]*([[:print:]]*)[[:s:]]+from[[:s:]]*" + t->getName()
					+ "([[:print:]]*)", regex_constants::icase);
	smatch m;
	bool flag = std::regex_search(select_input, m, reg_input);
	if (flag == true) {
		cout << "ok" << endl;
		cout << m[1] << "=" << m[2] << "=" << m[3] << "=" << endl;
		string str = m[2];
		regex e("([[:w:]]+)[[:s:]]*=[[:s:]]*([[:w:]]+)");
		sregex_iterator pos(str.cbegin(), str.cend(), e);
		sregex_iterator end;
		vector<pair<string, string>> v_pair_condition;
		for (; pos != end; pos++) {
			v_pair_condition.push_back(
					pair<string, string>(pos->str(1), pos->str(2)));
		}

		if (m[1] == "*") {
			if (v_pair_condition.empty() == true) {
				t->printTable();
			} else {
				list<Record> lis_result = t->findMatchingRow(v_pair_condition);
				for (auto i = lis_result.begin(); i != lis_result.end(); ++i) {
					cout << *i << endl;
				}
			}

		} else if (m[1] == "COUNT(*)") {
			if (v_pair_condition.empty() == true) {
				cout << t->sizeListData() << endl;
				;
			} else {
				cout << t->countMatchingRow(v_pair_condition) << endl;
			}
		} else {
			cout << "not supported:)" << endl;
			//TODO check if param is ok
			//specify column which can be printed
		}

	} else {
		cout << "Incorrect statement" << endl;
	}

}

void deleteRow(shared_ptr<Table> &t) {

	cout << "Write delete" << endl;
	string select_input;
	cin.ignore(256, '\n');
	getline(cin, select_input);
	std::transform(select_input.begin(), select_input.end(),
			select_input.begin(), ::toupper);
	regex reg_input(
			"delete[[:s:]]+from[[:s:]]+" + t->getName()
					+ "[[:s:]]*([[:print:]]*)", regex_constants::icase);
	smatch m;
	bool flag = std::regex_search(select_input, m, reg_input);
	cout << m[1] << "=" << endl;
	if (flag == true) {
		cout << "ok" << endl;
		string str = m[1];
		regex e("([[:w:]]+)[[:s:]]*=[[:s:]]*([[:w:]]+)");
		sregex_iterator pos(str.cbegin(), str.cend(), e);
		sregex_iterator end;
		vector<pair<string, string>> v_pair_condition;
		for (; pos != end; pos++) {
			v_pair_condition.push_back(
					pair<string, string>(pos->str(1), pos->str(2)));
		}
		t->removeRowFromDB(v_pair_condition);
	} else {
		cout << "Incorrect statement" << endl;
	}
}

void updateRow(shared_ptr<Table> &t) {

	cout << "Write update" << endl;
	string select_input;
	cin.ignore(256, '\n');
	getline(cin, select_input);
	std::transform(select_input.begin(), select_input.end(),
			select_input.begin(), ::toupper);
	regex reg_input(
			"update[[:s:]]+" + t->getName()
					+ "[[:s:]]+set([[:print:]]*)where([[:print:]]*)",
			regex_constants::icase);
	smatch m;
	bool flag = std::regex_search(select_input, m, reg_input);
	cout << m[1] << "=" << endl;
	if (flag == true) {
		cout << "ok" << endl;
		string str = m[1];
		regex e("([[:w:]]+)[[:s:]]*=[[:s:]]*([[:w:]]+)");
		sregex_iterator pos_u(str.cbegin(), str.cend(), e);
		sregex_iterator end_u;
		vector<pair<string, string>> v_pair_update;
		for (; pos_u != end_u; pos_u++) {
			std::cout << pos_u->str(1) << " " << pos_u->str(2) << endl;
			v_pair_update.push_back(
					pair<string, string>(pos_u->str(1), pos_u->str(2)));
		}
		str = m[2];
		e = "([[:w:]]+)[[:s:]]*=[[:s:]]*([[:w:]]+)";
		sregex_iterator pos_c(str.cbegin(), str.cend(), e);
		sregex_iterator end_c;
		vector<pair<string, string>> v_pair_condition;
		for (; pos_c != end_c; pos_c++) {
			std::cout << pos_c->str(1) << " " << pos_c->str(2) << endl;
			v_pair_condition.push_back(
					pair<string, string>(pos_c->str(1), pos_c->str(2)));
		}
		t->updateRowFromDB(v_pair_update, v_pair_condition);
	} else {
		cout << "Incorrect statement" << endl;
	}
}
