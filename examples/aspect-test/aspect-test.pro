TEMPLATE = app

QT += 3dcore 3drender 3dinput 3dquick qml quick
CONFIG += c++11
CONFIG -= android_install

SOURCES += main.cpp
#    physicssetter.cpp

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
include(deployment.pri)

include($$PWD/../../plugins/bullet/dependencies.pri)

LIBS += -lLinearMath -lBulletDynamics -lBulletCollision

#HEADERS += \
#    physicssetter.h

LIBS += -lQtPhysicsUnofficial
LIBS += -L../../src/lib
