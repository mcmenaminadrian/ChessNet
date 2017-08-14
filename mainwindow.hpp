#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QMainWindow>


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	explicit MainWindow(QWidget *parent = 0);
	~MainWindow();

private slots:
	void on_fileSelect_clicked();
	void on_pushButton_clicked();
	
private:
	Ui::MainWindow *ui;
	std::vector<std::pair<std::string, uint>> getTestFileList(QString tst);
};

#endif // MAINWINDOW_HPP
