import QtQuick
import QtQuick.Controls

Button{
    property color textColor: "#1d9bf0"
    property string label: "Text Button"
    property int fontPixelSize: 10
    property int fontWeight: Font.Bold
    width: innerText.contentWidth
    height: innerText.contentHeight
    background: Text{
        id: innerText
        text: label
        color: parent.pressed ? Qt.darker(textColor,1.2) : textColor
        font.weight: fontWeight
        font.pixelSize: fontPixelSize
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter

    }
}
