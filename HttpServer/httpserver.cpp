#include "httpserver.h"

HttpServer::HttpServer() {
    httpServer.route("/", [](){
        //return "Hello world";
        //return QHttpServerResponse::fromFile("./files/index.html");
        //return QHttpServerResponse::fromFile("./files/style.css");
        //return QHttpServerResponse::fromFile("./files/script.js");
        JsonSerializer jsonSer;
        QJsonObject jsonObj = jsonSer.readJsonFile("./configuration.json").object();

        QFile htmlFile("../ArtNetNode/indexInline.html");
        if(!htmlFile.open(QIODevice::ReadWrite)) {
            qInfo() << htmlFile.errorString();
        }
        QString textHtmlFile(htmlFile.readAll());
        htmlFile.close();
        textHtmlFile.replace("@shortName@", jsonObj.value("shortName").toString());
        textHtmlFile.replace("@longName@", jsonObj.value("longName").toString());
        textHtmlFile.replace("@ipAddress@", jsonObj.value("ipAddress").toString());
        textHtmlFile.replace("@subnetMask@", jsonObj.value("subnetMask").toString());
        textHtmlFile.replace("@net@", jsonObj.value("net").toString());
        textHtmlFile.replace("@primary@", jsonObj.value("primary").toString());
        textHtmlFile.replace("@ipAddress@", jsonObj.value("ipAddress").toString());

        QFile htmlFileToSend("../ArtNetNode/indexInlineToSend.html");
        if(!htmlFileToSend.open(QIODevice::WriteOnly)) {
            qInfo() << htmlFileToSend.errorString();
        }
        htmlFileToSend.seek(0);
        htmlFileToSend.write(textHtmlFile.toUtf8());
        htmlFileToSend.close();
        return QHttpServerResponse::fromFile("../ArtNetNode/indexInlineToSend.html");
        //return QHttpServerResponse::fromFile;

    });

    httpServer.route("/data.json", QHttpServerRequest::Method::Post, [this](const QHttpServerRequest &request){
        qInfo()<< "Post request received";
        emit fileReceived(request.body(), "./configuration.json");
        return QHttpServerResponse(QHttpServerResponder::StatusCode::Ok);
    });

    const auto port = httpServer.listen(QHostAddress::Any,8080);
    if (!port) {
        qWarning() << "Server failed to listen on a port.";
    }

    //qInfo().noquote()<< "QHttpServerExample, Running on http://127.0.0.1:" << port;

}

void HttpServer::listenNewIp(){

    //const auto port = httpServer.listen(QHostAddress::Any,8080);
    //if (!port) {
    //    qWarning() << "Server failed to listen on a port.";
    //}
    qInfo() << "http server new IP";
}

