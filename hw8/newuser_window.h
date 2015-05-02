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

class NewUserInfo : public QWidget
{
	Q_OBJECT

public:
	NewUserInfo(DStore* &pdbase, std::string &username, long long &finalpassword);
	~NewUserInfo();

	private slots:
	void Done();

private:

	std::string username_;
	long long finalpassword_;

	QVBoxLayout* overallLayout;
	QLabel* ageLabel;
	QLabel* creditLabel;
	QLineEdit* ageInput;
	QLineEdit* creditInput;

	QPushButton* OKButton;
	DStore* dbase_;	
};