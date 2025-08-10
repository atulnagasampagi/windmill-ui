import QtQuick 2.15
import QtQuick.Controls 2.5
Rectangle{

    anchors.fill: parent
    Image {
        id: name
        source: "qrc:/Images/TurbineImage.webp"
        anchors.fill: parent
    }
    signal loadTurbineParameter()
    signal sendCompanyIndex(var index)
    ListView{

        height: parent.height/1.5
        width: parent.width/2
        anchors.centerIn: parent
        model:countryobj.mycompanyListModel
        delegate: Rectangle{
            width: parent.width
            height: 80
            radius: 50
            color: "transparent"

            Label{
                id:_label
                text:CompanyName
                anchors.centerIn: parent
                font.pixelSize: 25
                font.bold: true
            }
            MouseArea{
                anchors.fill: _label
                hoverEnabled: true
                onEntered: {
                    _label.scale=1.2
                }
                onExited: {
                    _label.scale=1.0
                }

                onClicked: {
                    console.log(model.name)
                    sendCompanyIndex(model.index)
                    console.log("After Send Company Index in QML")
                    loadTurbineParameter()
                }
            }
        }
    }
}
