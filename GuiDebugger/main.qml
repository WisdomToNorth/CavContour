import QtQuick 2.13
import QtQuick.Controls 2.13
import QtQuick.Layouts 1.15
import QtQuick.Window 2.13
import QtQuick.Controls.Material 2.12

import "settings"
import "viewer"

ApplicationWindow {
    id: mainWindow

    Material.theme: Material.Light
    Material.accent: Material.Blue
    Material.primary: Material.Indigo
    Material.background: Material.White
    Material.foreground: Material.Black

    visible: true
    width: Screen.width - 200
    height: Screen.height - 200
    title: qsTr("Cavalier Contours")

    font {
        family: "Consolas"
    }

    header: TabBar {
        id: tabBar
        height: 40

        TabButton {
            height: tabBar.height
            text: "Polyline Offset"
        }

        TabButton {
            height: tabBar.height
            text: "Debugger Settings"
        }
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
                NgSettings {}
            }
        }
    }


}
