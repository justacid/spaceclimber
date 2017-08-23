#ifndef RESOURCE_MANAGER_H
#define RESOURCE_MANAGER_H

#include <unordered_map>
#include <vector>
#include <string>
#include <memory>

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Image.hpp>
#include <SFML/Audio/Music.hpp>
#include <SFML/Audio/SoundBuffer.hpp>

class ResourceManager
{
public:
    static ResourceManager& instance()
    {
        static ResourceManager instance;
        return instance;
    }

    ResourceManager(const ResourceManager&) = delete;
    void operator=(const ResourceManager&) = delete;

    sf::Texture& getTexture(const std::string& name);
    sf::Font& getFont(const std::string& name);
    sf::Image& getImage(const std::string& name);
    sf::Music& getMusic(const std::string &name);
    sf::SoundBuffer& getSoundBuffer(const std::string &name);

private:
    template <typename T>
    using ResourceMap = std::unordered_map<std::string, std::unique_ptr<T>>;
    using Buffer = std::vector<uint8_t>;

    ResourceManager();
    bool readFile(const std::string& name, Buffer& out, size_t& length);

    std::vector<std::vector<uint8_t>> mBufferedData;
    ResourceMap<sf::Texture> mTextureCache;
    ResourceMap<sf::Font> mFontCache;
    ResourceMap<sf::Music> mMusicCache;
    ResourceMap<sf::SoundBuffer> mSoundCache;
    ResourceMap<sf::Image> mImageCache;
};

#endif
