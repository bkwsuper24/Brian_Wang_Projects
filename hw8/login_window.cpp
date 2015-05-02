#include <iostream>
#include "login_window.h"
#include <cmath>


Login_Window::Login_Window(std::string filename)
{
	parser.addProductParser(new ProductBookParser);
 	parser.addProductParser(new ProductClothingParser);
  	parser.addProductParser(new ProductMovieParser);

	if(parser.parse(filename, dbase))
	{
		return;
	}

	setWindowTitle("Amazon User Login");

	//Overall Layout
	overallLayout = new QVBoxLayout();

	//username text
	usernameLabel = new QLabel("Username:");
	overallLayout->addWidget(usernameLabel);

	//username text box within overall layout
	usernameInput = new QLineEdit();
	overallLayout->addWidget(usernameInput);

	//password text
	passwordLabel = new QLabel("Password:");
	overallLayout->addWidget(passwordLabel);

	//password text box within overall layout
	passwordInput = new QLineEdit();
	overallLayout->addWidget(passwordInput);

	//create smaller layout for horizontal login/newUser
	buttonLayout = new QHBoxLayout();
	overallLayout->addLayout(buttonLayout);

	//create login button
	loginButton = new QPushButton("Login");
	buttonLayout->addWidget(loginButton);
	connect(loginButton, SIGNAL(clicked()), this, SLOT(LoginUser()));

	newuserButton = new QPushButton("New User");
	buttonLayout->addWidget(newuserButton);
	connect(newuserButton, SIGNAL(clicked()), this, SLOT(NewUser()));
	//connect to add new user functionality still need to implement

	quitButton = new QPushButton("QUIT");
	overallLayout->addWidget(quitButton);
	connect(quitButton, SIGNAL(clicked()), this, SLOT(Quit()));

	setLayout(overallLayout);
}

Login_Window::~Login_Window()
{


}

long long Login_Window::passwordHash(std::string password)
{
	//converting password hash
	long long LLpassword = 0;
	
	for(unsigned int i=0; i<password.size(); i++)
	{
		LLpassword = LLpassword + (((int)password[password.size()-(i+1)])*((long long)pow(128, i)));
	}

	long long w4 = LLpassword % 65521;
	long long w3 = (LLpassword/65521) % 65521;
	long long w2 = ((LLpassword/65521)/65521) % 65521;
	long long w1 = (((LLpassword/65521)/65521)/65521) % 65521;

	unsigned int pwordArray[4];

	pwordArray[0] = w4;
	pwordArray[1] = w3;
	pwordArray[2] = w2;
	pwordArray[3] = w1;

	long long encryptedPassword = ((4625*pwordArray[0]) + (65169*pwordArray[1]) + (35511*pwordArray[2]) + (45912*pwordArray[3])) % 65521;

	return encryptedPassword;
}

void Login_Window::LoginUser()
{
	if(usernameInput->text().isEmpty() == true)
	{
		QMessageBox::warning(this, "Blank username", "Please enter proper username");
		return;
	}

	if(passwordInput->text().isEmpty() == true)
	{
		QMessageBox::warning(this, "Blank password", "Please enter proper password");
		return;
	}

	std::string username;
	username = usernameInput->text().toStdString();
	
	std::string password;
	password = passwordInput->text().toStdString();

	User* u;
	u = dbase.findUser(username);

	long long temp = passwordHash(password);

	if(temp == u->getPasswordHash())
	{
		mainWindow = new Main_Window(username, dbase);
		mainWindow->show();
		this->close();
	}
	else
	{
		QMessageBox::warning(this, "Invalid Username/Password", "Try Again");
		return;
	}

}

void Login_Window::NewUser()
{
	if(usernameInput->text().isEmpty() == true)
	{
		QMessageBox::warning(this, "Blank username", "Please enter proper username");
		return;
	}

	if(passwordInput->text().isEmpty() == true)
	{
		QMessageBox::warning(this, "Blank password", "Please enter proper password");
		return;
	}

	std::string username;
	username = usernameInput->text().toStdString();
	
	std::string password;
	password = passwordInput->text().toStdString();

	User* u;
	u = dbase.findUser(username);

	//username check
	if(dbase.findUserCheck(u) == true)
	{
		QMessageBox::warning(this, "Username exists", "Username exists already. Try Again");
		return;
	}

	//password length check
	if(password.size() > 7)
	{
		QMessageBox::warning(this, "Password too long", "Password must be less than 8 characters. Try Again");
		return;
	}

	//check for spaces in password
	for(unsigned int i=0; i<password.size(); i++)
	{
		std::string arraySpace;
		arraySpace = " ";

		if(password[i] == arraySpace[0])
		{
			QMessageBox::warning(this, "Invalid Password", "Password may not contain space. Try Again");
			return;
		}
	}

	long long finalpassword = passwordHash(password);

	DStore* pdbase = &dbase;
	newinfo = new NewUserInfo(pdbase, username, finalpassword);
	newinfo->show();
}

void Login_Window::Quit()
{
	QApplication::quit();
}

