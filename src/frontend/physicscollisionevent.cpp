#include "physicscollisionevent.h"


namespace Physics {

PhysicsCollisionEvent::PhysicsCollisionEvent(QObject* parent):
    QObject(parent),
    m_target(Q_NULLPTR),
    m_contactPointOnBody(0,0,0),
    m_contactPointOnTarget(0,0,0),
    m_normalOnTarget(0,0,0)
{

}
void PhysicsCollisionEvent::setTarget(Qt3D::QEntity* target){
    m_target=target;
}
void PhysicsCollisionEvent::setContactPointOnBody(QVector3D point){
    m_contactPointOnBody=point;
}
void PhysicsCollisionEvent::setContactPointOnTarget(QVector3D point){
    m_contactPointOnTarget=point;
}
void PhysicsCollisionEvent::setNormalOnTarget(QVector3D normal){
    m_normalOnTarget=normal;
}





}