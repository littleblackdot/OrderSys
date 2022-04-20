#include "form1.h"
#include "ui_form1.h"

Form1::Form1(int tableID, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Form1),
    tableID(tableID)
{
    QFile qss(":/white.qss");
    qss.open(QFile::ReadOnly);
    qApp->setStyleSheet(qss.readAll());
    qss.close();
    ui->setupUi(this);
    //ui->tabWidget->
    this->setWindowTitle("点菜");
    QStringList headText;
    headText<< "编号"<< "菜名"<< "价格"<< "备注";
    ui->tableWidget->setColumnCount(headText.count());
    ui->tableWidget->setHorizontalHeaderLabels(headText);
    headText.clear();
    headText<< "编号"<< "菜名"<< "价格";
    ui->tableWidget_2->setColumnCount(headText.count());
    ui->tableWidget_2->setHorizontalHeaderLabels(headText);
    ui->label->setText(QString("当前桌号：%1").arg(tableID));
    this->setFixedSize(420, 360);
    socket = new QTcpSocket;
    socket->connectToHost(QHostAddress(QString(SERVERIPADDR)), SERVERPORT);

    connect(socket, &QTcpSocket::readyRead,
            [&](){
                while(socket->bytesAvailable() > 0){
                    MessageFromServer mess;
                    QByteArray array = socket->read(4);
                    int len = bytesToInt(array);
                    QByteArray array2 = socket->read(len);
                    mess.praseJson(array2);
                    switch(mess.getAction()){
                        case MENU_SEND:{
                            updateMenu(mess);
                            break;
                        }
                        case ORDER_SEND:{
                            updateOrder(mess);
                            break;
                        }
                        case SERVER_DISHES:{
                            updateDishesStatus(mess);
                            break;
                        }
                        default: break;
                    }
                }
            });
    connect(socket, &QTcpSocket::disconnected,
            [&](){
            socket->close();
    });
    MessageFromClient mess;
    mess.setAction(REQUEST_MENU);
    sendMessToServer(mess);
    MessageFromClient mess2;
    mess2.setTableId(tableID);
    mess2.setAction(REQUEST_ORDER);
    sendMessToServer(mess2);
}

Form1::~Form1()
{
    delete ui;
}

void Form1::updateMenu(MessageFromServer mess)
{
    ui->tableWidget_2->setRowCount(0);
    vector<Dish> dishes = mess.getDishes();
    for(int i=0; i<dishes.size(); i++){
        int rowCount = ui->tableWidget_2->rowCount();
        ui->tableWidget_2->insertRow(rowCount);
        QTableWidgetItem *item = new QTableWidgetItem(QString("%1").arg(dishes[i].id));
        ui->tableWidget_2->setItem(rowCount, 0, item);
        item = new QTableWidgetItem(dishes[i].name);
        ui->tableWidget_2->setItem(rowCount, 1, item);
        item = new QTableWidgetItem(QString("%1").arg(dishes[i].price));
        ui->tableWidget_2->setItem(rowCount, 2, item);
    }
}

void Form1::updateOrder(MessageFromServer mess)
{
    ui->tableWidget->setRowCount(0);
    vector<Dish> dishes = mess.getDishes();
    ui->label_2->setText(QString("已点菜肴：%1个").arg(dishes.size()));
    for(int i=0; i<dishes.size(); i++){
        int rowCount = ui->tableWidget->rowCount();
        ui->tableWidget->insertRow(rowCount);
        QTableWidgetItem *item = new QTableWidgetItem(QString("%1").arg(dishes[i].id));
        ui->tableWidget->setItem(rowCount, 0, item);
        item = new QTableWidgetItem(dishes[i].name);
        ui->tableWidget->setItem(rowCount, 1, item);
        item = new QTableWidgetItem(QString("%1").arg(dishes[i].price));
        ui->tableWidget->setItem(rowCount, 2, item);
        item = new QTableWidgetItem(QString(""));
        ui->tableWidget->setItem(rowCount, 3, item);
    }
}

void Form1::updateDishesStatus(MessageFromServer mess)
{

}

