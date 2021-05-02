#ifndef ENTITY_SYSTEM_H
#define ENTITY_SYSTEM_H

#include <set>

#include "../entity.h"
#include "../../../global_dependencies.h"

const unsigned int MAX_SYSTEMS = 32;

class EntitySystem {
  protected:
    bool enabled = false;
  public:
    std::set<Entity> entities;

    bool IsEnabled() {
        return enabled;
    }

    virtual void Enable() {
        enabled = true;
    }
    virtual void Disable() {
        enabled = false;
    }
};

#endif //ENTITY_SYSTEM_H
