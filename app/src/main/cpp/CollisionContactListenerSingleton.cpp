
#include "CollisionContactListenerSingleton.h"

void CollisionContactListenerSingleton::BeginContact(b2Contact *contact)
{
    b2ContactListener::BeginContact(contact);
    auto owner1 = (GameObject*)contact->GetFixtureA()->GetBody()->GetUserData();
    auto owner2 = (GameObject*)contact->GetFixtureB()->GetBody()->GetUserData();
    owner1->OnCollisionBegin(owner2);
    owner2->OnCollisionBegin(owner1);
}

void CollisionContactListenerSingleton::EndContact(b2Contact *contact)
{
    b2ContactListener::EndContact(contact);
    auto owner1 = (GameObject*)contact->GetFixtureA()->GetBody()->GetUserData();
    auto owner2 = (GameObject*)contact->GetFixtureB()->GetBody()->GetUserData();
    owner1->OnCollisionEnd(owner2);
    owner2->OnCollisionEnd(owner1);
}
