#include "form.h"
#include "ui_form.h"
#include <QFile>
Form::Form(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Form)
{
    QFile qss(":/white.qss");
    qss.open(QFile::ReadOnly);
    qApp->setStyleSheet(qss.readAll());
    qss.close();
    ui->setupUi(this);
    this->setWindowTitle("添加用户");
    this->setFixedSize(315, 275);
}

Form::~Form()
{
    delete ui;
}

void Form::on_pushButton_2_clicked()
{
    //重置
    ui->lineEdit->setText("");
    ui->lineEdit_2->setText("");
    ui->lineEdit_3->setText("");
    ui->comboBox->setCurrentIndex(0);
}

void Form::on_pushButton_clicked()
{
    //提交
    QString name = ui->lineEdit->text();
    QString pwd = ui->lineEdit_2->text();
    QString pwdCheck = ui->lineEdit_3->text();
    int type = ui->comboBox->currentIndex();
    if("" == name || "" == pwd){
        QMessageBox::information(this, QString("提示"), QString("请输入完整信息"), QMessageBox::Cancel, QMessageBox::Cancel);
        return ;
    }
    if( 0 == type){
        QMessageBox::information(this, QString("提示"), QString("请选择用户类型"), QMessageBox::Cancel, QMessageBox::Cancel);
        return;
    }
    if(pwdCheck != pwd){
        QMessageBox::information(this, QString("提示"), QString("密码不一致，请检查"), QMessageBox::Cancel, QMessageBox::Cancel);
        return;
    }
    DBHelper helper;
    QSqlQuery query(helper.getDB());
    QString sql = QString("insert into user values(NULL, %1, '%2', '%3')")
            .arg(type-1)
            .arg(name)
            .arg(pwd);
    bool ret = query.exec(sql);
    if(!ret){
        QSqlError err = query.lastError();   //得到最近一次的错误信息
        QString str = QString("错误信息:%1, %2").arg(err.driverText()).arg(err.databaseText());
        QMessageBox::warning(this, "提示", str);
    }
    QMessageBox::information(this, QString("提示"), QString("用户添加成功"), QMessageBox::Cancel, QMessageBox::Cancel);
    ui->lineEdit->setText("");
    ui->lineEdit_2->setText("");
    ui->lineEdit_3->setText("");
    ui->comboBox->setCurrentIndex(0);
    emit newUser();
}
