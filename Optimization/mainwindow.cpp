#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->setWindowTitle("Optimization");

    ui->GRAPH->setInteraction(QCP::iRangeZoom, true); //удаление и приближение
    ui->GRAPH->setInteraction(QCP::iRangeDrag, true); //перетаскивание

    ui->GRAPH->xAxis->setLabel("X");
    ui->GRAPH->yAxis->setLabel("Y");

    numbGraph = 0;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_BUTTON_clicked()
{

    myOpt.a = ui->lineEdit_a->text().toDouble();
    myOpt.b = ui->lineEdit_b->text().toDouble();
    myOpt.c = ui->lineEdit_c->text().toDouble();
    myOpt.d = ui->lineEdit_d->text().toDouble();

    myOpt.rightBorder = ui->lineEdit_rightBorder->text().toDouble();
    myOpt.leftBorder = ui->lineEdit_leftBorder->text().toDouble();

    myOpt.n = ui->lineEdit_n->text().toInt();
    myOpt.E = ui->lineEdit_E->text().toDouble();
    myOpt.r = ui->lineEdit_r->text().toDouble();
    myOpt.m = ui->lineEdit_m->text().toDouble();


   if(ui->radioButton_BruteForce->isChecked())
       myOpt.BruteForce();

   if(ui->radioButton_Leech->isChecked()){
      if(ui->radioButton_E->isChecked()){
          myOpt.LeechE();
      } else {
          myOpt.Leech();
      }
    }

   if(ui->radioButton_Strong->isChecked()){
       if(ui->radioButton_E->isChecked()){
           myOpt.StrongE();
       } else {
           myOpt.Strong();
       }
   }

   ui->label_F->setText("minF = " + QVariant(myOpt.minFun).toString());
   ui->label_x->setText("x = " + QVariant(myOpt.minX).toString());
   ui->label_n->setText("n = " + QVariant(myOpt.n).toString());



   PaintGraph(myOpt.arrayX, myOpt.arrayFun, myOpt.n, numbGraph, QVariant(numbGraph).toString());
   numbGraph++;
   PaintGraph(myOpt.arrayX, myOpt.arrayDensity, myOpt.n, numbGraph, QVariant(numbGraph).toString());
   numbGraph++;
}


void MainWindow::PaintGraph(double* myX, double* myY, int N, const int nGraph, QString nameGraph){


    QVector<double> X(N);
    QVector<double> Y(N);

    for(int i = 0; i < N; i++){
        X[i] = myX[i];
        Y[i] = myY[i];
    }

    ui->GRAPH->legend->setVisible(true);
    ui->GRAPH->legend->setFont(QFont("Helvetica", 9));
    ui->GRAPH->legend->setRowSpacing(-3);

    QVector<QCPScatterStyle::ScatterShape> shapes;
    shapes << QCPScatterStyle::ssCross;
    shapes << QCPScatterStyle::ssPlus;
    shapes << QCPScatterStyle::ssCircle;
    shapes << QCPScatterStyle::ssDisc;
    shapes << QCPScatterStyle::ssSquare;
    shapes << QCPScatterStyle::ssDiamond;
    shapes << QCPScatterStyle::ssStar;
    shapes << QCPScatterStyle::ssTriangle;
    shapes << QCPScatterStyle::ssTriangleInverted;
    shapes << QCPScatterStyle::ssCrossSquare;
    shapes << QCPScatterStyle::ssPlusSquare;
    shapes << QCPScatterStyle::ssCrossCircle;
    shapes << QCPScatterStyle::ssPlusCircle;
    shapes << QCPScatterStyle::ssPeace;
    shapes << QCPScatterStyle::ssCustom;

    QPen pen;

    pen.setColor(QColor(qSin(nGraph%14*0.3)*100+100, qSin(nGraph%14*0.6+0.7)*100+100, qSin(nGraph%14*0.4+0.6)*100+100));

    ui->GRAPH->addGraph();
    ui->GRAPH->graph(nGraph)->setData(X, Y);

    ui->GRAPH->graph(nGraph)->setPen(pen);
    ui->GRAPH->graph(nGraph)->setName(nameGraph);
    ui->GRAPH->graph(nGraph)->setLineStyle(QCPGraph::lsLine);

    // set scatter style:

   if(nGraph%2 != 0){
     if (shapes.at(nGraph%14) != QCPScatterStyle::ssCustom)
     {
       ui->GRAPH->graph(nGraph)->setScatterStyle(QCPScatterStyle(shapes.at(nGraph%14), 10));
     }
     else
     {
       QPainterPath customScatterPath;
       for (int i=0; i<3; ++i)
         customScatterPath.cubicTo(qCos(2*M_PI*i/3.0)*9, qSin(2*M_PI*i/3.0)*9, qCos(2*M_PI*(i+0.9)/3.0)*9, qSin(2*M_PI*(i+0.9)/3.0)*9, 0, 0);
           ui->GRAPH->graph(nGraph)->setScatterStyle(QCPScatterStyle(customScatterPath, QPen(Qt::black, 0), QColor(40, 70, 255, 50), 10));
     }

}

     ui->GRAPH->graph(nGraph)->rescaleAxes();
     ui->GRAPH->replot();

   }

void MainWindow::on_pushButton_CLEAN_clicked()
{
    ui->GRAPH->clearGraphs();
    numbGraph = 0;
    ui->GRAPH->replot();
}

void MainWindow::on_radioButton_E_clicked(bool checked)
{
    ui->lineEdit_E->setReadOnly(false);
    QPalette *palette = new QPalette();
    palette->setColor(QPalette::Base,Qt::white);
    ui->lineEdit_E->setPalette(*palette);
}
