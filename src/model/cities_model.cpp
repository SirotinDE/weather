#include "cities_model.h"

#include <QSqlDatabase>
#include <QStringList>
#include <QSqlError>
#include <QDebug>
#include "../dto/city_dto.h"


CitiesModel::CitiesModel(QSqlDatabase &db)
    :m_db(db)
    ,m_query(m_db)
{
    createTables();
}

void CitiesModel::insertCityAsFavorite(const CityDto &city)
{
    if(insertCityIfNotExists(city)){
       m_query.exec(QString("INSERT INTO favorite_city (city_id) VALUES(%1)").arg(city.id));
    }
}

void CitiesModel::deleteCityFromFavorite(int id)
{
    if(m_query.exec(QString("DELETE from favorite_city WHERE id = %1").arg(id))){
        //если не является текущим городом, то удаляем из city
        if(!isCurentCity(id)){
            m_query.exec(QString("DELETE from city WHERE id = %1").arg(id));
        }
    }
}

void CitiesModel::resetCurentCity(const CityDto &city)
{
    if(isCurentCity(city.id)){
        return;
    }
    ////////удаляем текущий сurentCityId//////////
    int curentCityId = getCurentCityId();

    //если существует сurentCityId
    if(curentCityId != -1){
        m_query.exec("DELETE from curent_city");
        //и сurentCityId не в favorite
        if(!isFavorite(curentCityId)){
            //удаляем его из city
            m_query.exec(QString("DELETE from city WHERE id = %1").arg(curentCityId));
        }
    }
    //////////////////////////////////////////////
    /// добавляем новый ///
    if(insertCityIfNotExists(city)){
        m_query.exec(QString("INSERT INTO curent_city (city_id) VALUES(%1)").arg(city.id));
    }
}

bool CitiesModel::isFavorite(int id)
{
    return isHaveIdInTable(id, "favorite_city");
}

bool CitiesModel::insertCityIfNotExists(const CityDto& city)
{
    bool ok =   m_query.prepare(
                    "INSERT INTO city "
                    "SELECT :id, :name, :lat, :lon "
                    "WHERE NOT EXISTS(SELECT 1 FROM city WHERE id = :id)"
                );

    if(ok){
        m_query.bindValue(":id",    city.id);
        m_query.bindValue(":name",  city.name);
        m_query.bindValue(":lat",   city.coordinates.lat);
        m_query.bindValue(":lon",   city.coordinates.lon);

        ok = m_query.exec();
    }

    if(!ok){
        qDebug() << m_query.lastError().text();
    }

    return ok;
}

bool CitiesModel::isCurentCity(int id)
{
    return isHaveIdInTable(id, "curent_city");
}

bool CitiesModel::isHaveIdInTable(int id, const QString &tableName)
{
    bool answer = false;

    if(m_query.exec(QString("SELECT COUNT(city_id) as itis FROM %1 WHERE city_id = %2").arg(tableName).arg(id))){
        if(m_query.next()){
            answer = m_query.value("itis").toBool();
        }
    }else{
        qDebug() << m_query.lastError().text();
    }

    return answer;
}

int CitiesModel::getCurentCityId()
{
    int answer = -1;

    if(m_query.exec("SELECT * FROM curent_city")){
        if(m_query.next()){
            answer = m_query.value("city_id").toInt();
        }
    }

    return answer;
}


void CitiesModel::createTables()
{
    m_query.exec( "CREATE TABLE IF NOT EXISTS city"
                "("
                    "id INTEGER PRIMARY KEY, "
                    "name INTEGER, "
                    "lat REAL, "
                    "lon REAL"
                ")");

    m_query.exec( "CREATE TABLE IF NOT EXISTS favorite_city"
                "("
                    "city_id INTEGER NULL,"
                    "CONSTRAINT FK_favorite_city_city FOREIGN KEY ('city_id') REFERENCES 'city' ('id') ON DELETE No Action ON UPDATE No Action"
                ")");

    m_query.exec( "CREATE TABLE IF NOT EXISTS curent_city"
                "("
                    "city_id INTEGER NULL,"
                    "CONSTRAINT FK_curent_city_city FOREIGN KEY ('city_id') REFERENCES 'city' ('id') ON DELETE No Action ON UPDATE No Action"
                ")");


}

std::optional<CityDto> CitiesModel::getCurentCity()
{
    std::optional<CityDto> answer = std::nullopt;
    int curentCityId = getCurentCityId();

    //если существует сurentCityId
    if(curentCityId != -1){

        if(m_query.exec(QString("SELECT * FROM city WHERE id = %1").arg(curentCityId))){
            if(m_query.next()){

                CoordinatesDto coordinates{
                    m_query.value("lat").toDouble(),
                    m_query.value("lon").toDouble()
                };

                answer.emplace(
                                m_query.value("id").toInt(),
                                m_query.value("name").toString(),
                                std::move(coordinates)
                            );
                answer->isFavorite = isFavorite(answer->id);
            }
        }
    }

    return answer;
}

std::vector<CityDto> CitiesModel::getFavoriteCities()
{
    std::vector<CityDto> answer;

    if(m_query.exec("SELECT * from city WHERE id IN (SELECT * FROM favorite_city)")){
        while(m_query.next()){

            CoordinatesDto coordinates{
                m_query.value("lat").toDouble(),
                m_query.value("lon").toDouble()
            };

            CityDto cityDto(m_query.value("id").toInt(),
                            m_query.value("name").toString(),
                            std::move(coordinates));

            cityDto.isFavorite = true;

            answer.emplace_back(std::move(cityDto));
        }
    }

    return answer;
}
