import QtQuick 2.15
import QtQuick.Layouts 1.15
import QtQuick.Controls 1.4
import QtQuick.Controls 2.15
import QtQuick.Dialogs 1.3
import "./CustomComponents"

Rectangle{
    id:_rect
    height: parent.height
    width: parent.width

    signal loadSettingsPage()
    signal loadTurbinePage(var currPage)
    signal loadMapViewer()
    signal loadLoginPage()
    signal sendCountryName(var countryName)
    signal sendTableRow(var row)

    property int selectedCountry: -1
    property bool imgvisibility: true

    ColumnLayout{
        anchors.fill: parent
        Rectangle{
            id:_titlerect
            Layout.preferredHeight: _rect.height/12
            Layout.preferredWidth: _rect.width
            color: "#2C3639"
            radius: 10

            Image {
                id: _menu
                height: parent.height/2
                width: parent.width/50
                source: "qrc:/Images/menu.png"
                anchors.left: _titlerect.left
                anchors.leftMargin: _titlerect.width/40
                anchors.verticalCenter: _titlerect.verticalCenter
                transform: Translate{
                    x: drawer.position * width * 0.23
                }
            }

            CustomPropertyAnimation{
                id: _scaleout
                myfrom: 1.0
                myto: 1.2
                mytarget: _menu
            }

            CustomPropertyAnimation{
                id: _scalein
                myfrom: 1.2
                myto: 1.0
                mytarget: _menu
            }

            MouseArea {
                anchors.fill: _menu
                hoverEnabled: true

                onEntered: {
                    _scaleout.start();
                }

                onExited: {
                    _scalein.start()
                }
                onClicked: {
                    drawer.open()
                }
            }

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
                id: _worldPin
                source: "qrc:/Images/worldwide.png"
                height: _titlerect.height/1.5
                width: _titlerect.width/30.6
                anchors.right: _settingsicon.left
                anchors.rightMargin: 20
                anchors.verticalCenter: parent.verticalCenter

                MouseArea{
                    anchors.fill: parent
                    hoverEnabled: true

                    onEntered: {
                        _scaleoutworld.start()
                    }
                    onExited: {
                        _scaleinworld.start()
                    }

                    onClicked: {
                        loadMapViewer()
                    }
                }

                CustomPropertyAnimation{
                    id: _scaleoutworld
                    myfrom: 1.0
                    myto: 1.2
                    mytarget: _worldPin
                }

                CustomPropertyAnimation{
                    id: _scaleinworld
                    myfrom: 1.2
                    myto: 1.0
                    mytarget: _worldPin
                }
            }

            Image {
                id: _settingsicon
                height: _titlerect.height/1.5
                width: _titlerect.width/30.6
                source: "qrc:/Images/settings.png"
                anchors.right: parent.right
                anchors.rightMargin: parent.width/45
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
            color: "transparent"
            RowLayout{
                anchors.fill: parent
                Rectangle{
                    id:_lvrect
                    Layout.fillHeight: true
                    Layout.fillWidth: true
                    Layout.maximumWidth: parent.width/10
                    color: "transparent"

                    ListView{
                        id:_clv
                        height: parent.height
                        width: parent.width
                        clip: true
                        model: proxyModel.mycountryViewModel

                        delegate: Rectangle{
                            id:_delrect
                            height: _clv.height/10
                            width: _clv.width
                            color: "#2C3639"
                            border.color: "white"
                            radius: 10

                            ColumnLayout{
                                anchors.fill: parent
                                spacing: 0
                                Rectangle{
                                    id: _flagIcon
                                    Layout.preferredHeight: _delrect.height/1.45
                                    Layout.fillWidth: true
                                    color: "transparent"
                                    Image {
                                        id:_countryImage
                                        Layout.fillHeight: true
                                        Layout.preferredWidth: _delrect.width/2
                                        source: CFlag
                                        anchors.centerIn: parent
                                    }
                                }
                                Rectangle{
                                    Layout.fillHeight: true
                                    Layout.fillWidth: true
                                    color: "transparent"
                                    Label {
                                        text: CName
                                        font.pixelSize: _delrect.height/4.3
                                        font.family: "Arial"
                                        font.bold: true
                                        color: "white"
                                        anchors.top: parent.top
                                        anchors.horizontalCenter: parent.horizontalCenter
                                    }
                                }
                            }
                            MouseArea{
                                anchors.fill: _delrect
                                onClicked: {
                                    imgvisibility = false
                                    selectedCountry = model.index
                                    sendCountryName(model.CName)
                                    proxyModel.setSiteManager(model.CName)
                                }
                            }
                        }
                    }
                }
                Rectangle{
                    id:_tvrect
                    Layout.fillHeight: true
                    Layout.fillWidth: true
                    color: "transparent"
                    radius: 6

                    Image {
                        height: parent.height
                        width: parent.width
                        anchors.centerIn: parent
                        source: "qrc:/Images/homepic.jpg"
                        visible: imgvisibility
                    }

                    TableView{
                        id:_tv
                        visible: imgvisibility === false ? true : false
                        anchors.fill: parent
                        model: proxyModel.mysiteViewModel
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
                            id: _textRect
                            color: "transparent"
                            Label {
                                id: _siteData
                                text:" "+ styleData.value
                                font.pixelSize: parent.height/2.2
                                font.family: "Monospace"
                                color: "black"
                                anchors.verticalCenter: parent.verticalCenter
                            }
                        }

                        rowDelegate: Rectangle{
                            id: _rowData
                            border.color: "#2C3639"
                            radius: 4
                            height: _tvrect.height/18
                            MouseArea{
                                anchors.fill: _rowData
                                hoverEnabled: true

                                onClicked: {
                                    console.log(styleData.row)
                                    proxyModel.sendTurbineListToViewModel(model.PowerPlants)
                                    loadTurbinePage("Site")
                                }

                                onEntered: {
                                    _rowData.color = "#E0E0E0"
                                }
                                onExited: {
                                    _rowData.color = "transparent"
                                }
                            }
                        }

                        TableViewColumn{
                            role: "PowerPlants"
                            title: "Power Plant"
                            width: _tv.width/5
                        }
                        TableViewColumn{
                            role: "Locations"
                            title: "Location"
                            width: _tv.width/5
                        }
                        TableViewColumn{
                            role: "States"
                            title: "State"
                            width: _tv.width/5
                        }
                        TableViewColumn{
                            role: "Countries"
                            title: "Country"
                            width: _tv.width/5
                        }
                        TableViewColumn{
                            role: "PhoneNumbers"
                            title: "Phone Number"
                            width: _tv.width/5
                        }
                    }
                }
            }
        }
    }
    Drawer {
        id: drawer
        width: 0.23 * _rect.width
        height: _rect.height
        background: Rectangle{
            height: parent.height
            width: parent.width
            color: "#3F4E4F"
        }

        ColumnLayout{
            anchors.fill: parent
            Rectangle{
                id: _userInfoRect
                height: parent.height/12
                width: parent.width
                color: "#2C3639"
                radius: 10

                RowLayout{
                    anchors.fill: parent
                    Rectangle{
                        Layout.fillHeight: true
                        Layout.fillWidth: true
                        color: "transparent"
                        Image {
                            id: _userIcon
                            height: _userInfoRect.height/1.2
                            width: _userInfoRect.width/5.7
                            anchors.left: parent.left
                            anchors.leftMargin: parent.width/15
                            anchors.verticalCenter: parent.verticalCenter
                            source: "qrc:/Images/user.png"
                        }
                        MouseArea{
                            anchors.fill: _userIcon
                            onClicked: {
                                _fileDialog.open()
                            }
                        }
                    }
                    Rectangle{
                        Layout.fillHeight: true
                        Layout.fillWidth: true
                        color: "transparent"
                        Label{
                            text: proxyModel.myLoginCredentials.myUserName
                            anchors.centerIn: parent
                            color: "white"
                            font.pixelSize: _userInfoRect.height/3.5
                            font.family: "Monospace"
                        }
                    }
                }
            }
            Rectangle{
                Layout.fillWidth: true
                Layout.fillHeight: true
                color: "transparent"
                ListView{
                    anchors.fill: parent
                    model: 1
                    delegate: Rectangle{
                        id: _userOptions
                        height: 45
                        width: drawer.width
                        color: "#2C3639"
                        radius:5
                        RowLayout{
                            anchors.fill: parent
                            Image{
                                source: "qrc:/Images/logout.png"
                                Layout.alignment: Qt.AlignHCenter
                            }
                            Label{
                                text: "Logout"
                                color: "white"
                                font{
                                    bold: true
                                    family: "monospace"
                                    pixelSize: _userOptions.width/15
                                }
                                Layout.rightMargin: _userOptions.width/6
                            }
                        }
                        MouseArea{
                            anchors.fill: parent
                            hoverEnabled: true

                            onEntered: {
                                _userOptions.color = "#344044"
                            }

                            onExited: {
                                _userOptions.color = "#2C3639"
                            }
                            onClicked: {
                                _logoutDialog.myTitle = "Success"
                                _logoutDialog.myText = "Successfully Logged Out"
                                _logoutDialog.open()
                                loadLoginPage()
                            }
                        }
                    }
                }
            }
        }
        FileDialog{
            id: _fileDialog
            title: "Choose an Image"
            folder: shortcuts.home
        }
    }

    CustomDialog{
        id: _logoutDialog
    }
}

