import QtQuick
import QtQuick.Controls


TextField {
    property bool error: false
    property string fillColor: "#ffffff"
    width: 220
    height: 40
    color: "#000000"
    placeholderTextColor: "#7f1c1c1c"
    background: Rectangle{
        id: background
        width: parent.width
        height: parent.height
        color: fillColor
        radius: 5
        border.color: "#b5b5b5"
        border.width: 1
    }
    placeholderText: "hint"

    onErrorChanged: {
        setBorder()
    }

    onFocusChanged: {
        setBorder()
    }

    function setBorder(){
        if(error){
            background.border.color = "#ff0000"
            background.border.width = 2
        }
        else
        {
            if(focus){
                background.border.color = "#2f7fff"
                background.border.width = 2
            }else{
                background.border.color = "#b5b5b5"
                background.border.width = 1
            }
        }
    }
}
