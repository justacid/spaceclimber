#ifndef SOUND_MANAGER_H
#define SOUND_MANAGER_H

#include <SFML/Audio/Music.hpp>
#include <SFML/Audio/SoundBuffer.hpp>
#include <SFML/Audio/Sound.hpp>
#include <unordered_map>
#include <memory>
#include <string>

enum class MusicType
{
    MUSIC_TITLE,
    MUSIC_GAME_FAST,
    MUSIC_GAME_OVER
};

class SoundManager 
{
public:
    static SoundManager& instance()
    {
        static SoundManager instance;
        return instance;
    }

    SoundManager(const SoundManager&) = delete;
    void operator=(const SoundManager&) = delete;

    void playMusic(MusicType music);
    void playSound(const std::string& soundName);

private:
    SoundManager();

    sf::Music* bgMusic;
    std::unordered_map<std::string, std::unique_ptr<sf::Sound>> mSoundCache;
};
#endif
