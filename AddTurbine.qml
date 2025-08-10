import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15
import QtQuick.Dialogs 1.3
import "./CustomComponents"

Rectangle{
    id:_optionsrect
    color: "transparent"
    anchors.centerIn: parent

    signal loadCompanyPage()

    ColumnLayout{
        anchors.fill: parent
        CustomComboBox{
            id: _countrySelector
            myDisplayText: "Select Country"
            myModel: proxyModel.mycountryViewModel
        }
        CustomComboBox{
            id: _siteSelector
            myDisplayText: "Select Site"
            myModel: proxyModel.mysiteViewModel
            onSendTableRow:
            {
                console.log("in slot of combo"+currentIndex)
                countryobj.callprintCountry(currentIndex)
            }

        }

        CustomButton{
            myButtonName: "Configure Parameters"
            onClicked: {
                loadCompanyPage()
            }

        }

        CustomTextField{
            id:tname
            myplaceholder: "Enter Turbine Name"
            validator: RegExpValidator {
                regExp: /^[a-zA-Z\s]*$/
            }
        }
        CustomButton{
            myButtonName: "Submit"
            onClicked: {
                console.log("Submit Button Clicked")
                sendTurbineData(_countrySelector.selectedOption,_siteSelector.selectedOption,tname.text)
            }
        }
    }
}




