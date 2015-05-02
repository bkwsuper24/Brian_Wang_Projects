#include <QApplication>
#include "login_window.h"

int main(int argc, char* argv[])
{
	QApplication app(argc, argv);

	if(argc != 2)
	{
    	std::cerr << "Not enough arguments!" << std::endl;
    	return 1;
	}

	Login_Window loginWindow(argv[1]);

	loginWindow.show();

	return app.exec();
}