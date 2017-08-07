#include <QString>
#include <QFileDialog>
#include <vector>
#include <cstdint>
#include <iostream>
#include <ostream>
#include "sys/types.h"
#include "chessinput.hpp"
#include "leveloneneuron.hpp"
#include "filternet.hpp"
#include "fullyconnected.hpp"
#include "chessnet.hpp"
#include "mainwindow.hpp"
#include "ui_mainwindow.h"

using namespace std;

static const uint imageWidth = 100;
static const uint imageHeight = 100;
static const uint convSpan = 1;
static const uint field = 3;
static const uint filters = 9;


MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow)
{
	ui->setupUi(this);
	ui->fileName->setVisible(false);
	ui->progressNN->setVisible(false);
}

MainWindow::~MainWindow()
{
	delete ui;
}

void MainWindow::on_fileSelect_clicked()
{
	ui->fileName->setEnabled(false);
	ui->progressNN->setEnabled(false);
	QString JPEGName = QFileDialog::getOpenFileName(this,
		tr("Select JPEG"), "", tr("JPEGs (*.jpeg *.jpg *.jfif)"));
	ui->fileName->setText(JPEGName);
	ui->fileName->setVisible(true);
	ui->fileName->setEnabled(true);
	ui->progressNN->setProperty("value", 0);
	ui->progressNN->setVisible(true);
	ui->progressNN->setEnabled(true);
	ui->fileSelect->setEnabled(false);
	//load input
	ChessNet chess(imageWidth, imageHeight, convSpan, field, filters);
	QImage inputFile(JPEGName, "JPG");
}
