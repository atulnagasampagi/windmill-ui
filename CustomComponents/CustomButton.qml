import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

Button{
    property string myButtonName
    Layout.preferredHeight: parent.height/12
    Layout.preferredWidth: parent.width/2.3
    Layout.alignment: Qt.AlignCenter
    background: Rectangle{
        id:_buttonrect
        anchors.fill: parent
        radius: 6
        color: "#DCD7C9"

//        MouseArea{
//            anchors.fill: parent
//            hoverEnabled: true

//            onEntered: {
//                _buttonrect.color = "#A27B5C"
//            }

//            onExited: {
//                _buttonrect.color = "#DCD7C9"
//            }
//        }
    }
    contentItem: Label{
        id: _myLabel
        color: "#2C3639"
        text: myButtonName
        font.pixelSize: 15
        font.family: "Arial"
        anchors.centerIn: _buttonrect
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
    }
}
