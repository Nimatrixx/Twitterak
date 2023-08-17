import QtQuick
import QtQuick.Controls

Rectangle{
    width: parent.width
    height: column.height + 50
    color: "#ffffff"
    radius: 15
    Column{
        id: column
        width: parent.width - 50
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenter: parent.verticalCenter
        spacing: 10

        Row{
            spacing: 10
            Image{
                width: 40
                height: 40
                source: profilePicture
            }

            Text{
               text: name
               font.pixelSize: 17
               anchors.verticalCenter: parent.verticalCenter
            }
        }

        Text{
            id: tweetText
            width: parent.width
            font.pixelSize: 17
            text: txt
        }

        Rectangle{
            width: parent.width
            anchors.horizontalCenter: parent.horizontalCenter
            height: 1
            color: "#cccccc"

        }

        Row{
            Button{
                width: 30
                height: 30
                flat: true
                background: Image{
                    anchors.fill: parent
                    source: "../../img/like.png"
                }
            }

            Text{
                text: "123"
            }
        }
    }
}
