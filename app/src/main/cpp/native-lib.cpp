#include <jni.h>
#include <GLES2/gl2.h>
#include <android/input.h>

#define STB_IMAGE_IMPLEMENTATION

#include <cstdarg>

#include <vector>
#include <functional>
#include <string>
#include <thread>
#include <deque>
#include "Util.h"
#include "Scene.h"
#include <chrono>
#include "GameObjectFactory.h"
#include "SoundControllerSingleton.h"
#include <strstream>
#include "TextureLoader.h"
#include "TileMap.h"
#include "ParticleRendererSingleton.h"

// "Global state"
static  struct {
    // Global reference zum "Activity"-Objekt
    jobject activity;
    jmethodID setDebugText_method;

    struct {
        std::chrono::time_point<std::chrono::steady_clock> started;
        int frames;
        float current;
    } fps;

    // Position des letzten Touch-Events
    struct {
        float x;
        float y;
    } touch;

    // Aktuellstes Reading des Sensors
    struct {
        float x;
        float y;
        float z;
    } sensor;

    // Größe des sichtbaren Bereichs
    int width;
    int height;

    Scene* scene;
    GameObjectFactory* Factory;
    GameObject* Player;
    TextureLoader* TexLoader;
    TileMap* Map;
    bool ignoreKill = false;

} g;

struct TouchEvent {
    TouchEvent(int action, float x, float y, int finger) : action(action), x(x), y(y), finger(finger) {}

    int action;
    float x;
    float y;
    int finger;
};

struct TouchQueue {
    TouchQueue() = default;

    void
    append(int action, float x, float y, int finger)
    {
        std::lock_guard<std::mutex> lock(mutex);
        queue.emplace_front(action, x, y, finger);
    }

    void
    process(std::function<void(const TouchEvent &)> handler)
    {
        std::lock_guard<std::mutex> lock(mutex);
        while (!queue.empty()) {
            handler(queue.back());
            queue.pop_back();
        }
    }

    std::mutex mutex;
    std::deque<TouchEvent> queue;
};

static TouchQueue
g_touch_queue;

void
set_debug_text(JNIEnv *env, const char *debugText)
{
    jstring jdebugText = env->NewStringUTF(debugText);
    env->CallVoidMethod(g.activity, g.setDebugText_method, jdebugText);
    env->DeleteLocalRef(jdebugText);
}

extern "C"
JNIEXPORT void JNICALL
Java_local_fhs_mygame_GameRenderer_drawFrame(JNIEnv *env, jobject instance)
{
    // Touch-Events, die seit dem letzten Frame passiert sind, verarbeiten
    g_touch_queue.process([env] (const TouchEvent &event) {
        switch (event.action) {
            case AMOTION_EVENT_ACTION_DOWN:
                break;
            case AMOTION_EVENT_ACTION_MOVE:
                // TODO: Hier etwas sinnvolleres machen
                g.touch.x = event.x;
                g.touch.y = event.y;
                g.Player->GetComponent<PlayerComponent>()->Accelerate();
                break;
            case AMOTION_EVENT_ACTION_UP:
                // TODO: Hier etwas sinnvolleres machen
                break;
            case AMOTION_EVENT_ACTION_CANCEL:
                // TODO: Hier etwas sinnvolleres machen
                break;
            default:
                log_error("Invalid motion event action: %d", event.action);
                break;
        }
    });


    g.fps.frames++;

    auto now = std::chrono::steady_clock::now();
    float diff = std::chrono::duration_cast<std::chrono::milliseconds>(now - g.fps.started).count();

    float DeltaTime = diff/1000.0f;
    g.scene->Update(DeltaTime);

    if (diff > 500) {
        g.fps.current = (float)g.fps.frames * 1000.f / diff;
        g.fps.frames = 0;
        g.fps.started = now;

        char *tmp;
        asprintf(&tmp, "%5.2f FPS", g.fps.current);
        set_debug_text(env, tmp);
        free(tmp);
    }
    glClear(GL_COLOR_BUFFER_BIT);
    SpriteRendererSingleton& SpriteRendererReference = SpriteRendererSingleton::instance();
    SpriteRendererReference.PreRender();
    SpriteRendererReference.Render();
    SpriteRendererReference.PostRender();
    ParticleRendererSingleton& ParticleRendererReference = ParticleRendererSingleton::instance();
    ParticleRendererReference.PreRender();
    ParticleRendererReference.Render();
    ParticleRendererReference.PostRender();
    SoundControllerSingleton::instance().WorkSoundQueue(env);
    PlayerComponent* Player = g.Player->GetComponent<PlayerComponent>();
    Player->SetOrientation(b2Vec2(g.sensor.x, g.sensor.y));
}

