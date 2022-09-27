#include "protocolwindow.h"
#include <QGridLayout>
#include <QBuffer>
#include <QThread>
#include <QSqlDatabase>
#include <QSqlQuery>
#include "fight.h"

int currentX;

ProtocolWindow::ProtocolWindow(QWidget* p) : QWidget(p)
{
    currentX = 0;
    q = nullptr;
    address = "";
    mat = 0;
    vin = 0;                //0 - нет победителя, 1 - синий, 2 - красный

    QPalette pal = palette();
    pal.setColor(QPalette::Window, QColor("white"));
    setPalette(pal);
    setAutoFillBackground(true);

    lastItem = nullptr;
    pairedItem = nullptr;

    btnNk = new LeftRightPushButton("Нк");
    btnNk->setObjectName("NK");
    btnNk->setMinimumSize(30, 30);
    btnNk->setFocusPolicy(Qt::NoFocus);
    connect(btnNk, SIGNAL(left_right_clicked(bool, QString)), this, SLOT(Rate(bool, QString)));

    btnV = new LeftRightPushButton("V");
    btnV->setObjectName("V");
    btnV->setMinimumSize(30, 30);
    btnV->setFocusPolicy(Qt::NoFocus);
    connect(btnV, SIGNAL(left_right_clicked(bool, QString)), this, SLOT(Rate(bool, QString)));

    btnBP = new LeftRightPushButton("БП", this);
    btnBP->setObjectName("BP");
    btnBP->setMinimumSize(30, 30);
    btnBP->setFocusPolicy(Qt::NoFocus);
    connect(btnBP, SIGNAL(left_right_clicked(bool, QString)), this, SLOT(Rate(bool, QString)));

    btnUd = new LeftRightPushButton("Уд", this);
    btnUd->setObjectName("Ud");
    btnUd->setMinimumSize(30, 30);
    btnUd->setFocusPolicy(Qt::NoFocus);
    connect(btnUd, SIGNAL(left_right_clicked(bool, QString)), this, SLOT(Rate(bool, QString)));

    btnNkT = new LeftRightPushButton("Нк-Т", this);
    btnNkT->setObjectName("NKT");
    btnNkT->setMinimumSize(30, 30);
    btnNkT->setFocusPolicy(Qt::NoFocus);
    connect(btnNkT, SIGNAL(left_right_clicked(bool, QString)), this, SLOT(Rate(bool, QString)));

    btnYP = new LeftRightPushButton("ЯП", this);
    btnYP->setObjectName("YP");
    btnYP->setMinimumSize(30, 30);
    btnYP->setFocusPolicy(Qt::NoFocus);
    connect(btnYP, SIGNAL(left_right_clicked(bool, QString)), this, SLOT(Rate(bool, QString)));

    btnPT = new LeftRightPushButton("+", this);
    btnPT->setObjectName("PLUS");
    btnPT->setMinimumSize(30, 30);
    btnPT->setFocusPolicy(Qt::NoFocus);
    connect(btnPT, SIGNAL(left_right_clicked(bool, QString)), this, SLOT(Rate(bool, QString)));

    btnOPB = new LeftRightPushButton("ОПБ", this);
    btnOPB->setObjectName("OPB");
    btnOPB->setMinimumSize(30, 30);
    btnOPB->setFocusPolicy(Qt::NoFocus);
    connect(btnOPB, SIGNAL(left_right_clicked(bool, QString)), this, SLOT(Rate(bool, QString)));

    btnNPB = new LeftRightPushButton("НПБ", this);
    btnNPB->setObjectName("NPB");
    btnNPB->setMinimumSize(30, 30);
    btnNPB->setFocusPolicy(Qt::NoFocus);
    connect(btnNPB, SIGNAL(left_right_clicked(bool, QString)), this, SLOT(Rate(bool, QString)));

    btnNkd = new LeftRightPushButton("Нкд", this);
    btnNkd->setObjectName("Nkd");
    btnNkd->setMinimumSize(30, 30);
    btnNkd->setFocusPolicy(Qt::NoFocus);
    connect(btnNkd, SIGNAL(left_right_clicked(bool, QString)), this, SLOT(Rate(bool, QString)));

    btnTNk = new LeftRightPushButton("ТНк", this);
    btnTNk->setObjectName("TNK");
    btnTNk->setMinimumSize(30, 30);
    btnTNk->setFocusPolicy(Qt::NoFocus);
    connect(btnTNk, SIGNAL(left_right_clicked(bool, QString)), this, SLOT(Rate(bool, QString)));

    btnAr = new LeftRightPushButton("Ар", this);
    btnAr->setObjectName("AR");
    btnAr->setMinimumSize(30, 30);
    btnAr->setFocusPolicy(Qt::NoFocus);
    connect(btnAr, SIGNAL(left_right_clicked(bool, QString)), this, SLOT(Rate(bool, QString)));

    btnPs = new LeftRightPushButton("Пс", this);
    btnPs->setObjectName("PS");
    btnPs->setMinimumSize(30, 30);
    btnPs->setFocusPolicy(Qt::NoFocus);
    connect(btnPs, SIGNAL(left_right_clicked(bool, QString)), this, SLOT(Rate(bool, QString)));

    btnBack = new LeftRightPushButton("<-", this);
    btnNk->setObjectName("NK");     //?????????????
    btnBack->setMinimumSize(40, 40);
    btnBack->setFocusPolicy(Qt::NoFocus);
    connect(btnBack, SIGNAL(left_right_clicked(bool, QString)), this, SLOT(Back()));

    btn2 = new LeftRightPushButton("2", this);
    btn2->setObjectName("TWO");
    btn2->setMinimumSize(40, 40);
    btn2->setFocusPolicy(Qt::NoFocus);
    connect(btn2, SIGNAL(left_right_clicked(bool, QString)), this, SLOT(Rate(bool, QString)));

    btn1 = new LeftRightPushButton("1", this);
    btn1->setObjectName("btn1");
    btn1->setMinimumSize(40, 40);
    btn1->setFocusPolicy(Qt::NoFocus);
    connect(btn1, SIGNAL(left_right_clicked(bool, QString)), this, SLOT(Rate(bool, QString)));

    btnA = new LeftRightPushButton("A", this);
    btnA->setObjectName("A");
    btnA->setMinimumSize(40, 40);
    btnA->setFocusPolicy(Qt::NoFocus);
    connect(btnA, SIGNAL(left_right_clicked(bool, QString)), this, SLOT(Rate(bool, QString)));

    btn2P = new LeftRightPushButton("", this);
    btn2P->setObjectName("2P");
    btn2P->setIcon(QIcon("A2.png"));
    btn2P->setMinimumSize(40, 40);
    btn2P->setFocusPolicy(Qt::NoFocus);
    connect(btn2P, SIGNAL(left_right_clicked(bool, QString)), this, SLOT(Rate(bool, QString)));

    btn1P = new LeftRightPushButton("", this);
    btn1P->setObjectName("1P");
    btn1P->setIcon(QIcon("A1.png"));
    btn1P->setMinimumSize(40, 40);
    btn1P->setFocusPolicy(Qt::NoFocus);
    connect(btn1P, SIGNAL(left_right_clicked(bool, QString)), this, SLOT(Rate(bool, QString)));

    btnAP = new LeftRightPushButton("", this);
    btnAP->setObjectName("AP");
    btnAP->setIcon(QIcon("AA.png"));
    btnAP->setMinimumSize(40, 40);
    btnAP->setFocusPolicy(Qt::NoFocus);
    connect(btnAP, SIGNAL(left_right_clicked(bool, QString)), this, SLOT(Rate(bool, QString)));

    btnZv = new LeftRightPushButton("Зв", this);
    btnZv->setObjectName("ZV");
    btnZv->setMinimumSize(40, 40);
    btnZv->setFocusPolicy(Qt::NoFocus);
    connect(btnZv, SIGNAL(left_right_clicked(bool, QString)), this, SLOT(Rate(bool, QString)));

    btnVyh = new LeftRightPushButton("В", this);
    btnVyh->setObjectName("VYH");
    btnVyh->setMinimumSize(40, 40);
    btnVyh->setFocusPolicy(Qt::NoFocus);
    connect(btnVyh, SIGNAL(left_right_clicked(bool, QString)), this, SLOT(Rate(bool, QString)));

    btnZp = new LeftRightPushButton("Зп", this);
    btnZp->setObjectName("ZP");
    btnZp->setMinimumSize(40, 40);
    btnZp->setFocusPolicy(Qt::NoFocus);
    connect(btnZp, SIGNAL(left_right_clicked(bool, QString)), this, SLOT(Rate(bool, QString)));

    btnP1 = new LeftRightPushButton("П1", this);
    btnP1->setObjectName("P1");
    btnP1->setMinimumSize(40, 40);
    btnP1->setFocusPolicy(Qt::NoFocus);
    connect(btnP1, SIGNAL(left_right_clicked(bool, QString)), this, SLOT(Rate(bool, QString)));

    btnP2 = new LeftRightPushButton("П2", this);
    btnP2->setObjectName("P2");
    btnP2->setMinimumSize(40, 40);
    btnP2->setFocusPolicy(Qt::NoFocus);
    connect(btnP2, SIGNAL(left_right_clicked(bool, QString)), this, SLOT(Rate(bool, QString)));

    btnNy = new LeftRightPushButton("н/я", this);
    btnNy->setObjectName("NY");
    btnNy->setMinimumSize(30, 30);
    btnNy->setFocusPolicy(Qt::NoFocus);
    connect(btnNy, SIGNAL(left_right_clicked(bool, QString)), this, SLOT(Rate(bool, QString)));

    btnDoc = new LeftRightPushButton("сн.вр", this);
    btnDoc->setObjectName("DOCT");
    btnDoc->setMinimumSize(30, 30);
    btnDoc->setFocusPolicy(Qt::NoFocus);
    connect(btnDoc, SIGNAL(left_right_clicked(bool, QString)), this, SLOT(Rate(bool, QString)));

    btnVin = new LeftRightPushButton("VIN", this);
    btnVin->setObjectName("VIN");
    btnVin->setMinimumSize(30, 30);
    btnVin->setFocusPolicy(Qt::NoFocus);
    connect(btnVin, SIGNAL(left_right_clicked(bool, QString)), this, SLOT(Rate(bool, QString)));

    BallsRed = new QLabel("0");
    BallsRed->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    BallsRed->setStyleSheet("color:black; font-size: 20px; border-style:solid; border-left:none;"
                                        "border-width:1px; border-color:black");
    BallsBlue = new QLabel("0");
    BallsBlue->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    BallsBlue->setStyleSheet("color:black; font-size: 20px;border-style:solid; border-top:none;"
                                         "border-left:none; border-width:1px; border-color:black");

    AktRed = new QLabel("0");
    AktRed->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    AktRed->setStyleSheet("color:black; font-size: 16px; border-style:solid; border-top:none;"
                                      "border-left:none; border-width:1px; border-color:black");
    AktBlue = new QLabel("0");
    AktBlue->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    AktBlue->setStyleSheet("color:black; font-size: 16px; border-style:solid; border-top:none;"
                                       "border-left:none; border-width:1px; border-color:black");

    ResultRed = new QLabel("");
    ResultRed->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    ResultRed->setStyleSheet("color:black; font-size: 20px; border-style:solid;"
                                       "border-left:none; border-width:1px; border-color:black");
    ResultBlue = new QLabel("");
    ResultBlue->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    ResultBlue->setStyleSheet("color:black; font-size: 20px; border-style:solid; border-top:none;"
                                       "border-left:none; border-width:1px; border-color:black");

    QLabel lblRef("Судьи");
    lblRef.setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    lblRef.setStyleSheet("border-style:solid; border-left:none;"
                                       "border-bottom:none; border-width:1px; border-color:black");

    nameMain = new QLabel("рук. ковра");
    nameMain->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
    nameMain->setStyleSheet("border-style:solid; border-left:none; border-top: none;"
                                       "border-bottom:none; border-width:1px; border-color:black");

    nameRef = new QLabel("рефери");
    nameRef->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
    nameRef->setStyleSheet("border-style:solid; border-left:none; border-top: none;"
                                       "border-bottom:none; border-width:1px; border-color:black");

    nameSide = new QLabel("боковой");
    nameSide->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
    nameSide->setStyleSheet("border-style:solid; border-left:none; border-top: none;"
                                       "border-bottom:none; border-width:1px; border-color:black");

    QLabel lblTime("Время");
    lblTime.setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    lblTime.setStyleSheet("border-style:solid; border-left:none;"
                                       "border-bottom:none; border-width:1px; border-color:black");
    time = new QLabel("0:00");
    time->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    time->setStyleSheet("border-style:solid; border-left:none;"
                        "border-top:none; border-width:1px; border-color:black; font-size: 20px;");

    itemNameRed = new ProtocolNames();
    itemNameRed->setName("");
    sceneNameRed = new QGraphicsScene();
    sportsmenRed = new QGraphicsView(sceneNameRed);
    sportsmenRed->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    sportsmenRed->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    sceneNameRed->addItem(itemNameRed);

    itemNameBlue = new ProtocolNames();
    itemNameBlue->setName("");
    sceneNameBlue = new QGraphicsScene();
    sportsmenBlue = new QGraphicsView(sceneNameBlue);
    sportsmenBlue->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    sportsmenBlue->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    sceneNameBlue->addItem(itemNameBlue);

    sceneBlue = new QGraphicsScene();
    sceneRed = new QGraphicsScene();

    rateRed = new MyGraphicsView(&currentX);
    rateRed->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    rateRed->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    rateRed->setMinimumHeight(20);
    rateRed->setStyleSheet("border-style:solid; border-width:1px; border-color:black");
    rateRed->setScene(sceneRed);

    rateBlue = new MyGraphicsView(&currentX);
    rateBlue->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    rateBlue->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    rateBlue->setMinimumHeight(20);
    rateBlue->setStyleSheet("border-style:solid; border-top:none; border-width:1px; border-color:black;");
    rateBlue->setScene(sceneBlue);


    //self.margin = 6

    //QGridLayout grid(this);
    grid.setSpacing(0);
    grid.setMargin(6);

    grid.addWidget(btnNk,         0,  0, 3, 3);
    grid.addWidget(btnV,          0,  3, 3, 3);
    grid.addWidget(btnBP,         0,  6, 3, 3);
    grid.addWidget(btnUd,         0,  9, 3, 3);
    grid.addWidget(btnNkT,        0, 12, 3, 3);
    grid.addWidget(btnYP,         0, 15, 3, 3);
    grid.addWidget(btnPT,         0, 18, 3, 3);
    grid.addWidget(btnDoc,        0, 21, 3, 3);

    grid.addWidget(btnOPB,        3,  0, 3, 3);
    grid.addWidget(btnNPB,        3,  3, 3, 3);
    grid.addWidget(btnNkd,        3,  6, 3, 3);
    grid.addWidget(btnTNk,        3,  9, 3, 3);
    grid.addWidget(btnAr,         3, 12, 3, 3);
    grid.addWidget(btnPs,         3, 15, 3, 3);
    grid.addWidget(btnNy,         3, 18, 3, 3);
    grid.addWidget(btnVin,        3, 21, 3, 3);

    grid.addWidget(btn2,          1, 24, 4, 4);
    grid.addWidget(btn1,          1, 28, 4, 4);
    grid.addWidget(btnA,          1, 32, 4, 4);
    grid.addWidget(btn2P,         1, 36, 4, 4);
    grid.addWidget(btn1P,         1, 40, 4, 4);
    grid.addWidget(btnAP,         1, 44, 4, 4);
    grid.addWidget(btnZv,         1, 48, 4, 4);
    grid.addWidget(btnVyh,        1, 52, 4, 4);
    grid.addWidget(btnZp,         1, 56, 4, 4);
    grid.addWidget(btnP1,         1, 60, 4, 4);
    grid.addWidget(btnP2,         1, 64, 4, 4);
    grid.addWidget(btnBack,       1, 68, 4, 4);
    grid.addWidget(sportsmenRed,  6, 0, 4, 10);
    grid.addWidget(sportsmenBlue, 10, 0, 4, 10);
    grid.addWidget(rateRed,       6, 10, 4, 45);
    grid.addWidget(rateBlue,      10, 10, 4, 45);
    grid.addWidget(BallsRed,      6,  55, 2, 5);
    grid.addWidget(AktRed,        8,  55, 2, 5);
    grid.addWidget(BallsBlue,     10, 55, 2, 5);
    grid.addWidget(AktBlue,       12, 55, 2, 5);
    grid.addWidget(ResultRed,     6,  60, 4, 5);
    grid.addWidget(ResultBlue,    10, 60, 4, 5);

    grid.addWidget(&lblRef,        6, 65, 1, 7);
    grid.addWidget(nameMain,       7, 65, 1, 7);
    grid.addWidget(nameRef,        8, 65, 1, 7);
    grid.addWidget(nameSide,       9, 65, 1, 7);
    grid.addWidget(&lblTime,       10, 65, 1, 7);
    grid.addWidget(time,           11, 65, 3, 7);

    setLayout(&grid);

    QFont font;
    connect(rateRed, SIGNAL(shift(int, int)), this, SLOT(shiftBlue(int, int)));
    connect(rateBlue, SIGNAL(shift(int, int)), this, SLOT(shiftRed(int, int)));

    connect(rateRed, SIGNAL(strike(int, int)), this, SLOT(strikeBlue(int, int)));
    connect(rateBlue, SIGNAL(strike(int, int)), this, SLOT(strikeRed(int, int)));

    num_fight = NULL;
}

