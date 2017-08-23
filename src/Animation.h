/// @file
/// @brief Class Animation

#ifndef ANIMATION_H
#define	ANIMATION_H

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/Sprite.hpp>

#include <vector>
#include <cstddef>

/** @brief Handles animations
 * 
 * @details Animations consist of frames which contain the sub rectangle of the sprite sheet
 * and the time to display the current frame.
 * 
 * Usage example:
 * @code
 * sf::Texture texture;
 * texture.loadFromFile("player.png");
 * 
 * Animation animation(texture);
 * animation.addFrame(sf::IntRect(0,0,50,50), 0.5);
 * 
 * sf::Sprite sprite;
 * animation.apply(sprite);
 * animation.play();
 * 
 * // [...] in the render code:
 * animation.update(clock.getElapsedTime.asSeconds());
 * window.draw(sprite);
 * @endcode
 * */
class Animation
{
    public:

        /// @brief Default constructor
        Animation();
        /**
         * @brief Constructor which sets a texture and specifies whether the
         * the Animation shall loop
         * @param texture the texture from where the frames are to be taken
         * @param loop specifies whether the animation shall loop
         * */
        Animation(const sf::Texture& texture, bool loop = true);
        /**
         * @brief Sets the texture
         * */
        void setTexture(const sf::Texture& texture);
        /**
         * @brief Set whether the animation shall be looped
         * */
        void setLoop(bool loop = true);
        /**
         * @brief Adds a frame to the animation
         * @details Adds a frame to the animation, based on the subrect and
         * displayTime specified.
         * @param subRect Rectangle which specifies the source of the frame on the texture
         * @param displayTime the time the frame shall be display in seconds
         * */
        void addFrame(const sf::IntRect& subRect, const float& displayTime);
        /**
         * @brief Apply the animation to a sprite
         * @details This function connects a sprite with a animation. You can connect
         * multiple sprites, just call this function once for each sprite. addFrame() must
         * be called at least once before calling apply().
         * @param sprite The sprite to apply the animation to
         * */
        void apply(sf::Sprite& sprite);
         /**
         * @brief Play the animation
         * @details Plays the animation. Has no effect if already playing. 
         * */
        void play();
         /**
         * @brief Pause the animation.
         * @details Pauses the animation. Has no effect if already paused or the animation is
         * finished. In order to replay a finished animation you have to call stop() beforehand.
         * */
        void pause();
         /**
         * @brief Stop the animation
         * @details Stops the animation and resets to the first frame, works even while paused.
         * Has no effect if already stopped. 
         * */
        void stop();
        /**
        * @brief Update function
        * @details This is the most important function of this class. It gets passed the elapsed time
        * in seconds and handles the animating. Call it once each frame! 
        * @param time The elapsed game time in seconds.
        * */
        void update(float time);
            
    private:
        
        void updateTextureRects();

        class Frame
        {
            public:
                
                Frame(const sf::IntRect& subrect, const float& displayTime);
                float mDisplayTime;
                sf::IntRect mSubRect;
        };

        std::vector<Frame> mFrames;
        std::vector<sf::Sprite*> mSprites;
        const sf::Texture* mTexture;

        std::size_t mCurrentFrame;
        bool mIsPlaying;
        bool mLooping;
        float mTime;
};

#endif
