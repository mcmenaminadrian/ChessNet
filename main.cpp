#include <vector>
#include <iostream>
#include <QImage>
#include <sstream>
#include "sys/types.h"
#include "chessinput.hpp"
#include "hiddenneuron.hpp"
#include "filternet.hpp"
#include "fullyconnected.hpp"
#include "chessnet.hpp"
#include "mainwindow.hpp"
#include <QApplication>


int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	MainWindow w;
	w.show();

	return a.exec();
}
