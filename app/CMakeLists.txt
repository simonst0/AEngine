# For more information about using CMake with Android Studio, read the
# documentation: https://d.android.com/studio/projects/add-native-code.html

# Sets the minimum version of CMake required to build the native library.

cmake_minimum_required(VERSION 3.4.1)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../Box2D)
add_library(Box2D

        STATIC

        ${CMAKE_CURRENT_SOURCE_DIR}/../Box2D/Box2D/Collision/Shapes/b2ChainShape.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../Box2D/Box2D/Collision/Shapes/b2CircleShape.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../Box2D/Box2D/Collision/Shapes/b2EdgeShape.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../Box2D/Box2D/Collision/Shapes/b2PolygonShape.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../Box2D/Box2D/Collision/b2BroadPhase.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../Box2D/Box2D/Collision/b2CollideCircle.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../Box2D/Box2D/Collision/b2CollideEdge.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../Box2D/Box2D/Collision/b2CollidePolygon.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../Box2D/Box2D/Collision/b2Collision.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../Box2D/Box2D/Collision/b2Distance.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../Box2D/Box2D/Collision/b2DynamicTree.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../Box2D/Box2D/Collision/b2TimeOfImpact.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../Box2D/Box2D/Common/b2BlockAllocator.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../Box2D/Box2D/Common/b2Draw.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../Box2D/Box2D/Common/b2Math.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../Box2D/Box2D/Common/b2Settings.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../Box2D/Box2D/Common/b2StackAllocator.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../Box2D/Box2D/Common/b2Timer.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../Box2D/Box2D/Dynamics/Contacts/b2ChainAndCircleContact.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../Box2D/Box2D/Dynamics/Contacts/b2ChainAndPolygonContact.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../Box2D/Box2D/Dynamics/Contacts/b2CircleContact.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../Box2D/Box2D/Dynamics/Contacts/b2Contact.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../Box2D/Box2D/Dynamics/Contacts/b2ContactSolver.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../Box2D/Box2D/Dynamics/Contacts/b2EdgeAndCircleContact.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../Box2D/Box2D/Dynamics/Contacts/b2EdgeAndPolygonContact.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../Box2D/Box2D/Dynamics/Contacts/b2PolygonAndCircleContact.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../Box2D/Box2D/Dynamics/Contacts/b2PolygonContact.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../Box2D/Box2D/Dynamics/Joints/b2DistanceJoint.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../Box2D/Box2D/Dynamics/Joints/b2FrictionJoint.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../Box2D/Box2D/Dynamics/Joints/b2GearJoint.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../Box2D/Box2D/Dynamics/Joints/b2Joint.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../Box2D/Box2D/Dynamics/Joints/b2MotorJoint.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../Box2D/Box2D/Dynamics/Joints/b2MouseJoint.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../Box2D/Box2D/Dynamics/Joints/b2PrismaticJoint.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../Box2D/Box2D/Dynamics/Joints/b2PulleyJoint.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../Box2D/Box2D/Dynamics/Joints/b2RevoluteJoint.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../Box2D/Box2D/Dynamics/Joints/b2RopeJoint.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../Box2D/Box2D/Dynamics/Joints/b2WeldJoint.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../Box2D/Box2D/Dynamics/Joints/b2WheelJoint.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../Box2D/Box2D/Dynamics/b2Body.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../Box2D/Box2D/Dynamics/b2ContactManager.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../Box2D/Box2D/Dynamics/b2Fixture.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../Box2D/Box2D/Dynamics/b2Island.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../Box2D/Box2D/Dynamics/b2World.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../Box2D/Box2D/Dynamics/b2WorldCallbacks.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../Box2D/Box2D/Rope/b2Rope.cpp
        )

file(GLOB game_SRC
        "src/main/cpp/native-lib.cpp"
        "src/main/cpp/Shader.cpp"
        "src/main/cpp/Shader.h"
        "src/main/cpp/GameObject.cpp"
        "src/main/cpp/GameObject.h"
        "src/main/cpp/AComponent.cpp"
        "src/main/cpp/AComponent.h"
        "src/main/cpp/FactoryTemplate.h"
        "src/main/cpp/GameObjectFactory.cpp"
        "src/main/cpp/GameObjectFactory.h"
        "src/main/cpp/stb_image.h"
        "src/main/cpp/Texture.h"
        "src/main/cpp/Texture.cpp"
        "src/main/cpp/Util.h"
        "src/main/cpp/Scene.cpp"
        "src/main/cpp/Scene.h"
        "src/main/cpp/Scene.h"
        "src/main/cpp/BodyComponent.cpp"
        "src/main/cpp/BodyComponent.h"
        "src/main/cpp/SpriteComponent.h"
        "src/main/cpp/SpriteComponent.cpp"
        "src/main/cpp/SpriteRendererSingleton.cpp"
        "src/main/cpp/SpriteRendererSingleton.h"
        "src/main/cpp/CollisionContactListenerSingleton.cpp"
        "src/main/cpp/CollisionContactListenerSingleton.h"
        "src/main/cpp/PlayerComponent.h"
        "src/main/cpp/PlayerComponent.cpp"
        "src/main/cpp/FixtureComponent.cpp"
        "src/main/cpp/FixtureComponent.h"
        "src/main/cpp/SoundControllerSingleton.h"
        "src/main/cpp/SoundControllerSingleton.cpp"
        "src/main/cpp/TextureLoader.cpp"
        "src/main/cpp/TextureLoader.h"
        "src/main/cpp/TileMap.h"
        "src/main/cpp/TileMap.cpp"
        "src/main/cpp/CarSteeringComponent.cpp"
        "src/main/cpp/CarSteeringComponent.h"
        "src/main/cpp/ARenderer.h"
        "src/main/cpp/ARenderer.cpp"
        "src/main/cpp/ParticleRendererSingleton.cpp"
        "src/main/cpp/ParticleRendererSingleton.h"
        "src/main/cpp/ParticleSystemComponent.cpp"
        "src/main/cpp/ParticleSystemComponent.h"
        )


# Creates and names a library, sets it as either STATIC
# or SHARED, and provides the relative paths to its source code.
# You can define multiple libraries, and CMake builds them for you.
# Gradle automatically packages shared libraries with your APK.

add_library( # Sets the name of the library.
        native-lib

        # Sets the library as a shared library.
        SHARED

        # Provides a relative path to your source file(s).
        ${game_SRC})

#find_library(box2D-lib Box2D)
target_link_libraries(native-lib Box2D)

# Searches for a specified prebuilt library and stores the path as a
# variable. Because CMake includes system libraries in the search path by
# default, you only need to specify the name of the public NDK library
# you want to add. CMake verifies that the library exists before
# completing its build.

find_library( # Sets the name of the path variable.
        log-lib

        # Specifies the name of the NDK library that
        # you want CMake to locate.
        log)

# Specifies libraries CMake should link to your target library. You
# can link multiple libraries, such as libraries you define in this
# build script, prebuilt third-party libraries, or system libraries.


target_link_libraries( # Specifies the target library.
        native-lib

        # Links the target library to the log library
        # included in the NDK.
        ${log-lib})

find_library(gles-lib GLESv2)
target_link_libraries(native-lib ${gles-lib})
