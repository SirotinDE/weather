#pragma once

#include <QSharedPointer>
#include <QSqlQuery>
#include <optional>

class QSqlDatabase;
class CityDto;

class CitiesModel
{
public:
    CitiesModel(QSqlDatabase& db);

    void insertCityAsFavorite(const CityDto &city);
    void deleteCityFromFavorite(int id);

    void resetCurentCity(const CityDto &city);
    bool isFavorite(int id);

    std::optional<CityDto> getCurentCity();
    std::vector<CityDto> getFavoriteCities();

private:
    QSqlDatabase& m_db;
    QSqlQuery m_query;

    void createTables();
    bool insertCityIfNotExists(const CityDto &city);
    bool isCurentCity(int id);
    bool isHaveIdInTable(int id, const QString& tableName);
    int getCurentCityId();
};

