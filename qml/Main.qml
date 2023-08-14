import QtQuick
import QtQuick.Window
import QtQuick.Controls
import "pages" as Pages
import Backend

Window {
    width: 800
    height: 601
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

    Component{
        id:loginPage
        Pages.LoginPage{
        }
    }

    Component{
        id:signupPage
        Pages.SignupPage{

        }
    }

    Component{
        id:mainPage
        Pages.MainPage{

        }
    }

    Component{
        id:profilePage
        Pages.ProfilePage{

        }
    }
}
