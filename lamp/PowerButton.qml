import QtQuick 2.0

Item {
    id: root
    signal clicked()
    width: 100
    height: 100

    Image {
        id: power
        source: "qrc:/images/power.svg"
        sourceSize.height: height
        sourceSize.width: width

        anchors.centerIn: parent
        fillMode: Image.PreserveAspectFit
        antialiasing: true

        MouseArea {
            anchors.fill: parent
            onClicked: {
                root.clicked()
            }
            onPressed: root.state = "pressed"
            onReleased: root.state = "released"
        }
    }

    state: "released"
    states: [
        State {
            name: "released"
            PropertyChanges { target: power; width: 50}
            PropertyChanges { target: power; height: 50 }
        },

        State {
            name: "pressed"
            PropertyChanges { target: power; width: 40 }
            PropertyChanges { target: power; height: 40 }
        }
    ]

    transitions: [
        Transition {
          PropertyAnimation { target: power; properties: "width";
                              duration: 100; easing.type: Easing.InOutExpo }
          PropertyAnimation { target: power; properties: "height";
                              duration: 100; easing.type: Easing.InOutExpo }
        }
    ]

}

