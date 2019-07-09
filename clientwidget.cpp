#include "clientwidget.h"
#include "ui_clientwidget.h"
#include <QHostAddress>

ClientWidget::ClientWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ClientWidget)
{
    ui->setupUi(this);
    tcpSocket = new QTcpSocket(this);
    setWindowTitle("客户端");
    connect(tcpSocket,&QTcpSocket::connected,
            [=](){
        ui->textEditRead->setText("成功和服务器建立好连接");
    });

    connect(tcpSocket,&QTcpSocket::readyRead,
            [=](){
        //从通信套接字中取出内容
        QByteArray array = tcpSocket->readAll();
        ui->textEditRead->append(array);
    });
}

ClientWidget::~ClientWidget()
{
    delete ui;
}

void ClientWidget::on_buttonConnect_clicked()
{
    //获取服务器的IP和端口号
    QString ip = ui->lineEditIP->text();
    quint16 port = ui->lineEditPort->text().toInt();

    //主动和服务器建立连接
    tcpSocket->connectToHost(QHostAddress(ip),port);
}

void ClientWidget::on_buttonSend_clicked()
{
    //获取编辑框的内容
    QString str = ui->textEditWrite->toPlainText();
    //发送数据
    tcpSocket->write(str.toUtf8().data());
}

void ClientWidget::on_buttonClose_clicked()
{
    tcpSocket->disconnectFromHost();
    tcpSocket->close();
}
