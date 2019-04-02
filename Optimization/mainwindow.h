#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "opt.h"
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void MainWindow::PaintGraph(double* myX, double* myY, int N, const int nGraph, QString nameGraph);

    Opt myOpt;
    int numbGraph;


private slots:
    void on_BUTTON_clicked();

    void on_pushButton_CLEAN_clicked();

    void on_radioButton_E_clicked(bool checked);

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
