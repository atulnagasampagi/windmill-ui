import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

Rectangle{
    property var currentTime: new Date()

    Timer {
        interval: 1000
        running: true
        repeat: true
        onTriggered: {
            currentTime = new Date()
        }
    }

    Text {
        id: currentTimeText
        text: getTimeString(currentTime)
        anchors.centerIn: parent
        font.pixelSize: 20
        color: "white"
    }

    function getTimeString(dateTime) {
        var hours = dateTime.getHours().toString().padStart(2, '0');
        var minutes = dateTime.getMinutes().toString().padStart(2, '0');
        var seconds = dateTime.getSeconds().toString().padStart(2, '0');
        return hours + ":" + minutes + ":" + seconds;
    }
}
