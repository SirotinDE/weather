#include "weather_view.h"
#include "../presenter/weather_presenter.h"

WeatherView::WeatherView(WeatherPresenter *weatherPresenter,
                         std::optional<CityDto>& cityWeather,
                         QObject *parent)
    : QObject(parent)
    ,m_weatherPresenter(weatherPresenter)
    ,m_cityWeather(cityWeather)
{
    connect(m_weatherPresenter, &WeatherPresenter::weatherUpdated, this, &WeatherView::updateData);
    m_weatherPresenter->updateWeather();
}
/*
namespace  {
    int toCelcius(double kelvin){
        return static_cast<int>(kelvin - 273.0);
    }
}
*/

QString WeatherView::temperature() const
{
    QString answer;

    if(m_cityWeather && m_cityWeather->weather){
        answer = QString::number(m_cityWeather->weather->temp);
    }

    return answer;
}

QString WeatherView::maxTemperature() const
{
    QString answer;

    if(m_cityWeather && m_cityWeather->weather){
        answer = QString::number(m_cityWeather->weather->temp_max);
    }

    return answer;
}

QString WeatherView::minTemperature() const
{
    QString answer;

    if(m_cityWeather && m_cityWeather->weather){
        answer = QString::number(m_cityWeather->weather->temp_min);
    }

    return answer;
}

QString WeatherView::humidity() const
{
    QString answer;

    if(m_cityWeather && m_cityWeather->weather){
        answer = QString::number(m_cityWeather->weather->humidity);
    }

    return answer;
}

void WeatherView::updateData()
{
    emit temperatureChanged();
    emit maxTemperatureChanged();
    emit minTemperatureChanged();
    emit humidityChanged();
    emit cityNameChanged();
    emit cityIsFavoriteChanged();
    emit weatherIconTypeChanged();
}

void WeatherView::switchCurentCityIsFavorite()
{
    m_weatherPresenter->switchCurentCityIsFavorite();
    emit cityIsFavoriteChanged();
}

QString WeatherView::cityName() const
{
    QString answer;

    if(m_cityWeather){
        answer = m_cityWeather->name;
    }

    return answer;
}

bool WeatherView::cityIsFavorite() const
{
    bool answer = false;

    if(m_cityWeather){
        answer = m_cityWeather->isFavorite;
    }

    return answer;
}

int WeatherView::weatherIconType() const
{
    int answer = 0;

    if(m_cityWeather && m_cityWeather->weather){
        answer = static_cast<int>(m_cityWeather->weather->description);
    }

    return answer;
}
