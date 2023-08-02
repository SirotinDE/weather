#pragma once

#include <QObject>
#include <functional>
#include <QHash>
#include <QSharedPointer>

class QNetworkAccessManager;
class QNetworkReply;
struct CoordinatesDto;
struct CityDto;

class CityWeatherModel : public QObject
{
    Q_OBJECT
public:
    explicit CityWeatherModel(QObject *parent = nullptr);
    ~CityWeatherModel();

    void getWeather(CoordinatesDto coordinates);
    void getWeather(const QString& cityName);

signals:
    void weatherUpdated(CityDto& city);
    void weatherUpdateError(QString error);
private slots:
    void replyfinished(QNetworkReply *reply);
private:
    QScopedPointer<QNetworkAccessManager> m_manager;
    QHash<QNetworkReply*, std::function<void(QNetworkReply *reply)>> m_requests;
    QString m_url = "https://openweathermap.org/data/2.5/";
    QString m_appId = "439d4b804bc8187953eb36d2a8c26a02";
};
