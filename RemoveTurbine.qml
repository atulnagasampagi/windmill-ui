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
                        model: proxyModel.turbineListModel
                        anchors.top: parent.top
                        anchors.horizontalCenter: parent.horizontalCenter

                        delegate: Rectangle{
                            id:_lvrect
                            height: _clist.height/10
                            width: _clist.width
                            color: "#0F1035"
                            border.color: "white"
                            radius: 10

                            Label {
                                id: _siteName
                                text: Turbine
                                font.pixelSize: _lvrect.height/2
                                font.family: "Arial"
                                color: "white"
                                anchors.verticalCenter: parent.verticalCenter
                                anchors.left: parent.left
                                anchors.leftMargin: 5
                            }
                            MouseArea{
                                anchors.fill: parent
                                hoverEnabled: true

                                onEntered: {
                                    _lvrect.color = "white"
                                    _siteName.color = "#0F1035"
                                }
                                onExited: {
                                    _lvrect.color = "#0F1035"
                                    _siteName.color = "white"
                                }

                                onClicked: {
                                    _lvrect.color = "white"
                                    _siteName.color = "#0F1035"
                                    siteName = model.Turbine
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
                        id: _countrySelector
                        myModel: proxyModel.myCountryViewModel
                        myDisplayText: "Select Country"
                        anchors.centerIn: parent
                    }
                }
                Rectangle{
                    Layout.fillHeight: true
                    Layout.fillWidth: true
                    color: "transparent"
                    CustomComboBox{
                        id: _siteSelector
                        myModel: proxyModel.mySiteViewModel
                        myDisplayText: "Select Site"
                        anchors.centerIn: parent
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
                            countryName = _combo.selectedCountryName
                        }
                    }
                }
            }
        }
    }
}
