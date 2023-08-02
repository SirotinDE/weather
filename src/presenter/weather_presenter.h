#pragma once

#include <QObject>
#include <QSharedPointer>

#include "../dto/city_dto.h"

struct CityDto;
class GeopositionModel;
class CityWeatherModel;
class CppApi;
class CitiesModel;

class WeatherPresenter : public QObject
{
    Q_OBJECT
public:
    explicit WeatherPresenter(GeopositionModel* geopositionModel,
                              CityWeatherModel* cityWeatherModel,
                              CitiesModel* citiesModel,
                              CppApi* cppApi,
                              QObject *parent = nullptr);
    ~WeatherPresenter();

    void updateWeather();
    void switchCurentCityIsFavorite();
    std::optional<CityDto>& getCurentCity();

signals:
    void weatherUpdated();

public slots:
    void onCurentCityChanged();
private slots:
    void onWeatherUpdated(CityDto& cityWeather);

private:
    GeopositionModel* m_geopositionModel;
    CityWeatherModel* m_cityWeatherModel;
    CitiesModel* m_citiesModel;
    CppApi* m_cppApi;
    std::optional<CityDto> m_city;
};
