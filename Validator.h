#pragma once
#include <string>
#include "Dog.h"
#include <exception>

class ValidationException : public std::exception {
private:
	std::string message;
public:
	ValidationException(std::string& message);
	const char* what() const noexcept override;

};

class DogValidator {
public:
	DogValidator();

	void validate_breed(std::string& breed);

	void validate_name(std::string& name);

	void validate_age(int age);

	void validate_photo_link(std::string& photo_link);


};