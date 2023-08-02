#pragma once

class QJsonObject;

struct CoordinatesDto
{
    double lat = 0.0;
    double lon = 0.0;

    CoordinatesDto() = default;
    CoordinatesDto(double lat, double lon);
    CoordinatesDto(QJsonObject& json);
};

