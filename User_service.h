#pragma once
#include "user_repository.h"
#include "Repository.h"
#include <algorithm>
#include <string>  
#include <vector>

class UserService {
private:
	Repository& repository;
	UserRepository* user_repository;
public:
	explicit UserService(Repository& repository);

	UserService(Repository& repo, UserRepository* user_repo);

	vector<Dog>& get_adoption_list();

	int get_number_of_adopted_dogs();

	void add_dog_to_adoption_list(Dog dog_to_add);

	void filter_dog_data(vector<Dog>& dogs_that_validate_conditions, int age_condition, string name_codititon);

	void repository_type(string& file_type);

	string& get_user_filename();

	~UserService();

};
