import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15
import QtQuick.Dialogs 1.3
import "./CustomComponents"

Rectangle{
    id:_optionsrect

    property string countryName: ""
    property string siteName: ""
    color: "transparent"
    signal sendRemoveSite(var countryname,var sitename)

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
                    mytext: "Select Site"
                }

                //Specific Site List View
                Rectangle{
                    Layout.fillHeight: true
                    Layout.fillWidth: true
                    color: "transparent"
                    ListView{
                        id:_clist
                        height: parent.height/1.2
                        width: parent.width/1.2
                        clip: true
                        model: proxyModel.mysiteViewModel
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
                                id: _siteName
                                text: PowerPlants
                                font.pixelSize: _lvrect.height/2
                                font.family: "Arial"
                                color: "#2C3639"
                                anchors.verticalCenter: parent.verticalCenter
                                anchors.left: parent.left
                                anchors.leftMargin: 5
                            }
                            MouseArea{
                                anchors.fill: parent
                                hoverEnabled: true

                                onEntered: {
                                    _lvrect.color = "#A27B5C"
                                }
                                onExited: {
                                    _lvrect.color = "#DCD7C9"
                                }

                                onClicked: {
                                    siteName = model.PowerPlants
                                }
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
                Rectangle{
                    Layout.fillHeight: true
                    Layout.fillWidth: true
                    color: "transparent"
                    CustomComboBox{
                        id: _combo
                        myModel: proxyModel.mycountryViewModel
                        myDisplayText: "Select Country"
                        anchors.centerIn: parent

                        onSendCountryName: {
                            proxyModel.setSiteManager(country)
                        }
                    }
                }
                Rectangle{
                    Layout.fillHeight: true
                    Layout.fillWidth: true
                    color: "transparent"
                    CustomButton{
                        myButtonName: "Remove"
                        anchors.centerIn: parent
                        onClicked: {
                            countryName = _combo.selectedOption
                            sendRemoveSite(countryName,siteName)
                        }
                    }
                }
            }
        }
    }
}
