#pragma once
#include "Repository.h"
#include <string>
using namespace std;

class Service {
private:
	Repository& repository;
public:

	Service(Repository& repository);

	vector<Dog> get_all_service_data();

	int get_number_of_dogs();

	bool add_dog(string breed, string name, int age, string link_to_photography);

	bool delete_dog(string name_of_dog_to_delete);

	Dog get_dog(int position);

	bool update_dog_information(string name_of_dog_to_update, string new_breed, string new_name, int new_age, string new_link);

};


