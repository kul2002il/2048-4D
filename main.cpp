#include <QApplication>
#include <QLabel>
#include <QFormLayout>
#include <QFrame>
#include "game2048_4d.cpp"

int main(int argc, char *argv[])
{
	QApplication Applic(argc, argv);

	game2048_4D *MainWindow = new game2048_4D;
	MainWindow->resize(700, 500);
	MainWindow->show();
	Applic.exec();
}
