/*
 * Serializer.cpp
 *
 *  Created on: Dec 17, 2015
 *      Author: kaky
 */

#include "Serializer.h"

Serializer::Serializer() {
	// TODO Auto-generated constructor stub

}

Serializer::~Serializer() {
	// TODO Auto-generated destructor stub
}

bool Serializer::writaData(std::shared_ptr<Table> &t,const std::string &filename) {
	std::vector<FieldConfig> vec_c = t->getVec_config();
	std::list<Record> list_d = t->getList_data();
	std::ofstream myfile;
	myfile.open(filename);
	myfile << t->getName() << "|";
	for (auto it = vec_c.begin(); it != vec_c.end(); ++it) {
		myfile << *it << " ";
	}
	myfile << "|\n";

	for (auto it = list_d.begin(); it != list_d.end(); ++it) {
		myfile << *it << "\n";
	}
	myfile.close();
	return true;
}

bool Serializer::readData(std::shared_ptr<Table> &t, const std::string &filename) {
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
		t->createTable(filename, values);
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
