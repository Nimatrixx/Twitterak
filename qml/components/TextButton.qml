import QtQuick
import QtQuick.Controls

Button{
    property color textColor: "#1d9bf0"
    property string textContent: "Text Button"
    property int fontPixelSize: 10
    anchors.horizontalCenter: parent.horizontalCenter
    width: innerText.contentWidth
    height: innerText.contentHeight
    background: Text{
        id: innerText
        text: textContent
        color: parent.pressed ? Qt.darker(textColor,1.2) : textColor
        font.pixelSize: fontPixelSize
    }
}
