#include "SoundManager.h"
#include "ResourceManager.h"
#include <SFML/Audio/Listener.hpp>

SoundManager::SoundManager()
{
    sf::Listener::setGlobalVolume(20.f);
}

void SoundManager::playMusic(MusicType music)
{
    std::string file = "";
    switch (music)
    {
        case MusicType::MUSIC_TITLE:
            file = "music/title_music.wav";
            break;

        case MusicType::MUSIC_GAME_FAST:
            file = "music/game_music_fast.wav";
            break;

        case MusicType::MUSIC_GAME_OVER:
            file = "music/gameover_music.wav";
            break;
    }

    static bool setOnce = false;
    if (setOnce) bgMusic->stop();

    bgMusic = &ResourceManager::instance().getMusic(file);
    bgMusic->setLoop(true);
    bgMusic->play();
    setOnce = true;
}

void SoundManager::playSound(const std::string& name)
{
    if (mSoundCache.find(name) == mSoundCache.end())
        mSoundCache[name] = std::make_unique<sf::Sound>(ResourceManager::instance().getSoundBuffer(name));

    mSoundCache[name]->setVolume(sf::Listener::getGlobalVolume());
    mSoundCache[name]->play();
}
