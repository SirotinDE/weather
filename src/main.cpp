/*******************************************************************************
**
** Copyright (C) 2022 ru.auroraos
**
** This file is part of the Моё приложение для ОС Аврора project.
**
** Redistribution and use in source and binary forms,
** with or without modification, are permitted provided
** that the following conditions are met:
**
** * Redistributions of source code must retain the above copyright notice,
**   this list of conditions and the following disclaimer.
** * Redistributions in binary form must reproduce the above copyright notice,
**   this list of conditions and the following disclaimer
**   in the documentation and/or other materials provided with the distribution.
** * Neither the name of the copyright holder nor the names of its contributors
**   may be used to endorse or promote products derived from this software
**   without specific prior written permission.
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
** AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
** THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
** FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
** IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
** FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY,
** OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
** PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
** LOSS OF USE, DATA, OR PROFITS;
** OR BUSINESS INTERRUPTION)
** HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
** WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE)
** ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
** EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
**
*******************************************************************************/

#include <auroraapp.h>
#include <QtQuick>
#include <QScopedPointer>
#include <QStandardPaths>
#include "core/db_manager.h"
#include "view/cpp_api.h"
#include "view/weather_view.h"
#include "view/city_search_view.h"
#include "view/favorit_cities_view.h"
#include "presenter/weather_presenter.h"
#include "presenter/city_search_presenter.h"
#include "presenter/favorit_cities_presenter.h"
#include "model/city_weather_model.h"
#include "model/geoposition_model.h"
#include "model/cities_model.h"
#include <QDir>

#include "dto/coordinates_dto.h"

int main(int argc, char *argv[])
{
    QScopedPointer<QGuiApplication> application(Aurora::Application::application(argc, argv));
    application->setOrganizationName(QStringLiteral("ru.auroraos"));
    application->setApplicationName(QStringLiteral("weatherGlobal"));

    QString dbFilePath = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);// +
    QDir dir(dbFilePath);
    dir.mkpath(dbFilePath);

    dbFilePath += "/weatherGlobal.sqlite";

    DBManager dBManager(dbFilePath);
    QScopedPointer<CppApi> cppApi(new CppApi);

    QScopedPointer<GeopositionModel>        geopositionModel(new GeopositionModel);
    QScopedPointer<CityWeatherModel>        cityWeatherModel(new CityWeatherModel);
    QScopedPointer<CitiesModel>             citiesModel(new CitiesModel(dBManager.db()));

    auto favoriteCities = citiesModel->getFavoriteCities();

    QScopedPointer<WeatherPresenter>        weatherPresenter(new WeatherPresenter(geopositionModel.data(),
                                                                                  cityWeatherModel.data(),
                                                                                  citiesModel.data(),
                                                                                  cppApi.data()));

    QScopedPointer<CitySearchPresenter>     citySearchPresenter(new CitySearchPresenter);
    QScopedPointer<FavoritCitiesPresenter>  favoritCitiesPresenter(new FavoritCitiesPresenter(citiesModel.data()));


    QScopedPointer<WeatherView>        weatherView(new WeatherView(weatherPresenter.data(), weatherPresenter->getCurentCity()));
    QScopedPointer<CitySearchView>     citySearchView(new CitySearchView(citySearchPresenter.data()));
    QScopedPointer<FavoritCitiesView>  favoritCitiesView(new FavoritCitiesView(favoritCitiesPresenter.data()));

    weatherPresenter->connect(favoritCitiesPresenter.data(),
                              &FavoritCitiesPresenter::curentCityChanged,
                              weatherPresenter.data(),
                              &WeatherPresenter::onCurentCityChanged);

    cppApi->setWeatherView(weatherView.data());
    cppApi->setCitySearchView(citySearchView.data());
    cppApi->setFavoritCitiesView(favoritCitiesView.data());

    QScopedPointer<QQuickView> view(Aurora::Application::createView());
    view->rootContext()->setContextProperty("cppApi", cppApi.data());
    view->setSource(Aurora::Application::pathTo(QStringLiteral("qml/weatherGlobal.qml")));
    view->show();

    return application->exec();
}
