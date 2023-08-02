#include "weather_dto.h"
#include <QJsonObject>
#include <QJsonArray>

WeatherDto::WeatherDto(QJsonObject &json)
{
    QJsonObject main = json.value("main").toObject();

    temp = main.value("temp").toDouble(0.0);
    temp_min = main.value("temp_min").toDouble(0.0);
    temp_max = main.value("temp_max").toDouble(0.0);
    humidity = main.value("humidity").toInt(0);

    QJsonArray weatherArray = json.value("weather").toArray();
    QJsonObject weather = weatherArray[0].toObject();

    QString weatherDescription = weather.value("main").toString();

    if(weatherDescription == "Clear"){
        description = WeatherDto::Description::Clear;
    }else if(weatherDescription == "Clouds"){
        description = WeatherDto::Description::Clouds;
    }else{
        description = WeatherDto::Description::Rain;
    }

}
