#ifndef GHOST_TIME_TABLE_H
#define GHOST_TIME_TABLE_H


//WHAT:
//A class that manages and provides ongoing modes' phase times.

//HOW:
//Two main modes of the game - chase mode and scatter mode;
//The game is always at one of these two states, unless frighten mode is active;
//Every game level has 4 scatter phases and 4 chase phases that interchange during the game;
//The last phase in order is chase and lasts indefinitely;
//The time table returns how long the current phase should last,
//based on current game level and mode.

//USE:
//Get chasePhaseTime() or scatterPhaseTime() for external timers to work with;
//When timers reach that value, update phase times;
//reset() and updateLevel() after one round.


class GhostTimeTable
{
public:
	GhostTimeTable();
	~GhostTimeTable();

	//Update phase times after one phase ends
	void updatePhaseScatter();
	void updatePhaseChase();

	//Update current level
	void updateLevel(int level);

	//Reset both phases back to 1
	void reset();

	//Return current phase time based on level
	float chasePhaseDuration();
	float scatterPhaseDuration();
	float frightPhaseDuration();

	//Get phase counters for mode check
	int getScatterCounter() const;
	int getChaseCounter() const;

private:
	int current_level_;
	int current_scatter_phase_;
	int current_chase_phase_;
};

#endif //GHOST_TIME_TABLE_H
