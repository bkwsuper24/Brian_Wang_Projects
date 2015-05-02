#include <iostream>
#include "newuser_window.h"

NewUserInfo::NewUserInfo(DStore dbase, std::string &username, long long &finalpassword)
{
	setWindowTitle("Amazon New User Info");

	username_ = username;
	finalpassword_ = finalpassword;
	dbase_ = dbase;

	//Overall Layout
	overallLayout = new QVBoxLayout();

	//age text
	ageLabel = new QLabel("Age:");
	overallLayout->addWidget(ageLabel);

	//age text box within overall layout
	ageInput = new QLineEdit();
	overallLayout->addWidget(ageInput);

	//credit text
	creditLabel = new QLabel("Credit:");
	overallLayout->addWidget(creditLabel);

	//username text box within overall layout
	creditInput = new QLineEdit();
	overallLayout->addWidget(creditInput);

	//create OK button
	OKButton = new QPushButton("DONE");
	overallLayout->addWidget(OKButton);
	connect(OKButton, SIGNAL(clicked()), this, SLOT(Done()));

	setLayout(overallLayout);
}

NewUserInfo::~NewUserInfo()
{

}

void NewUserInfo::Done()
{

	if(ageInput->text().isEmpty() == true)
	{
		QMessageBox::warning(this, "Blank Age", "Please enter proper age");
		return;
	}

	if(creditInput->text().isEmpty() == true)
	{
		QMessageBox::warning(this, "Blank Credit", "Please enter proper credit");
		return;
	}
	int age;
	age = ageInput->text().toInt();
	
	double credit;
	credit = creditInput->text().toDouble();

	User* newUser = new User(username_, age, credit, 0, finalpassword_);

	dbase_.addUser(newUser);
	this->close();  
}