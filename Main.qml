import QtQuick
import QtQuick.Controls


ApplicationWindow {
    width: 1280
    height: 720
    visible: true
    title: qsTr("MineSweeper")
    color: '#e60db7'

    Rectangle {
        width: 320
        height: 100
        color: '#f0b5e3'
        x: 640 - width/2
        y: 500
        radius: 20
        
        Text{
            id: select_difficulty
            objectName: "select_difficulty"
            anchors.centerIn: parent
            anchors.margins: 20
            text: qsTr("simple")
            font.pixelSize: 50;
        }
        MouseArea{
            anchors.fill: parent
            onClicked: myClickObject.changeRate()
        }   
    }

    Rectangle {
        width: 320
        height: 100
        color: '#f0b5e3'
        x: 640 - width/2
        y: 350
        radius: 20
        Text{
            id: start_game
            objectName: "start_game"
            anchors.centerIn: parent
            anchors.margins: 20
            text: qsTr("Start")
            font.pixelSize: 50;
        }
        MouseArea{
            anchors.fill: parent
            onClicked: 
            {
                pageLoader.source = "MainGame.qml"
            }
        }   
    }

    Loader {
        id: pageLoader
        objectName: "pageLoader"
        anchors.fill: parent
    }
    
}
