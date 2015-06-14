import QtQuick 2.4
import QtGraphicalEffects 1.0

Item {
    id: root

    property color color
    property int radiusOfRays
    property int numberOfRays: 48
    property int animationDuration: 500
    Image {
        id: background
        source: "qrc:/images/background.png"
        fillMode: Image.Tile
        anchors.fill: parent
        z: -10
        RadialGradient {
            verticalOffset: -124
            anchors.fill: parent
            gradient: Gradient {
                GradientStop { position: 0.0; color: root.color }
                GradientStop { position: (radiusOfRays / 450)  + 0.01; color: "#00000000" }
            }
        }
    }

    Image {
        id: lamp
        source: "qrc:/images/lamp.svg"
        sourceSize.height: height
        sourceSize.width: width

        anchors.centerIn: parent
        fillMode: Image.PreserveAspectFit
        antialiasing: true
    }

    Repeater {
        model: numberOfRays
        Rectangle
        {
            color: root.color
            width: 34
            height: 3.5
            radius: 7
            x: lamp.x + 109 + radiusOfRays * Math.cos(index * (Math.PI / (numberOfRays / 2)))
            y: lamp.y + 124 + radiusOfRays * Math.sin(index * (Math.PI / (numberOfRays / 2)))
            z: -1
            rotation: index * (360 / numberOfRays)
            antialiasing: true
        }
    }

    state: "off"
    states: [
        State {
            name: "off"
            PropertyChanges { target: root; radiusOfRays: 0 }
        },

        State {
            name: "on"
            PropertyChanges { target: root; radiusOfRays: 150 }
        }
    ]

    transitions: [
        Transition {
          PropertyAnimation { target: root; properties: "radiusOfRays";
                              duration: animationDuration; easing.type: Easing.InOutExpo }
        }
    ]
}

