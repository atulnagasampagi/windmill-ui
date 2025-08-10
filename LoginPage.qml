import QtQuick 2.15
import QtQuick.Layouts 1.15
import QtQuick.Controls 2.15
import QtGraphicalEffects 1.15
import "./CustomComponents"

Rectangle{
    id:_rect
    height: parent.height
    width: parent.width

    signal loadRegistrationPage()
    signal sendLoginDetails(var username, var password)

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
        height: parent.height/2
        width: parent.width/4.5
        anchors.centerIn: parent
        radius: 10
        color: "#2C3639"
        ColumnLayout{
            anchors.fill: parent
            CustomTextField{
                id: _userName
                Layout.preferredWidth: _credRect.width/1.4
                Layout.topMargin: _credRect.height/6
                myplaceholder: "Username..."
            }

            CustomTextField{
                id: _password
                Layout.preferredWidth: _credRect.width/1.4
                Layout.topMargin: _credRect.height/12
                myplaceholder: "Password..."
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
                            _password.echoMode = _password.echoMode === TextInput.Password ? TextInput.Normal : TextInput.Password
                        }
                    }
                }
            }
            Label{
                text: "Forgot Password?"
                color: "white"
                Layout.leftMargin: _credRect.width/6.5
                font {
                    pixelSize: _registerRect.height/6
                    family: "monospace"
                }
            }
            CustomButton{
                Layout.preferredHeight: _credRect.height/10
                Layout.preferredWidth: _credRect.width/2.3
                Layout.topMargin: _credRect.height/4
                myButtonName: "Submit"

                onClicked: {
                    console.log("Submit Button Clicked")
                    sendLoginDetails(_userName.text,_password.text)
                }
            }

            Rectangle{
                id: _registerRect
                Layout.preferredHeight: _credRect.height/7
                Layout.preferredWidth: _credRect.width
                Layout.bottomMargin: _credRect.height/27
                color: "transparent"
                radius: 10
                RowLayout{
                    anchors.fill: parent
                    Label{
                        text: "New user ?"
                        color: "white"
                        Layout.alignment: Qt.AlignHCenter
                        font {
                            bold: true
                            pixelSize: _registerRect.height/3.5
                            family: "monospace"
                        }
                    }
                    Label{
                        id: _registerLabel
                        text: "Register"
                        color: "white"
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
                                loadRegistrationPage()
                            }
                        }
                    }
                }
            }
        }
    }
}

