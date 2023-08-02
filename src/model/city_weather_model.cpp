#include "city_weather_model.h"
#include <QNetworkAccessManager>
#include <QJsonObject>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QSslConfiguration>
#include <QJsonDocument>

#include "../dto/city_dto.h"
#include "../utility/json_helper.h"

CityWeatherModel::CityWeatherModel(QObject *parent)
    : QObject(parent)
    ,m_manager(new QNetworkAccessManager)
{
    QObject::connect(m_manager.data(), &QNetworkAccessManager::finished, this, &CityWeatherModel::replyfinished);
}

CityWeatherModel::~CityWeatherModel()
{

}

void CityWeatherModel::getWeather(CoordinatesDto coordinates)
{
    //weather?lat=57.6138699&lon=39.8894906&appid=439d4b804bc8187953eb36d2a8c26a02
    QUrl url = QString(m_url + "weather?lat=%1&lon=%2&appid=%3&units=metric").arg(coordinates.lat).arg(coordinates.lon).arg(m_appId);

    QNetworkRequest request(url);

    QSslConfiguration conf = request.sslConfiguration();
    conf.setPeerVerifyMode(QSslSocket::VerifyNone);
    request.setSslConfiguration(conf);

    auto repl = m_manager->get(request);
    m_requests.insert(repl, [&](QNetworkReply *reply){

        if(reply->error() == QNetworkReply::NoError){
            QByteArray qByteArrayResponse = reply->readAll();

            if(!qByteArrayResponse.isEmpty()){
                QString error;
                QJsonObject cityJS = JsonHelper::parse(qByteArrayResponse, error);

                qDebug() << "JSON!!" << qByteArrayResponse;

                if(error.isEmpty()){
                    CityDto cityDto(cityJS);
                    emit weatherUpdated(cityDto);
                }else{
                    emit weatherUpdateError(reply->errorString());
                    qDebug() << error;
                }
            }
        }else{
            emit weatherUpdateError(reply->errorString());
            qDebug() << QString::number((int)reply->error()) << reply->errorString();
        }
    });
}

void CityWeatherModel::getWeather(const QString &cityName)
{
    //https://openweathermap.org/data/2.5/find?q=%D1%8F%D1%80%D0%BE%D1%81%D0%BB%D0%B0%D0%B2%D0%BB%D1%8C&appid=439d4b804bc8187953eb36d2a8c26a02&units=metric
    QUrl url = QString(m_url + "find?q=%1&appid=" + m_appId).arg(cityName);
    QNetworkRequest request(url);

    QSslConfiguration conf = request.sslConfiguration();
    conf.setPeerVerifyMode(QSslSocket::VerifyNone);
    request.setSslConfiguration(conf);

    auto repl = m_manager->get(request);
    m_requests.insert(repl, [&](QNetworkReply *reply){
        if(reply->error() == QNetworkReply::NoError){
            QByteArray qByteArrayResponse = reply->readAll();

            if(!qByteArrayResponse.isEmpty()){
                QString error;
                QJsonObject cityJS = JsonHelper::parse(qByteArrayResponse, error);

                if(error.isEmpty()){
                    CityDto cityDto(cityJS);
                    emit weatherUpdated(cityDto);
                }else{
                    emit weatherUpdateError(reply->errorString());
                    qDebug() << error;
                }
            }
        }else{
            emit weatherUpdateError(reply->errorString());
            qDebug() << QString::number((int)reply->error()) << reply->errorString();
        }
    });
}

void CityWeatherModel::replyfinished(QNetworkReply *reply)
{
    auto iter = m_requests.find(reply);

    if(iter != m_requests.end()){
        iter.value()(reply);
        reply->deleteLater();
        m_requests.erase(iter);
    }
}
