#pragma once
#include "user_repository.h"

class CSVRepository : public UserRepository
{
public:
	CSVRepository(std::vector<Dog>& adoption_list, std::string user_filename);
	std::vector<Dog>& get_adoption_list() override;
	int get_number_of_adopted_dogs() override;
	void add_dog_to_adoption_list(Dog& dog_to_add) override;
	void write_to_file() override;
	std::string& get_user_filename() override;
	~CSVRepository();
};
