
#include <QApplication>

#include "VMainWindow.h"

int main(int argc, char *argv[])
{
	QApplication app(argc, argv);
	VMainWindow MainWin;
	MainWin.show();
	return app.exec();
}
