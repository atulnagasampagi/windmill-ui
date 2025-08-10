QT += quick core

QT += location

QT += network

LIBS += -L$$PWD/libs/ -lcrypto -lssl

DESTDIR += $$PWD

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        configurationmanagement.cpp \
        countryinfo.cpp \
        countrymanager.cpp \
        countryproxymodel.cpp \
        countryviewmodel.cpp \
        csvprocessor.cpp \
        datamanager.cpp \
        firebasereader.cpp \
        logincredentials.cpp \
        main.cpp \
        markerdatamodel.cpp \
        markerviewmodel.cpp \
        siteinfo.cpp \
        sitemanager.cpp \
        siteviewmodel.cpp \
        turbinedata.cpp \
        turbinedatamodel.cpp \
        turbineinfo.cpp \
        turbineinfoviewmodel.cpp \
        turbinemanager.cpp \
        turbineviewmodel.cpp

RESOURCES += qml.qrc


# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    configurationmanagement.h \
    countryinfo.h \
    countrymanager.h \
    countryproxymodel.h \
    countryviewmodel.h \
    csvprocessor.h \
    datamanager.h \
    firebasereader.h \
    logincredentials.h \
    markerdatamodel.h \
    markerviewmodel.h \
    siteinfo.h \
    sitemanager.h \
    siteviewmodel.h \
    turbinedata.h \
    turbinedatamodel.h \
    turbineinfo.h \
    turbineinfoviewmodel.h \
    turbinemanager.h \
    turbineviewmodel.h

DISTFILES +=
