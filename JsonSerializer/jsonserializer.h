#ifndef JSONSERIALIZER_H
#define JSONSERIALIZER_H

#include <QJsonObject>
#include <QJsonDocument>
#include <QIODevice>
#include <QFile>
class JsonSerializer : public QObject
{
    Q_OBJECT
public:
    JsonSerializer();
    QJsonDocument readJsonFile(QString path);

public slots:
    void writeToFile(QByteArray data, QString path);


signals:
    void configChanged();
    //void fileRead(QByteArray data);
};

#endif // JSONSERIALIZER_H
