import QtQuick 2.4
import QtQuick.Controls 1.3
import QtQuick.Window 2.2


ApplicationWindow {
    id: root
    title: "Lamp"
    width: 640
    height: 640
    visible: true

    function turnOn(){
        console.log("turnOn");
        lamp.state = "on"
    }

    function turnOff(){
        console.log("turnOff");
        lamp.state = "off"
    }

    function changeColor(color){
        console.log("changeColor");
        lamp.color = color;
    }

    function showConnectDialog(){
        console.log("showConnectDialog");
        dialog.open()
    }

    signal turnConnect(string hostname, int port)

    PowerButton{
        anchors.right:  lamp.right
        anchors.bottom: lamp.bottom
        onClicked: {
            lamp.state = lamp.state === "on" ? "off" : "on"
        }
        z: 10
    }

    LampView{
        id: lamp
        anchors.fill: parent
    }

    ConnectDialog {
        id: dialog
        onAccepted: root.turnConnect(dialog.hostname, dialog.port)
        onRejected: Qt.quit();
    }
    Component.onCompleted: dialog.open()
}
