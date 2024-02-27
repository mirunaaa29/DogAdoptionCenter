#pragma once
#include "Repository.h"
#include "Service.h"
#include <cassert>

class FakeRepository: public Repository {
private:
	std::vector<Dog> dogs;
public:
	FakeRepository(std::vector<Dog> data);
	bool add_dog_to_repository_data(Dog& dog) override {
		//dogs.push_back(dog);
		return true;
	}
	int get_number_of_items_in_repository() override {
		return 1;
	}
};

void test_add_function() {
	std::vector<Dog> dogs;
	FakeRepository repository(dogs);
	Service service(repository);

	service.add_dog("bichon", "Rex", 2, "https://www.new_dog_rex.com");
	assert(service.get_number_of_dogs() == 1);
}