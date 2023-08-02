#include "city_search_view.h"
#include "../presenter/city_search_presenter.h"

CitySearchView::CitySearchView(CitySearchPresenter* citySearchPresenter, QObject *parent)
    : QObject(parent)
    , m_citySearchPresenter(citySearchPresenter)
{

}
