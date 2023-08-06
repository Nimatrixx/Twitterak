import QtQuick
import QtQuick.Window
import QtQuick.Controls
import "pages" as Pages
import Backend

Window {
    width: 800
    height: 600
    visible: true
    title: qsTr("Twitterak")
    color: "#ffffff"

    Backend{
        id:backend
    }

    StackView{
        id: stack
        initialItem: loginPage
        anchors.fill:parent
    }

    Pages.LoginPage{
        id:loginPage
    }
}
