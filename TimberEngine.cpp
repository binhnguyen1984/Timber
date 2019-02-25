/*
 * TimberEngine.cpp
 *
 *  Created on: Feb 11, 2019
 *      Author: binh
 */

#include "TimberEngine.h"
#include "TextureLoader.h"
#include <iostream>
#include <stdlib.h>

void TimberEngine::load_object(const char *path, int posX, int posY, Sprite &objSprite)
{
	Texture &textureObj = TextureLoader::getTexture(path);
	objSprite.setTexture(textureObj);
	objSprite.setPosition(posX, posY);
}

void TimberEngine::prepare_sounds(const char *path, SoundBuffer &soundBuffer, Sound &sound)
{
	soundBuffer.loadFromFile(path);
	sound.setBuffer(soundBuffer);
}

void TimberEngine::initialize_objects()
{
	/* create branches */
	for (int i = 0; i < NUM_BRANCHES; i++) {
		// Set the sprite's origin to dead center
		branches[i].setPosition(-2000, -2000);
		// We can then spin it round without changing its position
		branches[i].setOrigin(220, 20);
	}

	/* reset player's position */
	player.setPosition(PLAYER_X, PLAYER_Y);
	player.set_side(Side::LEFT);

	/* create clouds */
	for(int i = 0; i< NUM_CLOUDS; i++)
	{
		clouds[i].setPosition(-300, i * 150);
		clouds[i].set_active_state(false);
		clouds[i].set_speed_X(0);
	}

	/* reset bees */
	bee.setPosition(0, 800);
	bee.set_active_state(false);
	bee.set_speed_X(0.0f);

	// Make sure the gravestone is hidden
	rip.setPosition(675, 2000);

	/* reset the clock */
	timeRemaining = MAX_TIME;
	// Time bar
	timeBarStartWidth = TIME_START_WIDTH;
	timeBarHeight = TIME_HEIGHT;
	timeRemaining = MAX_TIME;
	timeBar.setSize(Vector2f(timeBarStartWidth, timeBarHeight));
	timeBar.setFillColor(Color::Red);
	timeBar.setPosition((1920 / 2) - timeBarStartWidth / 2, 980);
	paused = true;
	score = 0;
}

void TimberEngine::load_stationary_objects()
{
	/* create background sprite */
	load_object("Data/graphics/background.png", 0,0, backgroundSprite);

	/* create tree textures */
	load_object("Data/graphics/tree.png", 810,0, spriteTree1);
	load_object("Data/graphics/tree2.png", 20, 0, spriteTree2[0]);
	load_object("Data/graphics/tree2.png", 300,-400, spriteTree2[1]);
	load_object("Data/graphics/tree2.png", 1300,-400, spriteTree2[2]);
	load_object("Data/graphics/tree2.png", 1500,-500, spriteTree2[3]);
	load_object("Data/graphics/tree2.png", 1900, 0, spriteTree2[4]);
}

void TimberEngine::load_sounds()
{
	/* loading sounds */
	prepare_sounds("Data/sound/chop.wav", chopBuffer, chop);
	prepare_sounds("Data/sound/death.wav", deathBuffer, death);
	prepare_sounds("Data/sound/out_of_time.wav", ootBuffer, outOfTime);
}

void TimberEngine::position_message_text()
{
	FloatRect textRect = messageText.getLocalBounds();
	messageText.setOrigin(textRect.left +
		textRect.width / 2.0f,
		textRect.top +
		textRect.height / 2.0f);
	messageText.setPosition(1920 / 2.0f, 1080 / 2.0f);
}
void TimberEngine::load_texts()
{
	// load font from file
	font.loadFromFile("Data/fonts/KOMIKAP_.ttf");

	// Set the font to the messages
	messageText.setFont(font);
	scoreText.setFont(font);
	fpsText.setFont(font);

	// Set up the fps text
	fpsText.setFillColor(Color::White);
	fpsText.setCharacterSize(100);
	fpsText.setPosition(1200, 20);

	// Make it really big
	messageText.setCharacterSize(75);
	scoreText.setCharacterSize(100);

	// Choose a color
	messageText.setFillColor(Color::White);
	scoreText.setFillColor(Color::White);

	// Position the text
	position_message_text();
	scoreText.setPosition(20, 20);

	messageText.setString("Press Enter to start!");

	// Backgrounds for the text
	rect1.setFillColor(sf::Color(0, 0, 0, 150));
	rect1.setSize(Vector2f(600,105));
	rect1.setPosition(0,30);

	rect2.setFillColor(sf::Color(0, 0, 0, 150));
	rect2.setSize(Vector2f(1000, 105));
	rect2.setPosition(1150, 30);
}

