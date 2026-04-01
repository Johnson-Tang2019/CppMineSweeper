import QtQuick
import QtQuick.Controls


Rectangle {
    anchors.fill: parent
    visible: true
    color: '#e60db7'

    Text {
        anchors.centerIn: parent
        text: qsTr("Game Over")
        font.pixelSize: 100;
        color: "red"
    }

    Rectangle {
        width: 100
        height: 100
        color: '#f157c8'
        x:  width / 2 + 20
        y: height / 2
        radius: 10

        Text{
            id: backToMain
            objectName: "backToMain"
            anchors.centerIn: parent
            anchors.margins: 20
            text: qsTr("Back")
            font.pixelSize: 30;

        }
        MouseArea{
            anchors.fill: parent
            onClicked: pageLoader.source = ""
        }
    }

}
