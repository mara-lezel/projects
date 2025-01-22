#include "Game.h"

Game::Game() :

	SCREEN_WIDTH(480), SCREEN_HEIGHT(576),

	running(true), game_window(nullptr), game_renderer(nullptr),

	level(1), dot_counter(0), dot_total(244), game_score(0), life_count(6),

	life_lost(false), ghost_eaten(false), level_complete(false), bonus_fruit_eaten(false), scene_playing(false), transmission_scene(false),

	menu_open(true), option(1), volume_slider(1), eternal_mode(false),

	maze_layout(), maze_transition(), sprites(), menu_screen(),

	game_clips(),

	input_direction(Direction::LEFT), game_map(), game_sounds(),

	ghost_time_table(), speed_table(), game_values_table(),

	utility_timer(),

	fright_timer(), phase_timer(), pellet_timer(), freeze_frame_timer(), bonus_timer(), bonus_score_timer(), scene_play_timer(),

	pacman(2.344f, Direction::LEFT),

	blinky(2.1975f, Direction::LEFT), pinky(2.1975f, Direction::DOWN), inky(2.1975f, Direction::UP), clyde(2.1975f, Direction::UP),

	pacman_animation(4, 2),
	
	blinky_animation(2, 10), pinky_animation(2, 10), inky_animation(2, 10), clyde_animation(2, 10),

	energizer_animation(2, 8), pacman_life_lost_animation(12, 5), big_pacman_animation(4, 4), blinky_retreat_animation(2, 4) {}

Game::~Game()
{

}