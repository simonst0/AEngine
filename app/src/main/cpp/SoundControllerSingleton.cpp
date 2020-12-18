
#include "SoundControllerSingleton.h"

void SoundControllerSingleton::Initialize(jobject activity, jmethodID playSound_method, jmethodID loadSound_method)
{
    this->activity = activity;
    this->playSound_method = playSound_method;
    this->loadSound_method = loadSound_method;
}

void SoundControllerSingleton::LoadSound(JNIEnv* env, std::string path, std::string soundName)
{
    jstring jfilename = env->NewStringUTF(path.c_str());
    int res = env->CallIntMethod(activity, loadSound_method, jfilename);
    env->DeleteLocalRef(jfilename);
    Sounds[soundName] = res;
}

void SoundControllerSingleton::PlaySound(std::string soundName)
{
    if(Sounds.count(soundName) >= 1)
        ActivatedSounds.push(Sounds[soundName]);
}

void SoundControllerSingleton::WorkSoundQueue(JNIEnv *env)
{
    while(!ActivatedSounds.empty())
    {
        env->CallVoidMethod(activity, playSound_method, ActivatedSounds.front());
        ActivatedSounds.pop();
    }
}
