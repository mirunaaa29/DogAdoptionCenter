#include "User_service.h"
#include <iterator>
#include "CSVRepository.h"
#include "HTMLRepository.h"


UserService::UserService(Repository& repo, UserRepository* user_repo) : repository(repo) {
    this->user_repository = user_repo;
}

UserService::UserService(Repository& repo) : repository(repo) {
    this->user_repository = nullptr;
}

vector<Dog>& UserService::get_adoption_list() {
    return this->user_repository->get_adoption_list();
}

int UserService::get_number_of_adopted_dogs() {
    return this->user_repository->get_number_of_adopted_dogs();
}

void UserService::add_dog_to_adoption_list(Dog dog_to_add) {
    this->user_repository->add_dog_to_adoption_list(dog_to_add);
    // delete the dog from repository, now that it was adopted
    this->repository.delete_dog_from_repository(dog_to_add.get_name());
}

void UserService::filter_dog_data(vector<Dog>& dogs_that_validate_conditions, int age_condition, string breed_condition) {
    auto all_dogs = this->repository.get_all_repository_data();
    if (breed_condition.empty()) {
        copy_if(all_dogs.begin(), all_dogs.end(), back_inserter(dogs_that_validate_conditions),
            [age_condition](Dog& dog) {
                return dog.get_age() < age_condition;
            });
    }
    else {
        copy_if(all_dogs.begin(), all_dogs.end(), back_inserter(dogs_that_validate_conditions),
            [age_condition, breed_condition](Dog& dog) {
                return dog.get_age() < age_condition && dog.get_breed() == breed_condition;
            });
    }
}

string& UserService::get_user_filename() {
    return this->user_repository->get_user_filename();
}

void UserService::repository_type(string& file_type) {
    if (file_type == "CSV") {
        vector<Dog> user_vector;
        string file_name = "AdoptionList.csv";
        auto* user_repo = new CSVRepository(user_vector, file_name);
        this->user_repository = user_repo;
    }
    else if (file_type == "HTML") {
        vector<Dog> user_vector;
        string file_name = "AdoptionList.html";
        auto* user_repo = new HTMLRepository(user_vector, file_name);
        this->user_repository = user_repo;
    }
}

UserService::~UserService() {
    delete this->user_repository;
}