/*******************************************************************************
**
** Copyright (C) 2022 ru.auroraos
**
** This file is part of the Приложение для просмотра погоды project.
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

import QtQuick 2.0
import Sailfish.Silica 1.0
import QtQuick.Layouts 1.1

import "../components/pages"
import "../theme/theme.js" as MyTheme

CPage {
    objectName: "mainPage"
    allowedOrientations: Orientation.All

    ColumnLayout{
        anchors.top : parent.top
        anchors.topMargin: 200
        width: parent.width
        spacing: 15

        Layout.alignment: Qt.AlignHCenter

        RowLayout {
            Layout.alignment: Qt.AlignHCenter

            Item {
                id: spacer1
                width: searchIcon.width
            }

            Label {
                Layout.alignment: Qt.AlignHCenter
                text: cppApi.weatherView.cityName
                font.pixelSize: Theme.fontSizeHuge
                color: MyTheme.black
            }

            IconButton {
                id: searchIcon
                anchors.verticalCenter: parent.verticalCenter
                icon.source: "image://theme/icon-m-search"
                icon.scale: 0.88

                onClicked: {
                    pageStack.push("Cities.qml")
                }
            }
        }

        Icon {
            Layout.alignment: Qt.AlignHCenter
            source: {
                switch(cppApi.weatherView.weatherIconType){
                    case 0 : return "image://theme/icon-l-weather-d000-light";
                    case 1 : return "image://theme/icon-l-weather-d400-light";
                    case 2 : return "image://theme/icon-l-weather-d410-light";
                }
            }
        }

        Label {
            Layout.alignment: Qt.AlignHCenter
            text: cppApi.weatherView.temperature + MyTheme.degree
            font.pixelSize: Theme.fontSizeHuge*1.5
            color: MyTheme.black
        }

        Label {
            Layout.alignment: Qt.AlignHCenter
            text: "макс. " + cppApi.weatherView.maxTemperature + MyTheme.degree +", мин."+ cppApi.weatherView.minTemperature + MyTheme.degree
            font.pixelSize: Theme.fontSizeSmall
            color: MyTheme.black
        }

        Label {
            Layout.alignment: Qt.AlignHCenter
            text: "💧" + cppApi.weatherView.humidity + "%"
            font.pixelSize: Theme.fontSizeLarge
            color: MyTheme.black
        }

        Item {
            id: spacer2
            height: 15
        }
        RowLayout {
            Layout.alignment: Qt.AlignHCenter

            IconButton {
                Layout.alignment: Qt.AlignHCenter
                icon.source: cppApi.weatherView.cityIsFavorite ? "image://theme/icon-m-favorite-selected" : "image://theme/icon-m-favorite"
                icon.color: 'yellow'
                icon.scale: 0.88
                onClicked: {
                    cppApi.weatherView.switchCurentCityIsFavorite()
                }
            }

            Button {
                text: "избранные города"
                onClicked: {
                    pageStack.push("FavoriteCities.qml")
                }
            }
        }
    }
}
