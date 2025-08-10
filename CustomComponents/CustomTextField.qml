import QtQuick 2.15
import QtQuick.Layouts 1.15
import QtQuick.Controls 2.15


TextField{
    property string myplaceholder
    Layout.preferredWidth: parent.width/3
    Layout.alignment: Qt.AlignCenter
    background: Rectangle{
        height: 1
        Layout.fillWidth: true
        color: "white"
        anchors.bottom: parent.bottom
    }
    color: "white"
    placeholderText: myplaceholder
    placeholderTextColor: "white"
}
