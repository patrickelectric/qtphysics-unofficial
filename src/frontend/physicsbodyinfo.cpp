#include <frontend/physicsbodyinfo.h>
#include <QVariantList>
namespace Physics {

PhysicsBodyInfo::PhysicsBodyInfo(Qt3DCore::QNode* parent):
    Qt3DCore::QComponent(parent),
    m_mask(1),
    m_group(1),
    m_kinematic(false),
    m_mass(0),
    m_fallInertia(),
    m_restitution(0.0f),
    m_friction(0.0f),
    m_rollingFriction(0.0f)
{
    m_inputTransform=Q_NULLPTR;
    m_outputTransform=new Qt3DCore::QTransform(this);
    setShareable(false);
}
//void PhysicsBodyInfo::copy(const Qt3DCore::QNode *ref){
//    Qt3DCore::QComponent::copy(ref);
//    const PhysicsBodyInfo * body_info = static_cast<const PhysicsBodyInfo *>(ref);

//    m_fallInertia=body_info->m_fallInertia;
//    m_restitution=body_info->m_restitution;
//    m_friction=body_info->m_restitution;
//    m_rollingFriction=body_info->m_rollingFriction;
//    m_mass=body_info->m_mass;
//    m_mask=body_info->m_mask;
//    m_group=body_info->m_group;
//    m_kinematic=body_info->m_kinematic;

//    m_inputTransform=body_info->m_inputTransform;
//    m_outputTransform=body_info->m_outputTransform;
//}

//PhysicsBodyInfo::~PhysicsBodyInfo(){
//    Qt3DCore::QComponent:
//}

void PhysicsBodyInfo::setMass(qreal mass){
    if(mass >=0 && m_mass!=mass){
        m_mass=mass;
        emit massChanged(m_mass);
    }
}

void PhysicsBodyInfo::setFallInertia(QVector3D fallInertia){
    if( m_fallInertia!=fallInertia){
        m_fallInertia=fallInertia;
        emit fallInertiaChanged(m_fallInertia);
    }
}

void PhysicsBodyInfo::setMask(int mask){
    if(mask >0 && m_mask!=mask){
        m_mask=mask;
        emit maskChanged(m_mask);
    }
}

void PhysicsBodyInfo::setGroup(int group){
    if(group >0 && m_group!=group){
        m_group=group;
        emit groupChanged(m_group);
    }
}
void PhysicsBodyInfo::setKinematic(bool kinematic){
    if(m_kinematic!=kinematic){
        m_kinematic=kinematic;
        emit kinematicChanged(m_kinematic);
    }
}

void PhysicsBodyInfo::setRestitution(qreal restitution){
    if(restitution!=m_restitution){
        m_restitution=restitution;
        emit restitutionChanged(m_restitution);
    }
}

void PhysicsBodyInfo::setRollingFriction(qreal rollingFriction){
    if(rollingFriction!=m_rollingFriction){
        m_rollingFriction=rollingFriction;
        emit rollingFrictionChanged(m_rollingFriction);
    }
}
void PhysicsBodyInfo::setFriction(qreal friction){
    if(friction!=m_friction){
        m_friction=friction;
        emit frictionChanged(m_friction);
    }
}

void PhysicsBodyInfo::setInputTransform(Qt3DCore::QTransform* inputTransform){
    m_inputTransform=inputTransform;
    emit inputTransformChanged();
}


QQmlListProperty<PhysicsCollisionEvent> PhysicsBodyInfo::collisionsList(){
    return QQmlListProperty<PhysicsCollisionEvent>(this, 0,
                                                 PhysicsBodyInfo::qmlComponentsCount,
                                                 PhysicsBodyInfo::qmlComponentAt);

}

PhysicsCollisionEvent* PhysicsBodyInfo::qmlComponentAt(QQmlListProperty<PhysicsCollisionEvent> *list, int index){
    PhysicsBodyInfo *self = static_cast<PhysicsBodyInfo *>(list->object);
    return self->m_collisionsList.at(index).data();
}

int PhysicsBodyInfo::qmlComponentsCount(QQmlListProperty<PhysicsCollisionEvent> *list){
     PhysicsBodyInfo *self = static_cast<PhysicsBodyInfo *>(list->object);
     return self->m_collisionsList.size();
}

Qt3DCore::QNodeCreatedChangeBasePtr PhysicsBodyInfo::createNodeCreationChange() const
{
    auto creationChange = Qt3DCore::QNodeCreatedChangePtr<PhysicsBodyInfoData>::create(this);
    auto &data = creationChange->data;
    data.mask=m_mask;
    data.group=m_group;
    data.kinematic=m_kinematic;
    data.mass=m_mass;
    data.fallInertia=m_fallInertia;
    data.restitution=m_restitution;
    data.friction=m_friction;
    data.rollingFriction=m_rollingFriction;
    data.inputTransformID=m_inputTransform!=Q_NULLPTR ? m_inputTransform->id() : Qt3DCore::QNodeId();
    return creationChange;
}

bool PhysicsBodyInfo::collisionTest(Qt3DCore::QNodeId id){
    return m_collisionsCache.contains(id);
}


void PhysicsBodyInfo::sceneChangeEvent(const Qt3DCore::QSceneChangePtr &change)
{
    Qt3DCore::QPropertyUpdatedChangePtr e = qSharedPointerCast< Qt3DCore::QPropertyUpdatedChange>(change);
    if (e->type() == Qt3DCore::PropertyUpdated) {
        /*if (e->propertyName() == QByteArrayLiteral("attachPhysicsTransfrom")) {
            bool val = e->value().toBool();
            if(val){
                QVector<Qt3D::QEntity*> entities = this->entities();
                if (entities.size() > 1)
                    qWarning()<< "It is strongly discouraged to share PhysicsBodyInfo component between entities";
                Q_FOREACH(Qt3D::QEntity* e, entities){
                    bool hasPhysicsTransform=false;
                    QMatrix4x4 m;
                    Q_FOREACH(Qt3D::QComponent* c, e->components()){
                        if(c->inherits("Qt3D::QTransform") && c->objectName().compare("@MaDeByPhYsIcS@")!=0){
                            c->setEnabled(false);
                            m=qobject_cast<Qt3D::QTransform*>(c)->matrix();
                        }
                        else if(c->inherits("Qt3D::QTransform") && c->objectName().compare("@MaDeByPhYsIcS@")==0){
                            hasPhysicsTransform=true;
                        }
                    }
                    if(!hasPhysicsTransform){
                        Qt3D::QTransform* physics_transform=new Qt3D::QTransform(this->parentNode());
                        physics_transform->setObjectName("@MaDeByPhYsIcS@");
                        Qt3D::QMatrixTransform* matrix= new Qt3D::QMatrixTransform(m,physics_transform);
                        physics_transform->addTransform(matrix);
                        e->addComponent(physics_transform);
                        m_attached_matrix=matrix;
                    }
                }
            }
    }*/
        if(e->propertyName() == QByteArrayLiteral("updateTransform")){
            QMatrix4x4 mat= e->value().value<QMatrix4x4>();
            m_outputTransform->setMatrix(mat);
            for(auto* entity : entities()) {
                auto vec = entity->components();
                if (std::none_of(std::begin(vec), std::end(vec), [](Qt3DCore::QComponent* comp){ return comp->inherits("Qt3DCore::QTransform"); })) {
                    entity->addComponent(m_outputTransform);
                }
            }
            emit outputTransformChanged();
        }
        if(e->propertyName() == QByteArrayLiteral("notifyCollision")){
            PhysicsCollisionEventPtrList collisions_list=e->value().value<PhysicsCollisionEventPtrList>();
            if(collisions_list.size()==0){
                if(m_hasCollided){
                    m_hasCollided=false;
                    emit hasCollidedChanged(m_hasCollided);
                }
                m_collisionsList.clear();
                m_collisionsCache.clear();
                emit collisionsListChanged();
            }
            else{
                m_collisionsList.clear();
                m_collisionsCache.clear();
                Q_FOREACH(PhysicsCollisionEventPtr event_ptr,collisions_list){
                    m_collisionsList.append(event_ptr);
                    m_collisionsCache.insert(event_ptr->target());
                    if(m_collisionsList.last()->isNew()){
                        emit collided(m_collisionsList.last());
                    }
                }
                if(!m_hasCollided){
                    m_hasCollided=true;
                    emit hasCollidedChanged(m_hasCollided);
                }
                emit collisionsListChanged();
            }
        }
    }
}



}