void ProtocolWindow::setMat(QString _mat){
    mat = _mat.toInt() * 2000 + 3;
}

void ProtocolWindow::setAddr(QString addr){
    address = addr;
}

void ProtocolWindow::Rate(bool button, QString name){
    //if(num_fight == NULL)
    //    return;
    pairedItem = nullptr;
    ProtocolRates* item = nullptr;
    if(name == "btn1"){
        item = new ProtocolRates("1", 1, false, false);
        item->setSize(rateRed->height()/5.8, rateRed->height()/3);
    }else if(name == "A"){
        item = new ProtocolRates("A", "A", false, false);
        item->setSize(rateRed->height()/3.4, rateRed->height()/3);
    }else if(name == "NK"){
        item = new ProtocolRates("V", "V", false, false);
        item->setSize(rateRed->height()/3.4, rateRed->height()/3);
        pairedItem = new ProtocolRates("Нк", 0, false, true);
        pairedItem->setSize(rateRed->height()/2.4, rateRed->height()/3);
        pairedItem->setPos(currentX + item->w / 2, rateRed->height()/2);
    }else if(name == "NY"){
        item = new ProtocolRates("н/я", 0);
        item->setSize(rateRed->height()/2.1, rateRed->height()/3);
    }else if(name == "V"){
        item = new ProtocolRates("V", "V", false, false);
        item->setSize(rateRed->height()/3.4, rateRed->height()/3);
    }else if(name == "BP"){
        item = new ProtocolRates("V", "V", false, false);
        item->setSize(rateRed->height()/3.4, rateRed->height()/3);
        pairedItem = new ProtocolRates("БП", 0, false, true);
        pairedItem->setSize(rateRed->height()/2.1, rateRed->height()/3);
        pairedItem->setPos(currentX + item->w / 2, rateRed->height()/2);
    }else if(name == "Ud"){
        item = new ProtocolRates("V", "V", false, false);
        item->setSize(rateRed->height()/3.4, rateRed->height()/3);
        pairedItem = new ProtocolRates("Уд", 0, false, true);
        pairedItem->setSize(rateRed->height()/2.3, rateRed->height()/3);
        pairedItem->setPos(currentX + item->w / 2, rateRed->height()/2);
    }else if(name == "NKT"){
        item = new ProtocolRates("V", "V", false, false);
        item->setSize(rateRed->height()/3.4, rateRed->height()/3);
        pairedItem = new ProtocolRates("Нк-Т", 0, false, true);
        pairedItem->setSize(rateRed->height()/1.35, rateRed->height()/3);
        pairedItem->setPos(currentX + item->w / 2, rateRed->height()/2);
    }else if(name == "DOCT"){
        item = new ProtocolRates("сн.вр", 0);
        item->setSize(rateRed->height()/1.28, rateRed->height()/3);
    }else if(name == "YP"){
        item = new ProtocolRates("V", "V", false, false);
        item->setSize(rateRed->height()/3.4, rateRed->height()/3);
        pairedItem = new ProtocolRates("ЯП", 0, false, true);
        pairedItem->setSize(rateRed->height()/2.1, rateRed->height()/3);
        pairedItem->setPos(currentX + item->w / 2, rateRed->height()/2);
    }else if(name == "PLUS"){
        item = new ProtocolRates("+", "+", false, false);
        item->setSize(rateRed->height()/4.0, rateRed->height()/3);
    }else if(name == "OPB"){
        item = new ProtocolRates("ОПБ", 0);
        item->setSize(rateRed->height()/1.4, rateRed->height()/3);
    }else if(name == "NPB"){
        item = new ProtocolRates("НПБ", 0);
        item->setSize(rateRed->height()/1.4, rateRed->height()/3);
    }else if(name == "Nkd"){
        item = new ProtocolRates("Нкд", 0);
        item->setSize(rateRed->height()/1.7, rateRed->height()/3);
        pairedItem = new ProtocolRates("2", false, true, 2);
        pairedItem->setSize(rateRed->height()/4.9, rateRed->height()/3);
        pairedItem->setPos(currentX + item->w / 2, rateRed->height()/2);
    }else if(name == "TNK"){
        item = new ProtocolRates("V", "V", false, false);
        item->setSize(rateRed->height()/3.4, rateRed->height()/3);
        pairedItem = new ProtocolRates("ТНк", 0, false, true);
        pairedItem->setSize(rateRed->height()/1.6, rateRed->height()/3);
        pairedItem->setPos(currentX + item->w / 2, rateRed->height()/2);
    }else if(name == "AR"){
        item = new ProtocolRates("Ар", "A", false, false);
        item->setSize(rateRed->height()/2.3, rateRed->height()/3);
    }else if(name == "PS"){
        item = new ProtocolRates("Пс", 0);
        item->setSize(rateRed->height()/2.3, rateRed->height()/3);
    }else if(name == "TWO"){
        item = new ProtocolRates("2", 2, false, false);
        item->setSize(rateRed->height()/4.9, rateRed->height()/3);
    }else if(name == "2P"){
        item = new ProtocolRates("2", 2, true, false);
        item->setSize(rateRed->height()/3.0, rateRed->height()/3);
    }else if(name == "1P"){
        item = new ProtocolRates("1", 1, true, false);
        item->setSize(rateRed->height()/3, rateRed->height()/3);
    }else if(name == "AP"){
        item = new ProtocolRates("A", "A", true, false);
        item->setSize(rateRed->height()/3, rateRed->height()/3);
    }else if(name == "ZV"){
        item = new ProtocolRates("Зв", "ЗВ", false, false);
        item->setSize(rateRed->height()/2.3, rateRed->height()/3);
    }else if(name == "VYH"){
        pairedItem = new ProtocolRates("1", 1, false, true);
        item = new ProtocolRates("В", "В", false, false);
        item->setSize(rateRed->height()/3.0, rateRed->height()/3);
        pairedItem->setSize(rateRed->height()/5.8, rateRed->height()/3);
        pairedItem->setPos(currentX + item->w / 2, rateRed->height()/2);
    }else if(name == "ZP"){
        item = new ProtocolRates("Зп", "ЗП", false, false);
        item->setSize(rateRed->height()/2.3, rateRed->height()/3);
    }else if(name == "P1"){
        pairedItem = new ProtocolRates("1", 1, false, true);
        item = new ProtocolRates("П1", "П1", false, false);
        item->setSize(rateRed->height()/2.4, rateRed->height()/3);
        pairedItem->setSize(rateRed->height()/5.8, rateRed->height()/3);
        pairedItem->setPos(currentX + item->w / 2, rateRed->height()/2);
     }else if(name == "P2"){
        pairedItem = new ProtocolRates("2", 2, false, true);
        item = new ProtocolRates("П2", "П2", false, false);
        item->setSize(rateRed->height()/2.3, rateRed->height()/3);
        pairedItem->setSize(rateRed->height()/4.9, rateRed->height()/3);
        pairedItem->setPos(currentX + item->w / 2, rateRed->height()/2);
     }else if(name == "VIN"){
        if(button){
            if(vin == 1)
                vin = 0;
            else
                vin = 1;
        }else{
            if(vin == 2)
                vin = 0;
            else
                vin = 2;
        }
        calculation();
        rate_to_png();
        return;
    }

    item->setPos(currentX + item->w / 2, rateRed->height()/2);
    currentX += item->w;
    lastItem = item;

    if(button){
        sceneBlue->addItem(item);
        if(pairedItem != nullptr)
            sceneRed->addItem(pairedItem);
    }else{
        sceneRed->addItem(item);
        if(pairedItem != nullptr)
            sceneBlue->addItem(pairedItem);
    }

    if(calculation())
        rate_to_png();
}

