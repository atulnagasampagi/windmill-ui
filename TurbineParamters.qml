import QtQuick 2.15
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.5

Rectangle {
    id:_rect
    anchors.fill: parent
    property int selectedIndex: -1
    property int selectedIndex1: -1
    property string selectedActualParam: ""
    property string selectedDeviceParam: ""


    signal loadMonitorPage()
    signal loadCompanyPage()
    signal writeToFile()
    signal sendParameters(var actualParam, var deviceParam)

    ColumnLayout{
        anchors.fill :parent
        RowLayout {
            Layout.fillWidth: true
            Layout.fillHeight: true
            ColumnLayout{
                id:_col1
                Layout.fillWidth: true
                Layout.fillHeight: true
                Layout.maximumWidth: parent.width/5

                Label{
                    Layout.alignment: Qt.AlignHCenter
                    text:"Actual Parameters"
                    font{
                        bold: true
                        pixelSize: 20
                    }
                }
                ListView {
                    id:listView
                    Layout.fillHeight: true
                    Layout.fillWidth: true
                    clip:true
                    model:countryobj.myviewModel

                    delegate: Rectangle {
                        width: _col1.width
                        height: 50
                        color: selectedIndex === index ? "#3559E0" : "lightblue"
                        border.color: "blue"

                        Item{
                            width:parent.width/1.5
                            height:parent.height
                            anchors.centerIn: parent

                            Label {
                                text: ParameterList
                                anchors.verticalCenter: parent.verticalCenter
                                font.pixelSize: 15
                                font.bold: true
                            }
                        }
                        MouseArea{
                            anchors.fill: parent
                            onClicked: {
                                selectedIndex = index
                                selectedActualParam = model.ParameterList
                            }
                        }
                    }
                }
            }
            ColumnLayout{
                id:_col2
                Layout.fillWidth: true
                Layout.fillHeight: true
                Layout.maximumWidth: parent.width/2

                Label{
                    Layout.alignment: Qt.AlignHCenter
                    text:"Device Parameters"
                    font{
                        bold: true
                        pixelSize: 20
                    }
                }

                ListView {
                    Layout.fillHeight: true
                    Layout.fillWidth: true
                    clip:true
                    model:countryobj.mydeviceViewModel

                    delegate: Rectangle {
                        width: _col2.width
                        height: 50
                        border.color: "green"
                        Rectangle {
                            id: _deviceParamList
                            color: selectedIndex1 === index ? "#3559E0" : "lightblue"
                            anchors.fill: parent
                            border.color: "blue"

                            Item{
                                width:parent.width/1.5
                                height:parent.height
                                anchors.centerIn: parent

                                Label {
                                    text: DeviceParameterList
                                    font.pixelSize: 15
                                    font.bold: true
                                    anchors.verticalCenter: parent.verticalCenter
                                }
                            }

                            MouseArea{
                                anchors.fill: parent
                                onClicked: {
                                    selectedIndex1 = index;
                                    selectedDeviceParam = model.DeviceParameterList
                                }
                            }
                        }
                    }
                }
            }
            ColumnLayout{
                id:_col3
                Layout.fillHeight: true
                Layout.fillWidth: true
                Label{
                    Layout.alignment: Qt.AlignHCenter
                    text:"Mapped Parameters"
                    font{
                        bold: true
                        pixelSize: 20
                    }
                }

                ListView {
                    Layout.fillHeight: true
                    Layout.fillWidth: true
                    clip:true
                    model:proxyModel.mymapViewModel
                    Rectangle{
                        z:-1
                        anchors.fill: parent
                        color: "skyblue"
                    }

                    delegate: Rectangle {
                        width: _col3.width
                        height: 50
                        color: "lightblue"
                        border.color: "blue"

                        Item{
                            width:parent.width/1.1
                            height:parent.height
                            anchors.centerIn: parent


                            Label {
                                text: MapParameter
                                anchors.verticalCenter: parent.verticalCenter
                                font.pixelSize: 15
                                font.bold: true
                            }
                        }

                        MouseArea{
                            anchors.fill: parent
                            onClicked: {
                                selectedActualParam = model.ParameterList
                            }
                        }
                    }
                }
            }
        }
        RowLayout{
            Layout.fillWidth: true
            Layout.fillHeight: true

            Button{
                text: "Back"
                Layout.fillWidth: true
                font{
                    pixelSize: 20
                    bold:true
                }

                onClicked: {
                    loadCompanyPage()
                }
            }

            Button{
                text: "Add"
                Layout.fillWidth: true
                font{
                    pixelSize: 20
                    bold:true
                }

                onClicked: {
                    sendParameters(selectedActualParam,selectedDeviceParam)
                }
            }

            Button{
                Layout.fillWidth: true
                text: "Submit"
                font{
                    pixelSize: 20
                    bold:true
                }
                onClicked: {
                    writeToFile()
                }
            }
        }
    }
}
