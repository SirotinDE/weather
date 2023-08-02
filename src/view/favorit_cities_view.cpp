#include "favorit_cities_view.h"
#include "../presenter/favorit_cities_presenter.h"
#include "view_model/favorit_cities_view_model.h"

FavoritCitiesView::FavoritCitiesView(FavoritCitiesPresenter *favoritCitiesPresenter,
                                     QObject *parent)
    : QObject(parent)
    , m_favoritCitiesPresenter(favoritCitiesPresenter)
    , m_favoritCitiesViewModel(new FavoritCitiesViewModel(m_favoritCitiesPresenter))
{
    m_favoritCitiesViewModel->updateCities(m_favoritCitiesPresenter->getFavoritCities());
}

FavoritCitiesView::~FavoritCitiesView()
{

}

QObject *FavoritCitiesView::favoritCities() const
{
    return m_favoritCitiesViewModel.data();
}
