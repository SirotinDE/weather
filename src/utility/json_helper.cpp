#include "json_helper.h"
#include <QJsonDocument>
#include <QByteArray>
#include <QString>
#include <QJsonObject>

QJsonObject JsonHelper::parse(const QByteArray &json, QString& error){
    if(json.isEmpty()){
        error = "json is empty";
        return QJsonObject();
    }

    error = "";

    QJsonParseError jsError;
    auto jsonDocument = QJsonDocument::fromJson(json, &jsError);

    if (jsonDocument.isNull() ||
        jsonDocument.isEmpty())
    {
        error = jsError.errorString();

        return QJsonObject();
    }

    return jsonDocument.object();
}

QByteArray JsonHelper::jsObjToBa(const QJsonObject &jso){
    QJsonDocument tmp(jso);
    return tmp.toJson();
}
