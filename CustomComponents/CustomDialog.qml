import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Dialogs 1.3

Dialog{
    property string myTitle
    property string myText

    title: myTitle
    Label{
        text: myText
        color: "black"
    }

    standardButtons: Dialog.Ok
}