extern "C"
JNIEXPORT void JNICALL
Java_local_fhs_mygame_GameRenderer_surfaceCreated(JNIEnv *env, jobject instance)
{
    SpriteRendererSingleton::instance().Initialize(env);
    ParticleRendererSingleton::instance().Initialize(env);
    g.TexLoader->LoadTextures(env);
}

extern "C"
JNIEXPORT void JNICALL
Java_local_fhs_mygame_GameRenderer_surfaceChanged(JNIEnv *env, jobject instance,
                                                      jint width, jint height)
{
    SpriteRendererSingleton::instance().OnSurfaceChanged();
    g.width = width;
    g.height = height;
}

GameObject* MakeBoxObject(b2Vec2 position, float width, float height, Color color, float mass = -1)
{
    GameObject* object = g.Factory->GenerateDefaultGameObject();
    BodyComponent* body = object->GetComponent<BodyComponent>();
    SpriteComponent* sprite = object->GetComponent<SpriteComponent>();
    body->position = position;
    if(mass < 0)
        body->type = b2_staticBody;
    else
        body->type = b2_dynamicBody;
    sprite->SpriteColor = color;
    sprite->Width = width;
    sprite->Height = height;
    g.scene->AddGameObject(object);
    return object;
}

void MakeBoxFixture(GameObject* target, b2Vec2 fixturePosition, float fixtureWidth, float fixtureHeight, float mass = -1)
{
    FixtureComponent* fixture = target->GetComponent<FixtureComponent>();
    fixture->fixtureData.type = Box;
    fixture->fixtureData.mass = mass;
    fixture->fixtureData.width = fixtureWidth;
    fixture->fixtureData.height = fixtureHeight;
    fixture->fixtureData.position = fixturePosition;
}

void MakeCircleFixture(GameObject* target, b2Vec2 fixturePosition, float radius, float mass = -1)
{
    FixtureComponent* fixture = target->GetComponent<FixtureComponent>();
    fixture->fixtureData.type = Circle;
    fixture->fixtureData.mass = mass;
    fixture->fixtureData.radius = radius;
    fixture->fixtureData.position = fixturePosition;
}

void MakeRock(b2Vec2 position, float width, float height)
{
    GameObject* Rock = g.Factory->NewGameObject();
    g.Factory->AddBodyComponent(Rock);
    BodyComponent* Body = Rock->GetComponent<BodyComponent>();
    Body->position = position;
    g.Factory->AddSpriteComponent(Rock);
    SpriteComponent* Sprite = Rock->GetComponent<SpriteComponent>();
    Sprite->Height = width;
    Sprite->Width = height;
    Sprite->SpriteTexture = g.TexLoader->GetTextureFromFile("rock3");
    g.Factory->AddFixtureComponent(Rock);
    MakeCircleFixture(Rock, b2Vec2(0,0), (width/2) * 0.8f);
    Rock->NameTag = "Kill";
    g.scene->AddGameObject(Rock);
}

