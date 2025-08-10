import QtQuick 2.15

PropertyAnimation {
    property double myfrom
    property double myto
    property var mytarget

    target: mytarget
    property: "scale"
    from: myfrom
    to: myto
    duration: 200
    easing.type: Easing.InOutQuad
}
