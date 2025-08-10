import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15
import QtQuick.Dialogs 1.3
import "./CustomComponents"

Rectangle{
    id:_optionsrect

    signal sendSiteData(var countryname, var statename, var sitename, var sitelocation, var producer, var phno)
    color: "transparent"
    anchors.centerIn: parent

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
                    mytext: "Available Sites"
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
                                text: PowerPlants
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
                    myDisplayText: "Select Country"
                    myModel: proxyModel.mycountryViewModel

                    onSendCountryName: {
                        proxyModel.setSiteManager(country)
                    }
                }

                CustomTextField{
                    id:statename
                    myplaceholder: "Enter State"
                    validator: RegExpValidator {
                        regExp: /^[a-zA-Z\s]*$/
                    }
                }
                CustomTextField{
                    id:sname
                    myplaceholder: "Enter Site Name"
                    validator: RegExpValidator {
                        regExp: /^[a-zA-Z\s]*$/
                    }
                }
                CustomTextField{
                    id:slocation
                    myplaceholder: "Enter Location"
                    validator: RegExpValidator {
                        regExp: /^[a-zA-Z\s]*$/
                    }
                }

                CustomTextField{
                    id:snum
                    myplaceholder: "Enter Phone Number"
                    validator: RegExpValidator {
                        regExp: /^[0-9]*$/
                    }
                }
                CustomButton{
                    myButtonName: "Submit"
                    onClicked: {
                        console.log("Submit Button Clicked")
                        proxyModel.addSiteToConfig(_countrySelector.selectedOption,statename.text,sname.text,slocation.text,snum.text)
                    }
                }
            }
        }
    }
}


