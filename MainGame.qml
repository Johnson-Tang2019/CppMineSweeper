import QtQuick
import QtQuick.Controls


Rectangle {
    anchors.fill: parent
    visible: true
    color: '#f5b5ec'

    Rectangle {
        width: 100
        height: 100
        color: '#f0b5e3'
        x: 1280 - width / 2
        y: height / 2

        Text{
            id: backToMain
            objectName: "backToMain"
            anchors.centerIn: parent
            anchors.margins: 20
            text: qsTr("Back")
            font.pixelSize: 50;

        }
        MouseArea{
            anchors.fill: parent
            onClicked: pageLoader.source = ""
        }

    }
       
        

    
}
