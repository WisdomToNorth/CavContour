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

        GroupBox {
            id: controlPanel
            Layout.fillWidth: true

            RowLayout {
                anchors.fill: parent
                RowLayout {
                    ComboBox {
                        id: caseIndexComboBox
                        Layout.fillWidth: false
                        model: viewer.caseList
                        currentIndex: 0
                        onCurrentIndexChanged: {
                            viewer.caseIndex = model[currentIndex]
                        }
                    }

                    CheckBox {
                        text: "Show Vertexes"
                        Layout.fillWidth: false
                        checked: viewer.showVertex
                        onCheckedChanged: {
                            viewer.showVertex = checked
                        }
                    }
                }
                RowLayout
                {
                    Label {
                        id: locLabel
                        text: viewer.mouseLoc
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
                onMouseLocationChanged: {
                    locLabel.text = location
                }
            }
        }

    }
}
