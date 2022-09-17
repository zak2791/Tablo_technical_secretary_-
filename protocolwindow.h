#ifndef PROTOCOLWINDOW_H
#define PROTOCOLWINDOW_H

#include <QGraphicsView>

class TcpClient : public QObject
{


private:
    QString data;
    QString address;

public:
    TcpClient(QString _data, QString _address, QWidget* parent){
        data = _data;
    }
    /*
    def run(self):
        sock = socket.socket()
        sock.settimeout(0.1)
        try:
            sock.connect(self.addr)
            sock.send(self.data)
        except:
            print("err socket")
        finally:
            sock.close()
            */
};



class ProtocolWindow : public QGraphicsView
{
    Q_OBJECT
public:
    ProtocolWindow(QWidget* parent = nullptr);
};

#endif // PROTOCOLWINDOW_H
