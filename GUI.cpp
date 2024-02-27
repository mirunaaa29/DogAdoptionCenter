#include "GUI.h"
#include <QVBoxLayout>
#include <QFormLayout>
#include <QMessageBox>
#include <QPixmap>

GUI::GUI(Service& service, UserService& user_service, DogValidator& validator, Repository& repository) : service{ service }, user_service{ user_service }, validator{ validator }, repository{ repository } {
	this->main_title = new QLabel(this);
	this->subtitle = new QLabel(this);
	this->administrator_mode_button = new QPushButton(this);
	this->user_mode_button = new QPushButton(this);
	this->initGUI();
	this->connectSignalsAndSlots();
	this->resize(800,600);
}

void GUI::initGUI() {
	auto* main_layout = new QVBoxLayout(this);
	main_layout->setAlignment(Qt::AlignCenter);
	this->main_title->setText("Make a new friend!");
	this->main_title->setAlignment(Qt::AlignCenter);
	QFont title_font("Qeskile Voyage", 30, QFont::Bold);
	main_title->setFont(title_font);
	main_title->setStyleSheet("color: #263A29");

	this->subtitle->setText("Adopt a pet today");
	this->subtitle->setAlignment(Qt::AlignCenter);
	QFont subtitle_font("Qeskile Voyage", 24);
	subtitle->setFont(subtitle_font);
	subtitle->setStyleSheet("color: #41644A");

	//make buttons
	administrator_mode_button = new QPushButton("Administrator", this);
	administrator_mode_button->setFixedSize(180, 50);  // Set a fixed size for the button

	// Apply styles to the administrator mode button
	QString adminButtonStyle = "QPushButton {"
		"    background-color: #263A29;"
		"    color: white;"
		"    border-radius: 20px;"
		"    font-size: 20px;"
		"    font-family: Mirador;"
		"}"
		"QPushButton:hover {"
		"    background-color: #558F55;"
		"}";
	administrator_mode_button->setStyleSheet(adminButtonStyle);

	// Create the user mode button
	user_mode_button = new QPushButton(" User ", this);
	user_mode_button->setFixedSize(150, 50);  // Set a fixed size for the button

	// Apply styles to the user mode button
	QString userButtonStyle = "QPushButton {"
		"    background-color: #263A29;"
		"    color: white;"
		"    border-radius: 20px;"
		"    font-size: 20px;"
		"    font-family: Mirador;"
		"}"
		"QPushButton:hover {"
		"    background-color: #558F55;"
		"}";
	user_mode_button->setStyleSheet(userButtonStyle);
	QHBoxLayout* buttons_layout = new QHBoxLayout();
	buttons_layout->addWidget(administrator_mode_button);
	buttons_layout->addWidget(user_mode_button);

	// add to layout
	main_layout->addWidget(main_title);
	main_layout->addWidget(subtitle);
	main_layout->addSpacing(20);
	main_layout->addLayout(buttons_layout);
	setLayout(main_layout);
}

void GUI::connectSignalsAndSlots() {
	QObject::connect(this->administrator_mode_button, &QPushButton::clicked, this, &GUI::showAdmin);
	QObject::connect(this->user_mode_button, &QPushButton::clicked, this, &GUI::showUser);
}

void GUI::showAdmin() {
	AdminGUI* admin_gui = new AdminGUI{ this, this->service, this->validator, this->repository };
	admin_gui->show();
}
AdminGUI::AdminGUI(QWidget* parent, Service& service, DogValidator& validator, Repository& repository): service { service }, validator{ validator }, repository{ repository } {
	this->dog_list_widget = new QListWidget{};
	this->nameLineEdit = new QLineEdit{};
	this->breedLineEdit = new QLineEdit{};
	this->ageLineEdit = new QLineEdit{};
	this->linkLineEdit = new QLineEdit{};
	this->addButton = new QPushButton("Add");
	this->deleteButton = new QPushButton("Delete");
	this->updateButton = new QPushButton("Update");
	setParent(parent);
	setWindowFlag(Qt::Window);
	this->initAdminGUI();
	this->populateList();
	this->connectSignalsAndSlots();
	this->resize(800,500);
}

