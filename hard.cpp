#include "hard.h"
#include "ui_hard.h"
#include <chooselevel.h>

Hard::Hard(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Hard)
{
    ui->setupUi(this);
    setFixedSize(1280,720);
}

Hard::~Hard()
{
    delete ui;
}

void Hard::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.drawPixmap(0, 0, 1280,720,QPixmap("://images/hardpattern.jpg"));
}

void Hard::on_pushButton_3_clicked()
{
    ChooseLevel *d=new ChooseLevel;
    this->hide();
    d->show();
}
