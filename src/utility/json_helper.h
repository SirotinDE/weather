#pragma once

class QJsonObject;
class QString;
class QByteArray;

class JsonHelper
{
public:
    static QJsonObject parse(const QByteArray& json, QString& error);
    static QByteArray jsObjToBa(const QJsonObject & jso);
};

