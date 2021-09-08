#include "adddishform.h"
#include "ui_adddishform.h"
#include <QMessageBox>
#include "DBHelper.h"
#include <QFile>
addDishForm::addDishForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::addDishForm)
{
    QFile qss(":/white.qss");
    qss.open(QFile::ReadOnly);
    qApp->setStyleSheet(qss.readAll());
    qss.close();
    ui->setupUi(this);
    this->setFixedSize(315, 275);
    this->setWindowTitle("添加菜品");
}

addDishForm::~addDishForm()
{
    delete ui;
}

void addDishForm::on_pushButton_2_clicked()
{
    ui->lineEdit->setText("");
    ui->lineEdit_2->setText("");
}

void addDishForm::on_pushButton_clicked()
{
    if(ui->lineEdit->text() == "" || "" == ui->lineEdit_2->text()){
        QMessageBox::information(this, QString("提示"), QString("请输入完整信息"), QMessageBox::Cancel, QMessageBox::Cancel);
        return;
    }
    QString name = ui->lineEdit->text();
    double price = ui->lineEdit_2->text().toDouble();
    DBHelper helper;
    QSqlQuery query(helper.getDB());
    QString sql = QString("insert into menu values(NULL, '%1', %2, 0)").arg(name).arg(price);
    bool ret = query.exec(sql);
    if(!ret){
        QSqlError err = query.lastError();   //得到最近一次的错误信息
        QString str = QString("错误信息:%1, %2").arg(err.driverText()).arg(err.databaseText());
        QMessageBox::warning(this, "提示", str);
    }
    QMessageBox::information(this, QString("提示"), QString("菜品添加成功"), QMessageBox::Cancel, QMessageBox::Cancel);
    ui->lineEdit->setText("");
    ui->lineEdit_2->setText("");
    emit newDish();
}
