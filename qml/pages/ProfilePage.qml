import QtQuick
import QtQuick.Controls
import "../components"

Item {
    Rectangle{
        anchors.fill: parent
        color: "#e8ecef"

        Component.onCompleted: {
            backend.loadTweets(tweetsModel, backend.get_temp_id());
        }


        Rectangle{
            anchors.top: parent.top
            height: 60
            width: parent.width
            color: "#ffffff"
            border.color: "#aeaeae"

            Text{
                width: 250
                height: 30
                anchors.centerIn: parent
                color: "#000000"
                text: backend.get_temp_username()
                font.pixelSize: 25
                horizontalAlignment: Text.AlignHCenter
            }

            Button{
                width: 50
                height: 50
                anchors.verticalCenter: parent.verticalCenter
                background: Image{
                    width: 40
                    height: 40
                    anchors.centerIn: parent
                    source: "../../img/arrow_icon.png"
                }
                onClicked: stack.pop();
            }
        }

        ScrollView{
            y: 60
            width: parent.width
            height: parent.height - 60
            contentHeight: column.height + 50
            clip: true

            ScrollBar.vertical.policy: ScrollBar.AlwaysOn

            Rectangle{
                width: parent.width - 50
                height: column.height - tweetsList.height - spacer.height
                anchors.horizontalCenter: parent.horizontalCenter
                radius: 10

                Column{
                    id: column
                    width: parent.width
                    padding: 20
                    Rectangle{
                        height: 150
                        width: parent.width - 40
                        anchors.horizontalCenter: parent.horizontalCenter
                        color: backend.get_temp_header()
                        radius: 10

                        Image{
                            width: 140
                            height: 140
                            anchors.left: parent.left
                            anchors.top: parent.top
                            anchors.leftMargin: 20
                            anchors.topMargin: 70
                            source: backend.get_temp_profilePicture()
                        }

                        FlatButton{
                            property bool isFollowed: backend.isFollowed(backend.get_temp_id())

                            width: 120
                            height: 40
                            anchors.right: parent.right
                            anchors.top: parent.top
                            anchors.rightMargin: 20
                            anchors.topMargin: 160
                            backgroundRadius: 20
                            backgoundColor: isFollowed ? "#2f7fff" : "transparent"
                            borderWidth: isFollowed ? 0 : 2
                            label: isFollowed ? "Unfollow" : "Follow"
                            textColor: isFollowed ? "#ffffff" : "#2f7fff"
                            onClicked: {
                                if(isFollowed)
                                   backend.unfollow(backend.get_temp_id());
                                else
                                    backend.follow(backend.get_temp_id());

                                isFollowed = !isFollowed

                            }
                        }
                    }

                    Text{
                        text: backend.get_temp_name()
                        font.pixelSize: 20
                        topPadding: 80
                    }

                    Text{
                        text: "@" + backend.get_temp_username()
                        font.pixelSize: 15
                        topPadding: 10
                        color: "#626262"
                    }

                    Text{
                        text: backend.get_temp_bio()
                        font.pixelSize: 17
                        topPadding: 15
                    }

                    Text{
                        text: backend.get_temp_country()
                        font.pixelSize: 17
                        topPadding: 10
                        color: "#4a4a4a"
                    }

                    Text{
                        text: backend.get_temp_link()
                        font.pixelSize: 17
                        topPadding: 5
                        color: "#4c9ded"
                    }

                    Row{
                        bottomPadding: 30
                        Text{
                            text: backend.get_temp_followers()
                            topPadding: 20
                            font.pixelSize: 15
                            color: "#000000"
                        }
                        Text{
                            text: qsTr(" followers")
                            topPadding: 20
                            font.pixelSize: 15
                            color: "#3a3a3a"
                        }
                        Text{
                            text: backend.get_temp_followings()
                            topPadding: 20
                            font.pixelSize: 15
                            color: "#000000"
                        }
                        Text{
                            text: qsTr(" followings")
                            topPadding: 20
                            font.pixelSize: 15
                            color: "#3a3a3a"
                        }
                    }

                    Rectangle{
                        id: spacer
                        width: parent.width
                        height: 50
                        color: "transparent"
                    }



                    ListModel{
                        id: tweetsModel
                        function addElement(value: string){
                            append({txt: value, name: backend.get_temp_name(), profilePicture: backend.get_temp_profilePicture()});
                        }
                    }

                    ListView{
                        id: tweetsList
                        width: parent.width
                        height: contentHeight
                        orientation: ListView.Vertical
                        anchors.horizontalCenter: parent.horizontalCenter
                        spacing: 20
                        model: tweetsModel
                        delegate: TweetCard{

                        }
                    }

                }
            }
        }
   }

}
