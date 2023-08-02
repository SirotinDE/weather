#include "favorit_cities_presenter.h"
#include "../dto/city_dto.h"
#include "../model/cities_model.h"

FavoritCitiesPresenter::FavoritCitiesPresenter(CitiesModel* citiesModel,
                                               QObject *parent)
    : QObject(parent)
    ,m_citiesModel(citiesModel)
{

}

std::vector<CityDto> FavoritCitiesPresenter::getFavoritCities()
{
    return m_citiesModel->getFavoriteCities();
}

void FavoritCitiesPresenter::updateCityIsFavorite(CityDto &city)
{
    if(city.isFavorite){
        m_citiesModel->insertCityAsFavorite(city);
    }else{
        m_citiesModel->deleteCityFromFavorite(city.id);
    }
}

void FavoritCitiesPresenter::setCityAsCurent(CityDto &city)
{
    m_citiesModel->resetCurentCity(city);
    emit curentCityChanged();
}
