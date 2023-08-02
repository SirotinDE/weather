#pragma once

#include <QObject>
#include <QScopedPointer>

class FavoritCitiesPresenter;
class FavoritCitiesViewModel;

class FavoritCitiesView : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QObject* favoritCities READ favoritCities NOTIFY favoritCitiesChanged)

public:
    explicit FavoritCitiesView(FavoritCitiesPresenter* favoritCitiesPresenter,
                               QObject *parent = nullptr);

    ~FavoritCitiesView();

    QObject *favoritCities() const;

signals:
    void favoritCitiesChanged();

private:
    FavoritCitiesPresenter* m_favoritCitiesPresenter;
    QScopedPointer<FavoritCitiesViewModel> m_favoritCitiesViewModel;
};