extern "C"
JNIEXPORT void JNICALL
Java_local_fhs_mygame_MainActivity_nativeInit
  (JNIEnv *env, jobject activity)
{
    g.activity = env->NewGlobalRef(activity);
    jclass Activity_class = env->GetObjectClass(g.activity);
    g.setDebugText_method = env->GetMethodID(Activity_class, "setDebugText", "(Ljava/lang/String;)V");
    jmethodID playSound_method = env->GetMethodID(Activity_class, "playSound", "(I)V");
    jmethodID loadSound_method = env->GetMethodID(Activity_class, "loadSound", "(Ljava/lang/String;)I");
    env->DeleteLocalRef(Activity_class);

    SoundControllerSingleton::instance().Initialize(g.activity, playSound_method, loadSound_method);
    g.TexLoader = new TextureLoader();

    SoundControllerSingleton::instance().LoadSound(env, "goal.ogg", "goal");
    SoundControllerSingleton::instance().LoadSound(env, "intro.ogg", "intro");
    SoundControllerSingleton::instance().LoadSound(env, "crash.ogg", "crash");

    g.fps.started = std::chrono::steady_clock::now();
    g.fps.frames = 0;
    g.fps.current = 0;

    g.scene = new Scene(b2Vec2(0.0f, 0.0f));

    //Generate GameObjects here
    g.Factory = new GameObjectFactory(20);

    //Background
    GameObject* Background = g.Factory->NewGameObject();
    g.Factory->AddBodyComponent(Background);
    BodyComponent* Body = Background->GetComponent<BodyComponent>();
    Body->position = b2Vec2(1080/2,1920/2);
    g.Factory->AddSpriteComponent(Background);
    SpriteComponent* Sprite = Background->GetComponent<SpriteComponent>();
    Sprite->Height = 1920;
    Sprite->Width = 1080;
    Sprite->SpriteTexture = g.TexLoader->GetTextureFromFile("background", ".jpg");
    g.scene->AddGameObject(Background);


    //TileMap
    std::vector<int> tileIndices =
            {
                    0,62,26,0,0,0,0,0,0,0,
                    0,280,171,258,258,258,258,258,209,0,
                    0,280,262,262,262,262,262,262,171,209,
                    0,226,261,261,261,261,261,154,262,244,
                    227,258,258,258,258,258,258,153,262,244,
                    280,262,262,262,262,262,262,262,172,208,
                    280,262,172,261,261,261,261,261,208,0,
                    280,262,244,0,0,0,0,0,0,0,
                    280,262,171,258,258,258,258,258,258,209,
                    280,262,262,262,262,262,262,262,262,244,
                    226,261,261,261,261,261,154,262,262,244,
                    0,0,0,0,0,227,153,262,172,208,
                    0,0,0,0,0,280,262,262,244,0,
                    0,0,0,0,0,280,262,262,171,209,
                    0,0,0,0,0,226,154,262,262,244,
                    0,0,0,227,258,258,153,262,172,208,
                    227,258,258,153,262,262,262,172,208,0,
                    280,262,262,262,172,261,261,208,0,0,
                    226,261,261,261,208,0,0,0,0,0,
                    0,0,0,0,0,0,0,0,0,0
            };
    g.Map = new TileMap(tileIndices, 10, 20, 18, 18, 100, b2Vec2(49, -180));
    g.Map ->SetTileTexture(g.TexLoader->GetTextureFromFile("spritesheet_tiles"));

    //Add Fixtures to Tiles here
    //Half Tiles
    g.Map->AddFixtureDataToTile(261, FixtureData(Box, b2Vec2(0,-0.4f), 1, 0.2f));
    g.Map->AddFixtureDataToTile(258, FixtureData(Box, b2Vec2(0,0.4f), 1, 0.2f));
    g.Map->AddFixtureDataToTile(244, FixtureData(Box, b2Vec2(0.4f,0), 0.2f, 1));
    g.Map->AddFixtureDataToTile(280, FixtureData(Box, b2Vec2(-0.4f,0), 0.2f, 1));


    //fourth Tiles
    g.Map->AddFixtureDataToTile(153, FixtureData(Box, b2Vec2(-0.4f,0.4f), 0.2f, 0.2f));
    g.Map->AddFixtureDataToTile(154, FixtureData(Box, b2Vec2(-0.4f,-0.4f), 0.2f, 0.2f));
    g.Map->AddFixtureDataToTile(171, FixtureData(Box, b2Vec2(0.4f,0.4f), 0.2f, 0.2f));
    g.Map->AddFixtureDataToTile(172, FixtureData(Box, b2Vec2(0.4f,-0.4f), 0.2f, 0.2f));

    // 3/4 Tiles
    float degToRad = 0.01745329251f;
    g.Map->AddFixtureDataToTile(226, FixtureData(Box, b2Vec2(-0.33f, -0.33f), 1.5f, 0.33f, 315 * degToRad));
    g.Map->AddFixtureDataToTile(227, FixtureData(Box, b2Vec2(-0.33f,0.33f), 1.5f, 0.33f, 225 * degToRad));
    g.Map->AddFixtureDataToTile(209, FixtureData(Box, b2Vec2(0.33f,0.33f), 1.5f, 0.33f, 135 * degToRad));
    g.Map->AddFixtureDataToTile(208, FixtureData(Box, b2Vec2(0.33f,-0.33f), 1.5f, 0.33f, 45 * degToRad));


    g.Map->GenerateObjects();
    g.Map->RegisterTilesToScene(g.scene);


    //Player
    GameObject* Player = MakeBoxObject(b2Vec2(150, 150), 60, 110, Color(1, 1, 1, 1), 10);
    MakeBoxFixture(Player, b2Vec2(0,0), 60, 110, 50);
    g.Factory->AddPlayerComponent(Player);
    BodyComponent* PlayerBody = Player->GetComponent<BodyComponent>();
    PlayerBody->linearDamping = 0.5f;
    Player->NameTag = "Player";
    Player->GetComponent<SpriteComponent>()->SpriteTexture = g.TexLoader->GetTextureFromFile("car");
    g.Factory->AddParticleSystemComponent(Player);
    ParticleSystemComponent* p = Player->GetComponent<ParticleSystemComponent>();
    p->SetActive(false);
    p->MaxParticleCount = 80000;
    p->minSize = 16;
    p->maxSize = 32;
    p->minVelocity = -10000;
    p->maxVelocity = 10000;
    p->texture = g.TexLoader->GetTextureFromFile("exclamation");
    ParticleRendererSingleton::instance().AddParticleSystem(p);
    g.Player = Player;

    //Goal
    GameObject* Goal = MakeBoxObject(b2Vec2(255, 1875), 180, 50, Color(0,1,1, 0.2f));
    MakeBoxFixture(Goal, b2Vec2(0,50), 170, 80);
    Goal->GetComponent<FixtureComponent>()->IsTrigger = true;
    Goal->NameTag = "Goal";

    MakeRock(b2Vec2(450, 1200), 300, 300);
    MakeRock(b2Vec2(1000, 680), 220, 220);
    MakeRock(b2Vec2(800, 200), 190, 190);
    MakeRock(b2Vec2(650, 1550), 250, 250);

    g.scene->Initialize();
    SoundControllerSingleton::instance().PlaySound("intro");
}

