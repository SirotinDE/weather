#pragma once

#include <QObject>
#include <vector>

class CityDto;
class CitiesModel;

class FavoritCitiesPresenter : public QObject
{
    Q_OBJECT
public:
    explicit FavoritCitiesPresenter(CitiesModel* citiesModel,
                                    QObject *parent = nullptr);

    std::vector<CityDto> getFavoritCities();
    void updateCityIsFavorite(CityDto& city);
    void setCityAsCurent(CityDto& city);

signals:
    void curentCityChanged();
private:
    CitiesModel* m_citiesModel;
};
