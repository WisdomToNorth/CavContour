import PolyDebugger 1.0
import QtQuick 2.13
import QtQuick.Controls 2.13
import QtQuick.Layouts 1.15

SplitView {
    id: splitViewHorzontal
    orientation: Qt.Horizontal

    ColumnLayout
    {
        anchors.fill: parent
        spacing: 3

        GroupBox {
            id: controlPanel
            Layout.fillWidth: true

            RowLayout {
                anchors.fill: parent
                spacing: 3

                ComboBox {
                    id: caseIndexComboBox
                    Layout.fillWidth: true
                    model: viewer.caseList
                    currentIndex: 0
                    onCurrentIndexChanged: {
                        viewer.caseIndex = model[currentIndex]
                    }
                }

                CheckBox {
                    text: "Show Vertexes"
                    Layout.fillWidth: true
                    checked: viewer.showVertex
                    onCheckedChanged: {
                        viewer.showVertex = checked
                    }
                }
            }
        }

        ViewScene2d {
            Layout.fillHeight: true
            Layout.fillWidth: true

            SceneViewer {
                id: viewer
                anchors.fill: parent
            }
        }

    }
}