void ProtocolWindow::Back(){
    if(lastItem != nullptr){
        QGraphicsScene* scene = lastItem->scene();
        currentX -= lastItem->w / 1;
        scene->removeItem(lastItem);
        lastItem = nullptr;
        if(pairedItem != nullptr){
            QGraphicsScene* paired_scene = pairedItem->scene();
            paired_scene->removeItem(pairedItem);
            pairedItem = nullptr;
        }
        calculation();
    }
}

void ProtocolWindow::shiftBlue(int shift, int x){
    QList<QGraphicsItem*> l = rateBlue->items(x, 0, rateBlue->scene()->width() - x, rateBlue->scene()->height(), Qt::IntersectsItemShape);
    for(int i = 0; i < l.length(); i++)
        l.at(i)->setPos(l.at(i)->pos().x() + shift, l.at(i)->pos().y());
    calculation();
}

void ProtocolWindow::shiftRed(int shift, int x){
    QList<QGraphicsItem*> l = rateRed->items(x, 0, rateRed->scene()->width() - x, rateRed->scene()->height(), Qt::IntersectsItemShape);
    for(int i = 0; i < l.length(); i++)
        l.at(i)->setPos(l.at(i)->pos().x() + shift, l.at(i)->pos().y());
    calculation();
}

void ProtocolWindow::strikeBlue(int x, int y){
    ProtocolRates* item = static_cast<ProtocolRates*>(rateBlue->scene()->itemAt(x, y, QTransform()));
    if(item == nullptr){
        calculation();
        return;
    }
    item->strikethrough = true;
    int penWidth = 1;
    item->update(QRectF(-item->w / 2 - penWidth / 2, -item->h / 2 - penWidth / 2, item->w + penWidth, item->h + penWidth));
    calculation();
}

