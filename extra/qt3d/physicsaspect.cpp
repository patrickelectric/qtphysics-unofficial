#include "physicsaspect.h"
#include "physicsmanager.h"
#include "physicsentity.h"
#include "jobs/debugjob.h"
#include <Qt3DCore/qaspectfactory.h>
#include <Qt3DCore/qnodevisitor.h>
#include <Qt3DCore/qscenepropertychange.h>

QT_BEGIN_NAMESPACE
namespace Physics {

PhysicsAspect::PhysicsAspect(QObject* parent):
    Qt3D::QAbstractAspect(AspectType::AspectPhysicsAndCollision,parent)
{
    m_manager=new PhysicsManager();
    registerBackendType<Qt3D::QEntity>(Qt3D::QBackendNodeFunctorPtr(new Physics::PhysicsEntityFunctor(m_manager)));

}

QVector<Qt3D::QAspectJobPtr> PhysicsAspect::jobsToExecute(qint64 time){
    QVector<Qt3D::QAspectJobPtr> jobs;
    Qt3D::QAspectJobPtr job;
    job.reset(new DebugJob(m_manager));
    jobs.append(job);
    return jobs;
}

void PhysicsAspect::sceneNodeAdded(Qt3D::QSceneChangePtr &e) {
    Qt3D::QScenePropertyChangePtr propertyChange = e.staticCast<Qt3D::QScenePropertyChange>();
    Qt3D::QNodePtr nodePtr = propertyChange->value().value<Qt3D::QNodePtr>();
    Qt3D::QNode *n = nodePtr.data();
    Qt3D::QNodeVisitor visitor;
    visitor.traverse(n, this, &PhysicsAspect::visitNode, &PhysicsAspect::visitNode);
}
void PhysicsAspect::sceneNodeRemoved(Qt3D::QSceneChangePtr &e) {
    Qt3D::QScenePropertyChangePtr propertyChange = e.staticCast<Qt3D::QScenePropertyChange>();
    Qt3D::QNodePtr nodePtr = propertyChange->value().value<Qt3D::QNodePtr>();
    Qt3D::QNode *n = nodePtr.data();
    Qt3D::QAbstractAspect::clearBackendNode(n);
}

void PhysicsAspect::setRootEntity(Qt3D::QEntity *rootObject) {
    Qt3D::QNodeVisitor visitor;
    visitor.traverse(rootObject, this, &PhysicsAspect::visitNode, &PhysicsAspect::visitNode);
    m_manager->setRootEntityId(rootObject->id());
}

void PhysicsAspect::onInitialize(const QVariantMap &data) {
    Q_UNUSED(data);

}

void PhysicsAspect::onCleanup() {
    delete m_manager;
}

void PhysicsAspect::visitNode(Qt3D::QNode *node){
    Qt3D::QAbstractAspect::createBackendNode(node);
}

}

QT_END_NAMESPACE

QT3D_REGISTER_NAMESPACED_ASPECT("physics", QT_PREPEND_NAMESPACE(Physics), PhysicsAspect);
//QT3D_REGISTER_ASPECT("physics", Physics::PhysicsAspect);
