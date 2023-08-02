import QtQuick 2.0
import Sailfish.Silica 1.0
import "../"
import "../labels"
import "../../theme/theme.js" as MyTheme

Page {
    showNavigationIndicator: false

    id: page
    allowedOrientations: Orientation.Portrait

    Rectangle {
        anchors.fill: parent
        gradient: Gradient {
            GradientStop { position: 0.0; color: '#403B4A' }
            GradientStop { position: 1.0; color: '#E7E9BB'}
        }
        opacity: 1
        z:-2
    }

    CBusyIndicator {

    }
}
