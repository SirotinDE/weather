#include "weather_presenter.h"
#include "../dto/city_dto.h"
#include "../model/geoposition_model.h"
#include "../model/city_weather_model.h"
#include "../model/cities_model.h"
#include "../view/cpp_api.h"

WeatherPresenter::WeatherPresenter(GeopositionModel* geopositionModel,
                                   CityWeatherModel* cityWeatherModel,
                                   CitiesModel* citiesModel,
                                   CppApi* cppApi,
                                   QObject *parent)
    : QObject(parent)
    , m_geopositionModel(geopositionModel)
    , m_cityWeatherModel(cityWeatherModel)
    , m_citiesModel(citiesModel)
    , m_cppApi(cppApi)
{
    QObject::connect(m_cityWeatherModel, &CityWeatherModel::weatherUpdated, this, &WeatherPresenter::onWeatherUpdated);
    QObject::connect(m_cityWeatherModel, &CityWeatherModel::weatherUpdateError, [&](QString error){
        Q_UNUSED(error);//TODO сделать показ ошибок
        m_cppApi->setIsBusy(false);
    });

    m_city = m_citiesModel->getCurentCity();
    m_cppApi->setIsBusy(true);
    m_cppApi->setBusyText("Запрос данных с сервера");
    m_cityWeatherModel->getWeather(m_geopositionModel->getGeoposition());
}

void WeatherPresenter::updateWeather()
{
    if(m_city){
        m_cppApi->setIsBusy(true);
        m_cppApi->setBusyText("Запрос данных с сервера");
        m_cityWeatherModel->getWeather(m_city->coordinates);
    }
}

void WeatherPresenter::switchCurentCityIsFavorite()
{
    if(m_city){
        m_city->isFavorite = !m_city->isFavorite;

        if(m_city->isFavorite){
            m_citiesModel->insertCityAsFavorite(*m_city);
        }else{
            m_citiesModel->deleteCityFromFavorite(m_city->id);
        }
    }
}

std::optional<CityDto> &WeatherPresenter::getCurentCity()
{
    return m_city;
}

void WeatherPresenter::onWeatherUpdated(CityDto &cityWeather)
{
    m_cppApi->setIsBusy(false);
    m_city = cityWeather;
    m_city->isFavorite = m_citiesModel->isFavorite(m_city->id);
    m_citiesModel->resetCurentCity(*m_city);
    emit weatherUpdated();
}

void WeatherPresenter::onCurentCityChanged()
{
    m_city = m_citiesModel->getCurentCity();
    updateWeather();
}

WeatherPresenter::~WeatherPresenter()
{

}