QByteArray Form1::intToByte(int i)
{
    QByteArray abyte0;
    abyte0.resize(4);
    abyte0[0] = (uchar)  (0x000000ff & i);
    abyte0[1] = (uchar) ((0x0000ff00 & i) >> 8);
    abyte0[2] = (uchar) ((0x00ff0000 & i) >> 16);
    abyte0[3] = (uchar) ((0xff000000 & i) >> 24);
    return abyte0;
}

int Form1::bytesToInt(QByteArray bytes)
{
    int addr = bytes[0] & 0x000000FF;
    addr |= ((bytes[1] << 8) & 0x0000FF00);
    addr |= ((bytes[2] << 16) & 0x00FF0000);
    addr |= ((bytes[3] << 24) & 0xFF000000);
    return addr;
}

void Form1::sendMessToServer(MessageFromClient mess)
{
    QByteArray json = mess.toJsonData();
    json.push_front(intToByte(json.size()));
    socket->write(json, json.size());
}

void Form1::on_pushButton_clicked()
{
    //加菜
    int  curRow = ui->tableWidget_2->currentRow();

    if(curRow >= 0 ){
      MessageFromClient mess;
      int rowCount = ui->tableWidget->rowCount();
      if(ui->tableWidget->rowCount() == 0){
          ui->tableWidget->setRowCount(0);
      }
      ui->tableWidget->insertRow(rowCount);
      for(int i=0; i < ui->tableWidget_2->columnCount(); i++){
          qDebug()<< i;
          QTableWidgetItem *item = new QTableWidgetItem(ui->tableWidget_2->item(curRow, i)->text());
          ui->tableWidget->setItem(rowCount, i, item);
      }
      ui->label_2->setText(QString("已点菜肴：%1个").arg(ui->tableWidget->rowCount()));
      Dish dish;
      mess.setTableId(tableID);
      mess.setAction(ADD_DISHES);
      dish.id = ui->tableWidget_2->item(curRow, 0)->text().toInt();
      dish.name = ui->tableWidget_2->item(curRow, 0)->text();
      mess.addDishes(dish);
      mess.setAction(ADD_DISHES);
      sendMessToServer(mess);
    }
}

void Form1::on_pushButton_2_clicked()
{
    //退菜
    int curRow = ui->tableWidget->currentRow();
    if(curRow >= 0){
        QString str = QString("确认退菜： %1?").arg(ui->tableWidget->item(curRow, 1)->text());
        int ret = QMessageBox::question(this, "退菜提示",str);
        if(QMessageBox::Yes == ret){
            MessageFromClient mess;
            Dish dish;
            dish.id = ui->tableWidget->item(curRow, 0)->text().toInt();
            mess.addDishes(dish);
            mess.setAction(SUB_DISHES);
            mess.setTableId(tableID);
            sendMessToServer(mess);
            ui->tableWidget->removeRow(curRow);
        }
    }
}

void Form1::on_pushButton_3_clicked()
{
    //备注
    int curRow = ui->tableWidget->currentRow();
    if(curRow >= 0){
        if(ui->tableWidget->item(curRow, 3)->text() == ""){
            return;
        }
        QString str = QString("是否添加备注： %1?").arg(ui->tableWidget->item(curRow, 3)->text());
        int ret = QMessageBox::question(this, "添加备注提示",str);
        if(QMessageBox::Yes == ret){
            MessageFromClient mess;
            Dish dish;
            dish.id = ui->tableWidget->item(curRow, 0)->text().toInt();
            dish.comment = ui->tableWidget->item(curRow, 3)->text();
            mess.addDishes(dish);
            mess.setAction(ADD_COMMENT);
            mess.setTableId(tableID);
            sendMessToServer(mess);
        }
    }
}


void Form1::on_pushButton_4_clicked()
{
    //催菜
    int curRow = ui->tableWidget->currentRow();
    if(curRow >= 0){
        MessageFromClient mess;
        Dish dish;
        dish.id = ui->tableWidget->item(curRow, 0)->text().toInt();
        mess.addDishes(dish);
        mess.setAction(BUSY_DISHES);
        mess.setTableId(tableID);
        sendMessToServer(mess);
        QMessageBox::information(this, QString("提示"), QString("催菜成功"), QMessageBox::Cancel, QMessageBox::Cancel);
    }
}
