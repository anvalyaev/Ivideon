import QtQuick 2.0
import QtQuick.Dialogs 1.2
import QtQuick.Controls 1.3
import QtQuick.Layouts 1.1

Dialog {
    id: dialog
    title: "Connect dialog"
    width: 300
    height: 150
    property string hostname: host.text
    property int port: port.value

    standardButtons: StandardButton.Ok | StandardButton.Close

    ColumnLayout {
        id: columnLayout
        anchors.centerIn: parent
        spacing: 6
        Label {
            text: "Please, enter the hostname
and port: "
        }
        RowLayout {
            id: rowLayout
            spacing: 6

            TextField{
                id: host
                text: "127.0.0.1"
            }

            SpinBox {
                id: port
                minimumValue: 0
                maximumValue: 9999
                value: 9999
            }
        }
    }
}

