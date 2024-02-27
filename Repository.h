#pragma once
#include "Dog.h"
#include <string>
#include<vector>
using namespace std;

class Repository {
private:
	vector<Dog> data;
	string file_name;
public:
	Repository();

	Repository(vector<Dog>& repository_vector, string& file_name);

	void load_dogs_data_from_file();

	void save_dogs_data_to_file();

	vector<Dog>& get_all_repository_data();

	int virtual get_number_of_items_in_repository();

	bool virtual add_dog_to_repository_data(Dog& dog_to_add);

	void delete_dog_from_repository(string name);

	void update_dog_information(string name_of_dog_to_update, string new_breed, string new_name, int new_age, string new_link);

	int find_dog_by_name(string name_to_find);

	Dog get_dog_from_position(int position);

	void initialize_dogs_data_in_repository();

};

class RepositoryException : public exception {
private:
	string message;
public:
	RepositoryException(string& message);
	const char* what() const noexcept override;
};