extern "C"
JNIEXPORT void JNICALL
Java_local_fhs_mygame_MainActivity_nativeDestroy
  (JNIEnv *env, jobject)
{
    if(g.ignoreKill)
        return;
    env->DeleteGlobalRef(g.activity);
    g.activity = nullptr;
    delete g.scene;
    g.scene = nullptr;
    delete g.Factory;
    g.Factory = nullptr;
    delete g.TexLoader;
    g.TexLoader = nullptr;
    log_debug("Destroy");
}

extern "C"
JNIEXPORT void JNICALL
Java_local_fhs_mygame_MainActivity_nativeTouch
  (JNIEnv *, jobject, jint action, jfloat x, jfloat y, jint finger)
{
    g_touch_queue.append(action, x, y, finger);
}

extern "C"
JNIEXPORT void JNICALL
Java_local_fhs_mygame_MainActivity_nativeAccelerometer(JNIEnv *env, jobject instance, jfloat x,
                                                           jfloat y, jfloat z)
{
    // Achtung! Kann von einem anderen Thread kommen -- bitte korrekt behandeln (threadsafe queue
    // oder mutex)
    g.sensor.x = x;
    g.sensor.y = y;
    g.sensor.z = z;
}

extern "C"
JNIEXPORT void JNICALL
Java_local_fhs_mygame_MainActivity_nativeResume
        (JNIEnv *env, jobject instance)
{
    g.scene->Resume();
    g.ignoreKill = false;
    log_debug("Resume");
}

extern "C"
JNIEXPORT void JNICALL
Java_local_fhs_mygame_MainActivity_nativePause
        (JNIEnv *env, jobject instance)
{
    g.scene->Pause();
    log_debug("Pause");
}

extern "C"
JNIEXPORT void JNICALL
Java_local_fhs_mygame_MainActivity_nativeOnBackPressed(JNIEnv* env, jobject instance)
{
    g.ignoreKill = true;
    log_debug("Back Pressed");
}