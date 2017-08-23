#include "Animation.h"

Animation::Animation() : 
    mCurrentFrame(0),
    mIsPlaying(false),
    mLooping(false),
    mTime(0)
{ 
}

Animation::Animation(const sf::Texture& texture, bool loop) :
    mTexture(&texture),
    mCurrentFrame(0),
    mIsPlaying(false),
    mLooping(loop),
    mTime(0)
{ 
}

Animation::Frame::Frame(const sf::IntRect& subRect, const float& displayTime) :
    mDisplayTime(displayTime),
    mSubRect(subRect)
{
}

void Animation::setTexture(const sf::Texture& texture)
{
    mTexture = &texture;
}

void Animation::setLoop(bool loop)
{
    mLooping = loop;
}

void Animation::addFrame(const sf::IntRect& subRect, const float& displayTime)
{
    mFrames.push_back(Frame(subRect, displayTime));
}

void Animation::apply(sf::Sprite& sprite)
{
    if (!mFrames.empty())
    {
        sprite.setTexture(*mTexture, true);
        sprite.setTextureRect(mFrames[0].mSubRect);
        mSprites.push_back(&sprite);
    }                    
}

void Animation::play()
{
    mIsPlaying = true;
}

void Animation::pause()
{
    mIsPlaying = false;
}

void Animation::stop()
{
    mIsPlaying = false;
    mCurrentFrame = 0;
    updateTextureRects();
}

void Animation::update(float time)
{
    if (!mIsPlaying || mFrames.empty())
        return;
        
    if ((time - mTime) > mFrames[mCurrentFrame].mDisplayTime)
    {                                    
        mCurrentFrame++;
                       
        if (mCurrentFrame >= mFrames.size())
        {
            if (!mLooping)
            {
                mIsPlaying = false;
                return;
            }
                  
            mCurrentFrame = 0;             
        }
                            
        updateTextureRects();

        mTime = time;
    }       
}

void Animation::updateTextureRects()
{
    for (unsigned int i = 0; i < mSprites.size(); ++i)
        mSprites[i]->setTextureRect(mFrames[mCurrentFrame].mSubRect);
}
