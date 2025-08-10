import QtQuick 2.15
import QtLocation 5.6
import QtPositioning 5.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15
import QtGraphicalEffects 1.15
import "./CustomComponents"

Rectangle{
    id: _rect
    anchors.fill: parent
    signal loadHomePage()
    signal loadTurbinePage(var currPage)

    property var myCountry
    property var mySite
    property var myState
    property var myLocation

    property var myTurbineCountry
    property var myTurbineSite
    property var myTurbineName
    property var myTurbineManufacturer

    ColumnLayout{
        anchors.fill: parent
        Rectangle{
            id:_titlerect
            Layout.preferredHeight: _rect.height/12
            Layout.preferredWidth: _rect.width
            Layout.alignment: Qt.AlignTop
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

            Label{
                text: "Wind Mill Monitor"
                color: "white"
                font.pixelSize: _titlerect.height/1.7
                font.family: "Arial"
                anchors.centerIn: _titlerect
            }
        }

        Rectangle {
            id: _maprect
            Layout.fillHeight: true
            Layout.fillWidth: true

            //Plugin is used to fetch the data from osm
            Plugin {
                id: mapPlugin
                name: "osm"
                PluginParameter{
                    name: "osm.mapping.custom.host"
                    value: "https://tile.openstreetmap.org/"
                }
            }

            //to display the map
            Map {
                id: map
                anchors.fill: parent
                plugin: mapPlugin
                center: QtPositioning.coordinate(20.5937, 78.9629)
                copyrightsVisible: false
                zoomLevel: 5
                activeMapType: supportedMapTypes[supportedMapTypes.length - 1]

                Component.onCompleted: {
                    console.log("MAP TYPE out : ")
                    for(var i = 0 ;i < map.supportedMapTypes.length;i++){
                        console.log("MAP TYPE : ", map.supportedMapTypes[i].name)
                    }
                }

                //for Image of Map Layers
                Rectangle{
                    id: _layersRect
                    height: _mapLayers.height + 5
                    width: _mapLayers.width + 5
                    radius: 5
                    color: "#2C3639"
                    anchors{
                        right: parent.right
                        top: parent.top
                        topMargin: _mapLayers.height/5
                        rightMargin: _mapLayers.width/5
                    }

                    transform: Translate{
                        x: _drawer.position * -width * 0.14
                    }

                    //image of Map Layers
                    Image {
                        id: _mapLayers
                        anchors.centerIn: parent
                        source: "qrc:/Images/layers.png"
                    }
                    MouseArea{
                        anchors.fill: parent
                        hoverEnabled: true

                        onEntered: {
                            _layersRect.color = "#3F4E4F"
                        }

                        onExited: {
                            _layersRect.color = "#2C3639"
                        }

                        onClicked: {
                            _drawer.open()
                        }
                    }
                }

                onZoomLevelChanged: {
                    if (zoomLevel >= 4.5 && zoomLevel <= 8) {
                        showObjects();
                    } else {
                        hideObjects();
                    }
                    if(zoomLevel > 8){
                        showTurbineMarkers()
                    }else{
                        hideTurbineMarkers()
                    }
                }

                function showTurbineMarkers(){
                    for (var i = 0; i < _turbineMarker.count; i++) {
                        _turbineMarker.itemAt(i).visible = true;
                    }
                }

                function hideTurbineMarkers(){
                    for (var i = 0; i < _turbineMarker.count; i++) {
                        _turbineMarker.itemAt(i).visible = false;
                    }
                }

                function showObjects(){
                    for (var i = 0; i < _marker.count; i++) {
                        _marker.itemAt(i).visible = true;
                    }
                }

                function hideObjects(){
                    for (var i = 0; i < _marker.count; i++) {
                        _marker.itemAt(i).visible = false;
                    }
                }

                Behavior on center {
                    PropertyAnimation {
                        id: _locate
                        duration: 5000
                        easing.type: Easing.InOutQuad
                    }
                }

                Repeater{
                    id: _turbineMarker
                    model: proxyModel.myturbineInfoViewModel
                    delegate: MapQuickItem{
                        id: _turbineMapMarker
                        visible: false
                        coordinate: QtPositioning.coordinate(MyTurbineLatitude,MyTurbineLongitude)
                        anchorPoint.x: turbineimage.width / 2
                        anchorPoint.y: turbineimage.height
                        sourceItem: Image {
                            id: turbineimage

                        }
                        Component.onCompleted: {
                            if(MyTurbineLatitude < 18.773){
                                turbineimage.source = "qrc:/Images/notworkingturbine.png"
                            }else{
                                turbineimage.source = "qrc:/Images/workingturbine.png"
                            }
                        }

                        MouseArea{
                            anchors.fill: _turbineMapMarker
                            hoverEnabled: true

                            onEntered: {
                                myTurbineCountry = MyCountryName
                                myTurbineSite = MySiteName
                                myTurbineName = MyTurbineName
                                myTurbineManufacturer = MyManufacturer
                                _turbineinfoBox.visible = true
                                _turbineinfoBox.x = _turbineMapMarker.x + _turbineMapMarker.width/2 - _turbineinfoBox.width/2
                                _turbineinfoBox.y = _turbineMapMarker.y - _turbineinfoBox.height - 5
                            }

                            onExited: {
                                _turbineinfoBox.visible = false
                            }
                        }
                    }
                }

                //to mark the location where the turbine is located
                Repeater {
                    id: _marker
                    model: proxyModel.mymarkerViewModel
                    delegate: MapQuickItem {
                        id: _mapMarker
                        // visible: false
                        coordinate: QtPositioning.coordinate(MyLatitude, MyLongitude)
                        anchorPoint.x: image.width / 2
                        anchorPoint.y: image.height
                        sourceItem: Image {
                            id: image
                            source: "qrc:/Images/windmill_marker.png"

                        }
                        MouseArea{
                            anchors.fill: parent
                            hoverEnabled: true

                            onEntered: {
                                myCountry = MyCountry
                                mySite = MySite
                                myLocation = MyLocation
                                myState = MyState
                                _infoBox.visible = true
                                _infoBox.x = _mapMarker.x + _mapMarker.width/2 - _infoBox.width/2
                                _infoBox.y = _mapMarker.y - _infoBox.height - 5
                            }

                            onExited: {
                                _infoBox.visible = false
                            }

                            onClicked: {
                                proxyModel.sendTurbineListToViewModel(mySite)
                                loadTurbinePage("Map")
                            }
                        }
                    }
                }

                //this is used to display the Individual Turbine Information
                Rectangle{
                    id: _turbineinfoBox
                    height: 150
                    width: _turbineManufacturer.width + 100
                    radius: 5
                    visible: false
                    color: "#2C3639"
                    ColumnLayout{
                        anchors.fill: parent
                        Label{
                            text: "Country : " + myTurbineCountry
                            color: "white"
                        }
                        Label{
                            text: "Site : " + myTurbineSite
                            color: "white"
                        }
                        Label{
                            text: "Turbine : " + myTurbineName
                            color: "white"
                        }
                        Label{
                            id: _turbineManufacturer
                            text: "Manufacturer : " + myTurbineManufacturer
                            color: "white"
                        }
                    }
                }

                //this is used for displaying the site information when hovered
                Rectangle{
                    id: _infoBox
                    height: 150
                    width: _siteName.width + 100
                    radius: 5
                    visible: false
                    color: "#2C3639"
                    ColumnLayout{
                        anchors.fill: parent
                        Label{
                            text: "Country : " + myCountry
                            color: "white"
                        }
                        Label{
                            id: _siteName
                            text: "Site : " + mySite
                            color: "white"
                        }
                        Label{
                            text: "Location : " + myLocation
                            color: "white"
                        }
                        Label{
                            text: "State : " + myState
                            color: "white"
                        }
                    }
                }

                //shadow effect for the tooltip
                DropShadow{
                    id: _shadow
                    anchors.fill: _infoBox
                    source:_infoBox
                    visible: _infoBox.visible === true ? true : false
                    radius: 10
                    verticalOffset: 5
                    horizontalOffset: 5
                    color: "#555555"
                }

                PropertyAnimation {
                    id: zoomInAnimation
                    target: map
                    property: "zoomLevel"
                    to: 4
                    duration: 2000
                    easing.type: Easing.InOutQuad

                }

                PropertyAnimation {
                    id: zoomOutAnimation
                    target: map
                    property: "zoomLevel"
                    to: 10
                    duration: 2000
                    easing.type: Easing.InOutQuad
                }

                TextField {
                    id: searchField
                    placeholderText: "Search..."
                    height: _rect.height/13
                    width: _rect.width/5
                    background: Rectangle{
                        height: _rect.height/13
                        width: _rect.width/5
                        color: "#2C3639"
                        radius: 5
                        anchors.verticalCenter: parent.verticalCenter
                        Rectangle{
                            id: _search
                            color: "#2C3639"
                            height: searchField.height
                            width: _searchIcon.width+20
                            radius: 5

                            anchors{
                                right: parent.right
                                verticalCenter: parent.verticalCenter
                            }

                            Image {
                                id: _searchIcon
                                source: "qrc:/Images/search.png"
                                anchors.centerIn: parent
                            }
                            MouseArea{
                                anchors.fill: parent
                                hoverEnabled: true

                                onEntered: {
                                    _search.color = "#34404A"
                                }

                                onExited: {
                                    _search.color = "#2C3639"
                                }

                                onClicked: {
                                    getLocation(searchField.text)
                                }
                            }
                        }
                    }

                    color: "white"
                    font.pixelSize: _rect.width/65
                    onAccepted: {
                        getLocation(searchField.text)
                    }
                }
            }

            //for displaying the map layers in Drawer Fashion
            Drawer {
                id: _drawer
                width: map.width/7
                height: parent.height
                edge: Qt.RightEdge
                parent: map

                background: Rectangle{
                    height: parent.height
                    width: parent.width
                    color: "#3F4E4F"
                }

                //for displaying the Supported Map Types
                ListView {
                    id: drawerList
                    anchors.fill: parent
                    model: map.supportedMapTypes
                    delegate: Rectangle{
                        id: _delRect
                        height: 70
                        width: _drawer.width
                        color: "#2C3639"
                        Label{
                            id: _supportedMapTypes
                            text: model.name
                            anchors.centerIn: _delRect
                            font {
                                family: "monospace"
                                pixelSize: _delRect.width/12
                            }
                            color: "white"
                        }

                        //for separation of List Items
                        Rectangle{
                            height: 1
                            width: _drawer.width
                            color: "white"
                        }

                        MouseArea{
                            anchors.fill: _delRect
                            hoverEnabled: true

                            onEntered: {
                                _delRect.color = "white"
                                _supportedMapTypes.color = "#2C3639"
                            }

                            onExited: {
                                _delRect.color = "#2C3639"
                                _supportedMapTypes.color = "white"
                            }

                            onClicked: {
                                map.activeMapType = map.supportedMapTypes[model.index]
                                _drawer.close()
                            }
                        }
                    }
                }
            }

            // for Legend Rectangle Shadow Effect
            RectangularGlow{
                id: effect
                anchors.fill: _legendRect
                glowRadius: 5
                spread: 0.2
                color: "black"
                cornerRadius: _legendRect.radius + glowRadius
            }

            //for Legend
            Rectangle{
                id: _legendRect
                height: parent.height/4
                width: parent.width/4
                color: "white"
                radius: 10
                anchors {
                    bottom: parent.bottom
                    left: parent.left
                    bottomMargin: parent.height/45
                    leftMargin: parent.width/75
                }

                ColumnLayout{
                    anchors.fill: parent
                    spacing: 0
                    Rectangle{
                        Layout.fillHeight: true
                        Layout.fillWidth: true
                        radius: 10
                        RowLayout{
                            anchors.fill: parent
                            Rectangle{
                                Layout.preferredHeight: _legendRect.height/8
                                Layout.preferredWidth: _legendRect.width/6
                                Layout.leftMargin: _legendRect.width/8
                                color: "green"
                            }

                            Label{
                                text: "Working Turbines"
                                font {
                                    family: "monospace"
                                    bold: true
                                    pixelSize: _legendRect.height/10
                                }
                            }
                        }
                    }
                    Rectangle{
                        Layout.fillHeight: true
                        Layout.fillWidth: true
                        radius: 10
                        RowLayout{
                            anchors.fill: parent
                            Rectangle{
                                Layout.preferredHeight: _legendRect.height/8
                                Layout.preferredWidth: _legendRect.width/6
                                Layout.leftMargin: _legendRect.width/8
                                color: "red"
                            }

                            Label{
                                text: "Non-Working Turbines"
                                font {
                                    family: "monospace"
                                    bold: true
                                    pixelSize: _legendRect.height/10
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    //function for locating the searched place on the screen center
    function getLocation(searchedPlaceName){
        var placeName = searchedPlaceName
        if (placeName !== "") {
            var xhr = new XMLHttpRequest();
            xhr.onreadystatechange = function() {
                if (xhr.readyState === XMLHttpRequest.DONE) {
                    if (xhr.status === 200) {
                        var response = JSON.parse(xhr.responseText);
                        if (response.length > 0) {
                            var place = response[0];
                            var latitude = place.lat;
                            var longitude = place.lon;
                            var boundingBox = place.boundingbox;

                            console.log(latitude,longitude)

                            var zoomLevel = calculateZoomLevel(boundingBox);

                            zoomOutAnimation.to = 5
                            zoomOutAnimation.start()
                            map.center = QtPositioning.coordinate(latitude, longitude);
                            zoomInAnimation.to = zoomLevel
                            zoomInAnimation.start()
                        } else {
                            openDialog("Not Found","Location Not Found")
                            console.warn("Location not found");
                        }
                    } else {
                        openDialog("Failure","Failed to retrive location data")
                        console.error("Failed to retrieve location data");
                    }
                }
            }
            xhr.open("GET", "https://nominatim.openstreetmap.org/search?q=" + encodeURIComponent(placeName) + "&format=json&limit=1");
            xhr.send();
        }else{
            openDialog("Info","Please enter any data")
            zoomOutAnimation.to = 5
            zoomOutAnimation.start()
            map.center = QtPositioning.coordinate(20.5937, 78.9629);
            zoomInAnimation.to = 5
            zoomInAnimation.start()
        }
    }

    //displays the location with the zoomlevel according to the area of the location
    function calculateZoomLevel(boundingBox) {
        var lat1 = parseFloat(boundingBox[0]);
        var lon1 = parseFloat(boundingBox[2]);
        var lat2 = parseFloat(boundingBox[1]);
        var lon2 = parseFloat(boundingBox[3]);

        var R = 2100;
        var dLat = deg2rad(lat2 - lat1);
        var dLon = deg2rad(lon2 - lon1);
        var a = Math.sin(dLat/2) * Math.sin(dLat/2) + Math.cos(deg2rad(lat1)) * Math.cos(deg2rad(lat2)) * Math.sin(dLon/2) * Math.sin(dLon/2);
        var c = 2 * Math.atan2(Math.sqrt(a), Math.sqrt(1-a));
        var d = R * c;
        var zoomLevel = Math.round(15 - Math.log2(d));
        return zoomLevel;
    }

    //to convert degree to radians
    function deg2rad(deg) {
        return deg * (Math.PI/180)
    }

    function openDialog(title,text){
        _mapSearch.myTitle = title
        _mapSearch.myText = text
        _mapSearch.open()
    }

    CustomDialog{
        id: _mapSearch
    }
}
