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
            spacing: 50


            Button{
                width: 25
                height: 25
                flat: true
                background: Image{
                    anchors.fill: parent
                    source: isLiked ? "../../img/like.png" : "../../img/unlike.png"
                }

                Text{
                    anchors.left: parent.right
                    leftPadding: 10
                    text: likes
                }

                onClicked: {
                    if(isLiked)
                        likes -= 1
                    else
                        likes += 1

                    isLiked = !isLiked

                    backend.likeTweet(ownerId, id, isLiked);
                }
            }



            Text{
                text: date
                color: "#d1d1d1"
                font.pixelSize: 15
            }
        }
    }
}
