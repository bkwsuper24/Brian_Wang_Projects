#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QTextEdit>
#include <QPushButton>
#include <string>
#include <QMessageBox>
#include <QApplication>


#include "util.h"
#include "db_parser.h"
#include "product_parser.h"
#include "main_window.h"
#include "newuser_window.h"

class Login_Window : public QWidget
{
	Q_OBJECT

public:
	Login_Window(std::string filename);
	~Login_Window();


	private slots:
	void Quit();
	void LoginUser();
	void NewUser();


private:
	DStore dbase;
	DBParser parser;

	long long passwordHash(std::string password);


	Main_Window* mainWindow;
	NewUserInfo* newinfo;

	QVBoxLayout* overallLayout;
	QHBoxLayout* buttonLayout;
	QLabel* usernameLabel;
	QLabel* passwordLabel;
	QLineEdit* usernameInput;
	QLineEdit* passwordInput;
	QPushButton* loginButton;
	QPushButton* newuserButton;
	QPushButton* quitButton;
};