void TimberEngine::load_time_bar()
{
	timeBarStartWidth = 400;
	timeBarHeight = 80;
	timeBar.setSize(Vector2f(timeBarStartWidth, timeBarHeight));
	timeBar.setFillColor(Color::Red);
	timeBar.setPosition((1920 / 2) - timeBarStartWidth / 2, 980);

	timeRemaining = 6.0f;
	timeBarWidthPerSecond = timeBarStartWidth / timeRemaining;
}

void TimberEngine::create_main_view()
{
	/* create the main window */
	mainView.create(VideoMode(1920, 1080),"Timber", Style::Fullscreen);

	load_stationary_objects();
	load_sounds();
	load_texts();
	load_time_bar();
	/* set up the clock */
	// reset the state
	initialize_objects();
}

void TimberEngine::draw_texts()
{
	// Draw backgrounds for the text
	mainView.draw(rect1);
	mainView.draw(rect2);

	// Draw the score
	mainView.draw(scoreText);

	//draw message text
	mainView.draw(messageText);
	// Draw the FPS
	mainView.draw(fpsText);
}

void TimberEngine::draw_clouds()
{
	for (int i = 0; i < NUM_CLOUDS; i++)
		mainView.draw(clouds[i]);
}

void TimberEngine::draw_trees_and_branches()
{
	mainView.draw(spriteTree1);
	for(int i = 0; i< 5; i++)
		mainView.draw(spriteTree2[i]);

	// Draw the branches
	for (int i = 0; i < NUM_BRANCHES; i++)
		mainView.draw(branches[i]);

	// Draw the tree
	mainView.draw(treeSprite);
}

void TimberEngine::update_time()
{
	Time dt = clock.restart();

	// Subtract from the amount of time remaining
	timeRemaining -= dt.asSeconds();
	// size up the time bar
	timeBar.setSize(Vector2f(timeBarWidthPerSecond *
		timeRemaining, timeBarHeight));
}

void TimberEngine::set_branch_sides(int seed)
{
	// Move all the branches down one place
	for (int j = NUM_BRANCHES - 1; j > 0; j--)
		branches[j].set_side(branches[j - 1].get_side());

	// Spawn a new branch at position 0
	// LEFT, RIGHT or NONE
	srand((int)time(0) + seed);
	int r = (rand() % 5);

	switch (r) {
	case 0:
		branches[0].set_side(Side::LEFT);
		break;

	case 1:
		branches[0].set_side(Side::RIGHT);
		break;

	default:
		branches[0].set_side(Side::NONE);
		break;
	}
}

void TimberEngine::update_branch_positions()
{
	for (int i = 0; i < NUM_BRANCHES; i++)
	{

		float height = i * 150;
		Side s = branches[i].get_side();
		if (s == Side::LEFT)
		{
			// Move the sprite to the left side
			branches[i].setPosition(610, height);
			// Flip the sprite round the other way
			branches[i].setOrigin(220, 40);
			branches[i].setRotation(180);
		}
		else if (s == Side::RIGHT)
		{
			// Move the sprite to the right side
			branches[i].setPosition(1330, height);
			// Set the sprite rotation to normal
			branches[i].setOrigin(220, 40);
			branches[i].setRotation(0);
		}
		else
		{
			// Hide the branch
			branches[i].setPosition(3000, height);
		}
	}
}

void TimberEngine::update_bee()
{
	Time dt = clock.restart();
	if (!bee.get_state())
	{
		// How fast is the bee
		srand((int)time(0) * 10);
		bee.set_speed_X((rand() % 200) + 200);

		// How high is the bee
		srand((int)time(0) * 10);
		float height = (rand() % 500) + 500;
		bee.setPosition(2000, height);
		bee.set_active_state(true);

	}
	else
		// Move the bee
	{

		bee.setPosition(bee.getX() -(bee.get_speed_X() * dt.asSeconds()),
			bee.getY());

		// Has the bee reached the right hand edge of the screen?
		if (bee.getX() < -100) bee.set_active_state(false);
	}
}

