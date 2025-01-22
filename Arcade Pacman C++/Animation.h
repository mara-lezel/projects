#ifndef ANIMATION_H
#define ANIMATION_H

#include <SDL.h>

//WHAT:
//Animation class that loops through sprites via pointer to sprite array.
//Animation frames - number of sprites in an animation loop.
//Frames - game loop frames.
//Delay - how many frames one part of the animation takes.
//Current animation - pointer to sprite array, an area of sprite sheet to clip.
//How it works: delay_ * animation_frames_ = max number of frames per cycle.

//USE:
//Optional: pre-set current animation with some sprite array;
//Set current animation in a loop using getCurrentFrame() as array index;
//Call animate() to update frames;
//Render from sprite sheet using getCurrentAnimation().

//IMPORTANT:
//Frame cycle (animate()) divides by delay_, therefore delay_ cannot be 0.
//Intended use is in tandem with clips - arrays with sprite image dimensions (SDL_Rect).

//Loops through sprites via pointer to sprite array.
class Animation
{
public:
    Animation()
        : animation_frames_(0), frame_(0), delay_(1), current_animation_(nullptr) {}

    Animation(unsigned short int ANIMATION_FRAMES, unsigned short int DELAY)
        : animation_frames_(ANIMATION_FRAMES), frame_(0), delay_(DELAY), current_animation_(nullptr) {}

    ~Animation() {}

    //GETTERS
    //Returns animation(SDL_Rect* object) - position on sprite sheet {x, y, w, h}
    SDL_Rect* getCurrentAnimation() const;

    //Returns current frame of the animation - animation_frames_
    int getCurrentFrame() const;

    //Returns total number of frames elapsed in the animation loop
    int getFrameCount() const;

    //Returns animation delay
    int getDelay() const;


    //SETTERS
    //Updates current animation
    void setCurrentAnimation(SDL_Rect* animation_clip);

    //Updates/manipulates frames elapsed in an animation cycle (to skip animations if needed)
    void setFrameCount(unsigned short int frames);

    //Updates animation delay, resets frame counter (cannot be set to 0)
    void setDelay(unsigned short int delay);


    //OTHER
    //Animation cycle - increases frame counter by one per call
    void animate();

private:
    //Number of pictures in an animation cycle
    unsigned short int animation_frames_;

    //Frames elapsed in an animation cycle
    unsigned short int frame_;

    //Number of frames per animation frame
    //animation_frame_ changes every <insert delay_ here> frames
    unsigned short int delay_;

    //Current picture from sprite sheet to be rendered
    SDL_Rect* current_animation_;
};

#endif //ANIMATION_H
