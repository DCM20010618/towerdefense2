#include "chooselevel.h"
#include "ui_chooselevel.h"
#include <QPainter>
#include <QPaintEvent>


ChooseLevel::ChooseLevel(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ChooseLevel)
{
    ui->setupUi(this);
    setFixedSize(1280,720);
}

ChooseLevel::~ChooseLevel()
{
    delete ui;
}

void ChooseLevel::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.drawPixmap(0, 0, 1280,720,QPixmap("://images/chooselevel.png"));
}

void ChooseLevel::on_pushButton_3_clicked()
{
    MainWindow *d=new MainWindow;
    this->hide();
    d->show();
}

void ChooseLevel::on_pushButton_2_clicked()
{
    Easy *d=new Easy;
    this->hide();
    d->show();
}

void ChooseLevel::on_pushButton_clicked()
{
    Hard *d=new Hard;
    this->hide();
    d->show();
}
