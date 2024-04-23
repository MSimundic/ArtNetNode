#include "jsonserializer.h"

JsonSerializer::JsonSerializer() {}

void JsonSerializer::writeToFile(QByteArray data){
    //qInfo()<<data;
    QJsonDocument jsonDoc = QJsonDocument::fromJson(QString(data).toUtf8());
    //QJsonObject jsonObject = jsonDoc.object();
    //qInfo()<<jsonDoc;


    QFile file("./configuration.json");
    file.open(QIODevice::WriteOnly | QIODevice::Text | QFile::Truncate);
    file.write(jsonDoc.toJson());
    file.close();
    emit configChanged();
}

QString JsonSerializer::readFile(){
    QFile file("./configuration.json");
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    QJsonParseError jsonParseError;
    QJsonDocument jsonDocument = QJsonDocument::fromJson(file.readAll(), &jsonParseError);
    file.close();
    //qInfo()<<jsonDocument.object();
    return QString(jsonDocument.toJson());
}
