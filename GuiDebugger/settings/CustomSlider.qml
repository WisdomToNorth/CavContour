import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

Item {
    id: customSlider

    property alias title: titleLabel.text
    property alias value: pointRadiusSlider.value
    property alias from: pointRadiusSlider.from
    property alias to: pointRadiusSlider.to
    property alias stepSize: pointRadiusSlider.stepSize

    width: parent.width
    height: 80 // Set a reasonable height for the slider component

    ColumnLayout {
        width: parent.width
        anchors.fill: parent

        Label {
            id: titleLabel

            text: "Title"
            Layout.alignment: Qt.AlignHCenter
        }

        Slider {
            id: pointRadiusSlider

            Layout.alignment: Qt.AlignHCenter
            Layout.fillWidth: true
            onValueChanged: valueLabel.text = value
        }

        RowLayout {
            Layout.alignment: Qt.AlignHCenter
            Layout.fillWidth: true

            Text {
                id: minLabel

                text: pointRadiusSlider.from
                Layout.alignment: Qt.AlignLeft
            }

            Text {
                id: valueLabel

                text: pointRadiusSlider.value
                Layout.fillWidth: true
                horizontalAlignment: Text.AlignHCenter
            }

            Text {
                id: maxLabel

                text: pointRadiusSlider.to
                Layout.alignment: Qt.AlignRight
            }

        }

    }

}