void ProtocolWindow::strikeRed(int x, int y){
    ProtocolRates* item = static_cast<ProtocolRates*>(rateRed->scene()->itemAt(x, y, QTransform()));
    if(item == nullptr){
        calculation();
        return;
    }
    item->strikethrough = true;
    int penWidth = 1;
    item->update(QRectF(-item->w / 2 - penWidth / 2, -item->h / 2 - penWidth / 2, item->w + penWidth, item->h + penWidth));
    calculation();
}

void ProtocolWindow::paintEvent(QPaintEvent*){
    QPainter pn(this);
    //pn.begin(this);
    pn.setPen(Qt::black);
    pn.end();
}

void ProtocolWindow::resizeEvent(QResizeEvent*){
    sceneRed->setSceneRect(0, 0, rateRed->width(), rateRed->height());
    sceneBlue->setSceneRect(0, 0, rateRed->width(), rateRed->height());

    itemNameRed->setSize(sportsmenRed->width(), sportsmenRed->height());
    sceneNameRed->setSceneRect(0, 0, sportsmenRed->width(), sportsmenRed->height());
    itemNameRed->setPos(itemNameRed->w / 2, itemNameRed->h / 2);

    itemNameBlue->setSize(sportsmenBlue->width(), sportsmenBlue->height());
    sceneNameBlue->setSceneRect(0, 0, sportsmenBlue->width(), sportsmenBlue->height());
    itemNameBlue->setPos(itemNameBlue->w / 2, itemNameBlue->h / 2);
}

