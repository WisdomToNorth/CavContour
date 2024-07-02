import "../controls"
import PolyDebugger 1.0
import Qt.labs.platform 1.1
import QtQuick 2.13
import QtQuick.Controls 2.13
import QtQuick.Layouts 1.15

SplitView {
    id: splitViewHorzontal

    orientation: Qt.Horizontal

    ColumnLayout {
        anchors.fill: parent

        GroupBox {
            id: controlPanel

            Layout.fillWidth: true

            RowLayout {
                anchors.fill: parent

                RowLayout {
                    Button {
                        text: "Load"
                        Layout.fillWidth: false
                        onClicked: {
                            viewer.loadCase();
                        }
                    }

                    Button {
                        text: "Save"
                        Layout.fillWidth: false
                        onClicked: {
                            viewer.saveCase();
                        }
                    }

                    Label {
                        text: "Case:"
                        Layout.fillWidth: false
                    }

                    ComboBox {
                        id: caseIndexComboBox

                        Layout.fillWidth: false
                        model: viewer.caseList
                        currentIndex: 0
                        onCurrentIndexChanged: {
                            viewer.caseIndex = model[currentIndex];
                        }
                    }

                    CheckBox {
                        text: "Show Vertexes"
                        Layout.fillWidth: false
                        checked: viewer.showVertex
                        onCheckedChanged: {
                            viewer.showVertex = checked;
                        }
                    }

                    CheckBox {
                        text: "Enable Slide"
                        Layout.fillWidth: false
                        checked: viewer.enableSlide
                        onCheckedChanged: {
                            viewer.enableSlide = checked;
                        }
                    }

                    CheckBox {
                        text: "Show Axis"
                        Layout.fillWidth: false
                        checked: viewer.showAxis
                        onCheckedChanged: {
                            viewer.showAxis = checked;
                        }
                    }

                    CheckBox {
                        text: "Show Dir"
                        Layout.fillWidth: false
                        checked: viewer.showDir
                        onCheckedChanged: {
                            viewer.showDir = checked;
                        }
                    }

                }

                Label {
                    id: locLabel

                    text: viewer.mouseLoc
                    Layout.alignment: Qt.AlignRight
                }

            }

        }

        ViewScene2d {
            Layout.fillHeight: true
            Layout.fillWidth: true

            SceneViewer {
                id: viewer

                anchors.fill: parent
                onMouseLocationChanged: function(location) {
                    locLabel.text = location;
                }
            }

        }

    }

}
