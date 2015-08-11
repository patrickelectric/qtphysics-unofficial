#ifndef DEBUGJOB_H
#define DEBUGJOB_H
#include "backend_global.h"

#include <Qt3DCore/qaspectjob.h>
#include <Qt3DCore/QNodeId>
namespace Physics {

class PhysicsManager;

class BACKENDSHARED_EXPORT DebugJob: public Qt3D::QAspectJob
{

public:
    DebugJob(PhysicsManager* manager);
protected:
     void run() Q_DECL_OVERRIDE;
private:
     void print(Qt3D::QNodeId id);
     PhysicsManager* m_manager;
};


}

#endif // DEBUGJOB_H