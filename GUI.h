#pragma once

#include <QtWidgets/QMainWindow>

#include "Service.h"
#include "User_service.h"
#include "Validator.h"
#include <QLabel>
#include <QPushButton>
#include <QListWidget>
#include <QLineEdit>
#include <QRadioButton>

class GUI : public QWidget {
private:
	Service& service;
	UserService& user_service;
	DogValidator& validator;
	Repository& repository;
	void initGUI();
	void connectSignalsAndSlots();
	void showAdmin();
	void showUser();
	QLabel* main_title;
	QLabel* subtitle;
	QPushButton* administrator_mode_button;
	QPushButton* user_mode_button;
public:
	explicit GUI(Service& service, UserService& user_service, DogValidator& validator, Repository& repository);
};

class AdminGUI : public QWidget {
private:
	Service& service;
	Repository& repository;
	DogValidator& validator;
	void initAdminGUI();
	void populateList();
	void connectSignalsAndSlots();
	void addDog();
	void deleteDog();
	int getSelectedIndex() const;
	void update_dog();
	QListWidget* dog_list_widget;
	QLineEdit* nameLineEdit, * breedLineEdit, * ageLineEdit, * linkLineEdit;
	QPushButton* addButton, * deleteButton, * updateButton;
public:
	explicit AdminGUI(QWidget* parent, Service& service, DogValidator& validator, Repository& repository);
};

class UserGUI : public QWidget {
private:
	Service& service;
	UserService& user_service;
	DogValidator& validator;
	void initUserGUI();
	QLabel* titleWidget;
	QListWidget* dogsListWidget, * adoptionListWidget;
	QLineEdit* nameLineEdit, * breedLineEdit, * ageLineEdit, * linkLineEdit, *breedFilterLineEdit, *ageFilterLineEdit;
	QPushButton* addButton, * filterButton, * openListButton;
	QRadioButton* csvButton, * htmlButton;
	bool repoTypeSelected;
	bool filtered;
	void populateDogList();
	void populateAdoptionList();
	void connectSignalsAndSlots();
	int getSelectedIndex() const;
	void addDog();
	void filterDogs();
public:
	explicit UserGUI(QWidget* parent, Service& serv, UserService& user_serv, DogValidator& validator);
};