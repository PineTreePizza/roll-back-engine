#ifndef TIMER_ENTITY_SYSTEM_H
#define TIMER_ENTITY_SYSTEM_H

#include "entity_system.h"
#include "../../../timer/timer_manager.h"

class TimerEntitySystem : public EntitySystem {
  private:
    TimerManager *timerManager = nullptr;
  public:
    TimerEntitySystem() {
        timerManager = TimerManager::GetInstance();
        enabled = true;
    }

    void Initialize() override {}

    void Enable() override {}

    void Disable() override {}

    void UnregisterEntity(Entity entity) override {
        timerManager->RemoveTimer(entity);
    }

    void Tick() {
        for (auto const &pair : timerManager->activeTimers) {
            Entity entity = pair.first;
            Timer *timer = pair.second;
            if (timer->HasReachedTimeOut()) {
                timer->Stop();
                // Emit signal
//              signalManager->EmitSignal(entity, "timeout");
                if (timer->DoesLoop()) {
                    timer->Start();
                } else {
                    timerManager->activeTimers.erase(entity);
                }
            }
        }
    }
};

#endif //COLLISION_ENTITY_SYSTEM_H
