#include "typechangeform.h"
#include "ui_typechangeform.h"
#include "DBHelper.h"
#include <QMessageBox>
#include <QFile>
typeChangeForm::typeChangeForm(int userId, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::typeChangeForm),
    userId(userId)
{
    QFile qss(":/white.qss");
    qss.open(QFile::ReadOnly);
    qApp->setStyleSheet(qss.readAll());
    qss.close();
    ui->setupUi(this);
    this->setFixedSize(315, 275);
}

typeChangeForm::~typeChangeForm()
{
    delete ui;
}

void typeChangeForm::on_pushButton_clicked()
{
    int type = ui->comboBox->currentIndex();
    if(type > 0){
        DBHelper helper;
        QSqlQuery query(helper.getDB());
        QString sql = QString("update user set type = %1 where id = %2").arg(type-1).arg(userId);
        bool ret = query.exec(sql);
        if(!ret){
            QSqlError err = query.lastError();   //得到最近一次的错误信息
            QString str = QString("错误信息:%1, %2").arg(err.driverText()).arg(err.databaseText());
            QMessageBox::warning(this, "提示", str);
        }
        QMessageBox::information(this, QString("提示"), QString("权限修改成功"), QMessageBox::Cancel, QMessageBox::Cancel);
        emit userChange();
    }
}