void AdminGUI::initAdminGUI() {
	auto* main_layout = new QHBoxLayout(this);

	main_layout->addWidget(this->dog_list_widget);
	auto* right_part = new QVBoxLayout(this);
	
	QFont font("Qeskile Voyage", 18);
	QFont font_list("Mirador", 15);
	this->dog_list_widget->setFont(font_list);
	QLabel* nameLabel = new QLabel("Name", this);
	QLabel* breedLabel = new QLabel("Breed", this);
	QLabel* ageLabel = new QLabel("Age", this);
	QLabel* linkLabel = new QLabel("Link", this);
	nameLabel->setFont(font);
	breedLabel->setFont(font);
	ageLabel->setFont(font);
	linkLabel->setFont(font);
	//make the form
	auto* dogDetailsLayout = new QFormLayout(this);
	dogDetailsLayout->addRow(nameLabel, this->nameLineEdit);
	dogDetailsLayout->addRow(breedLabel, this->breedLineEdit);
	dogDetailsLayout->addRow(ageLabel, this->ageLineEdit);
	dogDetailsLayout->addRow(linkLabel, this->linkLineEdit);

	this->nameLineEdit->setFont(font);
	this->breedLineEdit->setFont(font);
	this->ageLineEdit->setFont(font);
	this->linkLineEdit->setFont(font);

	QString add_button_style = "QPushButton {"
		"    background-color: #41644A;"
		"    color: white;"
		"    border-radius: 20px;"
		"    font-size: 20px;"
		"    font-family: Mirador;"
		"}"
		"QPushButton:hover {"
		"    background-color: #558F55;"
		"}";
	addButton->setFixedSize(100, 50);
	addButton->setStyleSheet(add_button_style);

	deleteButton->setFixedSize(100, 50);
	deleteButton->setStyleSheet(add_button_style);
	updateButton->setFixedSize(100, 50);
	updateButton->setStyleSheet(add_button_style);

	auto* buttonsLayout = new QHBoxLayout(this);
	buttonsLayout->addWidget(this->addButton);
	buttonsLayout->addWidget(this->deleteButton);
	buttonsLayout->addWidget(this->updateButton);

	// Set alignment of buttonsLayout to center
	buttonsLayout->setAlignment(Qt::AlignHCenter);

	right_part->addLayout(dogDetailsLayout);
	right_part->addSpacing(40);
	right_part->addLayout(buttonsLayout);
	right_part->setAlignment(Qt::AlignTop);
	main_layout->addLayout(right_part);

}

void AdminGUI::populateList() {
	this->dog_list_widget->clear();
	std::vector<Dog> all_dogs = this->service.get_all_service_data();
	for (Dog& dog : all_dogs) {
		this->dog_list_widget->addItem(QString::fromStdString(dog.to_string()));
	}
}

void AdminGUI::connectSignalsAndSlots() {
	QObject::connect(this->addButton, &QPushButton::clicked, this, &AdminGUI::addDog);
	QObject::connect(this->deleteButton, &QPushButton::clicked, this, &AdminGUI::deleteDog);
	QObject::connect(this->updateButton, &QPushButton::clicked, this, &AdminGUI::update_dog);
}

void AdminGUI::addDog() {
	std::string breed = this->breedLineEdit->text().toStdString();
	std::string name = this->nameLineEdit->text().toStdString();
	std::string age_s = this->ageLineEdit->text().toStdString();
	int age = stoi(age_s);
	std::string link = this->linkLineEdit->text().toStdString();
	try {
		this->validator.validate_age(age);
		this->validator.validate_breed(breed);
		this->validator.validate_name(name);
		this->validator.validate_photo_link(link);
		this->service.add_dog(breed, name, age, link);
		this->populateList();
	}
	catch (ValidationException& exception) {
		auto* error = new QMessageBox(this);
		error->setIcon(QMessageBox::Critical);
		error->setText(exception.what());
		error->exec();
	}
	catch (RepositoryException& r_exception) {
		auto* error = new QMessageBox(this);
		error->setIcon(QMessageBox::Critical);
		error->setText(r_exception.what());
		error->exec();
	}
}

