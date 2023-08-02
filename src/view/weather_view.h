#pragma once

#include <QObject>
#include <QSharedPointer>
#include <optional>
#include "../dto/city_dto.h"

class WeatherPresenter;
class WeatherViewModel;
struct CityDto;

class WeatherView : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString temperature READ temperature NOTIFY temperatureChanged)
    Q_PROPERTY(QString maxTemperature READ maxTemperature NOTIFY maxTemperatureChanged)
    Q_PROPERTY(QString minTemperature READ minTemperature NOTIFY minTemperatureChanged)
    Q_PROPERTY(QString humidity READ humidity NOTIFY humidityChanged)
    Q_PROPERTY(QString cityName READ cityName NOTIFY cityNameChanged)
    Q_PROPERTY(bool cityIsFavorite READ cityIsFavorite NOTIFY cityIsFavoriteChanged)
    Q_PROPERTY(int weatherIconType READ weatherIconType NOTIFY weatherIconTypeChanged)

public:
    explicit WeatherView(WeatherPresenter* weatherPresenter,
                         std::optional<CityDto>& cityWeather,
                         QObject *parent = nullptr);

    QString temperature() const;
    QString maxTemperature() const;
    QString minTemperature() const;
    QString humidity() const;
    QString cityName() const;
    bool cityIsFavorite() const;
    int weatherIconType() const;

signals:
    void temperatureChanged();
    void maxTemperatureChanged();
    void minTemperatureChanged();
    void humidityChanged();
    void cityNameChanged();
    void cityIsFavoriteChanged();
    void weatherIconTypeChanged();

public slots:
    void updateData();
    void switchCurentCityIsFavorite();

private:
    WeatherPresenter* m_weatherPresenter;
    std::optional<CityDto>& m_cityWeather;
};


