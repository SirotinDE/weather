import QtQuick 2.0
import Sailfish.Silica 1.0
import QtQuick.Layouts 1.1

import "../components/pages"
import "../theme/theme.js" as MyTheme

CPage {
    objectName: "mainPage"
    allowedOrientations: Orientation.All

    SilicaFlickable {
        anchors.fill: parent
        visible: !cppApi.isBusy

         ColumnLayout {
            id: column
            anchors.left: parent.left
            anchors.right: parent.right

            IconButton {
                Layout.alignment: Qt.AlignLeft
                icon.source: "image://theme/icon-m-arrow-left-green"

                onClicked: {
                    pageStack.pop()
                }
            }

            Label {
                Layout.alignment: Qt.AlignHCenter
                text: "Выберите город"
            }
        }
        SilicaListView {
            anchors.top: column.bottom
            anchors.bottom: parent.bottom
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.leftMargin: Theme.paddingLarge
            clip: true
            spacing: 8

            model: cppApi.favoritCitiesView.favoritCities

            delegate: MouseArea {
                anchors.left: parent.left
                anchors.right: parent.right
                height: label.height*1.4

                onPressed: {
                    label.color = MyTheme.darkGray
                }

                onReleased: {
                    label.color = MyTheme.black
                }

                onClicked: {
                    cppApi.favoritCitiesView.favoritCities.setCityAsCurent(model.index)
                    pageStack.pop()
                }

                RowLayout {
                    Layout.fillWidth: true

                    IconButton {
                        Layout.alignment: Qt.AlignHCenter
                        icon.source: model.isFavorite ? "image://theme/icon-m-favorite-selected" : "image://theme/icon-m-favorite"
                        icon.color: 'yellow'
                        icon.scale: 0.88

                        onClicked: {
                            model.isFavorite = !model.isFavorite
                        }
                    }

                    Label {
                        id: label
                        Layout.alignment: Qt.AlignHCenter
                        text: model.cityName
                        color: MyTheme.black
                    }
                }

                VerticalScrollDecorator{}
            }
        }
    }
}