void AdminGUI::deleteDog() {
	try {
		std::string name = this->nameLineEdit->text().toStdString();
		this->validator.validate_name(name);
		this->service.delete_dog(name);
		this->populateList();
	}
	catch (ValidationException& exception) {
		auto* error = new QMessageBox(this);
		error->setIcon(QMessageBox::Critical);
		error->setText(exception.what());
		error->exec();
	}
	catch (RepositoryException& r_exception) {
		auto* error = new QMessageBox(this);
		error->setIcon(QMessageBox::Critical);
		error->setText(r_exception.what());
		error->exec();
	}
}

int AdminGUI::getSelectedIndex() const {
	QModelIndexList selectedIndexes = this->dog_list_widget->selectionModel()->selectedIndexes();
	if (selectedIndexes.empty()) {
		this->nameLineEdit->clear();
		this->breedLineEdit->clear();
		this->ageLineEdit->clear();
		this->linkLineEdit->clear();
		return -1;
	}
	int selectedIndex = selectedIndexes.at(0).row();
	return selectedIndex;
}

void AdminGUI::update_dog() {
	int index = this->getSelectedIndex();
	try {
		if (index < 0) {
			auto* error = new QMessageBox(this);
			error->setIcon(QMessageBox::Critical);
			error->setText("No dog was selected!");
			error->exec();
		}
		else {
			std::string old_name = this->service.get_all_service_data()[index].get_name();
			std::string new_name = this->nameLineEdit->text().toStdString();
			std::string breed = this->breedLineEdit->text().toStdString();
			std::string age_s = this->ageLineEdit->text().toStdString();
			int age = stoi(age_s);
			std::string link = this->linkLineEdit->text().toStdString();
			this->validator.validate_age(age);
			this->validator.validate_breed(breed);
			this->validator.validate_name(new_name);
			this->validator.validate_photo_link(link);
			this->service.update_dog_information(old_name, breed, new_name, age, link);
			this->populateList();
		}
	}
	catch (ValidationException& exception) {
		auto* error = new QMessageBox(this);
		error->setIcon(QMessageBox::Critical);
		error->setText(exception.what());
		error->exec();
	}
	catch (RepositoryException& r_exception) {
		auto* error = new QMessageBox(this);
		error->setIcon(QMessageBox::Critical);
		error->setText(r_exception.what());
		error->exec();
	}
}

void GUI::showUser() {
	auto* user = new UserGUI(this, this->service, this->user_service, this->validator);
	user->show();
}

UserGUI::UserGUI(QWidget* parent, Service& serv, UserService& userserv, DogValidator& validator1) : service(serv), user_service{ userserv }, validator(validator1) {
	this->titleWidget = new QLabel(this);
	this->dogsListWidget = new QListWidget{};
	this->adoptionListWidget = new QListWidget{};
	this->nameLineEdit = new QLineEdit{};
	this->breedLineEdit = new QLineEdit{};
	this->ageLineEdit = new QLineEdit{};
	this->linkLineEdit = new QLineEdit{};
	this->breedFilterLineEdit = new QLineEdit{};
	this->ageFilterLineEdit = new QLineEdit{};
	this->addButton = new QPushButton("Add to the adoption list");
	this->filterButton = new QPushButton("Filter");
	this->openListButton = new QPushButton("Open file");
	QString button_style = "QPushButton {"
		"    background-color: #41644A;"
		"    color: white;"
		"    border-radius: 18px;"
		"    font-size: 18px;"
		"    font-family: Mirador;"
		"}"
		"QPushButton:hover {"
		"    background-color: #558F55;"
		"}";
	addButton->setStyleSheet(button_style);
	addButton->setFixedSize(250, 50);
	filterButton->setStyleSheet(button_style);
	filterButton->setFixedSize(90, 50);
	openListButton->setStyleSheet(button_style);
	openListButton->setFixedSize(100, 50);
	this->csvButton = new QRadioButton("CSV");
	this->htmlButton = new QRadioButton("HTML");
	this->repoTypeSelected = false;
	this->filtered = false;
	setParent(parent);
	setWindowFlag(Qt::Window);
	this->initUserGUI();
	this->populateDogList();
	this->connectSignalsAndSlots();
	this->resize(800, 800);
}

