#ifndef FIGHT_H
#define FIGHT_H

#include <QLabel>
#include <QComboBox>
#include <QByteArray>
#include <QSplashScreen>
#include <QSqlDatabase>
#include <QSqlQuery>
class ViewFight : public QSplashScreen
{
public:
    ViewFight(QPixmap _pix, QWidget* parent = nullptr) : QSplashScreen(parent){
        //setGeometry(500, 500, _pix->width(), _pix->height());
        pix = _pix;
        //QPixmap pixmap("1.png");
        setPixmap(pix);

    }

private:
    QPixmap pix;

    virtual void mousePressEvent(QMouseEvent*){
        deleteLater();
    }

};

class Fight : public QLabel
{
    Q_OBJECT

public:
    Fight(QString, QString, QString, QString, QString, int, QWidget* parent = nullptr);
    void setPix(QByteArray);
    void setCombo(void);

    QString red;
    QString blue;
    QLabel* lblFight;
    QString title;

private:
    QString note_red;
    QString note_blue;
    int num_fight;

    QComboBox* cmbMain;
    QString refMain;
    QComboBox* cmbRef;
    QString refRef;
    QComboBox* cmbSaid;
    QString refSaid;

    QSqlDatabase db;
    QSqlQuery query;

    virtual void mousePressEvent(QMouseEvent*);
    virtual void paintEvent(QPaintEvent*);

private slots:
    void selectRef(int);

signals:
    void show_fight(QString);
    void select_fight(QString);

};

#endif // FIGHT_H
