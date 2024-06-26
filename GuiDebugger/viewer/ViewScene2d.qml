import QtQuick 2.13

Rectangle {
    id: rect

    default property alias content: plineSceneItem.children

    clip: true

    Rectangle {
        id: plineSceneItem

        property real cur_window_x: rect.width
        property real cur_window_y: rect.height
        width: 20000
        height: 20000
        // initially center (0, 0)
        x: cur_window_x / 2 - width / 2
        y: cur_window_y / 2 - height / 2
        border.width: 1 / scaler.xScale
        border.color: "blue"

        PinchArea {
            id: pinchArea

            property real m_x1: 0
            property real m_y1: 0
            property real m_y2: 0
            property real m_x2: 0
            property real m_zoom1: 1
            property real m_zoom2: 1
            property real m_max: 100
            property real m_min: 0.05

            anchors.fill: parent
            onPinchStarted: {
                m_x1 = scaler.origin.x
                m_y1 = scaler.origin.y
                m_x2 = pinch.startCenter.x
                m_y2 = pinch.startCenter.y
                plineSceneItem.x = plineSceneItem.x
                        + (pinchArea.m_x1 - pinchArea.m_x2) * (1 - pinchArea.m_zoom1)
                plineSceneItem.y = plineSceneItem.y
                        + (pinchArea.m_y1 - pinchArea.m_y2) * (1 - pinchArea.m_zoom1)
            }

            onPinchUpdated: {
                m_zoom1 = scaler.xScale
                var dz = pinch.scale - pinch.previousScale
                var newZoom = m_zoom1 + dz
                if (newZoom <= m_max && newZoom >= m_min)
                    m_zoom2 = newZoom
            }

            MouseArea {
                id: dragArea

                hoverEnabled: true
                anchors.fill: parent
                drag.target: plineSceneItem
                drag.filterChildren: true

                onWheel: function (wheel) {
                    pinchArea.m_x1 = scaler.origin.x
                    pinchArea.m_y1 = scaler.origin.y
                    pinchArea.m_zoom1 = scaler.xScale
                    pinchArea.m_x2 = mouseX
                    pinchArea.m_y2 = mouseY
                    var newZoom
                    if (wheel.angleDelta.y > 0) {
                        newZoom = pinchArea.m_zoom1 + 0.2
                        if (newZoom <= pinchArea.m_max)
                            pinchArea.m_zoom2 = newZoom
                        else
                            pinchArea.m_zoom2 = pinchArea.m_max
                    } else {
                        newZoom = pinchArea.m_zoom1 - 0.2
                        if (newZoom >= pinchArea.m_min)
                            pinchArea.m_zoom2 = newZoom
                        else
                            pinchArea.m_zoom2 = pinchArea.m_min
                    }
                    plineSceneItem.x = plineSceneItem.x
                            + (pinchArea.m_x1 - pinchArea.m_x2) * (1 - pinchArea.m_zoom1)
                    plineSceneItem.y = plineSceneItem.y
                            + (pinchArea.m_y1 - pinchArea.m_y2) * (1 - pinchArea.m_zoom1)
                }

                MouseArea {
                    anchors.fill: parent
                }
            }
        }

        Rectangle {
            id: horizontalAxis

            x: parent.width / 2
            height: parent.height
            color: "black"
            width: 1 / pinchArea.m_zoom2
        }

        Rectangle {
            id: verticalAxis

            y: parent.width / 2
            width: parent.width
            color: "black"
            height: 1 / pinchArea.m_zoom2
        }

        transform: Scale {
            id: scaler

            origin.x: pinchArea.m_x2
            origin.y: pinchArea.m_y2
            xScale: pinchArea.m_zoom2
            yScale: pinchArea.m_zoom2
        }
    }
}
