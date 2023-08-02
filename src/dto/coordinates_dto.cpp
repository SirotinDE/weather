#include "coordinates_dto.h"
#include <QJsonObject>

CoordinatesDto::CoordinatesDto(QJsonObject &json)
{
    QJsonObject main = json.value("coord").toObject();
    lat = main.value("lat").toDouble(0.0);
    lon = main.value("lon").toDouble(0.0);
}

CoordinatesDto::CoordinatesDto(double lat, double lon)
    :lat(lat)
    ,lon(lon)
{

}
