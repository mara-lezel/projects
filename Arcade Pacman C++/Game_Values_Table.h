#ifndef GAME_VALUES_TABLE_H
#define GAME_VALUES_TABLE_H

//WHAT:
//A class returning gameplay related values based on current level.

class GameValuesTable
{
public:
	GameValuesTable();
	~GameValuesTable();

	//Pellet limits for ghosts
	int pinkyDotLimit();
	int inkyDotLimit();
	int clydeDotLimit();

	int pinkyGlobalDotLimit();
	int inkyGlobalDotLimit();
	int clydeGlobalDotLimit();

	//Blinky's elroy behaviour pellet count
	int elroyDotCount();
	int superElroyDotCount();

	//Points awarded for eating fruit
	int bonusPoints();

	//Points awarded for eating ghosts in succession
	int ghostPoints(int ghosts_eaten);

	//Update current level
	void updateLevel(int level);

private:
	int level_;
};


#endif //GAME_VALUES_TABLE_H
