#ifndef HTTPSERVER_H
#define HTTPSERVER_H

#include <QHttpServer>
#include <QHttpServerResponse>

class HttpServer
{
public:
    HttpServer();
private:
    QHttpServer httpServer;
};

#endif // HTTPSERVER_H
