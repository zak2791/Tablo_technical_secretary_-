#ifndef FIGHT_H
#define FIGHT_H

#include <QLabel>
#include <QComboBox>
#include <QByteArray>
#include <QSplashScreen>

class ViewFight : public QSplashScreen
{
public:
    ViewFight(QPixmap _pix, QWidget* parent = nullptr) : QSplashScreen(parent){
        setGeometry(50, 50, _pix.width(), _pix.height());
        setPixmap(_pix);
        pix = _pix;
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
    Fight(QString, QString, QString, QString, int, int, QWidget* parent = nullptr);
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

    virtual void mousePressEvent(QMouseEvent*);
    virtual void paintEvent(QPaintEvent*);

private slots:
    void selectRef(int);

signals:
    void show_fight(QString);
    void select_fight(QString);

};

#endif // FIGHT_H
