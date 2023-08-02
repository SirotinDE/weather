#pragma once

class QJsonObject;

struct WeatherDto
{
    enum Description {
        Clear = 0,
        Clouds,
        Rain
    };

    Description description;
    float temp = 0.0f;
    float temp_min = 0.0f;
    float temp_max = 0.0f;
    int humidity = 0;

    WeatherDto() = default;
    WeatherDto(QJsonObject& json);
};

