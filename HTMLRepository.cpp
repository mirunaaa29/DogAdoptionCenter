#include <fstream>
#include "HTMLRepository.h"

HTMLRepository::HTMLRepository(vector<Dog>& adoption_list, std::string user_filename) : UserRepository(adoption_list) {
	this->user_filename = user_filename;
	this->adoption_list = adoption_list;
}

vector<Dog>& HTMLRepository::get_adoption_list() {
	return this->adoption_list;
}

int HTMLRepository::get_number_of_adopted_dogs() {
	return this->adoption_list.size();
}

void HTMLRepository::add_dog_to_adoption_list(Dog& dog_to_add) {
	this->adoption_list.push_back(dog_to_add);
	this->write_to_file();
}

string& HTMLRepository::get_user_filename() {
	return this->user_filename;
}

void HTMLRepository::write_to_file() {
	ofstream fout(this->user_filename);
	fout << "<!DOCTYPE html>\n";
	fout << "<html><head><title>Adoption List</title></head><body>\n";
	fout << "<table border=\"1\">\n";
	fout << "<tr><td>Breed</td><td>Name</td><td>Age</td><td>Link</td></tr>\n";
	for (auto& dog : this->adoption_list) {
		fout << "<tr>\n";
		fout << "<td>" << dog.get_breed() << "</td>\n";
		fout << "<td>" << dog.get_name() << "</td>\n";
		fout << "<td>" << dog.get_age() << "</td>\n";
		fout << "<td><a href=\"" << dog.get_link_to_photograph() << "\">Link</a></td>\n";
		fout << "</tr>\n";
	}
	fout << "</table></body></html>";
	fout.close();
}

HTMLRepository::~HTMLRepository() = default;