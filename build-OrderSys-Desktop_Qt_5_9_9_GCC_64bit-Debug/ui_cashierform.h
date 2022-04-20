/********************************************************************************
** Form generated from reading UI file 'cashierform.ui'
**
** Created by: Qt User Interface Compiler version 5.9.9
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CASHIERFORM_H
#define UI_CASHIERFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_CashierForm
{
public:
    QLabel *label;
    QLabel *label_2;
    QTableWidget *tableWidget;
    QLabel *label_3;
    QLineEdit *lineEdit;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QPushButton *pushButton_3;
    QLabel *label_4;
    QLabel *label_5;
    QLabel *label_6;
    QLabel *label_7;

    void setupUi(QWidget *CashierForm)
    {
        if (CashierForm->objectName().isEmpty())
            CashierForm->setObjectName(QStringLiteral("CashierForm"));
        CashierForm->resize(499, 368);
        label = new QLabel(CashierForm);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(10, 10, 111, 21));
        label_2 = new QLabel(CashierForm);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(260, 10, 201, 21));
        tableWidget = new QTableWidget(CashierForm);
        tableWidget->setObjectName(QStringLiteral("tableWidget"));
        tableWidget->setGeometry(QRect(10, 40, 291, 271));
        label_3 = new QLabel(CashierForm);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(320, 40, 61, 16));
        lineEdit = new QLineEdit(CashierForm);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));
        lineEdit->setGeometry(QRect(310, 70, 113, 24));
        pushButton = new QPushButton(CashierForm);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(310, 100, 80, 24));
        pushButton_2 = new QPushButton(CashierForm);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));
        pushButton_2->setGeometry(QRect(310, 280, 80, 24));
        pushButton_3 = new QPushButton(CashierForm);
        pushButton_3->setObjectName(QStringLiteral("pushButton_3"));
        pushButton_3->setGeometry(QRect(400, 280, 80, 24));
        label_4 = new QLabel(CashierForm);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(310, 130, 49, 16));
        label_5 = new QLabel(CashierForm);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setGeometry(QRect(310, 160, 49, 16));
        label_6 = new QLabel(CashierForm);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setGeometry(QRect(310, 180, 181, 21));
        label_7 = new QLabel(CashierForm);
        label_7->setObjectName(QStringLiteral("label_7"));
        label_7->setGeometry(QRect(310, 210, 131, 21));

        retranslateUi(CashierForm);

        QMetaObject::connectSlotsByName(CashierForm);
    } // setupUi

    void retranslateUi(QWidget *CashierForm)
    {
        CashierForm->setWindowTitle(QApplication::translate("CashierForm", "Form", Q_NULLPTR));
        label->setText(QApplication::translate("CashierForm", "\347\224\250\346\210\267\345\220\215\357\274\232", Q_NULLPTR));
        label_2->setText(QString());
        label_3->setText(QApplication::translate("CashierForm", "\350\276\223\345\205\245\346\241\214\345\217\267\357\274\232", Q_NULLPTR));
        pushButton->setText(QApplication::translate("CashierForm", "\346\237\245\350\257\242", Q_NULLPTR));
        pushButton_2->setText(QApplication::translate("CashierForm", "\347\273\223\345\270\220", Q_NULLPTR));
        pushButton_3->setText(QApplication::translate("CashierForm", "\346\241\214\345\217\267\351\207\215\347\275\256", Q_NULLPTR));
        label_4->setText(QApplication::translate("CashierForm", "\347\273\237\350\256\241", Q_NULLPTR));
        label_5->setText(QApplication::translate("CashierForm", "\345\215\225\345\217\267\357\274\232", Q_NULLPTR));
        label_6->setText(QString());
        label_7->setText(QApplication::translate("CashierForm", "\346\200\273\350\256\241\357\274\232", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class CashierForm: public Ui_CashierForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CASHIERFORM_H
