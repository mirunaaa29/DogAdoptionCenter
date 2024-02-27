#pragma once
#pragma once
#include "Service.h"
#include "User_service.h"
#include "Validator.h"
#include <string.h>

class Ui {
private:
	Service& service;
	UserService& user_service;
	DogValidator& validator;
public:

	Ui(Service& service, UserService& user_service, DogValidator& validator);

	void print_all_dogs();

	void add_dog();

	void delete_dog();

	void update_dog_information();

	void print_menu_for_administrator();

	void start_administrator_mode();

	void start_listing_adoption_list();

	void start_listing_filtered_adoption_list();

	void openFile();

	void print_user_menu();

	void start_user_mode();

	void start_aplication();

};