void UserGUI::initUserGUI() {
	auto* layout = new QVBoxLayout(this);
	QFont titleFont("Mirador", 18);
	this->titleWidget->setText("<p style='text-align:center'><font color=#263A29>USER MODE <br> Select the type of file!</font></p>");
	this->titleWidget->setFont(titleFont);
	layout->addWidget(this->titleWidget);

	auto* radioButtonsLayout = new QGridLayout(this);
	radioButtonsLayout->addWidget(this->csvButton, 0, 0);
	radioButtonsLayout->addWidget(this->htmlButton, 1, 0);
	radioButtonsLayout->addWidget(this->openListButton, 0, 1);
	layout->addLayout(radioButtonsLayout);

	auto* listLayout = new QGridLayout(this);
	listLayout->addWidget(this->dogsListWidget, 0, 0);
	listLayout->addWidget(this->adoptionListWidget, 0, 1);
	layout->addLayout(listLayout);

	auto* dogDetailsLayout = new QFormLayout{};
	dogDetailsLayout->addRow("Name", this->nameLineEdit);
	dogDetailsLayout->addRow("Breed", this->breedLineEdit);
	dogDetailsLayout->addRow("Age", this->ageLineEdit);
	dogDetailsLayout->addRow("Link", this->linkLineEdit);
	dogDetailsLayout->addRow(this->addButton);
	layout->addLayout(dogDetailsLayout);


	auto* filterTitle = new QLabel("<p style='text-align:center'><font color=#263A29><br>Filter the available dogs by breed and age</font></p>");
	QFont filterFont("Mirador", 14);
	filterTitle->setFont(filterFont);
	layout->addWidget(filterTitle);

	auto* filterDetailsLayout = new QFormLayout{};
	filterDetailsLayout->addRow("Breed", this->breedFilterLineEdit);
	filterDetailsLayout->addRow("Age", this->ageFilterLineEdit);
	filterDetailsLayout->addRow(this->filterButton);
	layout->addLayout(filterDetailsLayout);
}

void UserGUI::populateDogList() {
	this->dogsListWidget->clear();
	std::vector<Dog> allDogs = this->service.get_all_service_data();
	for (Dog& dog : allDogs)
		this->dogsListWidget->addItem(QString::fromStdString(dog.to_string()));
}

void UserGUI::connectSignalsAndSlots() {
	QObject::connect(this->dogsListWidget, &QListWidget::itemClicked, [this]() {
		int index = this->dogsListWidget->row(this->dogsListWidget->selectedItems().at(0));
		Dog dog = this->service.get_all_service_data()[index];
		this->nameLineEdit->setText(QString::fromStdString(dog.get_name()));
		this->breedLineEdit->setText(QString::fromStdString(dog.get_breed()));
		this->ageLineEdit->setText(QString::fromStdString(std::to_string(dog.get_age())));
		this->linkLineEdit->setText(QString::fromStdString(dog.get_link_to_photograph()));
		std::string link = std::string("start ").append(dog.get_link_to_photograph());
		system(link.c_str());
		});

	QObject::connect(this->csvButton, &QRadioButton::clicked, [this]() {
		string file_type = "CSV";
		this->user_service.repository_type(file_type);
		this->repoTypeSelected = true;
		});

	QObject::connect(this->htmlButton, &QRadioButton::clicked, [this]() {
		string file_type2 = "HTML";
		this->user_service.repository_type(file_type2);
		this->repoTypeSelected = true;
		});

	QObject::connect(this->openListButton, &QPushButton::clicked, [this]() {
		if (!this->repoTypeSelected) {
			auto* error = new QMessageBox();
			error->setIcon(QMessageBox::Warning);
			error->setText("Please select the type of file you want!");
			error->setWindowTitle("File type warning!");
			error->exec();
		}
		else {
			std::string link = std::string("start ").append(this->user_service.get_user_filename());
			system(link.c_str());
		}
		});

	QObject::connect(this->addButton, &QPushButton::clicked, this, &UserGUI::addDog);
	QObject::connect(this->filterButton, &QPushButton::clicked, this, &UserGUI::filterDogs);
}

