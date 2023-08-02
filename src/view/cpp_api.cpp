#include "cpp_api.h"

CppApi::CppApi(QObject *parent)
    : QObject(parent)
{

}

QObject* CppApi::weatherView()
{
    return m_weatherView;
}

QObject* CppApi::citySearchView()
{
    return m_citySearchView;
}

QObject* CppApi::favoritCitiesView()
{
    return m_favoritCitiesView;
}

void CppApi::setWeatherView(QObject* weatherView)
{
    m_weatherView = weatherView;
}

void CppApi::setCitySearchView(QObject* citySearchView)
{
    m_citySearchView = citySearchView;
}

void CppApi::setFavoritCitiesView(QObject* favoritCitiesView)
{
    m_favoritCitiesView = favoritCitiesView;
}

void CppApi::setIsBusy(bool isBusy)
{
    m_isBusy = isBusy;
    emit isBusyChanged();
}

void CppApi::setBusyText(const QString &busyText)
{
    m_busyText = busyText;
    emit busyTextChanged();
}

bool CppApi::isBusy() const
{
    return true;//m_isBusy;
}

const QString &CppApi::busyText() const
{
    return m_busyText;
}
