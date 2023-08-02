#pragma once

#include <QAbstractListModel>
#include <vector>
#include "../../dto/city_dto.h"

class FavoritCitiesPresenter;

class FavoritCitiesViewModel : public QAbstractListModel
{
    Q_OBJECT

public:
    explicit FavoritCitiesViewModel(FavoritCitiesPresenter* favoritCitiesPresenter,
                                    QObject *parent = nullptr);
    ~FavoritCitiesViewModel();

    enum Roles {
        CityName = Qt::UserRole + 1,
        IsFavorite
    };

    virtual int rowCount(const QModelIndex &parent) const override;
    virtual QVariant data(const QModelIndex &index, int role) const override;
    virtual QHash<int, QByteArray> roleNames() const override;
    virtual bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;

    void updateCities(std::vector<CityDto>&& cities);

public slots:
    void setCityAsCurent(int index);
private:
    FavoritCitiesPresenter* m_favoritCitiesPresenter;
    std::vector<CityDto> m_cities;
};

