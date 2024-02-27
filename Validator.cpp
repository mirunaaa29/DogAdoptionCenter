#include "Validator.h"
#include <iostream>

ValidationException::ValidationException(std::string& message) {
	this->message = message;
}

const char* ValidationException::what() const noexcept {
	return this->message.c_str();
}

DogValidator::DogValidator() = default;

void DogValidator::validate_breed(std::string& breed) {
	if (breed.empty()) {
		std::string error_message = "Breed cannot be empty!";
		throw ValidationException(error_message);
	}
}

void DogValidator::validate_name(std::string& name) {
	std::string errors;
	if (name.empty()) {
		errors += "Name cannot be empty!\n";
	}
	if (!isupper(name[0])) {
		std::cout << name[0];
		errors += "Name must start with an uppercase letter!\n";
	}
	if (name.size() < 3) {
		errors += "Name must have at least 3 characters!\n";
	}
	if (errors.size() > 0) {
		throw ValidationException(errors);
	}
}

void DogValidator::validate_age(int age) {
	std::string errors;
	if (age < 0) {
		errors += "Age cannot be negative!\n";
	}
	if (errors.size() > 0) {
		throw ValidationException(errors);
	}
}

void DogValidator::validate_photo_link(std::string& photo_link) {
	std::string errors;
	if (photo_link.empty()) {
		errors += "Photo link cannot be empty!\n";
	}
	if (photo_link.find("http") != 0) {
		errors += "Photo link must start with http!\n";
	}
	if (errors.size() > 0) {
		throw ValidationException(errors);
	}
}