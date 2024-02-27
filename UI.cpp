#include "Ui.h"
#include <iostream>
#define EXIT_OPTION 0
using namespace std;

Ui::Ui(Service& service_to_set, UserService& user_service_to_set, DogValidator& validator_to_set) : service(service_to_set), user_service(user_service_to_set), validator(validator_to_set) {
}

void Ui::print_all_dogs() {
	vector<Dog> all_dogs = this->service.get_all_service_data();
	for (auto& dog : all_dogs) {
		cout << dog.to_string() << endl;
	}

}

void Ui::add_dog() {
	string breed;
	string name;
	int age;
	string link_to_photograph;

	while (true) {
		//VALIDATE DATA
		try {
			cout << "Enter the breed: " << endl;

			getline(cin, breed);
			this->validator.validate_breed(breed);
			break;
		}
		catch (ValidationException& ex) {
			cout << ex.what() << endl;
		}
	}
	while (true) {
		try {
			cout << "Enter the name: " << endl;
			getline(cin, name);
			this->validator.validate_name(name);
			break;
		}
		catch (ValidationException& ex) {
			cout << ex.what() << endl;
		}
	}
	while (true) {
		try {
			cout << "Enter age: " << endl;
			cin >> age;
			this->validator.validate_age(age);
			break;
		}
		catch (ValidationException& ex) {
			cout << ex.what() << endl;
		}
	}
	while (true) {
		try {
			cout << "Enter the phothograph link: " << endl;
			//cin.ignore();
			getline(cin, link_to_photograph);
			this->validator.validate_photo_link(link_to_photograph);
			break;
		}
		catch (ValidationException& ex) {
			cout << ex.what() << endl;
		}
	}
	bool dog_was_added = this->service.add_dog(breed, name, age, link_to_photograph);
	cout << "Dog was added!" << endl;
}

void Ui::delete_dog() {
	string name_of_dog_to_delete;
	while (true) {
		//VALIDATE NAME
		try {
			cout << "Enter the dog name that you want to delete: " << endl;
			//cin.ignore();
			getline(cin, name_of_dog_to_delete);
			this->validator.validate_name(name_of_dog_to_delete);
			break;
		}
		catch (ValidationException& ex) {
			cout << ex.what() << endl;
		}
	}
	bool dog_was_deleted = this->service.delete_dog(name_of_dog_to_delete);
	cout << "Dog deleted!";
}

void Ui::update_dog_information() {
	string old_name;
	while (true) {
		try {
			cout << "Enter the name of the dog that you want to update informations for: " << endl;
			//cin.ignore();
			getline(cin, old_name);
			this->validator.validate_name(old_name);
			break;
		}
		catch (ValidationException& ex) {
			cout << ex.what() << endl;
		}
	}

	string new_breed;
	string new_name;
	int new_age;
	string new_link_to_photograph;

	// VALIDATE DATA
	while (true) {
		try {
			cout << "Enter the new breed: " << endl;
			getline(cin, new_breed);
			this->validator.validate_breed(new_breed);
			break;
		}
		catch (ValidationException& ex) {
			cout << ex.what() << endl;
		}
	}

	while (true) {
		try {
			cout << "Enter the new name: " << endl;
			getline(cin, new_name);
			this->validator.validate_name(new_name);
			break;
		}
		catch (ValidationException& ex) {
			cout << ex.what() << endl;
		}
	}

	while (true) {
		try {
			cout << "Enter new age: " << endl;
			cin >> new_age;
			this->validator.validate_age(new_age);
			break;
		}
		catch (ValidationException& ex) {
			cout << ex.what() << endl;
		}
	}

	while (true) {
		try {
			cout << "Enter the new phothograph link: " << endl;
			//cin.ignore();
			getline(cin, new_link_to_photograph);
			this->validator.validate_photo_link(new_link_to_photograph);
			break;
		}
		catch (ValidationException& ex) {
			cout << ex.what() << endl;
		}
	}

	bool successfull_update = this->service.update_dog_information(old_name, new_breed, new_name, new_age, new_link_to_photograph);
	cout << "Dog information updated!" << endl;
}

void Ui::print_menu_for_administrator() {
	cout << "~ADMINISTRATOR MODE~" << endl;
	cout << "1. Add dog " << endl;
	cout << "2. Update dog information " << endl;
	cout << "3. Delete dog" << endl;
	cout << "4. Display all dogs" << endl;
	cout << "0. Exit administrator mode" << endl;
	cout << ">>" << endl;
}

void Ui::start_administrator_mode() {
	const int ADD_OPTION = 1;
	const int DELETE_OPTION = 3;
	const int UPDATE_OPTION = 2;
	const int PRINT_ALL_DOGS_OPTION = 4;
	int user_input;
	while (true) {
		try {
			print_menu_for_administrator();
			cin >> user_input;
			if (user_input == ADD_OPTION) {
				this->add_dog();
			}
			else if (user_input == DELETE_OPTION) {
				this->delete_dog();
			}
			else if (user_input == UPDATE_OPTION) {
				this->update_dog_information();
			}
			else if (user_input == PRINT_ALL_DOGS_OPTION) {
				this->print_all_dogs();
			}
			else if (user_input == EXIT_OPTION) {
				return;
			}
			else {
				cout << "Command does not exists!" << endl;
			}
		}
		catch (ValidationException& ex) {
			cout << ex.what() << endl;
		}
		catch (RepositoryException& ex) {
			cout << ex.what() << endl;
		}
	}
}

