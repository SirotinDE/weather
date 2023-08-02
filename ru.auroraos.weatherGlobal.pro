TARGET = ru.auroraos.weatherGlobal

QT += concurrent sql network positioning

CONFIG += \
    auroraapp


CONFIG += auroraapp_i18n c++17
QMAKE_CXXFLAGS += -std=c++17

PKGCONFIG += \

SOURCES += \
    src/core/db_manager.cpp \
    src/model/cities_model.cpp \
    src/model/city_weather_model.cpp \
    src/dto/city_dto.cpp \
    src/dto/coordinates_dto.cpp \
    src/dto/weather_dto.cpp \
    src/main.cpp \
    src/model/geoposition_model.cpp \
    src/presenter/city_search_presenter.cpp \
    src/presenter/favorit_cities_presenter.cpp \
    src/presenter/weather_presenter.cpp \
    src/utility/json_helper.cpp \
    src/utility/randomizer.cpp \
    src/view/city_search_view.cpp \
    src/view/cpp_api.cpp \
    src/view/favorit_cities_view.cpp \
    src/view/view_model/favorit_cities_view_model.cpp \
    src/view/weather_view.cpp

HEADERS += \
    src/core/db_manager.h \
    src/model/cities_model.h \
    src/model/city_weather_model.h \
    src/dto/city_dto.h \
    src/dto/coordinates_dto.h \
    src/dto/weather_dto.h \
    src/model/geoposition_model.h \
    src/presenter/city_search_presenter.h \
    src/presenter/favorit_cities_presenter.h \
    src/presenter/weather_presenter.h \
    src/utility/json_helper.h \
    src/utility/randomizer.h \
    src/view/city_search_view.h \
    src/view/cpp_api.h \
    src/view/favorit_cities_view.h \
    src/view/view_model/favorit_cities_view_model.h \
    src/view/weather_view.h

HEADERS += \

DISTFILES += \
    rpm/ru.auroraos.weatherGlobal.spec \
    AUTHORS.md \
    CODE_OF_CONDUCT.md \
    CONTRIBUTING.md \
    LICENSE.BSD-3-CLAUSE.md \
    README.md \

AURORAAPP_ICONS = 86x86 108x108 128x128 172x172


TRANSLATIONS += \
    translations/ru.auroraos.weatherGlobal.ts \
    translations/ru.auroraos.weatherGlobal-ru.ts \
