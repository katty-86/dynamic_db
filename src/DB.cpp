/*
 * DB.cpp
 *
 *  Created on: Jan 11, 2016
 *      Author: kaky
 */

#include "DB.h"



DB::DB() {
	t = make_shared<Table>();
}

DB::~DB() {
	// TODO Auto-generated destructor stub
}

void DB::insert( SQL &s) {
	if (t->checkIfVecConfigEmpty() == false){
		t->addRow(s.expression);
	}
}

void DB::select(SQL &s) {

	if (s.flag_all == true) {
		if (s.where_condition.empty() == true) {
			this->printTable();
		} else {
			list<Record> lis_result = t->findMatchingRow(s.where_condition);
			for (auto i = lis_result.begin(); i != lis_result.end(); ++i) {
				cout << *i << endl;
			}
		}

	} else if (s.flag_count == true) {
		if (s.where_condition.empty() == true) {
			cout << t->sizeListData() << endl;
		} else {
			cout << t->countMatchingRow(s.where_condition) << endl;
		}
	} else {
		cout << "not supported:)" << endl;
		//cout<<t->findMatchingRowAccordingExpression(s.expression, s.where_condition);
		//TODO check if param is ok
		//specify column which can be printed
	}

}

void DB::deleteRow( SQL &s) {

	if (s.where_condition.empty() == true) {
		t->removeAllFromDB();
	} else {
		t->removeRowFromDB(s.where_condition);
	}

}

void DB::updateRow( SQL &s) {

	if (s.where_condition.empty() == true) {
		t->updateAllFromDB(s.expression);
	} else {
		t->updateRowFromDB(s.expression, s.where_condition);
	}
}
/*
 *TODO for current state during recreation table  shared ptr is deleted
 */
void DB::createTable(const std::string &f,
		const std::vector<std::pair<std::string, std::string>> &values) {
	if(t->empty()!=true){
		t.reset(new Table);
	}
	t->setName(f);
		for (auto &i : values) {
			t->addConfigField(i.first, i.second);
		}
	this->printTable();
}


void DB::printTable() {
	if(t->describeTable()){
		t->printData();
	} else {
		std::cout << "Table does not exist" << std::endl;
	}
}

/*
 * TODO check if there is sth in db - now only one db so I only check one table.
 *
*/
bool DB::empty(){
	return t->empty();
}


const std::vector<FieldConfig> DB::getFieldConfig(){
	return t->getVec_config();
}


bool DB::writaData(const std::string &filename) {
	if(t->empty()){
		return false;
	}
	std::ofstream myfile;
	std::vector<FieldConfig> vec_config =getFieldConfig();
	std::list<Record> list_data=t->getList_data();
	myfile.open(filename);
	myfile << t->getName() << "|";
	for (auto it = begin(vec_config); it != end(vec_config); ++it) {
		myfile << *it << " ";
	}
	myfile << "|\n";

	for (auto it = begin(list_data); it != end(list_data); ++it) {
		myfile << *it << "\n";
	}
	myfile.close();
	return true;
}
//add additional checking
bool DB::readData(const std::string &filename) {
	std::string line;
	std::string tablename;
	std::ifstream myfile(filename);
	if (myfile.is_open()) {
		getline(myfile, line);
		int pos = line.find('|');
		tablename = line.substr(0, pos);
		std::transform(tablename.begin(), tablename.end(), tablename.begin(), ::toupper);
		line.erase(0, pos + 1);
		pos = line.find('|');
		std::string config = line.substr(0, pos);
		std::vector<std::pair <std::string, std::string>> values;
		do {
			std::string type, name;
			pos = line.find('[');
			name = line.substr(0, pos);
			line.erase(0, pos + 1);
			pos = line.find("]: ");
			type = line.substr(0, pos);
			line.erase(0, pos + 3); //deleting "]: "
			std::transform(type.begin(), type.end(), type.begin(), ::toupper);
			std::transform(name.begin(), name.end(), name.begin(), ::toupper);
			values.push_back(std::pair <std::string, std::string>(type, name));
		} while (line != "|");
		values.shrink_to_fit();
		createTable(filename, values);
		while (getline(myfile, line)) {
			std::transform(line.begin(), line.end(), line.begin(), ::toupper);
			t->addRow(line);

		}
		myfile.close();
	} else {
		std::cout << "Unable to open file" << std::endl;
		return false;
	}
	return true;
}

std::string DB::getTableName()const{
	return t->getName() ;
}

