#include "chefForm.h"
#include "ui_chefform.h"



ChefForm::ChefForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ChefForm)
{
    QFile qss(":/white.qss");
    qss.open(QFile::ReadOnly);
    qApp->setStyleSheet(qss.readAll());
    qss.close();
    ui->setupUi(this);
    this->setWindowTitle("厨房");
    timer = new QTimer;
    connect(timer, SIGNAL(timeout()), this, SLOT(updateTime()));
    timer->start(1000);
    QStringList headText;
    headText<<"编号" <<"桌号" <<"菜名" <<"状态" <<"备注";
    ui->tableWidget->setColumnCount(headText.count());
    ui->tableWidget->setHorizontalHeaderLabels(headText);
    ui->tableWidget->setRowCount(0);
    QTcpServer *listen = server.getServer();
    connect(listen, &QTcpServer::newConnection, [=](){
        QTcpSocket *socket = listen->nextPendingConnection(); //accept连接
        ServerThread *thread = new ServerThread(socket);
        connect(thread, SIGNAL(requestReport(int)), this, SLOT(dataUpDate(int)), Qt::QueuedConnection);//信号函数不能带变量名
        connect(thread, SIGNAL(tableIdReport(int , QTcpSocket*)), this, SLOT(addTableId(int , QTcpSocket*)), Qt::QueuedConnection);
        thread->start();
    });//每次有连接请求，调用lambda表达式， lamdba表达式执行完，连接才建立......., lamdba中不能对连接write， 不然只能读到空值。
    this->move(600, 400);
    this->setFixedSize(570, 430);
    dataUpDate(-1);
}

ChefForm::~ChefForm()
{
    delete ui;
}

void ChefForm::updateTime()
{
    QDateTime curDateTime = QDateTime::currentDateTime();
    QString cur = curDateTime.toString("yyyy.MM.dd hh:mm:ss ddd");
    ui->label->setText(cur);
}

void ChefForm::dataUpDate(int tableId)
{
    DBHelper helper;
    QSqlQuery query(helper.getDB());
    QSqlQuery query2(helper.getDB());
    QString sql("select *from orders");
    query.exec(sql);
    bool ret = query.exec("select * from orders");
    if(!ret){
        QSqlError err = query.lastError();   //得到最近一次的错误信息
        QString str = QString("错误信息:%1, %2").arg(err.driverText()).arg(err.databaseText());
        QMessageBox::warning(this, "提示", str);
    }
    ui->tableWidget->setRowCount(0);
    while(query.next()){
        int rowCount = ui->tableWidget->rowCount();
        ui->tableWidget->insertRow(rowCount);
        for(int i=0; i<ui->tableWidget->columnCount(); ++i){
            QTableWidgetItem *item;
            if(2 == i){
                QString sql2 = QString("select name from menu where id = %1").arg(query.value(2).toInt());
                ret = query2.exec(sql2);
                if(!ret){
                    QSqlError err = query.lastError();   //得到最近一次的错误信息
                    QString str = QString("错误信息:%1, %2").arg(err.driverText()).arg(err.databaseText());
                    QMessageBox::warning(this, "提示", str);
                }
                if(query2.next()){
                    item = new QTableWidgetItem(query2.value(0).toString());
                }
            }else if(3 == i){
                QString statusStrings[3] = {"待做", "缺菜", "催菜中"};
                int status = query.value(i).toInt();
                item = new QTableWidgetItem(statusStrings[status]);
            }else{
                item = new QTableWidgetItem(query.value(i).toString());
            }
            ui->tableWidget->setItem(rowCount, i, item);
        }
    }

    //向在线的客户端分发改变了的orders

    sendOrderstoClients(tableId);
}

void ChefForm::sendOrderstoClients(int tableId)
{
    DBHelper helper;
    QSqlQuery query(helper.getDB());
    QSqlQuery query2(helper.getDB());
    QString sql = QString("select * from orders where tableID = %1").arg(tableId);
    MessageFromServer messToC;
    messToC.setAction(ORDER_SEND);
    bool ret = query.exec(sql);
    if(!ret){
        QSqlError err = query.lastError();   //得到最近一次的错误信息
        QString str = QString("错误信息:%1, %2").arg(err.driverText()).arg(err.databaseText());
        qDebug()<< str << endl;
    }
    while(query.next()){
        Dish dish;
        dish.id = query.value(2).toInt();
        sql = QString("select * from menu where id = %1").arg(dish.id);
        bool ret = query2.exec(sql);
        if(!ret){
            QSqlError err = query.lastError();   //得到最近一次的错误信息
            QString str = QString("错误信息:%1, %2").arg(err.driverText()).arg(err.databaseText());
            qDebug()<< str << endl;
        }
        if(query2.next()){
            dish.name = query2.value(1).toString();
            dish.price = query2.value(2).toDouble();
        }
        messToC.addDishes(dish);
    }
    QByteArray json = messToC.toJsonData();
    auto socketMap = server.getSocketMap();
    auto pr = socketMap.equal_range(tableId);
    for(auto i = pr.first; i != pr.second; ++i){
        json.push_front(intToByte(json.size()));
        i->second->write(json, json.size());
    }
}

void ChefForm::addTableId(int tableId, QTcpSocket *socket)
{
    server.addSocket(tableId, socket);
}

QByteArray ChefForm::intToByte(int i)
{
    QByteArray abyte0;
    abyte0.resize(4);
    abyte0[0] = (uchar)  (0x000000ff & i);
    abyte0[1] = (uchar) ((0x0000ff00 & i) >> 8);
    abyte0[2] = (uchar) ((0x00ff0000 & i) >> 16);
    abyte0[3] = (uchar) ((0xff000000 & i) >> 24);
    return abyte0;
}

int ChefForm::bytesToInt(QByteArray bytes)
{
    int addr = bytes[0] & 0x000000FF;
    addr |= ((bytes[1] << 8) & 0x0000FF00);
    addr |= ((bytes[2] << 16) & 0x00FF0000);
    addr |= ((bytes[3] << 24) & 0xFF000000);
    return addr;
}