bool ProtocolWindow::calculation(){
    bool clearVin = false;          //флаг чистой победы
    bool red_p2 = false;            //флаг второго нарушения правил
    bool blue_p2 = false;
    bool red_p1 = false;
    bool blue_p1 = false;
    bool red_zp = false;
    bool blue_zp = false;
    bool red_zv = false;
    bool blue_zv = false;
    bool red_v = false;
    bool blue_v = false;
    bool red_plus = false;
    bool blue_plus = false;
    bool finish = false;            //флаг окончания боя

    itemNameRed->setStatus(0);
    itemNameBlue->setStatus(0);
    QList<QGraphicsItem*> l = sceneRed->items();
    int redBall = 0;
    int redAct = 0;

    for(int i = 0; i < l.length(); i++){
        ProtocolRates* each = static_cast<ProtocolRates*>(l.at(i));
        QVariant val;
        if(each->getTypeValue())
            val = each->getSValue();
        else
            val = each->getIValue();

        if(val.toInt() == 1 || val.toInt() ==2){
            if(each->strikethrough == false)
                redBall += val.toInt();
        }else if(val.toString() == "A"){
            if(each->strikethrough == false)
                redAct += 1;
        }else if(val.toString() == "V" && each->strikethrough == false){
            itemNameRed->setStatus(1);
            itemNameBlue->setStatus(2);
            ResultRed->setText("5");
            ResultBlue->setText("0");
            clearVin = true;
        }else if(val.toString() == "П2" && each->strikethrough == false)
            red_p2 = true;
        else if(val.toString() == "П1" && each->strikethrough == false)
            red_p1 = true;
        else if(val.toString() == "З2" && each->strikethrough == false)
            red_zp = true;
        else if(val.toString() == "В" && each->strikethrough == false)
            red_v = true;
        else if(val.toString() == "ЗВ" && each->strikethrough == false)
            red_zv = true;
        else if(val.toString() == "+" && each->strikethrough == false)
            red_plus = true;
    }

    BallsRed->setText(QString::number(redBall));
    AktRed->setText(QString::number(redAct));

    l = sceneBlue->items();
    int blueBall = 0;
    int blueAct = 0;

    for(int i = 0; i < l.length(); i++){
        ProtocolRates* each = static_cast<ProtocolRates*>(l.at(i));
        QVariant val;
        if(each->getTypeValue())
            val = each->getSValue();
        else
            val = each->getIValue();

        if(val.toInt() == 1 || val.toInt() ==2){
            if(each->strikethrough == false)
                blueBall += val.toInt();
        }else if(val.toString() == "A"){
            if(each->strikethrough == false)
                blueAct += 1;
        }else if(val.toString() == "V" && each->strikethrough == false){
            itemNameRed->setStatus(2);
            itemNameBlue->setStatus(1);
            ResultRed->setText("0");
            ResultBlue->setText("5");
            clearVin = true;
        }else if(val.toString() == "П2" && each->strikethrough == false)
            blue_p2 = true;
        else if(val.toString() == "П1" && each->strikethrough == false)
            blue_p1 = true;
        else if(val.toString() == "З2" && each->strikethrough == false)
            blue_zp = true;
        else if(val.toString() == "В" && each->strikethrough == false)
            blue_v = true;
        else if(val.toString() == "ЗВ" && each->strikethrough == false)
            blue_zv = true;
        else if(val.toString() == "+" && each->strikethrough == false)
            blue_plus = true;
    }

    BallsBlue->setText(QString::number(blueBall));
    AktBlue->setText(QString::number(blueAct));
    if(clearVin == false){
        finish = true;
        if(vin == 1){
            itemNameBlue->setStatus(1);
            itemNameRed->setStatus(2);
            if(redBall == blueBall){
                ResultRed->setText("2");
                ResultBlue->setText("3");
            }else{
                ResultRed->setText("1");
                ResultBlue->setText("4");
            }
        }else if(vin == 2){
            itemNameBlue->setStatus(2);
            itemNameRed->setStatus(1);
            if(redBall == blueBall){
                ResultRed->setText("3");
                ResultBlue->setText("2");
            }else{
                ResultRed->setText("4");
                ResultBlue->setText("1");
            }
        }else{
            ResultRed->setText("");
            ResultBlue->setText("");
            finish = false;
       }
    }else

    finish = true;

    if(red_p2)
        change_prav(0, "П2");    //первый аргумент: 0 - красный, 1 - синий
    else if(red_p1)
        change_prav(0, "П1");
    else if(red_zp)
        change_prav(0, "ЗП");
    else
        change_prav(0, "");

    if(blue_p2)
        change_prav(1, "П2");     //первый аргумент: 0 - красный, 1 - синий
    else if(blue_p1)
        change_prav(1, "П1");
    else if(blue_zp)
        change_prav(1, "ЗП");
    else
        change_prav(1, "");

    if(red_v)
        change_vyh(0, "В");
    else if(red_zv)
        change_vyh(0, "ЗВ");
    else
        change_vyh(0, "");

    if(blue_v)
        change_vyh(1, "В");
    else if(blue_zv)
        change_vyh(1, "ЗВ");
    else
        change_vyh(1, "");

    if(red_plus)
        set_plus(0, "+");
    else
        set_plus(0, "");

    if(blue_plus)
        set_plus(1, "+");
    else
        set_plus(1, "");

    change_rate(redBall, blueBall, redAct, blueAct);
    qDebug()<<redBall<<blueBall<<redAct<<blueAct;

    qDebug()<<"calc";

    return finish;
}

