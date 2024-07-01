import QtQuick 2.13
import QtQuick.Controls 2.13
import QtQuick.Layouts 1.15
import QtQuick.Window 2.13

import "settings"
import "viewer"

ApplicationWindow {
    id: mainWindow

    function adjustFontSize(baseSize) {
        return baseSize * Screen.pixelDensity
    }

    visible: true
    width: Screen.width - 200
    height: Screen.height - 200
    title: qsTr("Cavalier Contours")

    font {
        family: "Consolas"
    }

    Page {
        anchors.fill: parent

        Rectangle {
            anchors.fill: parent
            border.width: 2
            border.color: "grey"

            StackLayout {
                anchors.fill: parent
                anchors.margins: 2
                currentIndex: tabBar.currentIndex

                Viewer2d {}

                DebuggerSettings {}
            }
        }
    }

    header: TabBar {
        id: tabBar

        TabButton {
            text: "Polyline Offset"
        }

        TabButton {
            text: "Debugger Settings"
        }
    }
}
