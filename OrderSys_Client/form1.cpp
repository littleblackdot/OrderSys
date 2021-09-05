#include "form1.h"
#include "ui_form1.h"

Form1::Form1(int tableID, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Form1),
    tableID(tableID)
{
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
            [=](){
                MessageFromServer mess;
                QByteArray array = socket->readAll();
                mess.praseJson(array);
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
            });
    MessageFromClient mess;
    mess.setAction(REQUEST_MENU);
    QByteArray json = mess.toJsonData();
    json.push_front(intToByte(json.size()));
    socket->write(json, json.size());
    MessageFromClient mess2;
    mess2.setTableId(tableID);
    mess2.setAction(REQUEST_ORDER);
    QByteArray json2 = mess2.toJsonData();
    json2.push_front(intToByte(json2.size()));
    socket->write(json2, json2.size());
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

void Form1::on_pushButton_clicked()
{
    //加菜
}

void Form1::on_pushButton_2_clicked()
{
    //退菜

}

void Form1::on_pushButton_3_clicked()
{
    //备注
}

