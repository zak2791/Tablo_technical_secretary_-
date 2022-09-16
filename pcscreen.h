#ifndef PCSCREEN_H
#define PCSCREEN_H

#include <QWidget>

class PCScreen : public QWidget
{
    Q_OBJECT

public:
    PCScreen(QWidget *parent = nullptr);
    ~PCScreen();
};
#endif // PCSCREEN_H