void ProtocolWindow::rate_to_png(){
    if(num_fight == NULL)
        return;
    QPixmap pix(sportsmenRed->width() + rateRed->width() + BallsRed->width() + ResultRed->width() + time->width(), rateRed->height() * 2);
    render(&pix, QPoint(-sportsmenRed->pos().x(), -sportsmenRed->pos().y()));

    QByteArray ba;
    QBuffer buff(&ba);
    buff.open(QIODevice::WriteOnly);
    int ok = pix.save(&buff, "PNG");
    char* pix_bytes = ba.data();
    ba.prepend(QByteArray::number(num_fight));
    char* pixmap_bytes = ba.data();
    QSqlDatabase db = QSqlDatabase::addDatabase ("QSQLITE");
    db.setDatabaseName("baza_out.db");
    QSqlQuery query;
    query.prepare("UPDATE rounds SET result = ? WHERE fight = " + QString::number(num_fight));
    query.bindValue(0, pix_bytes);
    if(!query.exec()){
        qDebug()<<"error database";
    }else{
        QThread* thread = new QThread;
        TcpClient* client = new TcpClient(pixmap_bytes, address, mat, nullptr);
        client->moveToThread(thread);
        connect(thread, SIGNAL(started()), client, SLOT(run()));
        thread->start();
        thread->quit();
        thread ->wait();
    }
    db.close();
}

