#include <QString>
#include <QFileDialog>
#include <QImage>
#include <vector>
#include <cstdint>
#include <iostream>
#include <ostream>
#include <fstream>
#include <sstream>
#include <string>
#include <QFile>
#include <QIODevice>
#include <QTextStream>
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
static const uint filters = 25;
static const uint fibreDepth = 7;


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
	QString trainingName = QFileDialog::getOpenFileName(this,
		tr("Select training file"), "", tr("TXT (*.txt)"));
	ui->fileName->setText(trainingName);
	ui->fileName->setVisible(true);
	ui->fileName->setEnabled(true);

	ui->fileSelect->setEnabled(false);
	//load input
	ifstream weightsFile;
	weightsFile.open("weights.txt");
	ChessNet chess(imageWidth, imageHeight, convSpan, field, filters,
		fibreDepth, weightsFile);
	vector<pair<string, uint>> testFileList =
		getTestFileList(trainingName);
	for (auto tests: testFileList) {
		QImage inputFile(QString(tests.first.c_str()), "JPG");
		chess.loadInput(inputFile);
		chess.feedForward(tests.first, tests.second);
	}
	chess.storeWeights();
}

void MainWindow::on_pushButton_clicked()
{
   QApplication::exit();
}

vector<pair<string, uint>> MainWindow::getTestFileList(QString tst)
{
	QFile tester(tst);
	tester.open(QIODevice::ReadOnly | QIODevice::Text);
	vector<pair<string, uint>> returnPairs;
	QTextStream in(&tester);
	QString line = in.readLine();
	while (!line.isNull()) {
		QStringList pieces = line.split(' ', QString::SkipEmptyParts);
		pair<string, uint> answer(pieces[0].toStdString(),
			pieces[1].toInt());
		returnPairs.push_back(answer);
		line = in.readLine();
	}
	return returnPairs;
}
