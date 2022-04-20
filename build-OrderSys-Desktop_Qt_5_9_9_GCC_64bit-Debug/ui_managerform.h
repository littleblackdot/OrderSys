/********************************************************************************
** Form generated from reading UI file 'managerform.ui'
**
** Created by: Qt User Interface Compiler version 5.9.9
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MANAGERFORM_H
#define UI_MANAGERFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ManagerForm
{
public:
    QTabWidget *tabWidget;
    QWidget *tab;
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout;
    QPushButton *pushButton;
    QSpacerItem *horizontalSpacer;
    QPushButton *pushButton_2;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *pushButton_3;
    QSpacerItem *horizontalSpacer_3;
    QPushButton *pushButton_4;
    QTableWidget *tableWidget;
    QWidget *tab_2;
    QComboBox *comboBox;
    QTableWidget *tableWidget_2;
    QLineEdit *lineEdit;
    QPushButton *pushButton_5;
    QLabel *label;
    QWidget *tab_3;
    QTableWidget *tableWidget_3;
    QWidget *layoutWidget1;
    QVBoxLayout *verticalLayout_2;
    QPushButton *pushButton_6;
    QPushButton *pushButton_7;
    QPushButton *pushButton_8;
    QPushButton *pushButton_9;

    void setupUi(QWidget *ManagerForm)
    {
        if (ManagerForm->objectName().isEmpty())
            ManagerForm->setObjectName(QStringLiteral("ManagerForm"));
        ManagerForm->resize(546, 374);
        tabWidget = new QTabWidget(ManagerForm);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        tabWidget->setGeometry(QRect(10, 30, 521, 331));
        tab = new QWidget();
        tab->setObjectName(QStringLiteral("tab"));
        layoutWidget = new QWidget(tab);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(10, 10, 82, 271));
        verticalLayout = new QVBoxLayout(layoutWidget);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        pushButton = new QPushButton(layoutWidget);
        pushButton->setObjectName(QStringLiteral("pushButton"));

        verticalLayout->addWidget(pushButton);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        verticalLayout->addItem(horizontalSpacer);

        pushButton_2 = new QPushButton(layoutWidget);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));

        verticalLayout->addWidget(pushButton_2);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        verticalLayout->addItem(horizontalSpacer_2);

        pushButton_3 = new QPushButton(layoutWidget);
        pushButton_3->setObjectName(QStringLiteral("pushButton_3"));

        verticalLayout->addWidget(pushButton_3);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        verticalLayout->addItem(horizontalSpacer_3);

        pushButton_4 = new QPushButton(layoutWidget);
        pushButton_4->setObjectName(QStringLiteral("pushButton_4"));

        verticalLayout->addWidget(pushButton_4);

        tableWidget = new QTableWidget(tab);
        tableWidget->setObjectName(QStringLiteral("tableWidget"));
        tableWidget->setGeometry(QRect(110, 20, 381, 251));
        tableWidget->horizontalHeader()->setDefaultSectionSize(127);
        tabWidget->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QStringLiteral("tab_2"));
        comboBox = new QComboBox(tab_2);
        comboBox->setObjectName(QStringLiteral("comboBox"));
        comboBox->setGeometry(QRect(10, 10, 101, 21));
        tableWidget_2 = new QTableWidget(tab_2);
        tableWidget_2->setObjectName(QStringLiteral("tableWidget_2"));
        tableWidget_2->setGeometry(QRect(10, 40, 491, 241));
        lineEdit = new QLineEdit(tab_2);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));
        lineEdit->setGeometry(QRect(130, 10, 161, 21));
        pushButton_5 = new QPushButton(tab_2);
        pushButton_5->setObjectName(QStringLiteral("pushButton_5"));
        pushButton_5->setGeometry(QRect(310, 10, 80, 24));
        label = new QLabel(tab_2);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(410, 10, 101, 21));
        tabWidget->addTab(tab_2, QString());
        tab_3 = new QWidget();
        tab_3->setObjectName(QStringLiteral("tab_3"));
        tableWidget_3 = new QTableWidget(tab_3);
        tableWidget_3->setObjectName(QStringLiteral("tableWidget_3"));
        tableWidget_3->setGeometry(QRect(130, 30, 381, 231));
        layoutWidget1 = new QWidget(tab_3);
        layoutWidget1->setObjectName(QStringLiteral("layoutWidget1"));
        layoutWidget1->setGeometry(QRect(20, 20, 91, 241));
        verticalLayout_2 = new QVBoxLayout(layoutWidget1);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        pushButton_6 = new QPushButton(layoutWidget1);
        pushButton_6->setObjectName(QStringLiteral("pushButton_6"));

        verticalLayout_2->addWidget(pushButton_6);

        pushButton_7 = new QPushButton(layoutWidget1);
        pushButton_7->setObjectName(QStringLiteral("pushButton_7"));

        verticalLayout_2->addWidget(pushButton_7);

        pushButton_8 = new QPushButton(layoutWidget1);
        pushButton_8->setObjectName(QStringLiteral("pushButton_8"));

        verticalLayout_2->addWidget(pushButton_8);

        pushButton_9 = new QPushButton(layoutWidget1);
        pushButton_9->setObjectName(QStringLiteral("pushButton_9"));

        verticalLayout_2->addWidget(pushButton_9);

        tabWidget->addTab(tab_3, QString());

        retranslateUi(ManagerForm);

        tabWidget->setCurrentIndex(2);


        QMetaObject::connectSlotsByName(ManagerForm);
    } // setupUi

    void retranslateUi(QWidget *ManagerForm)
    {
        ManagerForm->setWindowTitle(QApplication::translate("ManagerForm", "Form", Q_NULLPTR));
        pushButton->setText(QApplication::translate("ManagerForm", "\346\267\273\345\212\240\347\224\250\346\210\267", Q_NULLPTR));
        pushButton_2->setText(QApplication::translate("ManagerForm", "\345\210\240\351\231\244\347\224\250\346\210\267", Q_NULLPTR));
        pushButton_3->setText(QApplication::translate("ManagerForm", "\344\277\256\346\224\271\345\257\206\347\240\201", Q_NULLPTR));
        pushButton_4->setText(QApplication::translate("ManagerForm", "\344\277\256\346\224\271\346\235\203\351\231\220", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(tab), QApplication::translate("ManagerForm", "\347\224\250\346\210\267\347\256\241\347\220\206", Q_NULLPTR));
        comboBox->clear();
        comboBox->insertItems(0, QStringList()
         << QString()
         << QApplication::translate("ManagerForm", "\345\275\223\346\227\245\346\266\210\350\264\271\346\203\205\345\206\265", Q_NULLPTR)
         << QApplication::translate("ManagerForm", "\345\275\223\346\234\210\346\266\210\350\264\271\346\203\205\345\206\265", Q_NULLPTR)
         << QApplication::translate("ManagerForm", "\346\214\211\350\264\246\345\215\225\346\237\245\350\257\242", Q_NULLPTR)
        );
        pushButton_5->setText(QApplication::translate("ManagerForm", "\346\237\245\350\257\242", Q_NULLPTR));
        label->setText(QApplication::translate("ManagerForm", "\346\200\273\350\256\241\357\274\232", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QApplication::translate("ManagerForm", "\350\264\246\345\215\225", Q_NULLPTR));
        pushButton_6->setText(QApplication::translate("ManagerForm", "\346\267\273\345\212\240", Q_NULLPTR));
        pushButton_7->setText(QApplication::translate("ManagerForm", "\345\210\240\351\231\244", Q_NULLPTR));
        pushButton_8->setText(QApplication::translate("ManagerForm", "\344\270\213\346\236\266", Q_NULLPTR));
        pushButton_9->setText(QApplication::translate("ManagerForm", "\344\270\212\346\236\266", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(tab_3), QApplication::translate("ManagerForm", "\350\217\234\350\260\261\347\256\241\347\220\206", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class ManagerForm: public Ui_ManagerForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MANAGERFORM_H
