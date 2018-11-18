import QtQuick 2.0
import QtQuick.Scene3D 2.0
import QtPhysics.unofficial 1.0
import QtQuick.Controls 2.4

ApplicationWindow {
    id: window
    title: "Mini-QML"
    visible: true
    height: 600
    width: 800

    Text {
        text: "Click me!"
        anchors.top: parent.top
        anchors.topMargin: 10
        anchors.horizontalCenter: parent.horizontalCenter

    }
    Rectangle {
        id: scene
        width: Math.min(parent.width, parent.height) - 100
        height: width
        anchors.centerIn: parent
        color: "darkRed"

        Scene3D {
            anchors.fill: parent
            anchors.margins: 10
            focus: true
            aspects: ["input","physics"]

            AnimatedEntity {
                id:sceneroot
            }
        }
    }

}
