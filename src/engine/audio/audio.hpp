#pragma once

#include <iostream>
#include <unordered_map>

#include <bass/bass.h>
#include <bass_fx/bass_fx.h>

//#include "../filesystem/filesystem.hpp"
#include <filesystem>
namespace fs = std::filesystem;

class Sound {
    HSAMPLE file;
    HCHANNEL channel;
public:
    Sound(const fs::path& path);

    ~Sound();

    HCHANNEL getChannel();

    void play();
};

class Sounds {
    std::unordered_map<std::string, std::unique_ptr<Sound>> sounds;
public:
    Sounds() = default;

    void reset();

    void load(const std::string& key, const fs::path& path);

    void setVolume(float volume);

    void playSound(const std::string& key);
};

class Music {
    HSTREAM stream;
    DWORD fxStream;
    int length;
    int pos;

    int get_length() {
        return static_cast<int>(
            BASS_ChannelBytes2Seconds(
                stream,
                BASS_ChannelGetLength(
                    stream,
                    BASS_POS_BYTE
                )
            ) * 1000);
    };

    int get_pos() {
        return static_cast<int>(
            BASS_ChannelBytes2Seconds(
                stream,
                BASS_ChannelGetPosition(
                    stream,
                    BASS_POS_BYTE
                )
            ) * 1000);
    };
public:
    Music() = default;

    void reset();

    void load(const fs::path& path);

    int GetPos();

    int GetLength();

    void ResetPos();

    void SetPos(double pos);

    void Play();

    void Pause();

    void Stop();

    void SetVolume(float volume);

    bool checkActive();
};

class Audio {
    Sounds sounds;
    Music music;
    float musicVolume = .4f;
    float soundsVolume = .3f;
    bool pausedAudio = false;
public:
    Audio();
    ~Audio();

    // Sounds
    void playSound(const std::string& key);

    void setSoundsVolume(float volume);

    void upSoundsVol();

    void downSoundsVol();

    float getSoundVolume();

    // Music
    void resetPos();

    void setPos(double pos);

    void loadAudio(const fs::path& path);

    void playAudio();

    void unPauseAudio();

    void pauseAudio();

    void stopAudio();

    void setAudioVolume(float volume);

    void upAudioVol();

    void downAudioVol();

    int getMusicPos();

    float getMusicVolume();

    bool checkMusicIsActive();

    bool paused();
};
