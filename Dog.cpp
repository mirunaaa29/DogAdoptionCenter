#include "Dog.h"
#include<vector>
#include<sstream>

using namespace std;

Dog::Dog()
{
	breed = "";
	name = "";
	age = 0;
	link_to_photograph = "";
}

Dog::Dog(string dog_breed, string dog_name, int dog_age, string dog_link_to_photograph) :
	breed{ dog_breed }, name{ dog_name }, age{ dog_age }, link_to_photograph{ dog_link_to_photograph }
{
}

string Dog::get_name() {
	return name;
}

string Dog::get_breed() {
	return breed;
}

int Dog::get_age() {
	return age;
}

string Dog::get_link_to_photograph() {
	return link_to_photograph;
}

string Dog::to_string() {
	string string_age = std::to_string(age);
	return this->breed + " | " + this->name + " | " + string_age + " | " + this->link_to_photograph;
}

std::vector<std::string> tokenize(const std::string& str, char delimiter) {
	std::vector<std::string> result;
	std::stringstream ss(str);
	std::string token;
	while (getline(ss, token, delimiter))
		result.push_back(token);

	return result;
}

std::istream& operator>>(std::istream& input_stream, Dog& dog_to_read) {
	string line;
	getline(input_stream, line);
	vector<string> tokens = tokenize(line, ',');
	if (tokens.size() != 4)
		return input_stream;
	dog_to_read.breed = tokens[0];
	dog_to_read.name = tokens[1];
	dog_to_read.age = stoi(tokens[2]);
	dog_to_read.link_to_photograph = tokens[3];
	return input_stream;
}

std::ostream& operator<<(std::ostream& output_stream, const Dog& dog_to_write) {
	output_stream << dog_to_write.breed << "," << dog_to_write.name << "," << to_string(dog_to_write.age) << "," << dog_to_write.link_to_photograph << "\n";
	return output_stream;
}

