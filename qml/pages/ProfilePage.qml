import QtQuick
import QtQuick.Controls
import "../components"

Item {
    Rectangle{
        width: parent.width
        height: parent.height
        color: "#e8ecef"


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
                text: "Profile"
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
                height: column.height
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
                        color: "#000000"

                        Image{
                            width: 140
                            height: 140
                            anchors.left: parent.left
                            anchors.top: parent.top
                            anchors.leftMargin: 20
                            anchors.topMargin: 70
                            source: "qrc:/qtquickplugin/images/template_image.png"
                        }

                        FlatButton{
                            width: 120
                            height: 40
                            anchors.right: parent.right
                            anchors.top: parent.top
                            anchors.rightMargin: 20
                            anchors.topMargin: 160
                            backgroundRadius: 20
                            label: "Follow"
                        }
                    }
                    
                    Text{
                        text: backend.get_temp_name()
                        font.pixelSize: 20
                        topPadding: 80
                    }

                    Text{
                        text: backend.get_temp_username()
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
                            text: qsTr("   " + backend.get_temp_followings().toString())
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
                }
            }
        }
   }

}
