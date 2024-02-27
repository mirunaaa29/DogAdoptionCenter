#include "user_repository.h"

UserRepository::UserRepository(vector<Dog>& vector_adoption_list) {
	this->adoption_list = vector_adoption_list;
}

UserRepository::~UserRepository() = default;
