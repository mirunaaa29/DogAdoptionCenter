#include "CSVRepository.h"
#include <fstream>

CSVRepository::CSVRepository(std::vector<Dog>& adoption_list, std::string user_filename) : UserRepository(adoption_list) {
	this->user_filename = user_filename;
	this->adoption_list = adoption_list;
}

std::vector<Dog>& CSVRepository::get_adoption_list() {
	return this->adoption_list;
}

int CSVRepository::get_number_of_adopted_dogs() {
	return this->adoption_list.size();
}

void CSVRepository::add_dog_to_adoption_list(Dog& dog_to_add) {
	this->adoption_list.push_back(dog_to_add);
	this->write_to_file();
}

std::string& CSVRepository::get_user_filename() {
	return this->user_filename;
}

void CSVRepository::write_to_file() {
	ofstream fout(this->user_filename);
	if (!this->adoption_list.empty()) {
		for (auto& dog : this->adoption_list) {
			fout << dog << "\n";
		}
	}
	fout.close();
}

CSVRepository::~CSVRepository() = default;