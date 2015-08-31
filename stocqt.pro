TEMPLATE = app
INCLUDEPATH +=/usr/local/lib/R/site-library/RInside/include/
INCLUDEPATH +=/usr/local/lib/R/site-library/Rcpp/include/
INCLUDEPATH +=/usr/local/lib/R/include
INCLUDEPATH +=/opt/Qt/Examples/Qt-5.5/quick/demos/stocqt/fema_contest/API/include
INCLUDEPATH += /opt/Qt/Examples/Qt-5.5/quick/demos/stocqt
QT += qml quick gui
QT +=                   svg
LIBS+=-lR
LIBS+=-lRInside
LIBS+=-lpthread
LIBS+=-lrt
LIBS+=-lUSTPmduserapi64
LIBS+=-lUSTPtraderapi
HEADERS       = profile.h \
                USTPMDClient.h \
                USTPMDHandler.h \
                USTPFtdcUserApiDataType.h \
                USTPFtdcMduserApi.h \
                USTPFtdcUserApiStruct.h \
                custom.hpp \
    graph.h \
    linenode.h \
    USTPFtdcTraderApi.h \
    PublicFuncs.h \
    TraderSpi.h
SOURCES = main.cpp \
          profile.cpp \
          USTPMDClient.cpp \
          USTPMDHandler.cpp \
            MsClient.cpp \
    graph.cpp \
    linenode.cpp \
    TraderSpi.cpp \
    PublicFuncs.cpp \
    testapi.cpp
RESOURCES += stocqt.qrc
OTHER_FILES += *.qml content/*.qml content/images/*.png \
    mduserdemo.ini

target.path = $$[QT_INSTALL_EXAMPLES]/quick/demos/stocqt
INSTALLS += target

#DISTFILES += \
#s    content/trade_panel.qml

DISTFILES += \
    ../build-stocqt-Desktop_Qt_5_5_0_GCC_64bit-Debug/mduserdemo.ini \
    ../../../opt/Qt/Examples/Qt-5.5/quick/scenegraph/graph/shaders/line.fsh \
    ../../../opt/Qt/Examples/Qt-5.5/quick/scenegraph/graph/shaders/noisy.fsh \
    ../../../opt/Qt/Examples/Qt-5.5/quick/scenegraph/graph/shaders/line.vsh \
    ../../../opt/Qt/Examples/Qt-5.5/quick/scenegraph/graph/shaders/noisy.vsh
