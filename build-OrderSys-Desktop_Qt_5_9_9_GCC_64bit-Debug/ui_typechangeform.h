/********************************************************************************
** Form generated from reading UI file 'typechangeform.ui'
**
** Created by: Qt User Interface Compiler version 5.9.9
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TYPECHANGEFORM_H
#define UI_TYPECHANGEFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_typeChangeForm
{
public:
    QPushButton *pushButton;
    QWidget *widget;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QComboBox *comboBox;

    void setupUi(QWidget *typeChangeForm)
    {
        if (typeChangeForm->objectName().isEmpty())
            typeChangeForm->setObjectName(QStringLiteral("typeChangeForm"));
        typeChangeForm->resize(377, 319);
        pushButton = new QPushButton(typeChangeForm);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(150, 100, 101, 21));
        widget = new QWidget(typeChangeForm);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setGeometry(QRect(40, 40, 211, 31));
        horizontalLayout = new QHBoxLayout(widget);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(widget);
        label->setObjectName(QStringLiteral("label"));

        horizontalLayout->addWidget(label);

        comboBox = new QComboBox(widget);
        comboBox->setObjectName(QStringLiteral("comboBox"));

        horizontalLayout->addWidget(comboBox);


        retranslateUi(typeChangeForm);

        QMetaObject::connectSlotsByName(typeChangeForm);
    } // setupUi

    void retranslateUi(QWidget *typeChangeForm)
    {
        typeChangeForm->setWindowTitle(QApplication::translate("typeChangeForm", "Form", Q_NULLPTR));
        pushButton->setText(QApplication::translate("typeChangeForm", "\347\241\256\350\256\244", Q_NULLPTR));
        label->setText(QApplication::translate("typeChangeForm", "\351\200\211\346\213\251\346\235\203\351\231\220\357\274\232", Q_NULLPTR));
        comboBox->clear();
        comboBox->insertItems(0, QStringList()
         << QString()
         << QApplication::translate("typeChangeForm", "\347\256\241\347\220\206\345\221\230", Q_NULLPTR)
         << QApplication::translate("typeChangeForm", "\346\224\266\351\223\266\345\221\230", Q_NULLPTR)
         << QApplication::translate("typeChangeForm", "\345\216\250\345\270\210", Q_NULLPTR)
        );
    } // retranslateUi

};

namespace Ui {
    class typeChangeForm: public Ui_typeChangeForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TYPECHANGEFORM_H
