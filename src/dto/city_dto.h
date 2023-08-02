#pragma once

#include <QString>
#include <optional>

#include "weather_dto.h"
#include "coordinates_dto.h"

class QJsonObject;

struct CityDto
{
    int id = 0;
    QString name;

    CoordinatesDto coordinates;
    std::optional<WeatherDto> weather = std::nullopt;

    bool isFavorite = false;

    CityDto() = default;

    CityDto(size_t id, QString&& name);

    CityDto(size_t id,
            QString&& name,
            CoordinatesDto&& coordinates);

    CityDto(size_t id,
            QString&& name,
            CoordinatesDto&& coordinates,
            WeatherDto&& weather);

    CityDto(size_t id,
            QString&& name,
            CoordinatesDto&& coordinates,
            WeatherDto&& weather,
            bool isFavorite);

    CityDto(QJsonObject& json);
};

