import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Controls.Styles 1.4
import QtQuick.Layouts 1.15

ComboBox {
    id: _customComboBox
    property string selectedOption
    property string myDisplayText
    property var myRow
    property var myModel
    signal sendTableRow(var myval)
    signal sendCountryName(var country)

    model: myModel
    displayText: myDisplayText
    Layout.alignment: Qt.AlignCenter


    delegate: Rectangle{
        id: _rect
        height: 35
        width: parent.width
        radius: 6
        color: "#DCD7C9"
        border.color: "#2C3639"
        Label{
            id: _text
            text:myModel===proxyModel.mycountryViewModel?CName:PowerPlants
            font.pixelSize: 15
            font.family: "Arial"
            color: "#2C3639"
        }
        MouseArea{
            anchors.fill: parent
            hoverEnabled: true
            onEntered: {
                _rect.color = "#A27B5C"
                _text.color = "#2C3639"
            }
            onExited: {
                _rect.color = "#DCD7C9"
                _text.color = "#2C3639"
            }
            onClicked: {
                currentIndex = index
                selectedOption = _text.text
                sendCountryName(selectedOption)
                _customComboBox.popup.visible = false
                _customComboBox.displayText = selectedOption
            }
        }
    }


    background: Rectangle {
        implicitWidth: 150
        implicitHeight: 40
        radius: 3
        color: "#DCD7C9"
    }

    onCurrentIndexChanged: {
        var currentItem = delegateModel.items.get(currentIndex)
        sendTableRow(currentIndex)
    }
}
