#ifndef SERVERWIDGET_H
#define SERVERWIDGET_H

#include <QWidget>
#include <QTcpServer>
#include <QTcpSocket>
namespace Ui {
class ServerWidget;
}

class ServerWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ServerWidget(QWidget *parent = 0);
    ~ServerWidget();

private slots:
    void on_buttonSend_clicked();

    void on_buttonClose_clicked();

private:
    Ui::ServerWidget *ui;
    QTcpServer *tcpServer;//监听套接字
    QTcpSocket *tcpSocket = Q_NULLPTR;//通信套接字
};

#endif // SERVERWIDGET_H
