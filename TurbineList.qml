import QtQuick 2.15
import QtQuick.Layouts 1.15
import QtQuick.Controls 1.4
import "./CustomComponents"

Rectangle{
    id:_tvrect
    Layout.fillHeight: true
    Layout.fillWidth: true
    color: "transparent"
    radius: 6

    signal loadMapViewer()
    signal loadHomePage()
    signal loadSettingsPage()

    property var prevPage

    ColumnLayout{
        anchors.fill: parent
        Rectangle{
            id:_titlerect
            Layout.preferredHeight: _tvrect.height/12
            Layout.preferredWidth: _tvrect.width
            color: "#2C3639"
            radius: 10

            CustomTime{
                anchors.left: _titlerect.left
                anchors.leftMargin: _titlerect.width/8
                anchors.verticalCenter: _titlerect.verticalCenter
            }

            Label{
                text: "Wind Mill Monitor"
                color: "white"
                font.pixelSize: _titlerect.height/1.7
                font.family: "Arial"
                anchors.centerIn: _titlerect
            }
            Image{
                id: _backicon
                height:40
                width:40
                source: "qrc:/Images/back.png"
                anchors.left: parent.left
                anchors.leftMargin: 15
                anchors.verticalCenter: parent.verticalCenter
                MouseArea{
                    anchors.fill: _backicon
                    hoverEnabled: true
                    onClicked: {
                        if(prevPage === "Map"){
                            loadMapViewer()
                        }else{
                            loadHomePage()
                        }
                    }
                    onEntered: {
                        _scaleout.start()
                    }

                    onExited: {
                        _scalein.start()
                    }
                }
                CustomPropertyAnimation{
                    id: _scaleout
                    myfrom: 1.0
                    myto: 1.2
                    mytarget: _backicon
                }
                CustomPropertyAnimation{
                    id: _scalein
                    myfrom: 1.2
                    myto: 1.0
                    mytarget: _backicon
                }
            }

            Image {
                id: _settingsicon
                height: _titlerect.height/1.5
                width: _titlerect.width/28.5
                source: "qrc:/Images/settings.png"
                anchors.right: parent.right
                anchors.rightMargin: parent.width/20
                anchors.verticalCenter: parent.verticalCenter

                MouseArea{
                    anchors.fill: parent
                    hoverEnabled: true

                    onEntered: {
                        rotateanticlock.start()
                    }
                    onExited: {
                        rotateclock.start()
                    }

                    onClicked: {
                        loadSettingsPage()
                    }
                }
            }
            RotationAnimation {
                id: rotateclock
                target: _settingsicon
                property: "rotation"
                from: 0
                to: 50
                duration: 300
                running: false
                easing.type: Easing.Linear
            }
            RotationAnimation {
                id: rotateanticlock
                target: _settingsicon
                property: "rotation"
                from: 50
                to: 0
                duration: 300
                running: false
                easing.type: Easing.Linear
            }
        }
        Rectangle{
            Layout.fillHeight: true
            Layout.fillWidth: true
            TableView{
                id:_tv
                anchors.fill: parent
                Layout.fillHeight: true
                Layout.fillWidth: true
                model: proxyModel.myturbineViewModel
                headerDelegate: Rectangle{
                    height: _tvrect.height/18
                    width:parent.width
                    color: "#2C3639"
                    border.color: "white"
                    radius: 3
                    Label {
                        anchors.centerIn: parent
                        text: styleData.value
                        font.pixelSize: _tv.height/45
                        font.bold: true
                        font.family: "Arial"
                        color: "white"
                    }
                }

                itemDelegate: Rectangle{
                    color: "transparent"
                    Label {
                        id: _siteData
                        text: " "+styleData.value
                        font.pixelSize: parent.height/2.2
                        font.family: "Arial"
                        color: "black"
                        anchors.centerIn: parent
                    }
                }

                rowDelegate: Rectangle{
                    border.color: "#2C3639"
                    radius: 4
                    height: _tvrect.height/18
                }

                TableViewColumn{
                    role: "Turbine"
                    title: "Turbine Name"
                    width: _tv.width/9
                }
                TableViewColumn{
                    role: "Wind Speed"
                    title: "Wind Speed(m/s)"
                    width: _tv.width/9
                }
                TableViewColumn{
                    role: "Wind Direction"
                    title: "Wind Direction(°)"
                    width: _tv.width/9
                }
                TableViewColumn{
                    role: "Power Output(KW)"
                    title: "Power Output(KW)"
                    width: _tv.width/9
                }
                TableViewColumn{
                    role: "Temperature"
                    title: "Temperature(°C)"
                    width: _tv.width/9
                }
                TableViewColumn{
                    role: "Pressure"
                    title: "Pressure(atm)"
                    width: _tv.width/9
                }
                TableViewColumn{
                    role: "Pitch Angle"
                    title: "Pitch Angle(°)"
                    width: _tv.width/9
                }
                TableViewColumn{
                    role: "Blade Angle"
                    title: "Blade Angle(°)"
                    width: _tv.width/9
                }
                TableViewColumn{
                    role: "Yaw Direction"
                    title: "Yaw Direction(°)"
                    width: _tv.width/9
                }
            }
        }
    }
}
