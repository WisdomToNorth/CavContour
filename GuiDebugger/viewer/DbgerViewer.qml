import PolyDebugger 1.0
import QtQuick 2.13
import QtQuick.Controls 2.13
import QtQuick.Controls.Material 2.12
import QtQuick.Layouts 1.13

SplitView {
    id: splitViewVertical

    Material.theme: Material.Light
    Material.accent: Material.Indigo
    Material.primary: Material.Indigo
    Material.elevation: 5
    Material.background: Material.White
    Material.foreground: Material.Black

    orientation: Qt.Vertical
    SceneView2d {
        implicitHeight: splitViewVertical.height * 0.94

        SceneViewer {
            id: algorithmView

            anchors.fill: parent
        }
    }

    GroupBox {
        id: controlPanel
        implicitWidth: splitViewVertical.height * 0.06

        RowLayout {
            anchors.fill: parent
            spacing: 10

            ComboBox {
                id: caseIndexComboBox
                Layout.fillWidth: true
                model: ["default1", "default2", "default3"]
                currentIndex: 0
                onCurrentIndexChanged: {
                    algorithmView.caseIndex = model[currentIndex]
                }
            }

            CheckBox {
                text: "Show Vertexes"
                Layout.fillWidth: true
                checked: algorithmView.showVertexes
                onCheckedChanged: {
                    algorithmView.showVertexes = checked
                }
            }
        }
    }
}
