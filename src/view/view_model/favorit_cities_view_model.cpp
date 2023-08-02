#include "favorit_cities_view_model.h"
#include "../../presenter/favorit_cities_presenter.h"

FavoritCitiesViewModel::FavoritCitiesViewModel(FavoritCitiesPresenter* favoritCitiesPresenter,
                                               QObject *parent)
    : QAbstractListModel(parent)
    ,m_favoritCitiesPresenter(favoritCitiesPresenter)
{

}

FavoritCitiesViewModel::~FavoritCitiesViewModel()
{

}

int FavoritCitiesViewModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid()) {
        return 0;
    }

    return m_cities.size();
}

QVariant FavoritCitiesViewModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid()) {
        return QVariant();
    }

    switch (role) {
    case CityName:
        return QVariant(m_cities[index.row()].name);
    case IsFavorite:
        return  QVariant(m_cities[index.row()].isFavorite);
    default:
        return QVariant();
    }
}

QHash<int, QByteArray> FavoritCitiesViewModel::roleNames() const
{
    QHash<int, QByteArray> roles = QAbstractListModel::roleNames();
    roles[CityName] = "cityName";
    roles[IsFavorite] = "isFavorite";

    return roles;
}

bool FavoritCitiesViewModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (!index.isValid()) {
        return false;
    }
    m_cities[index.row()].isFavorite = value.toBool();
    m_favoritCitiesPresenter->updateCityIsFavorite( m_cities[index.row()]);

    emit dataChanged(index, index, QVector<int>() << role);

    return true;
}

void FavoritCitiesViewModel::updateCities(std::vector<CityDto>&& cities)
{
    m_cities = std::move(cities);
}

void FavoritCitiesViewModel::setCityAsCurent(int index)
{
    m_favoritCitiesPresenter->setCityAsCurent(m_cities[index]);
}

