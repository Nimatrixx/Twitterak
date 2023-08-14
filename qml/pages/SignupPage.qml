import QtQuick
import QtQuick.Controls
import "../components"

Item {
    // 0 : Anonymous   1 :‌ Personal   2 : Organ
    property int type

    StackView{
        id:signupStack
        anchors.fill: parent
        initialItem: account_type_page
        property int currentPage: 0
    }


    Component{
        id: account_type_page

        Rectangle{

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
                        textColor: "#000000"
                        backgoundColor: "#ededed"
                        label: "Anonymous Account"
                        fontPixelSize: 15
                        backgroundRadius: 10
                        onClicked: {
                            type = 0
                            signupStack.currentPage++
                            signupStack.push(username_password_page)
                        }
                    }
                    FlatButton{
                        width: 200
                        height: 250
                        textColor: "#000000"
                        backgoundColor: "#ededed"
                        label: "Personal Account"
                        fontPixelSize: 15
                        backgroundRadius: 10
                        onClicked: {
                            type = 1
                            signupStack.currentPage++
                            signupStack.push(username_password_page)
                        }

                    }
                    FlatButton{
                        width: 200
                        height: 250
                        textColor: "#000000"
                        backgoundColor: "#ededed"
                        label: "Organisation Account"
                        fontPixelSize: 15
                        backgroundRadius: 10
                        onClicked: {
                            type = 2
                            signupStack.currentPage++
                            signupStack.push(username_password_page)
                        }
                    }
                }
            }

        }
    }


    Component{
        id: username_password_page

        Item{

            Rectangle{
                anchors.centerIn: parent
                width: 350
                height: 500
                color: "#ededed"
                radius: 15

                Column{
                    id: column
                    anchors.centerIn: parent
                    spacing: 10


                    Text {
                        anchors.horizontalCenter: parent.horizontalCenter
                        width: contentWidth
                        height: 120
                        text: "Sign up"
                        font.bold: true
                        horizontalAlignment: Text.AlignHCenter
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
                        anchors.horizontalCenter: parent.horizontalCenter
                        topPadding: 20
                        width: 220
                        height: 40
                        label: "Next"
                        onClicked:{
                            if(backend.signUpFirstStep(type, usernameField, passwordField, username_warn, password_warn))
                            {
                                signupStack.push(final_signup_Page)
                                signupStack.currentPage++
                            }
                        }
                    }
                }
            }

        }
    }

    Component{
        id:final_signup_Page

        Item{
            Rectangle {
                anchors.centerIn: parent
                width: 600
                height: 500
                color: "#eeeeee"
                radius: 10

                Text{
                    text: {if(type == 0){ "Anonymous Account"; } else if(type == 1){ "Personal Account"; }else if(type == 2){ "Organisation Account"}}
                    font.pixelSize: 30
                    anchors.horizontalCenter: parent.horizontalCenter
                    padding: 10
                }

                Row{
                    x: 10
                    y: 70
                    padding: 20
                    spacing: 20
                    Column{
                        spacing: 10

                        Label {
                            anchors.horizontalCenter: parent.horizontalCenter
                            width: 220
                            height: 15
                            text: if(type==0) "Name"; else "Name *";
                            color: "#232323"
                        }

                        CustomTextField{
                            id: nameSignupField
                            anchors.horizontalCenter: parent.horizontalCenter
                            placeholderText: "Name"
                            validator: RegularExpressionValidator{
                                regularExpression: /^[a-zA-Z\s]*$/
                            }
                            maximumLength: 15
                            enabled: type== 0 ? false : true
                            text: type== 0 ? "Anonymous User" : ""
                        }

                        Label {
                            anchors.horizontalCenter: parent.horizontalCenter
                            width: 220
                            height: 15
                            text: if(type == 0) "Phone Number" ; else "Phone Number *"
                            color: "#232323"
                        }

                        CustomTextField{
                            id:phoneSignupField
                            anchors.horizontalCenter: parent.horizontalCenter
                            placeholderText: "Phone Number"
                            validator: RegularExpressionValidator{
                                regularExpression: /^\d+$/
                            }
                            maximumLength: 13
                        }


                       Label {
                           anchors.horizontalCenter: parent.horizontalCenter
                            width: 220
                            height: 15
                            text: qsTr("Country")
                            color: "#232323"
                        }

                        CustomTextField{
                            id:countrySignupField
                            anchors.horizontalCenter: parent.horizontalCenter
                            placeholderText: "Country"
                            validator: RegularExpressionValidator{
                                regularExpression: /^[a-zA-Z\s]*$/
                            }
                            maximumLength: 20
                        }

                        Label {
                            visible: type==2 ? false : true
                            anchors.horizontalCenter: parent.horizontalCenter
                            width: 220
                            height: 15
                            text: qsTr("Birth Date")
                            color: "#232323"
                        }

                        Row{
                            visible: type==2 ? false : true
                            spacing: 5
                            CustomTextField{
                                id:birthYearSignupField
                                width: 70
                                placeholderText: "Year"
                                validator: RegularExpressionValidator{
                                    regularExpression: /^\d+$/
                                }
                                maximumLength: 4
                            }

                            CustomTextField{
                                id:birthMonthSignupField
                                width: 70
                                placeholderText: "Month"
                                validator: RegularExpressionValidator{
                                    regularExpression: /^\d+$/
                                }
                                maximumLength: 2
                            }

                            CustomTextField{
                                id:birthDaySignupField
                                width: 70
                                placeholderText: "Day"
                                validator: RegularExpressionValidator{
                                    regularExpression: /^\d+$/
                                }
                                maximumLength: 2
                            }
                        }
                    }

                    Column{
                        spacing:10

                        Label {
                            width: 220
                            height: 15
                            text: qsTr("Bio")
                            color: "#232323"
                        }

                        TextArea {
                            id: bioSignupField
                            width: 300
                            height: 115
                            color: "#000000"
                            verticalAlignment: Text.AlignTop
                            hoverEnabled: true
                            placeholderTextColor: "#7f1c1c1c"
                            background: Rectangle{
                                width: 300
                                height: 120
                                color: "#ffffff"
                                radius: 5
                                border.width: 1
                                border.color: "#b5b5b5"
                            }
                            placeholderText: "Bio"

                            property int max :{ type== 2 ? 1100 : 160;}

                            onTextChanged: {

                                if (length > max) remove(max, length);

                                var pos = positionAt(1, 109);
                                if(length >= pos)
                                {
                                    remove(pos, length);
                                }
                            }
                        }

                        Label {
                            width: 220
                            height: 15
                            text: qsTr("Link")
                            color: "#232323"
                        }

                        CustomTextField{
                            id: linkSignupField
                            width: 300
                            height: 40
                            placeholderText: "Link"
                            onTextChanged:text = text.replace(/\s+/g,'')
                        }

                        Label {
                            width: 220
                            height: 15
                            text: if(type == 1) "office (username)"; else  "CEO (username)"
                            color: "#232323"
                            visible: type == 0 ? false : true
                        }

                        CustomTextField{
                            id: customField
                            width: 220
                            height: 40
                            placeholderText: if(type == 1) "office"; else  "CEO"
                            onTextChanged:text = text.replace(/\s+/g,'')
                            visible: type == 0 ? false : true
                        }
                    }
                }

                Label {
                    id: warnLabel
                    anchors.horizontalCenter: parent.horizontalCenter
                    anchors.bottom: parent.bottom
                    anchors.bottomMargin: 85
                    width: 220
                    height: 15
                    font.pixelSize: 12
                    horizontalAlignment: Text.AlignHCenter
                    color: "#ff0000"
                    visible: false
                }



                FlatButton{
                    id: signupButton
                    anchors.horizontalCenter: parent.horizontalCenter
                    anchors.bottom: parent.bottom
                    anchors.bottomMargin: 30
                    width: 220
                    height: 40
                    backgroundRadius: 10
                    label: "Sign up"
                    backgoundColor: "#ffffff"
                    textColor: "#379bed"
                    onClicked: {
                        if(type == 0 || (nameSignupField.text !== "" && phoneSignupField.text !== "")){
                            warnLabel.visible = false
                            nameSignupField.error = false
                            phoneSignupField.error = false

                            if(backend.saveUser(
                                type,
                                nameSignupField,
                                phoneSignupField,
                                countrySignupField,
                                birthYearSignupField,
                                birthMonthSignupField,
                                birthDaySignupField,
                                bioSignupField,
                                linkSignupField,
                                customField,
                                warnLabel
                            ))
                            {
                                //open twitterak
                                stack.pop()
                                stack.push(mainPage)
                            }
                        }
                        else
                        {
                            warnLabel.text = "* Name and Phone number are essential"
                            warnLabel.visible = true
                            if(nameSignupField.text === ""){
                                nameSignupField.error = true
                            }
                            if(phoneSignupField.text === ""){
                                phoneSignupField.error = true
                            }
                        }
                    }
                }
            }
        }
    }


    TextButton{
        anchors.left: parent.left
        anchors.top: parent.top
        anchors.topMargin: 20
        anchors.leftMargin: 20
        fontPixelSize: 15
        label: "Back"
        textColor: "#757575"
        onClicked: if(signupStack.currentPage == 0) stack.pop(); else {signupStack.currentPage--; signupStack.pop();}
    }
}
