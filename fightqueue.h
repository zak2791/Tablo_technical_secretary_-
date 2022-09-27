#ifndef FIGHTQUEUE_H
#define FIGHTQUEUE_H

#include <QDialog>

class FightQueue : public QDialog
{
    Q_OBJECT
public:
    FightQueue(QWidget *parent = 0);

private:
    int currentY;
    virtual void closeEvent(QCloseEvent*);

private slots:
    void selectFight(QString);
    void showFight(QString);

signals:
    void select_fight(QString);
    void show_fight(QString);

};

#endif // FIGHTQUEUE_H