void ProtocolWindow::resetRate(){
    currentX = 0;
    QList<QGraphicsItem*> items = sceneBlue->items();
    for(int i = 0; i < items.length(); i++)
        sceneBlue->removeItem(items.at(i));
    items = sceneRed->items();
    for(int i = 0; i < items.length(); i++)
        sceneRed->removeItem(items.at(i));
    vin = 0;
    calculation();
    rate_to_png();
}

void ProtocolWindow::showQueue(){
    q = new FightQueue;
    connect(q, SIGNAL(select_fight(QString)), this, SLOT(selectFight(QString)));
    connect(q, SIGNAL(show_fight(QString)), this, SLOT(showFight(QString)));
    q->exec();
    delete q;
}

void ProtocolWindow::showFight(QString s){
    QSqlDatabase db = QSqlDatabase::addDatabase ("QSQLITE");
    db.setDatabaseName("baza_out.db");
    QSqlQuery query;
    QString sql = "SELECT result FROM rounds WHERE fight = " + s;
    if(!query.exec(sql))
        qDebug()<<"error database";
    else{
        QPixmap pix;
        if(query.next()){
            QByteArray ba = query.value(0).toByteArray();
            pix.loadFromData(ba, "PNG");
            ViewFight view(pix, q);
            view.show();
        }
    }
}

