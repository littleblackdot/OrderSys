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
    QStringList headText;
    headText<<"账号"<<"用户类型"<<"用户名";
    ui->tableWidget->setColumnCount(headText.count());
    ui->tableWidget->setHorizontalHeaderLabels(headText);
    headText.clear();
    headText<< "交易号"<< "桌号"<< "菜品编号"<< "菜品名称"<< "菜品价格"<< "状态"<< "交易时间"<< "操作员";
    ui->tableWidget_2->setColumnCount(headText.count());
    ui->tableWidget_2->setHorizontalHeaderLabels(headText);
    headText.clear();
    headText<<"编号" <<"菜名" <<"价格" <<"状态";
    ui->tableWidget_3->setColumnCount(headText.count());
    ui->tableWidget_3->setHorizontalHeaderLabels(headText);
    showMenu();
    showUsers();

}

ManagerForm::~ManagerForm()
{
    delete ui;
}

void ManagerForm::showUsers()
{
    DBHelper helper;
    QSqlQuery query(helper.getDB());
    QString sql = QString("select * from user");
    QString userTypes[3] = {"管理员", "收银员", "厨师"};
    bool ret = query.exec(sql);
    if(!ret){
        QSqlError err = query.lastError();   //得到最近一次的错误信息
        QString str = QString("错误信息:%1, %2").arg(err.driverText()).arg(err.databaseText());
        qDebug()<< str << endl;
    }
    ui->tableWidget->setRowCount(0);
    while(query.next()){
        int rowCount = ui->tableWidget->rowCount();
        ui->tableWidget->insertRow(rowCount);
        for(int i=0; i<ui->tableWidget->columnCount(); i++){
            if(1 == i){
                QTableWidgetItem *item =  new QTableWidgetItem(userTypes[query.value(i).toInt()]);
                ui->tableWidget->setItem(rowCount, i, item);
                continue;
            }
            QTableWidgetItem *item =  new QTableWidgetItem(query.value(i).toString());
            ui->tableWidget->setItem(rowCount, i, item);
        }
    }
}

void ManagerForm::showMenu()
{
    DBHelper helper;
    QSqlQuery query(helper.getDB());
    QString sql = QString("select * from menu");
    QString statusList[2] = {"上架中", "下架中"};
    bool ret = query.exec(sql);
    if(!ret){
        QSqlError err = query.lastError();   //得到最近一次的错误信息
        QString str = QString("错误信息:%1, %2").arg(err.driverText()).arg(err.databaseText());
        qDebug()<< str << endl;
    }
    ui->tableWidget_3->setRowCount(0);
    while(query.next()){
        int rowCount = ui->tableWidget_3->rowCount();
        ui->tableWidget_3->insertRow(rowCount);
        for(int i=0; i<ui->tableWidget_3->columnCount(); i++){
            if(3 == i){
                QTableWidgetItem *item =  new QTableWidgetItem(statusList[query.value(i).toInt()]);
                ui->tableWidget_3->setItem(rowCount, i, item);
                continue;
            }
            QTableWidgetItem *item =  new QTableWidgetItem(query.value(i).toString());
            ui->tableWidget_3->setItem(rowCount, i, item);
        }
    }
}

void ManagerForm::showBills(int option, QString billId)
{
    DBHelper helper;
    QSqlQuery query(helper.getDB());
    QSqlQuery query2(helper.getDB());
    QString sql;
    double total = 0;
    switch(option){
        case 0: {
            return;
        }
        case 1:{//当日账单
            sql = QString("select * from bills where  DATEDIFF(now(), time) = 0");
            break;
        }
        case 2: {//当月账单
            sql = QString("select * from bills where  DATEDIFF(now(), time) <= 31");
            break;
        }
        case 3:{//按单号查找
            sql = QString("select * from bills where dealID = %1").arg(billId);
            break;
        }
        default: break;
    }
    bool ret = query.exec(sql);
    if(!ret){
        QSqlError err = query.lastError();   //得到最近一次的错误信息
        QString str = QString("错误信息:%1, %2").arg(err.driverText()).arg(err.databaseText());
        qDebug()<< str << endl;
    }
    ui->tableWidget_2->setRowCount(0);
    while(query.next()){
        int rowCount = ui->tableWidget_2->rowCount();
        ui->tableWidget_2->insertRow(rowCount);
        int dishId = query.value(2).toInt();
        for(int i=0; i<3; i++){
            QTableWidgetItem *item =  new QTableWidgetItem(query.value(i).toString());
            ui->tableWidget_2->setItem(rowCount, i, item);
        }
        QString sql2 = QString("select * from menu where id = %1").arg(dishId);
        ret = query2.exec(sql2);
        if(!ret){
            QSqlError err = query2.lastError();   //得到最近一次的错误信息
            QString str = QString("错误信息:%1, %2").arg(err.driverText()).arg(err.databaseText());
            qDebug()<< str << endl;
        }
        if(query2.next()){
            QTableWidgetItem *item =  new QTableWidgetItem(query2.value(1).toString());
            ui->tableWidget_2->setItem(rowCount, 3, item);
            item = new QTableWidgetItem(query2.value(2).toString());
            ui->tableWidget_2->setItem(rowCount, 4, item);
        }
        if(3 == query.value(3).toInt()){
            QTableWidgetItem *item =  new QTableWidgetItem("已做");
            total += query2.value(2).toDouble();
            ui->tableWidget_2->setItem(rowCount, 5, item);
        }else{
            QTableWidgetItem *item =  new QTableWidgetItem("未做");
            ui->tableWidget_2->setItem(rowCount, 5, item);
        }
        QTableWidgetItem *item =  new QTableWidgetItem(query.value(4).toString());
        ui->tableWidget_2->setItem(rowCount, 6, item);
        item =  new QTableWidgetItem(query.value(5).toString());
        ui->tableWidget_2->setItem(rowCount, 7, item);
    }
    ui->label->setText(QString("总计： %1").arg(total));
}

