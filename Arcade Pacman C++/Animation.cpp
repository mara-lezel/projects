#include "Animation.h"


//Get current picture for rendering
SDL_Rect* Animation::getCurrentAnimation() const
{
    return current_animation_;
}

//Which part of animation is currently loaded
int Animation::getCurrentFrame() const
{
    return (frame_ / delay_);
}

//How many frames elapsed since cycle began
//How it works: delay_ * animation_frames_ = max number of frames per cycle
int Animation::getFrameCount() const
{
    return frame_;
}

//How many frames for animation to change
int Animation::getDelay() const
{
    return delay_;
}

//Set current picture from sprite sheet
void Animation::setCurrentAnimation(SDL_Rect* animation_clip)
{
    current_animation_ = animation_clip;
}

//For skipping animations
//Cheking if requested frame total is in bounds
void Animation::setFrameCount(unsigned short int frames)
{
    if ((frames / delay_) < animation_frames_)
        frame_ = frames;
}

//Update delay and reset frame counter for safety
//Cannot be set to 0 - delay_ used for division
void Animation::setDelay(unsigned short int delay)
{
    if (delay > 0)
    {
        delay_ = delay;
        frame_ = 0;
    }
}

//Upadate frame count
//If all animation frames have looped, reset counter
//How it works: delay_ * animation_frames_ = max number of frames per cycle
void Animation::animate()
{
    ++frame_;
    if ((frame_ / delay_) == animation_frames_)
        frame_ = 0;
}
