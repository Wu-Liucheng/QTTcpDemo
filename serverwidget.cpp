#include "serverwidget.h"
#include "ui_serverwidget.h"

ServerWidget::ServerWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ServerWidget)
{
    ui->setupUi(this);

    //监听套接字，指定父对象，让其自动回收空间
    tcpServer = new QTcpServer(this);\

    tcpServer->listen(QHostAddress::Any,8888);

    setWindowTitle("服务器：8888");

    connect(tcpServer,&QTcpServer::newConnection,[=](){
        //取出建立好连接的套接字
        tcpSocket = tcpServer->nextPendingConnection();

        //获取对方的IP和端口
        QString ip = tcpSocket->peerAddress().toString();
        quint16 port = tcpSocket->peerPort();
        QString temp = QString("[%1:%2]:成功连接").arg(ip).arg(port);
        ui->textEditRead->setText(temp);
        connect(tcpSocket,&QTcpSocket::readyRead,
                [=](){
            //从通信套接字中取出内容
            QByteArray array = tcpSocket->readAll();
            ui->textEditRead->append(array);
        });
    });
}

ServerWidget::~ServerWidget()
{
    delete ui;
}

void ServerWidget::on_buttonSend_clicked()
{
    //获取编辑区的内容
    QString str = ui->textEditWrite->toPlainText();
    //给对方发送数据，使用套接字使tcpSocket
    if(tcpSocket != Q_NULLPTR)
        tcpSocket->write(str.toUtf8().data());
}

void ServerWidget::on_buttonClose_clicked()
{
    //和客户端断开连接
    if(tcpSocket != Q_NULLPTR)
    {
        tcpSocket->disconnectFromHost();
        tcpSocket->close();
        tcpSocket = Q_NULLPTR;
    }
}
