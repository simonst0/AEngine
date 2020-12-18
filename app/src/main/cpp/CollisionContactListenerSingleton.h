#pragma once

#include <Box2D/Box2D.h>
#include <unordered_map>
#include <mutex>
#include "GameObject.h"

class CollisionContactListenerSingleton : public b2ContactListener {
    public:
        static CollisionContactListenerSingleton& instance()
        {
            static CollisionContactListenerSingleton _instance;
            return _instance;
        }
        ~CollisionContactListenerSingleton() {}
    private:
        CollisionContactListenerSingleton() {};
        CollisionContactListenerSingleton( const CollisionContactListenerSingleton& );
        CollisionContactListenerSingleton& operator = (const CollisionContactListenerSingleton &);

public:
    void BeginContact(b2Contact *contact) override;
    void EndContact(b2Contact *contact) override;
};


