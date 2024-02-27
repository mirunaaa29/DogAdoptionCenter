#include <QtWidgets/QApplication>
#include "GUI.h"
#include "Repository.h"
#include "Service.h"
#include "Validator.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    std::vector<Dog> adminRepositoryVector;
    adminRepositoryVector.reserve(10);
    std::string file_name = "dogs.txt";
    Repository repository(adminRepositoryVector, file_name);
    repository.initialize_dogs_data_in_repository();
    Service service(repository);
    UserService user_service(repository);
    DogValidator validator;

    GUI gui(service, user_service, validator, repository);
    gui.show();
    return a.exec();
}
