import ".."
import "../controls"
import PolyDebugger 1.0
import QtQuick 2.13
import QtQuick.Controls 2.13
import QtQuick.Layouts 1.13

Rectangle {
    id: columnWrapper

    ColumnLayout {
        id: columnLayout

        width: parent.width * 0.5
        height: parent.height
        anchors.centerIn: parent

        SettingItem {
            id: ngsettings

            polyAlg: polyAlgComboBox.currentIndex
            pointRadius: pointRadiusSlider.value
            lineWidth: lineWidthSlider.value
            arcApproxError: arcApproxSlider.value
            useUInt32Index: useUInt32IndexCheckBox.checked
            colorIndex: colorIndexComboBox.currentIndex
            pickTol: pickTolSlider.value
            showPrecision: showPrecisionSlider.value
            uiScaleFactor: uiScaleFactorSlider.value
            onAppAlgChangedSig: {
                polyAlgComboBox.currentIndex = ngsettings.polyAlg;
            }
            onPointRadiusChangedSig: {
                pointRadiusSlider.value = ngsettings.pointRadius;
            }
            onLineWidthChangedSig: {
                lineWidthSlider.value = ngsettings.lineWidth;
            }
            onArcApproxErrorChangedSig: {
                arcApproxSlider.value = ngsettings.arcApproxError;
            }
            onUseUInt32IndexChangedSig: {
                useUInt32IndexCheckBox.checked = ngsettings.useUInt32Index;
            }
            onColorIndexChangedSig: {
                colorIndexComboBox.currentIndex = ngsettings.colorIndex;
            }
            onPickTolChangedSig: {
                pickTolSlider.value = ngsettings.pickTol;
            }
            onShowPrecisionChangedSig: {
                showPrecisionSlider.value = ngsettings.showPrecision;
            }
            onUiScaleFactorChangedSig: {
                uiScaleFactorSlider.value = ngsettings.uiScaleFactor;
            }
        }

        GroupBox {
            title: "Settings"
            implicitWidth: parent.width
            implicitHeight: parent.height

            ColumnLayout {
                anchors.fill: parent
                spacing: 10

                ComboBox {
                    id: polyAlgComboBox

                    Layout.fillWidth: true
                    model: ["Calc", "NgPoly", "Slipper"]
                    currentIndex: ngsettings.polyAlg
                    onCurrentIndexChanged: {
                        ngsettings.polyAlg = polyAlgComboBox.currentIndex;
                    }
                }

                ComboBox {
                    id: colorIndexComboBox

                    Layout.fillWidth: true
                    model: ["Red", "Blue", "Green", "Magenta", "Orange", "GreenYellow", "Olive", "Turquoise", "Purple", "Crimson", "Black"]
                    currentIndex: ngsettings.colorIndex
                    onCurrentIndexChanged: {
                        ngsettings.colorIndex = colorIndexComboBox.currentIndex;
                    }
                }

                CheckBox {
                    id: useUInt32IndexCheckBox

                    Layout.fillWidth: true
                    text: "Use UInt32 Index"
                    checked: ngsettings.useUInt32Index
                    onCheckedChanged: {
                        ngsettings.useUInt32Index = useUInt32IndexCheckBox.checked;
                    }
                }

                CustomSlider {
                    id: pointRadiusSlider

                    Layout.fillWidth: true
                    title: "Point Radius"
                    from: 0.1
                    to: 1
                    stepSize: 0.1
                    value: ngsettings.pointRadius
                    onValueChanged: {
                        ngsettings.pointRadius = pointRadiusSlider.value;
                    }
                }

                CustomSlider {
                    id: lineWidthSlider

                    Layout.fillWidth: true
                    title: "Line Width"
                    from: 1
                    to: 5
                    stepSize: 1
                    value: ngsettings.lineWidth
                    onValueChanged: {
                        ngsettings.lineWidth = lineWidthSlider.value;
                    }
                }

                CustomSlider {
                    id: arcApproxSlider

                    Layout.fillWidth: true
                    title: "Arc Approximation Error"
                    from: 0.0001
                    to: 0.1
                    stepSize: 0.0001
                    value: ngsettings.arcApproxError
                    onValueChanged: {
                        ngsettings.arcApproxError = arcApproxSlider.value;
                    }
                }

                CustomSlider {
                    id: pickTolSlider

                    Layout.fillWidth: true
                    title: "Pick Tolerance"
                    from: 0.001
                    to: 1
                    stepSize: 0.001
                    value: ngsettings.pickTol
                    onValueChanged: {
                        ngsettings.pickTol = pickTolSlider.value;
                    }
                }

                CustomSlider {
                    id: showPrecisionSlider

                    Layout.fillWidth: true
                    title: "Show Precision"
                    from: 1
                    to: 16
                    stepSize: 1
                    value: ngsettings.showPrecision
                    onValueChanged: {
                        ngsettings.showPrecision = showPrecisionSlider.value;
                    }
                }

                CustomSlider {
                    id: uiScaleFactorSlider

                    Layout.fillWidth: true
                    title: "UI Scale Factor"
                    from: 10
                    to: 200
                    stepSize: 10
                    value: ngsettings.uiScaleFactor
                    onValueChanged: {
                        ngsettings.uiScaleFactor = uiScaleFactorSlider.value;
                    }
                }

            }

        }

    }

}
