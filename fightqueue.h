#ifndef FIGHTQUEUE_H
#define FIGHTQUEUE_H

#include <QDialog>
#include "fight.h"

class FightQueue : public QDialog
{
    Q_OBJECT
public:
    FightQueue(QWidget *parent = 0);

private:
    int currentY;
    virtual void closeEvent(QCloseEvent*);
    QList<Fight*> f;

private slots:
    void selectFight(QString);
    void showFight(QString);

signals:
    void select_fight(QString);
    void show_fight(QString);

};

#endif // FIGHTQUEUE_H