void ProtocolWindow::pastTime(QString t){
    time->setText(t);
}

void ProtocolWindow::selectFight(QString s){
    Fight* obj = q->findChild<Fight*>(s);
    QMessageBox dialog(QMessageBox::Question, "Выбор спортсменов", obj->red + "\n" + obj->blue,
                                     QMessageBox::Ok | QMessageBox::Cancel, this);
    int result = dialog.exec();
    if(result == QMessageBox::Ok){
        itemNameRed->setName(obj->red);
        QList<QString> r = obj->red.split("\n");
        if(r.length() > 1){
            nameRed(r.at(0).split(" ").at(0));
            regRed(r.at(1).split("(").at(0));
        }
        itemNameBlue->setName(obj->blue);
        QList<QString> b = obj->blue.split("\n");
        if(b.length() > 1){
            nameBlue(b.at(0).split(" ").at(0));
            regBlue(b.at(1).split("(").at(0));
        }
        QPixmap pix(sportsmenRed->width() + rateRed->width() + BallsRed->width() + ResultRed->width(), sportsmenRed->height() * 2);
        render(&pix, QPoint(-sportsmenRed->pos().x(), -sportsmenRed->pos().y()));
        obj->lblFight->setPixmap(pix.scaled(obj->lblFight->width(), obj->lblFight->height()));
        obj->lblFight->setVisible(true);

        QByteArray ba;
        QBuffer buff(&ba);
        buff.open(QIODevice::WriteOnly);
        int ok = pix.save(&buff, "PNG");
        char* pixmap_bytes = ba.data();

        num_fight = obj->objectName().toInt();
        QSqlDatabase db = QSqlDatabase::addDatabase ("QSQLITE");
        db.setDatabaseName("baza_out.db");
        QSqlQuery query;

        QString sql = "INSERT INTO rounds (fight, result) VALUES (?, ?)";

        query.prepare(sql);
        query.bindValue(0, obj->objectName());
        query.bindValue(0, pixmap_bytes);
        if(!query.exec()){
            qDebug()<<"error database";
            db.close();
        }else{
            db.close();
            QSqlDatabase db_in = QSqlDatabase::addDatabase ("QSQLITE");
            db.setDatabaseName("baza_in.db");
            QSqlQuery query_in;
            if(!query_in.exec("SELECT * FROM referees WHERE id_fight = " + QString::number(num_fight)))
                qDebug()<<"error database";
            else{
                if(query.next()){
                    nameMain->setText(query.value(2).toString());
                    nameRef->setText(query.value(3).toString());
                    nameSide->setText(query.value(4).toString());
                }
            }

        }
        resetRate();
        setWeight(obj->title.split(",").at(2));
    }
}
