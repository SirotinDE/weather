#pragma once

#include <QObject>

class CppApi: public QObject
{
    Q_OBJECT

    Q_PROPERTY(QObject* weatherView READ weatherView NOTIFY weatherViewChanged)
    Q_PROPERTY(QObject* citySearchView READ citySearchView NOTIFY citySearchViewChanged)
    Q_PROPERTY(QObject* favoritCitiesView READ favoritCitiesView NOTIFY favoritCitiesViewChanged)
    Q_PROPERTY(bool isBusy READ isBusy NOTIFY isBusyChanged)
    Q_PROPERTY(QString busyText READ busyText NOTIFY busyTextChanged)

public:
    CppApi(QObject* parent = nullptr);
    QObject* weatherView();
    QObject* citySearchView();
    QObject* favoritCitiesView();

    void setWeatherView(QObject* weatherView);
    void setCitySearchView(QObject* citySearchView);
    void setFavoritCitiesView(QObject* favoritCitiesView);

    void setIsBusy(bool isBusy);
    void setBusyText(const QString &busyText);

    bool isBusy() const;
    const QString &busyText() const;

signals:
    void weatherViewChanged();
    void citySearchViewChanged();
    void favoritCitiesViewChanged();

    void isBusyChanged();
    void busyTextChanged();

private:
    QObject* m_weatherView;
    QObject* m_citySearchView;
    QObject* m_favoritCitiesView;
    bool m_isBusy = false;
    QString m_busyText;
};

