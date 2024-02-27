#pragma once
#include <vector>
#include "Dog.h"
using namespace std;

class UserRepository {
protected:
	vector<Dog> adoption_list;
	string user_filename;

public:
	explicit UserRepository(vector<Dog>& dynamic_vector_adoption_list);

	virtual vector<Dog>& get_adoption_list() = 0;
	virtual int get_number_of_adopted_dogs() = 0;
	virtual void add_dog_to_adoption_list(Dog& dog_to_add) = 0;
	virtual void write_to_file() = 0;
	virtual string& get_user_filename() = 0;

	~UserRepository();
};

