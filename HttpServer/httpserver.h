#ifndef HTTPSERVER_H
#define HTTPSERVER_H

#include <QHttpServer>
#include <QHttpServerResponse>

class HttpServer : public QObject
{
    Q_OBJECT
public:
    HttpServer();
private:
    QHttpServer httpServer;
    QByteArray data;

signals:
    void fileReceived(QByteArray data);

public slots:
    void listenNewIp();
};

#endif // HTTPSERVER_H
