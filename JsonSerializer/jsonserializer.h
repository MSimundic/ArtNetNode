#ifndef JSONSERIALIZER_H
#define JSONSERIALIZER_H

#include <QJsonObject>
class JsonSerializer : public QObject
{
    Q_OBJECT
public:
    JsonSerializer();

public slots:
    void fileReceived(QByteArray data);
};

#endif // JSONSERIALIZER_H
