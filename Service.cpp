#include "Service.h"

Service::Service(Repository& repo) : repository(repo) {
}

vector<Dog> Service::get_all_service_data() {
	return this->repository.get_all_repository_data();
}

int Service::get_number_of_dogs() {
	return this->repository.get_number_of_items_in_repository();
}

Dog Service::get_dog(int position) {
	return this->repository.get_dog_from_position(position);
}
bool Service::add_dog(string breed, string name, int age, string link_to_photograph) {
	Dog dog_to_add(breed, name, age, link_to_photograph);
	if (this->repository.add_dog_to_repository_data(dog_to_add))
		return true; //return true for success
	else
		return false;
}

bool Service::delete_dog(string name_of_dog_to_delete) {
	this->repository.delete_dog_from_repository(name_of_dog_to_delete);
	return true; //return 0 for success
}

bool Service::update_dog_information(string name_of_dog_to_update, string new_breed, string new_name, int new_age, string new_link) {
	this->repository.update_dog_information(name_of_dog_to_update, new_breed, new_name, new_age, new_link);
	return true;
}
