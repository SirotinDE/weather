#include "city_dto.h"
#include <memory>
#include <QJsonObject>

CityDto::CityDto(size_t id,
                 QString &&name)
    :id(id)
    ,name(std::move(name))
{

}

CityDto::CityDto(size_t id,
                 QString&& name,
                 CoordinatesDto&& coordinates)
    :id(id)
    ,name(std::move(name))
    ,coordinates(std::move(coordinates))
{

}

CityDto::CityDto(size_t id,
                 QString&& name,
                 CoordinatesDto&& coordinates,
                 WeatherDto&& weather)
    :id(id)
    ,name(std::move(name))
    ,coordinates(std::move(coordinates))
    ,weather(std::make_optional(std::move(weather)))
{

}

CityDto::CityDto(QJsonObject &json)
{
    id = json.value("id").toInt(0);
    name = json.value("name").toString();

    if(json.contains("main") && json.contains("weather")){
        weather.emplace(json);
    }

    if(json.contains("coord")){
        coordinates = CoordinatesDto(json);
    }
}