void TimberEngine::update_clouds()
{
	//Time dt = clock.restart();
	for (int i = 0; i < NUM_CLOUDS; i++)
	{
		if (!clouds[i].get_state())
		{
			// How fast is the cloud
			srand((int)time(0) * i);
			clouds[i].set_speed_X((rand() % 3));

			// How high is the cloud
			srand((int)time(0) * i);
			float height = (rand() % 150);
			clouds[i].setPosition(-200, height);
			clouds[i].set_active_state(true);
		}
		else
		{
			// Set the new position
			/*
			clouds[i].setPosition(
				clouds[i].getX() +
				(clouds[i].get_speed_X() * dt.asSeconds()),
				clouds[i].getY());
			*/
			clouds[i].move(clouds[i].get_speed_X(), 0);
			// Has the cloud reached the right hand edge of the screen?
			if (clouds[i].getX() > 1920)
				// Set it up ready to be a whole new cloud next frame
				clouds[i].set_active_state(false);
		}

	}
}

void TimberEngine::update_texts()
{
	Time dt = clock.restart();
	// Update the score text
	std::stringstream ss;
	ss << "Score = " << score;
	scoreText.setString(ss.str());

	// Draw the fps
	std::stringstream ss2;
	ss2 << "FPS = " << 1/dt.asSeconds();
	fpsText.setString(ss2.str());
}

void TimberEngine::update_log()
{
	//Time dt = clock.restart();
	if (log.get_state())
	{
		log.move(log.get_speed_X(), log.get_speed_Y());
		/*
		log.setPosition(
				log.getX() + (log.get_speed_X() * dt.asSeconds()),
				log.getY() + (log.get_speed_Y() * dt.asSeconds()));
		*/
		// Has the insect reached the right hand edge of the screen?
		if (log.getX() < -100 || log.getX() > 2000)
		{
			// Set it up ready to be a whole new cloud next frame
			log.set_active_state(false);
			log.setPosition(810, 720);
		}
	}
}

void TimberEngine::draw_objects() {
	// Draw our game scene here
	mainView.draw(backgroundSprite);
	// Draw the clouds
	draw_clouds();
	// draw trees and branches
	draw_trees_and_branches();
	// Draw the player
	mainView.draw(player);
	// Draw the axe
	mainView.draw(axe);
	// Draraw the flying log
	mainView.draw(log);
	// Draw the gravestone
	mainView.draw(rip);
	// Draw texts
	draw_texts();
	// Drawraw the bee
	mainView.draw(bee);
	// Draw the timebar
	mainView.draw(timeBar);
	if (paused) {
		// Draw our message
		mainView.draw(messageText);
	}
}

void TimberEngine::handle_dead_player(bool &acceptInput) {
	// has the player been squished by a branch?
	if (branches[NUM_BRANCHES - 1].get_side() == player.get_side()) {
		// death
		paused = true;
		acceptInput = false;
		// Draw the gravestone
		rip.setPosition(525, 760);
		// hide the player
		player.setPosition(2000, 660);
		// Change the text of the message
		messageText.setString("SQUISHED!!");
		// Center it on the screen
		position_message_text();
		// Play the death sound
		death.play();
	}
}

void TimberEngine::handle_out_of_time() {
	// handle out of time
	if (timeRemaining <= 0.0f) {
		// Pause the game
		paused = true;
		// Change the message shown to the player
		messageText.setString("Out of time!!");
		//Reposition the text based on its new size
		position_message_text();
		// Play the out of time sound
		outOfTime.play();
	}
}

void TimberEngine::handle_chopping(bool &acceptInput, const Side from) {
	// Make sure the player is on the right
	player.set_side(from);
	score++;
	// Add to the amount of time remaining
	timeRemaining += (2 / score) + .15;
	if(from==Side::RIGHT)
	{
		axe.setPosition(AXE_POSITION_RIGHT, axe.getY());
		player.setPosition(1200, 720);
		log.set_speed_X(-100);
	}
	else
	{
		axe.setPosition(AXE_POSITION_LEFT,	axe.getY());
		player.setPosition(580, 720);
		log.set_speed_X(100);
	}
	// update the branches
	set_branch_sides(score);
	// set the log flying to the left
	log.setPosition(810, 720);
	log.set_speed_Y(-50);
	log.set_active_state(true);
	acceptInput = false;
	// Play a chop sound
	chop.play();
}