int UserGUI::getSelectedIndex() const {
	QModelIndexList selectedIndexes = this->dogsListWidget->selectionModel()->selectedIndexes();
	if (selectedIndexes.empty()) {
		this->nameLineEdit->clear();
		this->breedLineEdit->clear();
		this->ageLineEdit->clear();
		this->linkLineEdit->clear();
		return -1;
	}
	int selectedIndex = selectedIndexes.at(0).row();
	return selectedIndex;
}

void UserGUI::populateAdoptionList() {
	this->adoptionListWidget->clear();
	std::vector<Dog> allDogs = this->user_service.get_adoption_list();
	for (Dog& dog : allDogs)
		this->adoptionListWidget->addItem(QString::fromStdString(dog.to_string()));
}

void UserGUI::addDog() {
	if (!this->repoTypeSelected) {
		auto* error = new QMessageBox();
		error->setIcon(QMessageBox::Warning);
		error->setText("Please select the type of file you want!");
		error->setWindowTitle("File type warning!");
		error->exec();
	}
	else {
		std::string breed = this->breedLineEdit->text().toStdString();
		std::string name = this->nameLineEdit->text().toStdString();
		std::string age_s = this->ageLineEdit->text().toStdString();
		std::string link = this->linkLineEdit->text().toStdString();
		int age = stoi(age_s);
		try {
			this->validator.validate_breed(breed);
			this->validator.validate_name(name);
			this->validator.validate_age(age);
			this->validator.validate_photo_link(link);
			Dog dog = Dog(breed, name, age, link);
			this->user_service.add_dog_to_adoption_list(dog);
			if (!this->filtered)
				this->populateDogList();
			else
				this->adoptionListWidget->addItem(this->dogsListWidget->takeItem(this->getSelectedIndex()));
			this->populateAdoptionList();
		}
		catch (ValidationException& exc) {
			auto* error = new QMessageBox();
			error->setIcon(QMessageBox::Critical);
			error->setText(exc.what());
			error->setWindowTitle("Invalid input!");
			error->exec();
		}
		catch (RepositoryException& re) {
			auto* error = new QMessageBox();
			error->setIcon(QMessageBox::Critical);
			error->setText(re.what());
			error->setWindowTitle("Error at adding dog!");
			error->exec();
		}
	}
}

void UserGUI::filterDogs() {
	try {
		std::string breed_filter = this->breedFilterLineEdit->text().toStdString();
		std::string age_filter_s = this->ageFilterLineEdit->text().toStdString();
		int age = stoi(age_filter_s);
		if (breed_filter.empty() && age_filter_s.empty()) {
			this->filtered = false;
			this->populateDogList();
		}
		else {
			this->validator.validate_age(age);
			std::vector<Dog> validDogs;
			this->user_service.filter_dog_data(validDogs, age, breed_filter);
			if (validDogs.empty()) {
				std::string error;
				error += std::string("The list of valid dogs is empty!");
			}
			else {
				this->filtered = true;
				this->dogsListWidget->clear();
				for (Dog& dog : validDogs)
					this->dogsListWidget->addItem(QString::fromStdString(dog.to_string()));
			}
		}
	}
	catch (ValidationException& ve) {
		auto* error = new QMessageBox();
		error->setIcon(QMessageBox::Critical);
		error->setText(ve.what());
		error->setWindowTitle("Validation error!");
		error->exec();
	}
}
