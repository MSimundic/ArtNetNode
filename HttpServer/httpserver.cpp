#include "httpserver.h"

HttpServer::HttpServer() {
    httpServer.route("/", [](){
        //return "Hello world";
        //return QHttpServerResponse::fromFile("./files/index.html");
        //return QHttpServerResponse::fromFile("./files/style.css");
        //return QHttpServerResponse::fromFile("./files/script.js");
        return QHttpServerResponse::fromFile("../ArtNetNode//indexInline.html");
    });

    httpServer.route("/data.json", QHttpServerRequest::Method::Post, [this](const QHttpServerRequest &request){
        qInfo()<< "Post request received";
        emit fileReceived(request.body());
        return QHttpServerResponse(QHttpServerResponder::StatusCode::Ok);
    });

    const auto port = httpServer.listen(QHostAddress::Any,8080);
    if (!port) {
        qWarning() << "Server failed to listen on a port.";
    }

    qInfo().noquote()<< "QHttpServerExample, Running on http://127.0.0.1:" << port;

}

