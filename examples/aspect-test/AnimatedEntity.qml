import Qt3D.Core 2.0
import Qt3D.Render 2.0
import QtPhysics.unofficial 1.0
import Qt3D.Input 2.0
import Qt3D.Extras 2.0


Entity {
    id: rootEntity
    property real friction: 0.8
    property real restitution: 0.8

    Camera {
        id: camera
        projectionType: CameraLens.PerspectiveProjection
        fieldOfView: 45
        aspectRatio: 16/9
        nearPlane : 0.1
        farPlane : 1000.0
        position: Qt.vector3d( 0.0, 0.0, -20.0 )
        upVector: Qt.vector3d( 0.0, 1.0, 0.0 )
        viewCenter: Qt.vector3d( 0.0, 0.0, 0.0 )
    }
    FirstPersonCameraController { camera: camera }
    components: [
        RenderSettings {
            activeFrameGraph: ForwardRenderer {
                camera: camera
                clearColor: "transparent"
            }
        }, PhysicsWorldInfo{
            gravity: Qt.vector3d(0, -9.8,0)
            scaleFactor: 1
        }, InputSettings {}
    ]

    PhongMaterial {
        id: material
    }

    Entity {
        id: sphereEntity

        SphereMesh {
            id: sphereMesh
            radius: 2
        }
        Transform {
            id: sphereTransform
            translation: Qt.vector3d(0, 3, -0.2)
        }
        PhysicsBodyInfo{
            id: sphereBodyinfo
            mass: 1
            restitution: rootEntity.restitution
            friction: rootEntity.friction
            inputTransform: sphereTransform
        }

        components: [sphereMesh, sphereBodyinfo, material]
    }

    Entity {
        id: torusEntity

        TorusMesh {
            id: torusMesh
            radius: 1
            minorRadius: 1
            rings: 100
            slices: 25
        }
        Transform {
            id: torusTransform
            translation: Qt.vector3d(0, 10, 0)
        }
        PhysicsBodyInfo{
            id: torusBodyinfo
            mass: 1
            restitution: rootEntity.restitution
            friction: rootEntity.friction
            inputTransform: torusTransform
        }

        components: [torusMesh, material, torusBodyinfo]
    }

    Entity {
        id: floor

        CuboidMesh{
            id: planeMesh
            xExtent: 100
            yExtent: 5
            zExtent: 100
        }
        Transform{
            id: transformFloor
            translation: Qt.vector3d(0, -10, 0)
        }
        PhysicsBodyInfo{
            id:floorBodyInfo
            restitution: 1
            friction: 1
            inputTransform: transformFloor
        }

        components: [planeMesh, material, floorBodyInfo]
    }
}
