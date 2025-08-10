import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15
import QtQuick.Dialogs 1.3
import "./CustomComponents"

Rectangle{
    id:_optionsrect
    property string selectedCountry
    color: "transparent"

    ColumnLayout{
        anchors.fill: parent
        Rectangle{
            Layout.preferredHeight: _optionsrect.height/6
            Layout.fillWidth: true
            color: "transparent"
            CustomLabel{
                mytext: "Select Country"
                anchors.centerIn: parent
            }
        }
        Rectangle{
            id: _leftrect
            Layout.preferredHeight: _optionsrect.height/1.5
            Layout.fillWidth: true
            color: "transparent"
            ListView{
                id:_cremovelist
                height: parent.height/1.2
                width: parent.width/1.2
                clip: true
                model: proxyModel.mycountryViewModel
                anchors.centerIn: parent

                delegate: Rectangle{
                    id:_removelvrect
                    height: _cremovelist.height/7
                    width: _cremovelist.width
                    color: "#DCD7C9"
                    border.color: "#2C3639"
                    radius: 10

                    Label {
                        id:_countryName
                        text: CName
                        font.pixelSize: _removelvrect.height/2
                        font.family: "Arial"
                        color: "#2C3639"
                        anchors.centerIn: parent
                    }

                    MouseArea{
                        anchors.fill: parent
                        hoverEnabled: true

                        onEntered: {
                            _removelvrect.color = "#A27B5C"
                        }
                        onExited: {
                            _removelvrect.color = "#DCD7C9"
                        }

                        onClicked: {
                            console.log("Country ", CName)
                            selectedCountry = CName
                        }
                    }
                }
            }
        }
        Rectangle{
            Layout.fillHeight: true
            Layout.fillWidth: true
            color: "transparent"

            CustomButton{
                id: _removebutton
                myButtonName: "Remove"
                anchors.centerIn: parent
                onClicked: {
                    console.log("Remove Button Clicked")
                    proxyModel.removeCountry(selectedCountry)
                }
            }
        }
    }
}
