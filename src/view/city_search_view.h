#pragma once

#include <QObject>

class CitySearchPresenter;

class CitySearchView: public QObject
{
    Q_OBJECT

public:
    CitySearchView(CitySearchPresenter* citySearchPresenter, QObject *parent = nullptr);

private:
    CitySearchPresenter* m_citySearchPresenter;
};

