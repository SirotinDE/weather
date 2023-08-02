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

            Item {
                id: spacer
                Layout.alignment: Qt.AlignHCenter
                height: 15
            }

            Label {
                Layout.alignment: Qt.AlignHCenter
                text: "Выберите город"
            }

            TextField {
                background: null
                Layout.alignment: Qt.AlignVCenter
                Layout.fillWidth: true
                color: MyTheme.black

                Rectangle{
                    anchors.fill: parent
                    anchors.margins: {
                        leftMargin: -5
                        rightMargin: -5
                    }

                    color: 'transparent'
                    z: -1
                    border.width: 1
                    radius: 6
                }
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

            model: []

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
                    console.log("clicked")
                }

                RowLayout {
                    Layout.fillWidth: true

                    IconButton {
                        Layout.alignment: Qt.AlignHCenter
                        icon.source: true ? "image://theme/icon-m-favorite-selected" : "image://theme/icon-m-favorite"
                        icon.color: 'yellow'
                        icon.scale: 0.88
                    }

                    Label {
                        id: label
                        Layout.alignment: Qt.AlignHCenter
                        text: model.modelData
                        color: MyTheme.black
                    }
                }

                VerticalScrollDecorator{}
            }
        }
    }
}
