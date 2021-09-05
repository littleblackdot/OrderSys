#include "managerForm.h"
#include "ui_managerform.h"
#include <QFile>
ManagerForm::ManagerForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ManagerForm)
{
    QFile qss(":/white.qss");
    qss.open(QFile::ReadOnly);
    qApp->setStyleSheet(qss.readAll());
    qss.close();
    ui->setupUi(this);
    this->setWindowTitle("管理员");
    this->setFixedSize(570, 430);
}

ManagerForm::~ManagerForm()
{
    delete ui;
}
