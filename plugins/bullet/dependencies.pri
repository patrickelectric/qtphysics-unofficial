
android{
    BULLET_INCLUDE_PATH +=  /home/chili/bullet3-2.83.5/build_android/install/include/
    BULLET_INCLUDE_PATH +=  /home/chili/bullet3-2.83.5/build_android/install/include/bullet/
    BULLET_LIBS_PATH += -L/home/chili/bullet3-2.83.5/build_android/install/lib/
}

linux|macx{
    CONFIG += link_pkgconfig
    PKGCONFIG += bullet
}

BULLET_LIBS_PATH += -lLinearMath -lBulletDynamics -lBulletCollision
