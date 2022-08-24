#include "widget.h"
#include "ui_widget.h"
#include <QMessageBox>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    ui->pbCoffee->setEnabled(false);
    ui->pbMilk->setEnabled(false);
    ui->pbMango->setEnabled(false);
//    ui->pbCoffee->isEnabled();
}

Widget::~Widget()
{
    delete ui;
}
void Widget::changeMoney(int diff){
    money += diff;
    ui->lcdNumber->display(money);
    checkMoney();
}

void Widget::checkMoney(){
    if(money >= 500)
        ui->pbMango->setEnabled(true);
    else
        ui->pbMango->setEnabled(false);
    if(money >= 300)
        ui->pbMilk->setEnabled(true);
    else
        ui->pbMilk->setEnabled(false);
    if(money >= 100)
        ui->pbCoffee->setEnabled(true);
    else
        ui->pbCoffee->setEnabled(false);
}

void Widget::on_pb500_clicked()
{
    changeMoney(500);
}

void Widget::on_pb100_clicked()
{
    changeMoney(100);
}

void Widget::on_pb50_clicked()
{
    changeMoney(50);
}

void Widget::on_pb10_clicked()
{
    changeMoney(10);
}

void Widget::on_pbCoffee_clicked()
{
    changeMoney(-100);
}

void Widget::on_pbMilk_clicked()
{
    changeMoney(-300);
}

void Widget::on_pbMango_clicked()
{
    changeMoney(-500);
}

int calcLenText(int num){
    int count = 0;
    while(num >= 10){
        num = num/10;
        ++count;
    }
    return count;
}

void Widget::on_pbRerset_clicked()
{
    QMessageBox msg;
    int len = 32;
    int change[4] = {money/500, money%500/100, money%500%100/50, money%500%100%50/10};
    for(int i = 0; i < 4; i++)
        len += calcLenText(change[i]);

    char * text = (char*)malloc(sizeof(char)*len);
    sprintf(text, "500 : %d\n100 : %d\n  50 : %d\n  10 : %d", change[0], change[1], change[2], change[3]);
    msg.information(nullptr, "change", text);
    changeMoney(money*-1);
    checkMoney();
    free(text);
}
