#pragma once
#include <string>
using namespace std;

class Dog {
private:
	std::string breed;
	std::string name;
	int age;
	std::string link_to_photograph;
public:



	Dog();

	Dog(string dog_breed, string dog_name, int dog_age, string dog_link_to_photograph);

	string get_name();

	string get_breed();

	int get_age();

	string get_link_to_photograph();

	string to_string();

	friend std::istream& operator>>(std::istream& input_stream, Dog& dog_to_read);
	friend std::ostream& operator<<(std::ostream& output_stream, const  Dog& dog_to_write);

};

