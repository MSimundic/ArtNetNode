#include "jsonserializer.h"

JsonSerializer::JsonSerializer() {}

void JsonSerializer::writeToFile(QByteArray data, QString path){
    //qInfo()<<data;
    QJsonDocument jsonDoc = QJsonDocument::fromJson(QString(data).toUtf8());
    //QJsonObject jsonObject = jsonDoc.object();
    //qInfo()<<jsonDoc;

    qInfo() << "Jsonser write";
    QFile file(path);
    file.open(QIODevice::WriteOnly | QIODevice::Text | QFile::Truncate);
    file.write(jsonDoc.toJson());
    file.close();
    emit configChanged();
}

QJsonDocument JsonSerializer::readJsonFile(QString path){
    QFile file(path);
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    QJsonParseError jsonParseError;
    QJsonDocument jsonDocument = QJsonDocument::fromJson(file.readAll(), &jsonParseError);
    file.close();
    //qInfo()<<jsonDocument.object();
    return jsonDocument;
}
