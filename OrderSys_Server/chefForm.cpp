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
        server.addSocket(socket);
        ServerThread *thread = new ServerThread(socket);
        connect(thread, SIGNAL(getRequest()), this, SLOT(dataUpDate()), Qt::QueuedConnection);
        thread->start();
    });
    this->move(600, 400);
    this->setFixedSize(570, 430);
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

void ChefForm::dataUpDate()
{
    DBHelper helper;
    QSqlQuery query(helper.getDB());
    QString sql("select *from orders");
    query.exec(sql);
    bool ret = query.exec("select * from stuInfo");
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
            QTableWidgetItem *item = new QTableWidgetItem(query.value(i).toString());
            ui->tableWidget->setItem(rowCount, i, item);
        }
    }
}
