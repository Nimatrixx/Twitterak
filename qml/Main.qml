import QtQuick
import QtQuick.Window
import QtQuick.Controls
import "pages" as Pages

Window {
    width: 800
    height: 600
    visible: true
    title: qsTr("Twitterak")
    color: "#ffffff"

    StackView{
        id: stack
        initialItem: loginPage
        anchors.fill:parent
    }

    Pages.LoginPage{
        id:loginPage
    }

}
