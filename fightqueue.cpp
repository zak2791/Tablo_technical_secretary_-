#include "fightqueue.h"

#include <QScrollArea>
#include <QtSql>
#include <QSqlQuery>
#include <fight.h>

FightQueue::FightQueue(QWidget *parent) : QDialog(parent)
{
    setGeometry(10, 50, 600, 600);
    QScrollArea* scroll = new QScrollArea(this);
    scroll->setGeometry(10, 10, 580, 580);
    scroll->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    QWidget* fight_window = new QWidget();
    fight_window->setGeometry(0, 0, 560, 0);

    QSqlDatabase db = QSqlDatabase::addDatabase ( "QSQLITE");
    db.setDatabaseName("baza_in.db");

    currentY = 0;

    if (!db.open()){
        qDebug() << "Cannot open database:" << db.lastError();
    }else{
        QSqlQuery query;
        QString sql = "SELECT * FROM rounds";
        if(!query.exec(sql)){
            qDebug()<<"error database";
        }else{
            QSqlDatabase db_out = QSqlDatabase::addDatabase ("QSQLITE");
            db_out.setDatabaseName("baza_out.db");
            if(!db_out.open()){
                qDebug() << "Cannot open database:" << db.lastError();
            }else{
                QSqlQuery query_out;
                QString sql_out = "SELECT * FROM rounds WHERE fight = ";
                while(query.next()){
                    Fight f(query.value(3).toString(),
                            query.value(4).toString(),
                            query.value(5).toString(),
                            query.value(6).toString(),
                            query.value(2).toInt(),
                            query.value(7).toInt(),
                            fight_window);
                    f.move(0, currentY);
                    f.setObjectName(QString::number(query.value(7).toInt()));
                    if(!query_out.exec(sql_out + QString::number(query.value(7).toInt()))){
                        qDebug()<<"error database";
                    }else{
                        if(query_out.next()){
                            f.setPix(query_out.value(2).toByteArray());
                        }else{
                            f.setCombo();
                        }
                        connect(&f, SIGNAL(select_fight(QString)), this, SLOT(selectFight(QString)));
                        connect(&f, SIGNAL(show_fight(QString)), this, SLOT(showFight(QString)));
                        currentY += 110;
                    }
                }
                fight_window->setGeometry(0, 0, 560, currentY);
                scroll->setWidget(fight_window);
                int max_fight = 0;
                if(!query_out.exec("SELECT MAX(fight) FROM rounds")){
                    qDebug()<<"error database";
                }else{
                    if(query_out.next()){
                        max_fight = query_out.value(0).toInt();
                        Fight* obj = findChild<Fight*>(QString::number(max_fight));
                        scroll->ensureWidgetVisible(obj);
                    }
                }
                db_out.close();
            }
        }
        db.close();
    }
}

void FightQueue::selectFight(QString s){
    select_fight(s);
}

void FightQueue::showFight(QString s){
    show_fight(s);
}

void FightQueue::closeEvent(QCloseEvent*){
    reject();
}
