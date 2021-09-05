#include "cashierForm.h"
#include "ui_cashierform.h"

#include <QFile>

CashierForm::CashierForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CashierForm)
{
    QFile qss(":/white.qss");
    qss.open(QFile::ReadOnly);
    qApp->setStyleSheet(qss.readAll());
    qss.close();
    ui->setupUi(this);
    this->setWindowTitle("收银");
    this->setFixedSize(570, 430);
}

CashierForm::~CashierForm()
{
    delete ui;
}
