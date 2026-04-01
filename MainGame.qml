import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Rectangle {
    id: gameRoot
    anchors.fill: parent
    visible: true
    color: '#f5b5ec'

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

    property int gridSize: myClickObject.getSize()   
    // 每个格子大小
    property int cellSize: 600 / gridSize

    Connections {
        target: myClickObject

        function onUpdateBox(index, number) {
            gameRoot.updateBox(index, number)
        }

    }


    function updateBox(index, number) {
        if(index == -1 && number == -1){
            pageLoader.source = "Gameover.qml";
            return;
        }
        if (index < 0 || index >= mineRepeater.count) {
            return;
        }

        var cell = mineRepeater.itemAt(index);   // 正確取得 delegate 的方式
        if (number === 0) {
            cell.color = "white";   // 翻開變白
        }else{
            cell.color = "#e6a4d5";
            // 找到 Text 並設定數字
            for (var i = 0; i < cell.children.length; ++i) {
                var child = cell.children[i];
                if (child.toString().indexOf("Text") !== -1) {  // 判斷是否為 Text
                    child.text = number.toString();
                    console.log("QML updated cell", index, "→", number);
                    return;
                }
            }
        }
    }

    // 整体网格容器
    GridLayout {
        id: mineGrid
        objectName: "mineGrid"  
        rows: gridSize
        columns: gridSize
        anchors.centerIn: parent  // 整个格子局中显示


        // 循环生成 N*N 个格子
        Repeater {
            id: mineRepeater
            model: gridSize * gridSize
            objectName: "mineGridRepeater"  // 总数量 = x*x

            // 每个格子
            Rectangle {
                width: cellSize
                height: cellSize
                color: '#e77887'
                radius: 3
                border.color: "white"
                border.width: 1
                objectName: "box" + index

                Text {
                    objectName: "boxText"
                    anchors.centerIn: parent
                    text: ""           // 初始文本为空
                    color: '#ff2a6e'
                    font.pixelSize: 10
                }

                // 格子点击效果
                MouseArea {
                    anchors.fill: parent
                    onClicked: {
                        myClickObject.clickBox(index)  // 调用 C++ 的 clickBox 方法
                    }
                }
            }
        }
    }

    
   
}
