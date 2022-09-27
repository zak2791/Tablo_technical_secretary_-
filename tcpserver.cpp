#include "tcpserver.h"

#include <QNetworkDatagram>
#include <QMessageBox>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QTcpSocket>

TcpServer::TcpServer(int _mat, QObject *parent) : QObject(parent)
{
    port = _mat * 2000 + 2;

    server = new QTcpServer(this);
    if (!server->listen(QHostAddress::Any, port)) {
        QMessageBox::critical (0, "Server Error", "UnaЫe to start the зerver:" + server->errorString());
        server->close();
        return;
    }
    connect(server, SIGNAL(newConnection()), this, SLOT(slotNewConnection()));

}

void TcpServer::slotNewConnection(void){
    qDebug()<<"new connection";
    QTcpSocket* pClientSocket = server->nextPendingConnection();
    connect(pClientSocket, SIGNAL(disconnected()),
    pClientSocket, SLOT(deleteLater()));
    connect(pClientSocket, SIGNAL(readyRead()), this, SLOT(slotReadClient()));
}

void TcpServer::slotReadClient(){
    QTcpSocket* pClientSocket = (QTcpSocket*)sender();
    QTextStream in(pClientSocket);
    QString c;
    while(pClientSocket->bytesAvailable())
        in >> c;
    QList<QString> dd = c.split("=");
    if(dd.length() < 3)
        return;
    QString rnd = dd.at(0);
    QString rnd_name = dd.at(1);
    QList<QString> ddd = dd.at(2).split("<");
    qDebug()<<rnd<<rnd_name<<ddd;
    QSqlDatabase db = QSqlDatabase::addDatabase ("QSQLITE");
    db.setDatabaseName("baza_in.db");
    if(!db.open()){
        qDebug()<<"error open database";
        return;
    }
    QSqlQuery query;
    QString sql = "SELECT * FROM rounds WHERE num_round = " + rnd;
    if(!query.exec(sql)){
        qDebug()<<"error database"<<sql;
        db.close();
        return;
    }else{
        if(!query.next()){
            for(int i = 1; i < ddd.length(); i++){
                QList<QString> e = ddd.at(i).split(";");
                qDebug()<<e;
                sql = "INSERT INTO rounds (num_round, name_round, name_red, name_blue, note_red, note_blue, num_fight) VALUES ('%1', '%2', '%3', '%4', '%5', '%6', '%7')";
                QString str = sql.arg(rnd).arg(rnd_name).arg(e.at(0)).arg(e.at(1)).arg(e.at(2)).arg(e.at(3)).arg(e.at(4));
                QSqlQuery q;
                if(!q.exec(str)){
                    qDebug()<<"error database"<<q.lastError();
                    db.close();
                    return;
                }
            }
            QTextStream out(pClientSocket);
            out << rnd;
        }
    }
    db.close();
}




