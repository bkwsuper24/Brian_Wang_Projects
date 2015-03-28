#include "main_window.h"
#include <QApplication>

int main(int argc, char* argv[])
{
	QApplication app(argc, argv);

	if(argc != 2)
	{
    	std::cerr << "Not enough arguments!" << std::endl;
    	return 1;
	}

	Main_Window mainWindow(argv[1]);

	mainWindow.show();

	return app.exec();
}