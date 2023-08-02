#pragma once

#include "../dto/coordinates_dto.h"

class GeopositionModel
{
public:
    GeopositionModel();

    CoordinatesDto getGeoposition();
};

