#pragma once
#include <unordered_map>
#include <string>
#include <jni.h>
#include <queue>

class SoundControllerSingleton {
public:
    static SoundControllerSingleton& instance()
    {
        static SoundControllerSingleton _instance;
        return _instance;
    }
    ~SoundControllerSingleton(){};
private:
    SoundControllerSingleton(){};
    SoundControllerSingleton( const SoundControllerSingleton& );
    SoundControllerSingleton& operator = (const SoundControllerSingleton&);

public:
    void Initialize(jobject activity, jmethodID playSound_method, jmethodID loadSound_method);
    void LoadSound(JNIEnv* env, std::string path, std::string soundName);
    void WorkSoundQueue(JNIEnv* env);
    void PlaySound(std::string soundName);

    jobject activity;
    jmethodID playSound_method;
    jmethodID loadSound_method;

private:
    std::unordered_map<std::string, int> Sounds;
    std::queue<int> ActivatedSounds;

};


