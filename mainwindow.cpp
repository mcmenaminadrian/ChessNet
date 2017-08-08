#include <QString>
#include <QFileDialog>
#include <QImage>
#include <vector>
#include <cstdint>
#include <iostream>
#include <ostream>
#include <fstream>
#include <sstream>
#include "sys/types.h"
#include "chessinput.hpp"
#include "hiddenneuron.hpp"
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
static const uint filters = 11;


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
	ifstream weightsFile;
	weightsFile.open("weights.txt");
	ChessNet chess(imageWidth, imageHeight, convSpan, field, filters,
		weightsFile);
	QImage inputFile(JPEGName, "JPG");
	chess.loadInput(inputFile);
	ui->progressNN->setProperty("value", 5);
	chess.feedForward();
	ui->progressNN->setProperty("value", 25);
	chess.storeWeights();
}

void MainWindow::on_pushButton_clicked()
{
   QApplication::exit();
}
