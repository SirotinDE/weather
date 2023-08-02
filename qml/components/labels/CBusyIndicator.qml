import QtQuick 2.0
import Sailfish.Silica 1.0

Column {
    property int timer: 0
    id: column
    z: 10
    visible: cppApi.isBusy
    spacing: Theme.paddingLarge
    anchors.bottom: parent.bottom
    anchors.horizontalCenter: parent.horizontalCenter

    onVisibleChanged: {
        if(!visible){
            timer = 0
            _timer.stop()
        }
    }

    Label {
        id: label
        anchors.horizontalCenter: parent.horizontalCenter
        text: timer ? cppApi.busyText + " " + timer : cppApi.busyText
        font.pixelSize: Theme.fontSizeLarge
        color: '#000000'
        horizontalAlignment: Text.AlignHCenter
        wrapMode: Text.WordWrap

        Timer {
            id: _timer
            running: timer > 0

            onTriggered: {
                --timer;
            }
        }
    }

    BusyIndicator {
        color: '#000000'
        size: BusyIndicatorSize.Medium
        anchors.horizontalCenter: parent.horizontalCenter
        running: cppApi.isBusy
    }
}