void Ui::start_listing_adoption_list() {
	const int NO_DOGS_LEFT = 0;
	string user_option;
	bool stop_listing = false;
	int index = 0;
	int number_of_available_dogs = this->service.get_number_of_dogs();
	bool clean_buffer = true;
	while (!stop_listing) {
		if (index == number_of_available_dogs)
			index = 0; //start again from 0

		cout << this->service.get_dog(index).to_string();
		cout << endl;
		cout << "Adopt? [Yes/No/Exit]" << endl;
		string link = string("start ").append(this->service.get_dog(index).get_link_to_photograph());
		system(link.c_str());
		if (clean_buffer) {
			cin.ignore();
			clean_buffer = false;
		}

		getline(cin, user_option);
		if (user_option == "Yes" || user_option == "yes") {
			Dog dog_to_adopt = this->service.get_dog(index);
			this->user_service.add_dog_to_adoption_list(dog_to_adopt);
			number_of_available_dogs -= 1;
		}
		else if (user_option == "No" || user_option == "no") {
			index++;
		}
		else if (user_option == "Exit" || user_option == "exit") {
			stop_listing = true;
		}
		else {
			cout << "Enter a valid option!" << endl;
		}
		if (number_of_available_dogs == NO_DOGS_LEFT) {
			stop_listing = true;
		}
	}
}

void Ui::start_listing_filtered_adoption_list() {
	cout << "Input the breed that you want tos search for: ";
	cin.ignore();
	string breed_to_search_for;
	getline(cin, breed_to_search_for);
	cout << endl << "Input the age: ";
	int age_condition;
	cin >> age_condition;
	string user_option;
	bool stop_listing = false;
	int index = 0;
	vector<Dog> dogs_that_validate_conditions;
	this->user_service.filter_dog_data(dogs_that_validate_conditions, age_condition, breed_to_search_for);
	int number_of_available_dogs = dogs_that_validate_conditions.size();
	while (!stop_listing) {
		if (number_of_available_dogs == 0) {
			throw "No dogs to adopt";
		}
		if (index == number_of_available_dogs)
			index = 0; //start again from 0

		cout << dogs_that_validate_conditions[index].to_string();
		cout << endl;
		cout << "Adopt? [Yes/No/Exit]" << endl;
		string link = string("start ").append(dogs_that_validate_conditions[index].get_link_to_photograph());
		system(link.c_str());
		getline(cin, user_option);
		if (user_option == "Yes" || user_option == "yes") {
			Dog dog_to_adopt = this->service.get_dog(index);
			this->user_service.add_dog_to_adoption_list(dog_to_adopt);
			number_of_available_dogs -= 1;
		}
		else if (user_option == "No" || user_option == "no") {
			index++;
		}
		else if (user_option == "Exit" || user_option == "exit") {
			stop_listing = true;
		}
		else {
			cout << "Enter a valid option" << endl;
		}
		if (number_of_available_dogs == 0) {
			stop_listing = true;
			cout << "No dogs left for adoption" << endl;
		}
	}
}

void Ui::openFile() {
	string link = string("start ").append(this->user_service.get_user_filename());
	system(link.c_str());
}

void Ui::print_user_menu() {

	cout << endl << "USER MENU: " << endl;
	cout << "0. Exit." << endl;
	cout << "1. See all the dogs avalaible for adoption" << endl;
	cout << "2. See all the dogs of a given breed, having an age less than a given number." << endl;
	cout << "3. See the adoption list." << endl;
	cout << "4. Open the adoption list file." << endl;
	cout << "Input option: " << endl;
}

void Ui::start_user_mode() {
	const int PRINT_ADOPTION_LIST = 3;
	const int DISPLAY_DOGS_FOR_ADOPTION = 1;
	const int FILTER_DOGS = 2;
	const int OPEN_FILE = 4;
	while (true) {
		try {
			print_user_menu();
			int user_menu_option;
			cin >> user_menu_option;
			if (user_menu_option == EXIT_OPTION) {
				return;
			}
			else if (user_menu_option == DISPLAY_DOGS_FOR_ADOPTION) {
				this->start_listing_adoption_list();
			}
			else if (user_menu_option == PRINT_ADOPTION_LIST) {
				vector<Dog> adoption_list = this->user_service.get_adoption_list();
				for (Dog dog : adoption_list) {
					cout << dog.to_string() << endl;
				}
			}
			else if (user_menu_option == OPEN_FILE) {
				this->openFile();
			}
			else if (user_menu_option == FILTER_DOGS) {
				this->start_listing_filtered_adoption_list();
			}
		}
		catch (ValidationException& ex) {
			cout << ex.what() << endl;
		}
		catch (RepositoryException& ex) {
			cout << ex.what() << endl;
		}
	}
}

void Ui::start_aplication() {
	const int ADMINISTRATOR_MODE = 1;
	const int USER_MODE = 2;
	while (true) {
		cout << "1.Administrator mode" << endl;
		cout << "2. User mode" << endl;
		cout << "0. Exit aplication" << endl;
		int user_option;
		cin >> user_option;
		if (user_option == ADMINISTRATOR_MODE) {
			this->start_administrator_mode();
		}
		else if (user_option == USER_MODE) {
			cout << "Enter the file type in which you want to save the adoption list(HTML or CSV)" << endl;
			string file_type;
			cin >> file_type;
			this->user_service.repository_type(file_type);
			this->start_user_mode();
		}
		else if (user_option == EXIT_OPTION) {
			return;
		}
		else {
			cout << "Invalid command!";
		}
	}
}
