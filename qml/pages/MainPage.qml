import QtQuick
import QtQuick.Controls
import QtQuick.Window
import "../components"
Item {
    property int type: backend.getType()

    StackView{
        id:mainStack
        initialItem: main
        anchors.fill: parent
    }

    Component{
        id: main
        Rectangle{
            width: parent.width
            height: parent.height
            color: "#e8ecef"

            Rectangle{
                anchors.top: parent.top
                height: 50
                width: parent.width
                color: "#ffffff"

                TextField{
                    width: 250
                    height: 30
                    anchors.centerIn: parent
                    color: "#000000"
                    placeholderText: "Search"
                    placeholderTextColor: "#a2a2a2"
                    background: Rectangle{
                        id: background
                        width: parent.width * 7/6
                        height: parent.height
                        anchors.centerIn: parent
                        color: "#e4eef3"
                        radius: 20
                        border.width: 1
                        border.color: "#b5b8ba"
                    }

                    onTextChanged:text = text.replace(/\s+/g,'')

                    onEditingFinished: {
                        if(text.length > 0)
                        {
                            if(text === backend.get_username())
                            {
                                mainStack.push(myProfile)
                            }
                            else if(backend.searchUser(text.toString()))
                            {
                                stack.push(profilePage)
                            }
                        }
                    }
                }

                Button{
                    width: 150
                    height: 40
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.right: parent.right
                    anchors.rightMargin: 20

                    background: Rectangle{
                        anchors.fill: parent
                        Image{
                            id:profilePic
                            anchors.right: parent.right
                            anchors.verticalCenter: parent.verticalCenter
                            source: backend.get_profilePicture()
                            width: 30
                            height: 30
                        }
                        Text{
                            text: backend.get_username();
                            anchors.right: parent.right
                            anchors.verticalCenter: parent.verticalCenter
                            anchors.rightMargin: 40
                        }
                    }

                    onClicked: {
                        mainStack.push(myProfile);
                    }
                }
            }
        }
    }

    Component{
        id: myProfile

        Rectangle{
            anchors.fill: parent
            color: "#e8ecef"

            Component.onCompleted: {
                backend.loadTweets(tweetsModel, backend.get_id());
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
                    text: backend.get_username()
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
                    onClicked: mainStack.pop();
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
                            color: backend.get_header()
                            radius: 10

                            Image{
                                width: 140
                                height: 140
                                anchors.left: parent.left
                                anchors.top: parent.top
                                anchors.leftMargin: 20
                                anchors.topMargin: 70
                                source: backend.get_profilePicture()
                            }

                            FlatButton{
                                width: 120
                                height: 40
                                anchors.right: parent.right
                                anchors.top: parent.top
                                anchors.rightMargin: 20
                                anchors.topMargin: 160
                                backgroundRadius: 20
                                label: "Edit"
                                onClicked: mainStack.push(editPage)
                            }

                            FlatButton{
                                width: 120
                                height: 40
                                anchors.right: parent.right
                                anchors.top: parent.top
                                anchors.rightMargin: 150
                                anchors.topMargin: 160
                                backgroundRadius: 20
                                backgoundColor: "red"
                                label: "Logout"
                                onClicked: {

                                    backend.logout();
                                    //close profile page
                                    mainStack.pop();
                                    //close main page
                                    stack.pop();
                                    //close login page and open it again
                                    stack.pop();
                                    stack.push(loginPage)
                                }
                            }
                        }

                        Text{
                            text: backend.get_name()
                            font.pixelSize: 20
                            topPadding: 80
                        }

                        Text{
                            text: "@" + backend.get_username()
                            font.pixelSize: 15
                            topPadding: 10
                            color: "#626262"
                        }

                        Text{
                            text: backend.get_bio()
                            font.pixelSize: 17
                            topPadding: 15
                        }

                        Text{
                            text: backend.get_country()
                            font.pixelSize: 17
                            topPadding: 10
                            color: "#4a4a4a"
                        }

                        Text{
                            text: backend.get_link()
                            font.pixelSize: 17
                            topPadding: 5
                            color: "#4c9ded"
                        }

                        Row{
                            bottomPadding: 30
                            Text{
                                text: backend.get_followers()
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
                                text: qsTr("   " + backend.get_followings().toString())
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
                            width: parent.width
                            height: newTweetColumn.height
                            anchors.horizontalCenter: parent.horizontalCenter
                            color: "#ffffff"
                            radius: 15
                            Column{
                                id: newTweetColumn
                                width: parent.width - 50
                                anchors.horizontalCenter: parent.horizontalCenter
                                anchors.verticalCenter: parent.verticalCenter
                                spacing: 10

                                Row{
                                    id: row
                                    spacing: 10
                                    Image{
                                        width: 40
                                        height: 40
                                        source: backend.get_profilePicture()
                                    }

                                    Text{
                                       text: backend.get_name()
                                       font.pixelSize: 17
                                       anchors.verticalCenter: parent.verticalCenter
                                    }
                                }

                                Rectangle{
                                    width: parent.width
                                    height: textInput.height + 20
                                    anchors.horizontalCenter: parent.horizontalCenter
                                    color: "#eeeeee"
                                    radius: 5
                                    border.width: 1
                                    border.color: "#dddddd"

                                    TextEdit {
                                        id: textInput;
                                        width: parent.width - 10
                                        anchors.centerIn: parent
                                        selectByMouse: true
                                        font.pixelSize: 17
                                        wrapMode: TextEdit.WrapAtWordBoundaryOrAnywhere;
                                        color: "black";
                                    }
                                }

                                FlatButton{
                                    width: 70
                                    height: 40
                                    label: "Tweet"
                                    anchors.right: parent.right

                                    onClicked: {
                                        backend.tweet(textInput);
                                        mainStack.pop()

                                    }
                                }
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
                                append({txt: value, name: backend.get_name(), profilePicture: backend.get_profilePicture()});
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

    Component{
        id: editPage
        Item{
            anchors.centerIn: parent
            Rectangle {
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.verticalCenter: parent.verticalCenter
                width: 600
                height: 570
                color: "#00ffffff"
                radius: 10

                Row{
                    x: 10
                    y: 20
                    padding: 20
                    spacing: 20
                    Column{
                        spacing: 10

                        Label {
                            anchors.horizontalCenter: parent.horizontalCenter
                            width: 220
                            height: 15
                            text: "Profile Picture"
                            color: "#232323"
                        }

                        ListView{
                            property string currentProfile: backend.get_profilePicture()
                            id: profileList
                            width: 220
                            height: 30

                            currentIndex: -1
                            highlightRangeMode: ListView.ApplyRange
                            orientation: ListView.Horizontal
                            interactive: false
                            highlight: Rectangle{ color: "#99878b93"; radius: 10 }

                            model: ListModel{
                                ListElement{ imgSource: "../../img/avatar1.png"}
                                ListElement{ imgSource: "../../img/avatar2.png"}
                                ListElement{ imgSource: "../../img/avatar3.png"}
                                ListElement{ imgSource: "../../img/avatar4.png"}
                                ListElement{ imgSource: "../../img/avatar5.png"}
                                ListElement{ imgSource: "../../img/avatar6.png"}
                            }

                            delegate: Rectangle{
                                width: 35
                                height: 35
                                color: "#00000000"
                                Image{
                                    anchors.centerIn: parent
                                    width: 30
                                    height: 30
                                    source: imgSource
                                }

                                MouseArea {
                                    anchors.fill: parent
                                    onClicked: {profileList.currentIndex = index; profileList.currentProfile = model.imgSource;}
                                }
                            }
                        }

                        Label {
                            anchors.horizontalCenter: parent.horizontalCenter
                            width: 220
                            height: 15
                            text: "Username *"
                            color: "#232323"
                        }

                        CustomTextField{
                            id: usernameField
                            maximumLength: 18
                            anchors.horizontalCenter: parent.horizontalCenter
                            onTextChanged:text = text.replace(/\s+/g,'')
                            placeholderText: "Username"
                            text: backend.get_username()
                        }

                        Text{
                            id:username_warn
                            visible: true
                            color: "#ff0000"
                            font.pointSize: 8
                        }

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
                            text: type== 0 ? "Anonymous User" : backend.get_name()
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
                            text: backend.get_phoneNumber()
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
                            text: backend.get_country()
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
                                text: backend.get_yearOfBirth() !== 0 ? backend.get_yearOfBirth() : ""
                            }

                            CustomTextField{
                                id:birthMonthSignupField
                                width: 70
                                placeholderText: "Month"
                                validator: RegularExpressionValidator{
                                    regularExpression: /^\d+$/
                                }
                                maximumLength: 2
                                text: backend.get_monthOfBirth() !== 0 ? backend.get_monthOfBirth()  : ""
                            }

                            CustomTextField{
                                id:birthDaySignupField
                                width: 70
                                placeholderText: "Day"
                                validator: RegularExpressionValidator{
                                    regularExpression: /^\d+$/
                                }
                                maximumLength: 2
                                text: backend.get_dayOfBirth() !== 0 ? backend.get_dayOfBirth() : ""
                            }
                        }
                    }

                    Column{
                        spacing:10

                        Label {
                            width: 220
                            height: 15
                            text: "Header Color"
                            color: "#232323"
                        }

                        ListView{
                            property string currentHeader: backend.get_header()
                            id: headerList
                            width: 220
                            height: 30

                            currentIndex: -1
                            highlightRangeMode: ListView.ApplyRange
                            orientation: ListView.Horizontal
                            interactive: false
                            highlight: Rectangle{ color: "#99878b93"; radius: 10 }

                            model: ListModel{
                                ListElement{ bgcolor: "lightblue"}
                                ListElement{ bgcolor: "lightgreen"}
                                ListElement{ bgcolor: "green"}
                                ListElement{ bgcolor: "purple"}
                                ListElement{ bgcolor: "red"}
                                ListElement{ bgcolor: "pink"}
                            }

                            delegate: Rectangle{
                                width: 40
                                height: 40
                                color: "#00000000"
                                Rectangle{
                                    anchors.centerIn: parent
                                    width: 30
                                    height: 30
                                    radius: 10
                                    color: bgcolor
                                }

                                MouseArea {
                                    anchors.fill: parent
                                    onClicked: {headerList.currentIndex = index; headerList.currentHeader = model.bgcolor;}
                                }
                            }
                        }

                        Label {
                            width: 220
                            height: 15
                            text: "Password *"
                            color: "#232323"
                        }

                        CustomTextField{
                            id: passwordField
                            maximumLength: 18
                            echoMode: TextInput.Password
                            onTextChanged:text = text.replace(/\s+/g,'')
                            placeholderText: "Password"
                            text: backend.get_password()
                        }

                        Text{
                            id: password_warn
                            visible: true
                            color: "#ff0000"
                            font.pointSize: 8
                        }

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
                            text: backend.get_bio()
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
                            text: backend.get_link()
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
                            text: if(type == 1) backend.get_office(); else  backend.get_ceo()
                        }
                    }
                }

                Label {
                    id: warnLabel
                    anchors.horizontalCenter: parent.horizontalCenter
                    anchors.bottom: parent.bottom
                    anchors.bottomMargin: 65
                    width: 220
                    height: 15
                    font.pixelSize: 12
                    horizontalAlignment: Text.AlignHCenter
                    color: "#ff0000"
                    visible: false
                }



                FlatButton{
                    id: saveButton
                    anchors.horizontalCenter: parent.horizontalCenter
                    anchors.bottom: parent.bottom
                    anchors.bottomMargin: 20
                    width: 220
                    height: 40
                    backgroundRadius: 10
                    label: "Save"
                    backgoundColor: "#ececec"
                    textColor: "#379bed"
                    onClicked: {
                        if(type == 0 || (nameSignupField.text !== "" && phoneSignupField.text !== "")){
                            warnLabel.visible = false
                            nameSignupField.error = false
                            phoneSignupField.error = false

                            if(backend.setMainInfo(type, usernameField, passwordField, username_warn, password_warn))
                            {
                                backend.updateUserKey()

                                if(backend.setSecondaryInfo(
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
                                    warnLabel,
                                    profileList.currentProfile.toString(),
                                    headerList.currentHeader.toString()
                                ))
                                {
                                    //save user info
                                    backend.saveUserInfo(0);
                                    //close edit page
                                    mainStack.pop()
                                    //close profile page
                                    mainStack.pop()
                                    //restart main page
                                    mainStack.pop()
                                    mainStack.push(mainPage)
                                }
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

                TextButton{
                    anchors.horizontalCenter: parent.horizontalCenter
                    anchors.horizontalCenterOffset: -150
                    anchors.bottom: parent.bottom
                    anchors.bottomMargin: 30
                    label: "cancel"
                    fontPixelSize: 12
                    onClicked: mainStack.pop()
                }
            }
        }
    }
}
