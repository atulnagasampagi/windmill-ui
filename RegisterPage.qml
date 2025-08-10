import QtQuick 2.15
import QtQuick.Layouts 1.15
import QtQuick.Controls 2.15
import QtGraphicalEffects 1.15
import "./CustomComponents"

Rectangle{
    id:_rect
    height: parent.height
    width: parent.width

    signal loadLoginPage()
    signal sendRegistrationDetails(var username, var email, var password, var confirmpassword)

    Image {
        id: _backgroundImage
        anchors.fill: parent
        source: "qrc:/Images/background.png"
    }
    Label{
        text: "Wind Mill Data Analysis"
        anchors {
            horizontalCenter: parent.horizontalCenter
            top: parent.top
            topMargin: 50
        }
        font {
            bold: true
            pixelSize: _rect.height/20
            family: "monospace"
        }
        color: "white"
    }

    RectangularGlow{
        anchors.fill: _credRect
        glowRadius: 10
        spread: 0.2
        color: "black"
        cornerRadius: _credRect.radius + glowRadius
    }
    Rectangle{
        id: _credRect
        height: parent.height/1.5
        width: parent.width/1.5
        anchors.centerIn: parent
        radius: 10
        color: "#2C3639"
        ColumnLayout{
            anchors.fill: parent
            spacing: 0
            Rectangle{
                id: _registerRect
                Layout.preferredHeight: _credRect.height/10
                Layout.preferredWidth: _credRect.width
                Layout.alignment: Qt.AlignTop
                color: "transparent"
                Label{
                    text: "Register"
                    color: "white"
                    font {
                        family: "Arial"
                        pixelSize: _credRect.height/15
                        bold:true
                    }
                    anchors.horizontalCenter: parent.horizontalCenter
                    anchors.top: parent.top
                    anchors.topMargin: parent.height/3
                }
            }
            Rectangle{
                Layout.preferredHeight: _credRect.height/20
                Layout.preferredWidth: _credRect.width
                Layout.topMargin: _credRect.height/40
                color: "transparent"
                Label{
                    text: "Kindly fill in this form to register"
                    color: "white"
                    font {
                        family: "Arial"
                        pixelSize: _credRect.height/28
                    }
                    anchors.horizontalCenter: parent.horizontalCenter
                    anchors.top: parent.top
                    // anchors.topMargin: parent.height/4
                }
            }
            Rectangle{
                id: _registerCredRect
                Layout.preferredHeight: _credRect.height/1.3
                Layout.preferredWidth: _credRect.width
                Layout.topMargin: _credRect.height/40
                color: "transparent"
                ColumnLayout{
                    anchors.fill: parent
                    spacing: 0
                    Rectangle{
                        Layout.fillWidth: true
                        Layout.fillHeight: true
                        color: "transparent"
                        RowLayout{
                            anchors.fill: parent
                            spacing: 0
                            Rectangle{
                                id: _rect1
                                Layout.fillHeight: true
                                Layout.fillWidth: true
                                color: "transparent"
                                ColumnLayout{
                                    anchors.fill: parent
                                    CustomTextField{
                                        id: _username
                                        Layout.preferredWidth: _rect1.width/1.5
                                        myplaceholder: "Enter username"
                                    }
                                    CustomTextField{
                                        id: _email
                                        Layout.preferredWidth: _rect1.width/1.5
                                        myplaceholder: "Enter email"
                                    }
                                }
                            }
                            Rectangle{
                                id: _rect2
                                Layout.fillHeight: true
                                Layout.fillWidth: true
                                color: "transparent"
                                ColumnLayout{
                                    anchors.fill: parent
                                    CustomTextField{
                                        id: _password
                                        Layout.preferredWidth: _rect1.width/1.5
                                        myplaceholder: "Enter password"
                                    }
                                    CustomTextField{
                                        id: _confirmPassword
                                        Layout.preferredWidth: _rect1.width/1.5
                                        myplaceholder: "Confirm password"
                                        echoMode: TextInput.Password

                                        Rectangle{
                                            height: _showPassword.height
                                            width: _showPassword.width
                                            anchors.right: parent.right
                                            anchors.rightMargin: _credRect.width/45
                                            color: "transparent"
                                            Image {
                                                id: _showPassword
                                                source: "qrc:/Images/hide.png"
                                            }
                                            MouseArea{
                                                anchors.fill: parent
                                                hoverEnabled: true

                                                onClicked: {
                                                    _confirmPassword.echoMode = _confirmPassword.echoMode === TextInput.Password ? TextInput.Normal : TextInput.Password
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                    Rectangle{
                        id: _rect3
                        Layout.preferredHeight: _registerCredRect.height/6
                        Layout.fillWidth: true
                        color: "transparent"
                        RowLayout{
                            anchors.fill: parent
                            CustomButton{
                                Layout.preferredHeight: _rect3.height/1.5
                                Layout.preferredWidth: _rect3.width/7
                                Layout.leftMargin: _rect3.width/15
                                myButtonName: "Register"

                                onClicked: {
                                    proxyModel.addNewUserToApplication(_username.text,_email.text,_password.text,_confirmPassword.text)

                                }
                            }
                            Label{
                                text: "Already have an account? "
                                Layout.leftMargin: _rect3.width/20
                                color: "white"
                                font {
                                    bold: true
                                    pixelSize: _registerRect.height/3.5
                                    family: "monospace"
                                }
                            }
                            Label{
                                id: _registerLabel
                                text: "Log In"
                                color: "white"
                                Layout.rightMargin: _rect3.width/2.5
                                font {
                                    bold: true
                                    pixelSize: _registerRect.height/4
                                    family: "monospace"
                                }
                                MouseArea{
                                    anchors.fill: _registerLabel
                                    hoverEnabled: true

                                    onEntered: {
                                        _registerLabel.color = "black"
                                    }
                                    onExited: {
                                        _registerLabel.color = "white"
                                    }

                                    onClicked: {
                                        loadLoginPage()
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}

