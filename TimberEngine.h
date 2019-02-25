/*
 * TimberEngine.h
 *
 *  Created on: Feb 11, 2019
 *      Author: binh
 */
#pragma once
#ifndef TIMBERENGINE_H_
#define TIMBERENGINE_H_
#include <sstream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Branch.h"
#include "Player.h"
#include "Cloud.h"
#include "Bee.h"
#include "Log.h"
#include "Axe.h"
#include "Rip.h"

/* define constant */
#define NUM_BRANCHES 6
#define NUM_CLOUDS 3
#define NUM_TREES 5
#define MAX_TIME 100.0f
#define TIME_START_WIDTH 400
#define TIME_HEIGHT 80
#define PLAYER_X 580
#define PLAYER_Y 720
#define AXE_POSITION_LEFT 700
#define AXE_POSITION_RIGHT 1075

using namespace sf;
class TimberEngine {
private:
	/* stationary objects */
	static RenderWindow mainView;
	static Sprite backgroundSprite;
	static Sprite treeSprite;
	static Cloud clouds[NUM_CLOUDS];
	static Sprite spriteTree2[NUM_TREES];
	static Sprite spriteTree1;
	static Sprite ripSprite;

	/* moving objects */
	static Log log;
	static Axe axe;
	static Player player;
	static Bee bee;
	static Rip rip;
	static Branch branches[NUM_BRANCHES];

	/* clock */
	static Clock clock;
	/* time bar */
	static RectangleShape timeBar;
	static float timeBarStartWidth;
	static float timeBarHeight;
	static float timeRemaining;
	static float timeBarWidthPerSecond;

	// Track whether the game is running
	static bool paused, started, gameover;
	// score of the player
	static int score;

	// messages to be displayed
	static Text messageText;
	static Text scoreText;
	static Text fpsText;

	// We need to choose a font
	static Font font;

	// background for texts
	static RectangleShape rect1, rect2;

	/* sound objects */
	static Sound chop, death, outOfTime;
	static SoundBuffer chopBuffer, deathBuffer, ootBuffer;

private:
	static void load_objects();
	static void load_sounds();
	static void load_texts();
	static void load_time_bar();
	static void position_message_text();
	static void set_branch_sides(int seed);
	static void update_branch_positions();
	static void create_view();
	static void prepare_sounds(const char *path, SoundBuffer &soundBuffer, Sound &sound);
	static void draw_texts();
	static void draw_clouds();
	static void draw_trees_and_branches();
	static void update_branches(int seed);
	static void update_bee();
	static void update_clouds();
	static void update_log();
	static void update_time();
	static void update_texts();
	static void initialize_objects();
	static void load_object(const char* path, int posX, int posY, Sprite &objSprite);
public:
	static void play();
};

#endif /* TIMBERENGINE_H_ */
