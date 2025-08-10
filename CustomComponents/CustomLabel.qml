import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15
Rectangle{
    property var mytext
    Layout.preferredHeight: _optionsrect.height/5
    Layout.preferredWidth: _leftrect.width
    color: "transparent"
    Layout.alignment: Qt.AlignTop
    Label{
        text: mytext
        font.pixelSize: 20
        font.family: "Arial"
        font.bold: true
        color: "white"
        anchors.centerIn: parent
    }
}
