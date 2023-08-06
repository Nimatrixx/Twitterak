import QtQuick
import QtQuick.Controls
import "../components"


Item{

    Rectangle {
        anchors.centerIn: parent
        anchors.horizontalCenterOffset: 130
        width: 350
        height: 500
        color: "#379bed"
        radius: 30

        Text{
            anchors.centerIn: parent
            anchors.horizontalCenterOffset: 45
            text: "it's what's happening"
            color: "#ffffff"
            font.weight: Font.Bold
            font.pixelSize: 20
        }
    }

    Rectangle {
        id: loginForm
        anchors.centerIn: parent
        anchors.horizontalCenterOffset: -130
        width: 350
        height: 500
        color: "#ededed"
        radius: 30

        Column{
            anchors.centerIn: parent
            spacing: 10

            Image {
                id: twitterIcon
                anchors.horizontalCenter: parent.horizontalCenter
                width: 128
                height: 128
                fillMode: Image.PreserveAspectFit
                source: "../../img/Logo_of_Twitter.svg"
            }

            Text {
                id: twitterText
                anchors.horizontalCenter: parent.horizontalCenter
                width: contentWidth
                height: contentHeight
                text: qsTr("Twitterak")
                font.bold: true
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                font.pixelSize: 40
            }

            CustomTextField{
                id: usernameField
                maximumLength: 18
                anchors.horizontalCenter: parent.horizontalCenter
                onTextChanged:text = text.replace(/\s+/g,'')
                placeholderText: "Username"
            }

            Text{
                id:username_warn
                visible: true
                color: "#ff0000"
                font.pointSize: 8
            }

            CustomTextField{
                id: passwordField
                maximumLength: 18
                echoMode: TextInput.Password
                anchors.horizontalCenter: parent.horizontalCenter
                onTextChanged:text = text.replace(/\s+/g,'')
                placeholderText: "Password"
            }

            Text{
                id: password_warn
                visible: true
                color: "#ff0000"
                font.pointSize: 8
            }

            FlatButton{
                id:login_button
                anchors.horizontalCenter: parent.horizontalCenter
                topPadding: 20
                width: 220
                height: 40
                label: "Login"
                backgroundRadius: 10
                onClicked:{
                    if(backend.loginBtn(usernameField, passwordField, username_warn, password_warn))
                    {
                        //open twitterak
                    }
                }
            }

            TextButton{
                textContent: "Don't have an account? Sign up here"
                fontPixelSize: 12
                onClicked: stack.push(signupPage)
            }
        }
    }
}


