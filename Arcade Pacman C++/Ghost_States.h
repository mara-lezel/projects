#ifndef GHOST_STATES_H
#define GHOST_STATES_H


//A class that monitors different ghost states.
class GhostStates
{
public:
	enum class State
	{
		CHASE,
		SCATTER,
		FRIGHTENED,
		EATEN,
		IN_CAGE,
		IN_TRANSITION_FROM_CAGE,
		IN_TRANSITION_TO_CAGE
	};

	void setState(State state);
	State getState() const;
	State getPreviousState() const;

	//Reset ghost state related properties
	void resetState();

protected:
	GhostStates();
	GhostStates(State state);
	virtual ~GhostStates();

protected:
	State current_state_;
	State previous_state_;
};

#endif //GHOST_STATES_H
