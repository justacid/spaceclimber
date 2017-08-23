#include "ResourceManager.h"

#include <physfs.h>
#include <iostream>

ResourceManager::ResourceManager()
{
    PHYSFS_addToSearchPath("assets.zip", 1);
}

sf::Texture& ResourceManager::getTexture(const std::string& name)
{
    if (mTextureCache.find(name) == mTextureCache.end())
    {
        mTextureCache[name] = std::make_unique<sf::Texture>();

        size_t length = 0;
        Buffer buffer;

        if (readFile(name, buffer, length))
            mTextureCache[name]->loadFromMemory(&buffer[0], length);
        else
            std::cerr << "File '" << name << "' doesn't exist." << std::endl;
    }

    return *mTextureCache[name].get();
}

sf::Font& ResourceManager::getFont(const std::string& name)
{
    if (mFontCache.find(name) == mFontCache.end())
    {
        mFontCache[name] = std::make_unique<sf::Font>();

        size_t length = 0;
        mBufferedData.push_back(Buffer());

        if (readFile(name, mBufferedData.back(), length))
            mFontCache[name]->loadFromMemory(&mBufferedData.back()[0], length);
        else
            std::cerr << "File '" << name << "' doesn't exist." << std::endl;
    }

    return *mFontCache[name].get();
}

sf::Image& ResourceManager::getImage(const std::string &name)
{
    if (mImageCache.find(name) == mImageCache.end())
    {
        mImageCache[name] = std::make_unique<sf::Image>();

        size_t length = 0;
        Buffer buffer;

        if (readFile(name, buffer, length))
            mImageCache[name]->loadFromMemory(&buffer[0], length);
        else
            std::cerr << "File '" << name << "' doesn't exist." << std::endl;
    }

    return *mImageCache[name].get();
}

sf::Music& ResourceManager::getMusic(const std::string &name)
{
    if (mMusicCache.find(name) == mMusicCache.end())
    {
        mMusicCache[name] = std::make_unique<sf::Music>();

        size_t length = 0;
        mBufferedData.push_back(Buffer());

        if (readFile(name, mBufferedData.back(), length))
            mMusicCache[name]->openFromMemory(&mBufferedData.back()[0], length);
        else
            std::cerr << "File '" << name << "' doesn't exist." << std::endl;
    }

    return *mMusicCache[name].get();
}

sf::SoundBuffer& ResourceManager::getSoundBuffer(const std::string &name)
{
    if (mSoundCache.find(name) == mSoundCache.end())
    {
        mSoundCache[name] = std::make_unique<sf::SoundBuffer>();

        size_t length = 0;
        Buffer buffer;

        if (readFile(name, buffer, length))
            mSoundCache[name]->loadFromMemory(&buffer[0], length);
        else
            std::cerr << "File '" << name << "' doesn't exist." << std::endl;
    }

    return *mSoundCache[name].get();
}

bool ResourceManager::readFile(const std::string &name, Buffer& out, size_t& length)
{
    if (PHYSFS_exists(name.c_str()))
    {
        auto file = PHYSFS_openRead(name.c_str());
        length = static_cast<size_t>(PHYSFS_fileLength(file));
        out.reserve(length);
        PHYSFS_read(file, &out[0], 1, static_cast<PHYSFS_uint32>(length));
        PHYSFS_close(file);

        return true;
    }

    return false;
}
