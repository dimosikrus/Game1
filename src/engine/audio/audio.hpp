#pragma once

#include <iostream>
#include <optional>
#include <unordered_map>
#include <memory>

#include <bass/bass.h>
#include <bass_fx/bass_fx.h>

#include "../filesystem/filesystem.hpp"

class Sound {
    HSAMPLE file;
    HCHANNEL channel;
public:
    Sound(const fs::path& path) {
        if (!chechFileExist(path)) 
            std::cerr << "Error load Sound: " << path << '\n';
        file = BASS_SampleLoad(FALSE, path.c_str(), 0, 0, 3, BASS_SAMPLE_OVER_POS);
        channel = BASS_SampleGetChannel(file, FALSE);
    }

    ~Sound() { BASS_SampleFree(file); }

    HCHANNEL getChannel() {
        return channel;
    }

    void play() {
        BASS_ChannelPlay(channel, TRUE);
    }
};

class Sounds {
    std::unordered_map<std::string, std::unique_ptr<Sound>> sounds;
public:
    Sounds() = default;

    void reset() {
        sounds.clear();
    }

    void load(const std::string& key, const fs::path& path) {
        sounds.emplace(key, std::make_unique<Sound>(path));
    }

    void setVolume(float volume) {
        for (auto& [_, sound] : sounds) {
            BASS_ChannelSetAttribute(sound->getChannel(), BASS_ATTRIB_VOL, volume);
        }
    }

    void playSound(const std::string& key) {
        if(sounds.find(key) != sounds.end()) {
            sounds.at(key)->play();
        };
    }
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

    void reset() {
        BASS_StreamFree(stream);
    }

    void load(const fs::path& path) {
        stream = BASS_StreamCreateFile(FALSE, path.c_str(), 0, 0, BASS_STREAM_AUTOFREE);
        this->length = get_length();
    }

    int GetPos() { return get_pos(); };

    int GetLength() { return get_length(); };

    void ResetPos() {
        BASS_ChannelSetPosition(stream, 0, BASS_POS_BYTE);
    }

    void SetPos(double pos) {
        BASS_ChannelSetPosition(stream, BASS_ChannelSeconds2Bytes(stream, pos), BASS_POS_BYTE);
    }

    void Play() {
        BASS_ChannelPlay(stream, FALSE);
    }

    void Pause() {
        BASS_ChannelPause(stream);
    }

    void Stop() {
        BASS_ChannelStop(stream);
        reset();
        length = 0;
    }

    void SetVolume(float volume) {
        BASS_ChannelSetAttribute(stream, BASS_ATTRIB_VOL, volume);
    }

    bool checkActive() {
        return BASS_ChannelIsActive(stream);
    }
};

class Audio {
private:
    Sounds sounds;
    Music music;
    float musicVolume = .4f;
    float soundsVolume = .3f;
    bool pausedAudio = false;
public:
    Audio() {
        if(!BASS_Init(-1, 44100, 0, nullptr, nullptr)) 
          std::cerr << "Ошибка инициализации BASS: " << BASS_ErrorGetCode() << '\n';
    }
    ~Audio() { BASS_Free(); }

    // Sounds
    void playSound(const std::string& key) {
        sounds.playSound(key);
    }

    void setSoundsVolume(float volume) {
        soundsVolume = volume;
        sounds.setVolume(soundsVolume);
    }

    void upSoundsVol() {
        if(soundsVolume <= 1.f) {
            soundsVolume += .1f;
            sounds.setVolume(soundsVolume);
        }
        else soundsVolume = 1.f;
    }

    void downSoundsVol() {
        if(soundsVolume >= 0) {
            soundsVolume -= .1f;
            sounds.setVolume(soundsVolume);
        }
        else soundsVolume = 0;
    }

    // Music
    void resetPos() {
        music.ResetPos();
    }

    void setPos(double pos) {
        music.SetPos(pos);
    }


    void loadAudio(const fs::path& path) {
        music.load(path);
        music.SetVolume(musicVolume);
    }

    void playAudio() {
        music.Play();
    }

    void unPauseAudio() {
        if (pausedAudio) {
            pausedAudio = false;
            music.Play();
        }
    }

    void pauseAudio() {
        if (!pausedAudio) {
            pausedAudio = true;
            music.Pause();
        }
    }

    void stopAudio() {
        music.Stop();
    }


    void setAudioVolume(float volume) {
        musicVolume = volume;
    }

    void upAudioVol() {
        if(musicVolume < 1.f) {
            musicVolume += .1f;
            music.SetVolume(musicVolume);
        }
        else musicVolume = 1.f;
    }

    void downAudioVol() {
        if(musicVolume > 0) {
            musicVolume -= .1f;
            music.SetVolume(musicVolume);
        }
        else musicVolume = 0;
    }

    int getMusicPos() { return music.GetPos(); }
    float getSoundVolume() { return soundsVolume; };
    float getMusicVolume() { return musicVolume; };
    bool checkMusicIsActive() { return music.checkActive(); }
    bool paused() { return pausedAudio; }
};
