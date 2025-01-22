#ifndef FRAME_TIMER_H
#define FRAME_TIMER_H

//WHAT:
//Timer for capping FPS using delta time.

//USE:
//start() - must call to start timer;
//update() - should be called before physics loop or rendering takes place;
//reset() - should be used after delta_time_ exceeds frame limit;
//getDeltaTime() - should be called at the end of the loop.

//EXAMPLE:
// start();
// while(running)
// {
//		update();
//		...
//		if (f_timer.getDeltaTime() >= 1.0f / FRAME_RATE)
//		{
//			loop();
//			...
//			reset();
//		}
// }


//Timer mainly used for tracking and limiting frame rate.
//Returns delta time - time between individual frames.
class FrameTimer
{
public:
	FrameTimer() :
		start_ticks_(0), elapsed_ticks_(0), delta_time_(0.0f) {}

	~FrameTimer() {}

	//Basic timer functions
	void start();
	void reset();

	//Update time elapsed since last frame (or last update() call)
	void update();

	//Returns delta time in seconds
	float getDeltaTime() const;

private:
	//Clock time at the start
	unsigned int start_ticks_;

	//Total time since timer start
	unsigned int elapsed_ticks_;

	//Time it takes to render a frame
	float delta_time_;
};

#endif //FRAME_TIMER_H
