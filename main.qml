import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15
import "./CustomComponents"

Window {
    id: window
    width: 1200
    height: 700
    visible: true
    title: "Country Management"

    Loader{
        id:_loader
        anchors.fill: parent
        source: "qrc:/LoginPage.qml"
    }

    Connections{
        target:_loader.item
        ignoreUnknownSignals: true

        function onLoadSettingsPage(){
            _loader.source = "qrc:/SettingsPage.qml"
        }

        function onLoadLoginPage() {
            _loader.source = "qrc:/LoginPage.qml"
        }

        function onLoadRegistrationPage() {
            _loader.source = "qrc:/RegisterPage.qml"
        }

        function onLoadTurbineParameter(){
            _loader.source = "qrc:/TurbineParamters.qml"
        }

        function onSendLoginDetails(username,password) {
            proxyModel.verfiyLoginDetails(username,password)
        }

        function onLoadCompanyPage(){
            _loader.source = "qrc:/CompanyTurbineLIst.qml"
        }

        function onSendCompanyIndex(index){
            _loader.source = "qrc:/TurbineParamters.qml"
        }

        function onLoadMapViewer(){
            _loader.source = "qrc:/MapViewer.qml"
        }

        function onLoadHomePage(){
            _loader.source = "qrc:/CountryList.qml"
        }

        function onLoadTurbinePage(condition){
            _loader.setSource("qrc:/TurbineList.qml",{prevPage: condition})
        }

        function onLoadCountryListPage(){
            _loader.source = "qrc:/CountryList.qml"
        }
    }

    Connections{
        target: proxyModel
        ignoreUnknownSignals: true

        onLoginSuccess: {
            _loginDialog.myTitle = a_title
            _loginDialog.myText = a_text
            _loginDialog.open()
            _loader.source = "qrc:/CountryList.qml"
        }

        onLoginFailure: {
            _loginDialog.myTitle = a_title
            _loginDialog.myText = a_text
            _loginDialog.open()
        }

        onRegistrationSuccess: {
            _regDialog.myTitle = a_title
            _regDialog.myText = a_text
            _regDialog.open()
            _loader.source = "qrc:/LoginPage.qml"
        }

        onRegistrationFailure: {
            _regDialog.myTitle = a_title
            _regDialog.myText = a_text
            _regDialog.open()
        }
    }

    CustomDialog{
        id: _loginDialog
    }

    CustomDialog{
        id: _regDialog
    }
}
