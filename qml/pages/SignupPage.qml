import QtQuick
import "../components"
Item {
    id: item1
    Column{
        anchors.centerIn: parent
        spacing: 30
        Text{
            anchors.horizontalCenter: parent.horizontalCenter
            text: "select account type:"
            font.pixelSize: 20
        }

        Row{
            anchors.horizontalCenter: parent.Center
            spacing: 10
            FlatButton{
                width: 200
                height: 250
                textColor: "#ffffff"
                backgoundColor: "#3aa5fc"
                label: "Personal Account"
                fontPixelSize: 15
            }
            FlatButton{
                width: 200
                height: 250
                textColor: "#ffffff"
                backgoundColor: "#3aa5fc"
                label: "Anonymous Account"
                fontPixelSize: 15
            }
            FlatButton{
                width: 200
                height: 250
                textColor: "#ffffff"
                backgoundColor: "#3aa5fc"
                label: "Organisation Account"
                fontPixelSize: 15
            }
        }
    }

    TextButton{
        anchors.left: parent.left
        anchors.top: parent.top
        anchors.topMargin: 20
        anchors.leftMargin: 20
        fontPixelSize: 15
        textContent: "Back"
        textColor: "#757575"
        onClicked: stack.pop()
    }
}
