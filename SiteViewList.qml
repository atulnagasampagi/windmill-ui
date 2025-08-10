import QtQuick 2.15
import QtQuick.Layouts 1.15
import QtQuick.Controls 2.5

Item{
    width: 1300
    height: 600
    visible: true

    ColumnLayout{
        anchors.fill: parent
        Rectangle{
            Layout.maximumWidth: parent.width
            Layout.maximumHeight: parent.height/7
            Layout.fillHeight: true
            Layout.fillWidth: true

            color: "pink"
            RowLayout{
                anchors.fill:parent
                Rectangle{
                    Layout.fillHeight: true
                    Layout.fillWidth: true
                    color: "skyblue"
                    Label {
                        anchors.centerIn: parent
                        text:"PowerPLant"
                    }
                }
                Rectangle{
                    Layout.fillHeight: true
                    Layout.fillWidth: true

                    color: "skyblue"
                    Label {
                        anchors.centerIn: parent
                        text:"Location"
                    }
                }

                Rectangle{
                    Layout.fillHeight: true
                    Layout.fillWidth: true

                    color: "skyblue"
                    Label {
                        anchors.centerIn: parent
                        text:"States"
                    }
                }
                Rectangle{
                    Layout.fillHeight: true
                    Layout.fillWidth: true

                    color: "skyblue"
                    Label {
                        anchors.centerIn: parent
                        text:"Country"
                    }
                }
                Rectangle{
                    Layout.fillHeight: true
                    Layout.fillWidth: true

                    color: "skyblue"
                    Label {
                        anchors.centerIn: parent
                        text:"Producer"
                    }
                }
                Rectangle{
                    Layout.fillHeight: true
                    Layout.fillWidth: true

                    color: "skyblue"
                    Label {
                        anchors.centerIn: parent
                        text:"PhoneNumber"
                    }
                }
            }
        }
        Rectangle{
            id:_rect
            Layout.fillHeight: true
            Layout.fillWidth: true
            ListView{
                anchors.fill: parent
                model: SiteList.myModel
                clip: true
                delegate: Rectangle{
                    width:_rect.width
                    height:_rect.height/8
                    border.color: "transparent"
                    RowLayout{
                        anchors.fill:parent
                        Rectangle{
                            Layout.fillHeight: true
                            Layout.fillWidth: true

                            color: "#F1EAFF"
                            Label {
                                anchors.centerIn: parent
                                text:PowerPLant
                            }
                        }
                        Rectangle{
                            Layout.fillHeight: true
                            Layout.fillWidth: true

                            color: "#C4FFDF"
                            Label {
                                anchors.centerIn: parent
                                text:Location
                            }
                        }
                        Rectangle{
                            Layout.fillHeight: true
                            Layout.fillWidth: true

                            color: "silver"
                            Label {
                                anchors.centerIn: parent
                                text:States
                            }
                        }
                        Rectangle{
                            Layout.fillHeight: true
                            Layout.fillWidth: true

                            color: "#FFFFFF"
                            Label {
                                anchors.centerIn: parent
                                text:Country
                            }
                        }
                        Rectangle{
                            Layout.fillHeight: true
                            Layout.fillWidth: true

                            color: "#FFF3FF"
                            Label {
                                anchors.centerIn: parent
                                text:Producer
                            }
                        }
                        Rectangle{
                            Layout.fillHeight: true
                            Layout.fillWidth: true

                            color: "#FFFFF1"
                            Label {
                                anchors.centerIn: parent
                                text:PhoneNumber
                            }
                        }
                    }

                }
            }
        }
    }
}




