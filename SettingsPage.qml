import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15
import QtQuick.Dialogs 1.3
import "./CustomComponents"

Rectangle{
    id: _settingspage
    height: parent.height
    width: parent.width
    signal loadHomePage()
    signal sendTableRow(var row)
    signal sendRemoveID(var cname)
    signal sendCountryName(var countryName)
    signal sendCountryData(var cname, var cflag)
    signal sendSiteData(var countryname, var statename, var sitename,var sitelocation, var producer, var phonenumber)
    signal sendTurbineData(var countryname, var sitename, var turbinename)
    signal sendRemoveSite(var countryname, var sitename)
    signal sendRemoveTurbine(var countryname, var sitename, var turbinename)

    property var optionsArr: ["Add Country","Remove Country","Add Site","Remove Site","Add Turbine","Remove Turbine"]

    property string actualParameter: ""
    property string deviceParameter: ""

    Rectangle{
        id:_titlerect
        height: parent.height/12
        width: parent.width
        color: "#2C3639"
        radius: 10
        Image {
            id: _backicon
            height: 40
            width: 40
            source: "qrc:/Images/back.png"
            anchors.left: parent.left
            anchors.leftMargin: 15
            anchors.verticalCenter: parent.verticalCenter
        }
        MouseArea{
            anchors.fill: _backicon
            hoverEnabled: true
            onClicked: {
                loadHomePage()
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

    Rectangle{
        id:_rect2
        height: _settingspage.height-_titlerect.height
        width: _titlerect.width/4
        anchors.top: _titlerect.bottom
        anchors.topMargin: _titlerect.height/4
        color: "transparent"
        ListView{
            id:_clv
            height: parent.height
            width:parent.width
            clip: true
            model: 6

            delegate: Rectangle{
                id:_delrect
                height: _clv.height/6
                width:_clv.width
                color: "#DCD7C9"
                border.color: "#2C3639"
                radius: 10

                Label {
                    id: options
                    text: optionsArr[index]
                    font.pixelSize: parent.height/5
                    font.family: "Arial"
                    color: "#2C3639"
                    anchors.centerIn: parent
                }

                MouseArea{
                    anchors.fill: _delrect
                    hoverEnabled: true
                    onClicked: {
                        switch(index){
                        case 0:
                            _operationsLoader.source = "qrc:/AddCountry.qml"
                            break;
                        case 1:
                            _operationsLoader.source = "qrc:/RemoveCountry.qml"
                            break;
                        case 2:
                            _operationsLoader.source = "qrc:/AddNewSite.qml"
                            break;
                        case 3:
                            _operationsLoader.source = "qrc:/RemoveSite.qml"
                            break;
                        case 4:
                            _operationsLoader.source = "qrc:/AddTurbine.qml"
                            break;
                        case 5:
                            _operationsLoader.source = "qrc:/RemoveTurbine.qml"
                            break;
                        }
                    }
                    onEntered: {
                        _delrect.color = "#A27B5C"
                    }
                    onExited: {
                        _delrect.color = "#DCD7C9"
                    }
                }
            }
        }
    }

    Rectangle{
        id: _arearect
        height: parent.height/1.4
        width: parent.width/1.4
        color: "#3F4E4F"
        anchors.top: _titlerect.bottom
        anchors.topMargin: _titlerect.height/4
        anchors.left: parent.left
        anchors.leftMargin: parent.width/3.7
        radius: 10

        Loader{
            id:_operationsLoader
            anchors.fill: parent
            source: "qrc:/AddCountry.qml"
        }

        Rectangle{
            height: parent.height/5
            width: parent.width/8.57
            color: "transparent"
            anchors.right: parent.right
            anchors.bottom: parent.bottom
            Image {
                id: _windMillImage
                height: parent.height
                width: parent.width
                source: "qrc:/Images/blades1.png"
                anchors.centerIn: parent
                opacity: 0.3
            }

            RotationAnimation {
                id: rotateclock
                target: _windMillImage
                property: "rotation"
                from: 0
                to: 360
                duration: 4000
                running: true
                loops: Animation.Infinite
                easing.type: Easing.Linear
            }
        }
    }

    Connections{
        target: _operationsLoader.item
        ignoreUnknownSignals: true

        function onSendSiteData(cname,statename,sname,slocation,cproducer,snum){
            console.log("Specific Slot Called")
            countryobj.calladdSite(cname,statename,sname,slocation,cproducer,snum)
        }

        function onLoadCompanyPage(){
            _operationsLoader.source = "qrc:/CompanyTurbineLIst.qml"
        }

        function onLoadMonitorPage(){
            _operationsLoader.source = "qrc:/CountryList.qml"
        }

        function onLoadTurbineParameter(){
            console.log("Turbine Parameter List")
            _operationsLoader.source = "qrc:/TurbineParamters.qml"
        }

        function onSendCompanyIndex(index){
            countryobj.initialzeObject(index)
        }

        function onSendParameters(actualParam,deviceParam){
            actualParameter = actualParam
            deviceParameter = deviceParam
            countryobj.sendActualAndDeviceParameter(actualParam,deviceParam)
        }

        function onWriteToFile(){
            _writeDialog.myTitle = "Warning"
            _writeDialog.myText = "Do you Want to Save"
            _writeDialog.open()
        }

        function onSendRemoveSite(countryname,sitename) {
            proxyModel.removeSite(countryname,sitename)
        }

    }

    Connections{
        target: proxyModel
        ignoreUnknownSignals: true

        onAddCountrySuccess: {
            _myDialog.myTitle = a_label
            _myDialog.myText = a_text
            _myDialog.open()
        }

        onAddCountryFailure: {
            _myDialog.myTitle = a_label
            _myDialog.myText = a_text
            _myDialog.open()
        }

        onAddSiteSuccess: {
            _myDialog.myTitle = a_label
            _myDialog.myText = a_text
            _myDialog.open()
        }

        onAddSiteFailure: {
            _myDialog.myTitle = a_label
            _myDialog.myText = a_text
            _myDialog.open()
        }

        onRemoveCountrySuccess: {
            _myDialog.myTitle = a_label
            _myDialog.myText = a_text
            _myDialog.open()
        }

        onRemoveCountryFailure: {
            _myDialog.myTitle = a_label
            _myDialog.myText = a_text
            _myDialog.open()
        }

        onRemoveSiteSuccess: {
            _myDialog.myTitle = a_label
            _myDialog.myText = a_text
            _myDialog.open()
        }

        onRemoveSiteFailure: {
            _myDialog.myTitle = a_label
            _myDialog.myText = a_text
            _myDialog.open()
        }
    }

    CustomDialog{
        id: _myDialog
        standardButtons: CustomDialog.Ok

//        onAccepted: {
//            _loader.source = "qrc:/CountryList.qml"
//        }
    }

    CustomDialog{
        id: _dataStoredDialog
        standardButtons: CustomDialog.Ok

        onAccepted: {
            _loader.source = "qrc:/CountryList.qml"
        }
    }

    CustomDialog{
        id: _updateDialog
        standardButtons: CustomDialog.Cancel | CustomDialog.Ok
        onAccepted: {
            countryobj.updateDeviceParameter(actualParameter,deviceParameter)
        }
    }

    CustomDialog{
        id: _writeDialog
        standardButtons: CustomDialog.Cancel | CustomDialog.Ok
        onAccepted: {
            countryobj.writeToFile()
//            _loader.source = "qrc:/CountryList.qml";
        }
    }
}
