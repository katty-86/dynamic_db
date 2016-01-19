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

bool DB::insert(SQL &s) {
	auto it_table = tables.find(s.tablename);
	if (it_table == tables.end()) {
		std::cout << "table not found" << std::endl;
		return false;
	}
	std::shared_ptr<Table> ptr_table = std::move(((*it_table).second));
	if (ptr_table->checkIfVecConfigEmpty() == false) {
		ptr_table->addRow(s.expression);
	}
	return true;
}

bool DB::select(SQL &s) {
	auto it_table = tables.find(s.tablename);
	if (it_table == tables.end()) {
		std::cout << "table not found" << std::endl;
		return false;
	}
	std::shared_ptr<Table> ptr_table = std::move(((*it_table).second));
	if (s.flag_all == true) {
		if (s.where_condition.empty() == true) {
			this->printTable(s.tablename);
		} else {
			//TODO: copy_if!
			list<Record> lis_result = ptr_table->findMatchingRow(
					s.where_condition);
			for (auto i = lis_result.begin(); i != lis_result.end(); ++i) {
				cout << *i << endl;
			}
		}
		return true;
	} else if (s.flag_count == true) {
		if (s.where_condition.empty() == true) {
			cout << ptr_table->sizeListData() << endl;
		} else {
			cout << ptr_table->countMatchingRow(s.where_condition) << endl;
		}
		return true;
	} else {
		cout << "not supported:)" << endl;
		return false;
		//cout<<t->findMatchingRowAccordingExpression(s.expression, s.where_condition);
		//TODO check if param is ok
		//specify column which can be printed
	}

}

bool DB::deleteRow(SQL &s) {
	auto it_table = tables.find(s.tablename);
	if (it_table == tables.end()) {
		std::cout << "table not found" << std::endl;
		return false;
	}
	std::shared_ptr<Table> ptr_table = std::move(((*it_table).second));
	if (s.where_condition.empty() == true) {
		ptr_table->removeAllFromDB();
	} else {
		ptr_table->removeRowFromDB(s.where_condition);
	}
	return true;
}

bool DB::updateRow(SQL &s) {
	auto it_table = tables.find(s.tablename);
	if (it_table == tables.end()) {
		std::cout << "table not found" << std::endl;
		return false;
	}
	std::shared_ptr<Table> ptr_table = std::move(((*it_table).second));
	if (s.where_condition.empty() == true) {
		ptr_table->updateAllFromDB(s.expression);
	} else {
		ptr_table->updateRowFromDB(s.expression, s.where_condition);
	}
	return true;
}
/*
 *TODO for current state during recreation table  shared ptr is deleted
 */
bool DB::createTable(const std::string &f,
		const std::vector<std::pair<std::string, std::string>> &values) {
	if (findIfTableExist(f) == true) {
		cout << "Table exist" << endl;
		return false;
	}
	std::unique_ptr<Table> ptr_table(new Table);
	ptr_table->setName(f);
	for (auto &i : values) {
		ptr_table->addConfigField(i.first, i.second);
	}

	return true;
}

bool DB::printTable(const string &tablename) {
	auto it_table = tables.find(tablename);
	if (it_table == tables.end()) {
		std::cout << "table not found" << std::endl;
		return false;
	}
	std::shared_ptr<Table> ptr_table = std::move(((*it_table).second));
	if (ptr_table->describeTable()) {
		ptr_table->printData();
	} else {
		std::cout << "Table does not exist" << std::endl;
		return false;
	}
	return true;
}

/*
 * TODO check if there is sth in db - now only one db so I only check one table.
 *
 */
bool DB::empty(const string &tablename) {
	auto it_table = tables.find(tablename);
	if (it_table == tables.end()) {
		std::cout << "table not found" << std::endl;
		return false;
	}
	std::shared_ptr<Table> ptr_table = std::move(((*it_table).second));
	return ptr_table->empty();
}

const std::vector<FieldConfig> DB::getFieldConfig(const string &tablename) {
	auto it_table = tables.find(tablename);
	/*	if (it_table == tables.end()) {
	 std::cout << "table not found" << std::endl;
	 return nullptr;
	 }*/
	std::shared_ptr<Table> ptr_table = std::move(((*it_table).second));
	return ptr_table->getVec_config();
}

bool DB::writaData(const string &tablename, const std::string &filename) {
	if (tablename == "") {
		//TODO: wrie all not done
		return false;
	}
	auto it_table = tables.find(tablename);
	if (it_table == tables.end()) {
		std::cout << "table not found" << std::endl;
		return false;
	}
	std::shared_ptr<Table> ptr_table = std::move(((*it_table).second));
	std::ofstream myfile;
	std::vector<FieldConfig> vec_config = ptr_table->getVec_config();
	std::list<Record> list_data = ptr_table->getList_data();
	myfile.open(filename);
	myfile << ptr_table->getName() << "|";
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
//TODO: write all db not done
std::string DB::readData(const std::string &filename) {
	std::string line;
	std::string tablename;
	std::ifstream myfile(filename);
	if (myfile.is_open()) {
		getline(myfile, line);
		int pos = line.find('|');
		tablename = line.substr(0, pos);
		std::transform(tablename.begin(), tablename.end(), tablename.begin(),
				::toupper);

		if (tables.find(tablename) != tables.end()) {
			return "";
		}
		line.erase(0, pos + 1);
		pos = line.find('|');
		std::string config = line.substr(0, pos);
		std::vector<std::pair<std::string, std::string>> values;
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
			values.push_back(std::pair<std::string, std::string>(type, name));
		} while (line != "|");
		values.shrink_to_fit();
		createTable(tablename, values);
		auto it_table = tables.find(tablename);
		std::shared_ptr<Table> ptr_table = std::move(((*it_table).second));
		while (getline(myfile, line)) {
			std::transform(line.begin(), line.end(), line.begin(), ::toupper);
			ptr_table->addRow(line);

		}
		myfile.close();
	} else {
		std::cout << "Unable to open file" << std::endl;
		return "";
	}
	return tablename;
}

/*std::string DB::getTableName(const string &tablename)const{
 return t->getName() ;
 }*/

bool DB::findIfTableExist(string tablename) {
	auto search = this->tables.find(tablename);
	if (search != end(tables)) {
		return true;
	}
	return false;
}

bool DB::addTableToDB(Table &t) {
	shared_ptr<Table> test(std::move(new Table(t)));
	auto ret = tables.insert(
			std::pair<std::string, shared_ptr<Table>>(t.getName(), test));
	if (ret.second == false) {
		std::cout << "Table exist not created" << endl;
	}
	return true;

}
bool DB::deleteTableFromDB(std::string tablename) {
	//0--false
	//non zero = true
	return tables.erase(tablename);

}
