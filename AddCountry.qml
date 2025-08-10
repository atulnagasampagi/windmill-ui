import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15
import QtQuick.Dialogs 1.3
import "./CustomComponents"

Rectangle{
    id:_optionsrect
    color: "transparent"

    RowLayout{
        anchors.fill: parent
        Rectangle{
            id: _leftrect
            Layout.fillHeight: true
            Layout.fillWidth: true
            color: "transparent"
            ColumnLayout{
                anchors.fill: parent
                CustomLabel{
                    mytext: "Available Countries"
                }
                Rectangle{
                    Layout.fillHeight: true
                    Layout.fillWidth: true
                    color: "transparent"
                    ListView{
                        id:_clist
                        height: parent.height/1.2
                        width: parent.width/1.2
                        clip: true
                        model: proxyModel.mycountryViewModel
                        anchors.top: parent.top
                        anchors.horizontalCenter: parent.horizontalCenter

                        delegate: Rectangle{
                            id:_lvrect
                            height: _clist.height/10
                            width: _clist.width
                            color: "#DCD7C9"
                            border.color: "#2C3639"
                            radius: 10

                            Label {
                                text: CName
                                font.pixelSize: _lvrect.height/2
                                font.family: "Arial"
                                color: "#2C3639"
                                anchors.verticalCenter: parent.verticalCenter
                                anchors.left: parent.left
                                anchors.leftMargin: 5
                            }
                        }
                    }
                }
            }
        }
        Rectangle{
            Layout.fillHeight: true
            Layout.fillWidth: true
            color: "transparent"
            ColumnLayout{
                anchors.fill: parent
                CustomComboBox{
                    id: _countrySelector
                    myModel: proxyModel.mycountryViewModel
                    myDisplayText: "Select Country"
                }

                CustomButton{
                    myButtonName: "Submit"
                    onClicked: {
                        console.log("Submit Button Clicked")
                        proxyModel.addCountryToConfig(_countrySelector.selectedOption)
                    }
                }
            }
        }
    }
}
