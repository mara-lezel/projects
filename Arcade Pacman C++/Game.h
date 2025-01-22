#ifndef PACMAN_GAME_H
#define PACMAN_GAME_H

#include "Frame_Timer.h"
#include "Timer.h"

#include "Texture.h"
#include "Animation.h"
#include "Clip_Wrapper.h"

#include "Game_Sounds.h"

#include "Speed_Table.h"
#include "Ghost_Time_Table.h"
#include "Game_Values_Table.h"

#include "Map.h"

#include "Pacman.h"
#include "Blinky.h"
#include "Pinky.h"
#include "Inky.h"
#include "Clyde.h"

#include <SDL_Mixer.h>

union SDL_Event;
struct SDL_Window;
struct SDL_Renderer;


class Game
{
public:
	Game();
	~Game();

	//Run game
	void start();

	//Initialize SDL, load game assets
	bool initialize(); 

	//Handle events - key presses
	void event(SDL_Event& e); 

	//Update game state / physics loop
	void loop(); 
	void freeze_loop();
	void scene_loop();

	//Render game objects
	void render(); 

	//Release resources, close SDL
	void close(); 

	//---------------------------------------------------------SYSTEM FUNCTIONS--------------------------------
	//---------------------------------------------------------------------------------------------------------

	//Manage game states and scenes
	void manageGameFlags();

	//Reset game elements after a life is lost
	void round_reset();

	//Reset and update game elements after completing a level
	void level_reset();

	//Arrow controlled options
	void handleMenu();

	//---------------------------------------------------------LOGIC FUNCTIONS---------------------------------
	//---------------------------------------------------------------------------------------------------------

	//Freeze frame after ghost has been eaten
	void freezeFrame();

	//Trigger 1UP after 10 000pts reached
	void countScore();

	//Track the number of consumed pellets
	void countDots();

	//Spawn bonus fruit and manage bonus fruit timer
	void handleBonusFruit(bool round_reset, bool level_reset);

	//Handle scatter/chase ghost behaviour
	void handleModeChanges(bool round_reset);

	//Release ghosts based on pellet counters or timer
	void handleInCageGhosts(bool round_reset, bool level_reset);

	//Trigger frightened state when Pacman eats an energizer
	void activateEnergizers(bool round_reset, bool level_reset);	

	//Assign state and direction to ghosts leaving cage
	void ghostTransitionToMaze(bool round_reset, bool level_reset);

	//Assign direction to ghosts getting back to cage
	void ghostTransitionToCage();

	//---------------------------------------------------------PHYSICS FUNCTIONS-------------------------------
	//---------------------------------------------------------------------------------------------------------

	//Pacman related speed check
	void handlePacmanSpeed();

	//Ghost related speed checks
	void handleBlinkySpeed();
	void handlePinkySpeed();
	void handleInkySpeed();
	void handleClydeSpeed();

	//Handle collision between Pacman and ghosts
	void handleImpact(bool round_reset);


	//---------------------------------------------------------ANIMATION FUNCTIONS-----------------------------
	//---------------------------------------------------------------------------------------------------------

	//Perform Pacman related animation changes
	void handlePacmanAnimation();

	//Perform ghost related animation changes
	void handleBlinkyAnimation();
	void handlePinkyAnimation();
	void handleInkyAnimation();
	void handleClydeAnimation();

	//Show score values after eating a ghost
	void freezeScoreAnimation(bool round_reset);

	//---------------------------------------------------------RENDER FUNCTIONS--------------------------------
	//---------------------------------------------------------------------------------------------------------

	//Render black areas to obfuscate ends of both tunnels
	void drawTunnelExits();

	//Draw pellets on the map
	void drawPellets();

	//Render energizers on the map
	void renderEnergizers();

	//Render bonus fruit
	void renderBonusFruit();

	//Render 1UP sign
	void renderOneUp();

	//Render HIGH SCORE letters
	void renderHighScoreLetters();

	//Render game score and high score
	void renderGameScore();

	//Render player life icons
	void renderPacmanLives();

	//Render fruits representing level
	void renderLevelRepresentation();

	//---------------------------------------------------------SCENE FUNCTIONS---------------------------------
	//---------------------------------------------------------------------------------------------------------

	//READY screen without the actors
	void introScene();

	//READY screen
	void resetScene();

	//Maze flashes in white for a few seconds
	void levelCompleteScene();

	//Pacman death animation
	void lifeLostScene();

	//GAME OVER screen
	void gameOverScene();

	//Blinky and Pacman chasing each other
	void firstTransmissionScene();

	//Blinky gets stuck on a nail
	void secondTransmissionScene();

	//Blinky runs away without his cloak
	void thirdTransmissionScene();

private:
	//Screen dimension constants
	const int SCREEN_WIDTH;
	const int SCREEN_HEIGHT;

	//Main game flag
	bool running;

	//Current game level
	int level;

	//Life check
	bool life_lost;

	//Level progress check
	bool level_complete;

	//Freeze frame check
	bool ghost_eaten;

	//Bonus fruit check
	bool bonus_fruit_eaten;

	//Scene player flag
	bool scene_playing;

	//Flag to play the transmission after certain levels
	bool transmission_scene;

	//Consumed pellets per level
	int dot_counter;
	const int dot_total;

	//Current game score
	int game_score;

	//Player life count
	int life_count;

	//Menu related
	bool menu_open;
	int option;

	int volume_slider;
	bool eternal_mode;

	//SDL interface elements
	SDL_Window* game_window;
	SDL_Renderer* game_renderer;

	//Image textures
	Texture maze_layout;
	Texture maze_transition;
	Texture menu_screen;
	Texture sprites;

	//Animation
	Animation pacman_animation;
	Animation blinky_animation;
	Animation pinky_animation;
	Animation inky_animation;
	Animation clyde_animation;

	Animation energizer_animation;
	Animation pacman_life_lost_animation;
	Animation big_pacman_animation;
	Animation blinky_retreat_animation;

	//Animation clips
	ClipWrapper game_clips;

	//Game sounds
	GameSounds game_sounds;

	//Maze map
	Map game_map;

	//Actors
	Pacman pacman;
	Blinky blinky;
	Pinky pinky;
	Inky inky;
	Clyde clyde;

	//Game Timers
	Timer fright_timer;
	Timer phase_timer;
	Timer pellet_timer;
	Timer bonus_timer;
	Timer bonus_score_timer;
	Timer freeze_frame_timer;
	Timer scene_play_timer;

	//Other
	Direction input_direction;

	SpeedTable speed_table;

	GhostTimeTable ghost_time_table;

	GameValuesTable game_values_table;

	FrameTimer utility_timer;
};

#endif //PACMAN_GAME_H
