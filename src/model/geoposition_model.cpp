#include "geoposition_model.h"
#include <array>
#include "../utility/randomizer.h"

GeopositionModel::GeopositionModel()
{

}

CoordinatesDto GeopositionModel::getGeoposition()
{
    static const std::array<CoordinatesDto, 3> coordinates{
        {
            {57.6139, 39.8895},
            {59.9375, 30.3086},
            {55.7522, 37.6156}
        }
    };

    return coordinates[Randomizer::getRandomInt(0,3)];
}
