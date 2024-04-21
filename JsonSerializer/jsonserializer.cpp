#include "jsonserializer.h"

JsonSerializer::JsonSerializer() {}

void JsonSerializer::fileReceived(QByteArray data){
    qInfo()<<data;
}