void TimberEngine::handle_game_start(bool &acceptInput)
{
	// Reset the time and the score
	score = 0;
	timeRemaining = 6;

	// Make all the branches disappear
	for (int i = 1; i < NUM_BRANCHES; i++)
		branches[i].set_side(Side::NONE);

	// Make sure the gravestone is hidden
	rip.setPosition(675, 2000);

	// Move the player into position
	player.setPosition(580, 720);
	acceptInput = true;
}
void TimberEngine::play()
{
	// create the main view
	TimberEngine::create_main_view();

	//play the game
	int lastDrawn = 0;
	bool acceptInput = false;
	while (mainView.isOpen())
	{
		// score ++;
		Event event;
		while (mainView.pollEvent(event))
		{
			/* detect release key event */
			if (event.type == Event::KeyReleased && !paused)
			{
				// Listen for key presses again
				acceptInput = true;
				// hide the axe
				axe.setPosition(2000,axe.getY());
				//hide the message
				messageText.setString("");
			}
		}

		/*
		****************************************
		Handle the players input
		****************************************
		*/

		if (Keyboard::isKeyPressed(Keyboard::Escape))
			mainView.close();

		// Start the game
		if (Keyboard::isKeyPressed(Keyboard::Return))
		{
			paused = false;
			handle_game_start(acceptInput);
		}

		// Wrap the player controls to
		// Make sure we are accepting input
		if (acceptInput)
		{
			// First handle pressing the right cursor key
			if (Keyboard::isKeyPressed(Keyboard::Right))
			{
				// Make sure the player is on the right
				handle_chopping(acceptInput, Side::RIGHT);
			}

			// Handle the left cursor key
			if (Keyboard::isKeyPressed(Keyboard::Left))
			{
				// Make sure the player is on the left
				handle_chopping(acceptInput, Side::LEFT);
			}
		}


		/*
		****************************************
		Update the scene
		****************************************
		*/
		if (!paused)
		{
			// update time
			update_time();
			// handle out of time
			handle_out_of_time();
			// update the bee
			update_bee();
			// update clouds
			update_clouds();
			// Draw the score and the frame rate once every 100 frames
			lastDrawn++;
			if (lastDrawn == 100) {
				update_texts();
				lastDrawn = 0;
			}

			// update the branch positions
			update_branch_positions();
			// Handle a flying log
			update_log();
			// has the player been squished by a branch?
			handle_dead_player(acceptInput);
		}// End if(!paused)

		 /*
		 ****************************************
		 Draw the scene
		 ****************************************
		 */
		 // Clear everything from the last frame
		mainView.clear();
		// Draw our game scene here
		draw_objects();
		// Show everything we just drew
		mainView.display();
	}
}

/* initialize objects */
RenderWindow TimberEngine::mainView;
Sprite TimberEngine::backgroundSprite;
Sprite TimberEngine::treeSprite;
Log TimberEngine::log;
Sprite TimberEngine::spriteTree2[NUM_TREES];
Sprite TimberEngine::spriteTree1;
Axe TimberEngine::axe;
Player TimberEngine::player;
Rip TimberEngine::rip;
Branch TimberEngine::branches[NUM_BRANCHES];
Cloud TimberEngine::clouds[NUM_CLOUDS];
Bee TimberEngine::bee;
SoundBuffer TimberEngine::chopBuffer;
SoundBuffer TimberEngine::deathBuffer;
SoundBuffer TimberEngine::ootBuffer;
Sound TimberEngine::chop;
Sound TimberEngine::death;
Sound TimberEngine::outOfTime;
RectangleShape TimberEngine::rect1;
RectangleShape TimberEngine::rect2;
Font TimberEngine::font;
Clock TimberEngine::clock;
/* time bar */
RectangleShape TimberEngine::timeBar;
float TimberEngine::timeBarStartWidth;
float TimberEngine::timeBarHeight;
float TimberEngine::timeRemaining;
float TimberEngine::timeBarWidthPerSecond;
bool TimberEngine::paused;
int TimberEngine::score;
Text TimberEngine::messageText, TimberEngine::fpsText, TimberEngine::scoreText;

