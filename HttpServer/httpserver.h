#ifndef HTTPSERVER_H
#define HTTPSERVER_H

#include <QHttpServer>
#include <QHttpServerResponse>
#include <QFile>

#include "jsonserializer.h"

class HttpServer : public QObject
{
    Q_OBJECT
public:
    HttpServer();
private:
    QHttpServer httpServer;
    QByteArray data;

signals:
    void fileReceived(QByteArray data, QString path);

public slots:
    void listenNewIp();
};

#endif // HTTPSERVER_H
