#include "Repository.h"
#include <algorithm>
#include <fstream>

RepositoryException::RepositoryException(string& message) {
	this->message = message;
}

const char* RepositoryException::what() const noexcept {
	return message.c_str();
}

Repository::Repository()
{
	this->file_name = "";
}

Repository::Repository(vector<Dog>& repository_vector, string& file_name) {
	this->data = repository_vector;
	this->file_name = file_name;

}

void Repository::load_dogs_data_from_file() {
	if (!this->file_name.empty()) {
		Dog dog_from_file;
		ifstream fin(this->file_name);
		while (fin >> dog_from_file) {
			if (find_dog_by_name(dog_from_file.get_name()) == -1)
				this->data.push_back(dog_from_file);
		}
		fin.close();
	}
}

void Repository::save_dogs_data_to_file() {
	if (!this->file_name.empty()) {
		ofstream fout(this->file_name);
		for (auto& dog : this->data) {
			fout << dog;
		}
		fout.close();
	}
}

vector<Dog>& Repository::get_all_repository_data() {
	if (this->data.empty()) {
		string error_message = "No data!";
		throw RepositoryException(error_message);
	}
	return data;
}

int Repository::get_number_of_items_in_repository() {
	if (this->data.empty()) {
		string error_message = "No data!";
		throw RepositoryException(error_message);
	}
	return data.size();
}

bool Repository::add_dog_to_repository_data(Dog& dog_to_add) {
	if (find_dog_by_name(dog_to_add.get_name()) != -1) {
		string error_message = "Dog already exists!";
		throw RepositoryException(error_message);
		return false;
	}
	else {
		data.push_back(dog_to_add);
		save_dogs_data_to_file();
		return true;
	}
}

void Repository::delete_dog_from_repository(string name_of_dog_to_delete) {
	int index_of_dog_to_delete = find_dog_by_name(name_of_dog_to_delete);
	if (index_of_dog_to_delete == -1) {
		string error_message = "Dog does not exist!";
		throw RepositoryException(error_message);
	}
	data.erase(data.begin() + index_of_dog_to_delete);
	save_dogs_data_to_file();
}

void Repository::update_dog_information(string name_of_dog_to_update, string new_breed, string new_name, int new_age, string new_link) {
	int index_of_dog_to_update = find_dog_by_name(name_of_dog_to_update);
	if (index_of_dog_to_update == -1) {
		string error_message = "Dog does not exist!";
		throw RepositoryException(error_message);
	}
	Dog dog_to_replace_with(new_breed, new_name, new_age, new_link);
	data[index_of_dog_to_update] = dog_to_replace_with;
	save_dogs_data_to_file();
}

int Repository::find_dog_by_name(string name_to_find) {
	auto find_iterator = find_if(data.begin(), data.end(), [name_to_find](Dog& dog_to_find) {return dog_to_find.get_name() == name_to_find; });
	if (find_iterator != data.end()) {
		return find_iterator - data.begin();
	}
	return -1;
}

Dog Repository::get_dog_from_position(int position) {
	return data.at(position);
}

void Repository::initialize_dogs_data_in_repository() {
	load_dogs_data_from_file();
}