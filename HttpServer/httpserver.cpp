#include "httpserver.h"

HttpServer::HttpServer() {

    httpServer.route("/", [](){
        //return "Hello world";
        return QHttpServerResponse::fromFile("./index.html");
    });

    const auto port = httpServer.listen(QHostAddress::Any,8080);
    if (!port) {
        qWarning() << "Server failed to listen on a port.";
    }

    qInfo().noquote()<< "QHttpServerExample, Running on http://127.0.0.1:" << port;
}