void ManagerForm::on_pushButton_5_clicked()
{
    //账单查询
    int option = ui->comboBox->currentIndex();
    qDebug() << ui->comboBox->currentIndex()<<endl;
    showBills(option, ui->lineEdit->text());
}

void ManagerForm::on_pushButton_clicked()
{
    //添加用户
    Form *from = new Form;
    from->show();
    connect(from, SIGNAL(newUser()), this, SLOT(updateUserTable()));
}

void ManagerForm::updateUserTable()
{
    showUsers();
}

void ManagerForm::updateMenuTable()
{
    showMenu();
}

void ManagerForm::on_pushButton_2_clicked()
{
    //删除用户
    int curRow = ui->tableWidget->currentRow();
    if(curRow < 0){
        return ;
    }
    QString str = QString("确认删除用户： %1?").arg(ui->tableWidget->item(curRow, 2)->text());
    int ret = QMessageBox::question(this, "删除提示",str);
    if(QMessageBox::Yes == ret){
        int userId = ui->tableWidget->item(curRow, 0)->text().toInt();
        DBHelper helper;
        QSqlQuery query(helper.getDB());
        QString sql = QString("delete from user where id = %1").arg(userId);
        bool ret = query.exec(sql);
        if(!ret){
            QSqlError err = query.lastError();   //得到最近一次的错误信息
            QString str = QString("错误信息:%1, %2").arg(err.driverText()).arg(err.databaseText());
            qDebug()<< str << endl;
        }
        ui->tableWidget->removeRow(curRow);
    }
}

void ManagerForm::on_pushButton_4_clicked()
{
    //权限修改
    int curRow = ui->tableWidget->currentRow();
    if(curRow < 0){
        return;
    }
    int userId = ui->tableWidget->item(curRow, 0)->text().toInt();
    typeChangeForm *form = new typeChangeForm(userId);
    form->show();
    connect(form, SIGNAL(userChange()), this, SLOT(updateUserTable()));
}

void ManagerForm::on_pushButton_3_clicked()
{
    //密码修改
    int curRow = ui->tableWidget->currentRow();
    if(curRow < 0){
        return;
    }
    int userId = ui->tableWidget->item(curRow, 0)->text().toInt();
    pwdChangeForm *form = new pwdChangeForm(userId);
    form->show();
}

void ManagerForm::on_pushButton_6_clicked()
{
    //菜品添加
    addDishForm *form = new addDishForm;
    form->show();
    connect(form, SIGNAL(newDish()), this, SLOT(updateMenuTable()));
}

void ManagerForm::on_pushButton_7_clicked()
{
    //菜品删除
    int curRow = ui->tableWidget_3->currentRow();
    if(curRow < 0){
        return;
    }
    int dishId = ui->tableWidget_3->item(curRow, 0)->text().toInt();
    DBHelper helper;
    QSqlQuery query(helper.getDB());
    QString sql = QString("delete from menu where id = %1").arg(dishId);
    bool ret = query.exec(sql);
    if(!ret){
        QSqlError err = query.lastError();   //得到最近一次的错误信息
        QString str = QString("错误信息:%1, %2").arg(err.driverText()).arg(err.databaseText());
        QMessageBox::warning(this, "提示", str);
    }
    ui->tableWidget_3->removeRow(curRow);
}

void ManagerForm::on_pushButton_8_clicked()
{
    //下架菜品
    int curRow = ui->tableWidget_3->currentRow();
    if(curRow < 0){
        return;
    }
    int dishId = ui->tableWidget_3->item(curRow, 0)->text().toInt();
    DBHelper helper;
    QSqlQuery query(helper.getDB());
    QString sql = QString("update menu set status = 1 where id = %1").arg(dishId);
    bool ret = query.exec(sql);
    if(!ret){
        QSqlError err = query.lastError();   //得到最近一次的错误信息
        QString str = QString("错误信息:%1, %2").arg(err.driverText()).arg(err.databaseText());
        QMessageBox::warning(this, "提示", str);
    }
    QTableWidgetItem *item = new QTableWidgetItem("下架中");
    ui->tableWidget_3->setItem(curRow, 3, item);
}

void ManagerForm::on_pushButton_9_clicked()
{
    //上架菜品
    int curRow = ui->tableWidget_3->currentRow();
    if(curRow < 0){
        return;
    }
    int dishId = ui->tableWidget_3->item(curRow, 0)->text().toInt();
    DBHelper helper;
    QSqlQuery query(helper.getDB());
    QString sql = QString("update menu set status = 0 where id = %1").arg(dishId);
    bool ret = query.exec(sql);
    if(!ret){
        QSqlError err = query.lastError();   //得到最近一次的错误信息
        QString str = QString("错误信息:%1, %2").arg(err.driverText()).arg(err.databaseText());
        QMessageBox::warning(this, "提示", str);
    }
    QTableWidgetItem *item = new QTableWidgetItem("上架中");
    ui->tableWidget_3->setItem(curRow, 3, item);
}
