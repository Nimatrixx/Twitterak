import QtQuick
import QtQuick.Controls

Button {
    property int fontPixelSize: 0
    property color backgoundColor: "#2f7fff"
    property string label: "button"
    property color textColor: "#ffffff"
    property int fontWeight: Font.Bold
    property int backgroundRadius: 0

    background: Rectangle {
        id: button_background
        width: parent.width; height: parent.height
        color: pressed ? Qt.darker(backgoundColor,1.2) : backgoundColor
        radius: backgroundRadius
        Text{
            id: innerText
            anchors.centerIn: parent
            color: textColor
            text: label
            font.weight: fontWeight
            font.pixelSize: fontPixelSize
        }
    }
}
