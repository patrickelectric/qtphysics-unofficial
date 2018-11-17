android|ios|tvos|winrt {
    warning( "This example is not supported for android, ios, tvos, or winrt." )
}


QT += 3dcore 3drender 3dinput 3dextras qml
QT += widgets

SOURCES += main.cpp

INCLUDEPATH += $$PWD/../../src


include($$PWD/../../plugins/bullet/dependencies.pri)

LIBS += -lLinearMath -lBulletDynamics -lBulletCollision

#HEADERS += \
#    physicssetter.h

LIBS += -lQtPhysicsUnofficial
LIBS += -L../../src/lib
