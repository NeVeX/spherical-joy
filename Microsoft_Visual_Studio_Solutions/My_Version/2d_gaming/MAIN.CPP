/*
Author:		Mark Cunningham
Student ID:	04424549
Project:	Graphics And Imaging Project CT336 / CT404 - Semester 1 - 2007/08
			Project selected is an OpenGL 2D Game.

Project Name:	Spherical Joy v1.00a - MY_VERSION

	OverView:
		This is a simple game that resembles the famous Breakout Series.
		You are given a paddle, a sphere, some blocks and a certain number of lives.
		The idea is to hit the blocks with the paddle using the sphere without letting 
		the sphere drop below the paddle or collect the death box which both results in
		a life being taken away from you. So without losing all your lives, you must 
		complete all levels, starting from 1 (easy) to 16 (much harder).There are weapons 
		you can collect that can help you aswell as make it harder for you to complete the level.
		There is an intro screen, then a menu where you can look at the instructions and see
		all the weapons available to you and also see other functions of the game. From the initial 
		menu you can also start the game. There are extra functionalities to the game aswell, 
		such as the ability to pause the game, excape to the menu, and toggle the cursor 
		visible/not visible. Also included in the game are sound effects which can give the 
		game a more complete feel.

		The program is relatively bug free, and should run correctly all of the time.

		Enjoy the Expreience.

	Notes:
		This game was done using the screen resolution of 1280x1024, so there may be disrepencies
		with different screen resolutions, although I have kept in mind the 800x600 and 1024x768 
		resolutions.
		This game works perfectly on Windows XP SP2 Professional Edition and with said resolution.
		If you are compiling this code make sure to have all dependicies set up correctly. You may
		need to change the include directories and such things like that. It shouldn't be too complicated.

		I have tried it in the college and the sphere seems to move very slow. Also the paddle doesn't seem
		to move that fast either but the settings are the same and even the processor is the
		same as my computer. So the game may run slow on your computer but it works perfect on mine 
		without any glitch.

		Also I have hardcoded a cheat into the game that allows you to skip levels. This is for testing
		purposes and obviously would be removed when shipping.
*/


// all nessecary header files
#pragma comment(lib, "glaux.lib")

#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <glut.h>
#include <math.h>
#include "media.h"
#include "HUD.h"
#include "intro.h"
#include "weapons.h"
#include <gl\glaux.h> 
#include <stdio.h>                                            
#include <dos.h>                                           
#include <sys\timeb.h>                                   

// my decleration's list of functions used 
void weapons(int weapon, float i, float j);
void show_menu();
void block_update(int row, int col);
void intro(int option);
void intro_off(int value);
void setup_lights();
void texture_loading();
void trademark_pic(void);
void neutralize_weapons(int option);
void take_effect(int weapon_type);
void game_init(int level, int lives);
void display();
void idle();
void levels(void);
void paddle(void);
void sphere(void);
void collision(void);
void speed_up(int value);
void block_collision(void);
void mouseMotion(int x, int y);
void reshape(GLsizei w, GLsizei h);
void clean_array(void);
void start_game(void);
void game_over(int option);
void frame(void);
void next_level(int level);
void HUD(int position, int info, char *string);
void get_paddle_length(void);
void keyboard(unsigned char key, int x, int y);
void weapon_collision(void);
void fireball(int row, int col);

// the float declerations
GLfloat i, j, paddle_movement, ball_rad, ball_x, ball_y;
GLfloat move_ball_x, move_ball_y, window_width, window_height;
GLfloat start_row, start_col, end_row, end_col;
GLfloat paddle_x_left, paddle_x_right, paddle_y_top, paddle_y_bottom;
GLfloat x_1, x_2, y_1, y_2, paddle_length;
GLfloat new_size_x, new_size_y;
GLfloat old_w, old_h;
GLfloat weapon_move_x, weapon_move_y;
GLfloat cube_size, collision_cube_size, original_ball_rad, original_paddle_length, speed_up_ball_x, speed_up_ball_y;
GLfloat paddle_x1, paddle_x2;

long double ball_speed_x, ball_speed_y, initial_ball_speed_x, initial_ball_speed_y;
	// this sets up the ball speed for a 1280 x 1024 screen
long double	original_ball_speed_x = 0.000450;	// for a 1280 x 1024 screen
long double	original_ball_speed_y = 0.000650;	// for a 1280 x 1024 screen

// the integers declerations
int blocks_touched[100][100][2], blocks, block_row, block_col, q, w,k, total_blocks;
int new_w, new_h, window_w, window_h, start, lives, width, height;
int move, original_width = 1280, original_height = 1024;
int level_number, played, finished, mouse_temp, mouse_temp_range;
int baseball_amount, fireball_amount, ball_smaller_size_amount, ball_bigger_size_amount, paddle_bigger_amount;
int	paddle_smaller_amount, lives_amount, death_amount;
int show_picture = 0, show_cursor, pause_game, show_menu_number, t_diff, t_diff_2;
int check_speed_x, check_speed_y, weapon_hit, weapon_type, weapon_dir;
int time_before;

// some booleans
bool playing = false, weapon_falling = false, collided = false;
bool weapon_block = false, fireball_on, baseball;
bool intro_now = true, show_menu_now = false;

struct timeb t_start, t_current; // for the timed speed up function

// defining texture arrays
GLuint texture[5], weapon_texture[8], block_texture[4], pictures[2];

// Setting up the lighting I will use on the sphere
static GLfloat MatSpec[] = {0.1,0.2,0.4,0.5};
static GLfloat MatShininess0[] = {10.0};
static GLfloat MatShininess1[] = {40.0};
static GLfloat LightPos[] = {0.0,0.0,3.0,0.0};
static GLfloat matAmbient[] = {0.33, 0.22, 0.03, 1.0};
static GLfloat matDiffuse0[] = {0.0, 0.3, 1.0, 1.0}; // normal color
static GLfloat matDiffuse1[] = {1.0, 0.1, 0.0, 1.0}; // fireball color



// the main function that sets up the initial game and then loops over the game code
int main(int argc, char** argv) {
	intro_now = true;
	pause_game = 0;
	show_menu_number = 0;
	time_before = 0;
	game_init(1,3);	// start the game with level 1 and 3 lives
	clean_array();	// assign weapons
	start_game();	// begin the game
	played = 0;
	finished = 0;	// did the player complete the game
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutCreateWindow("The MarX 2d Gaming Experience");
	glutMotionFunc(mouseMotion);	// the mouse function
	glutDisplayFunc(display);	// the looped display function
	glutKeyboardFunc(keyboard);	// the function to handle all keyboard input
	glutIdleFunc(idle);	// when the program is idle, this function is called
	glutReshapeFunc(reshape);	// gets the dimensions of the current screen and correctly reshapes it
	glutFullScreen();	// makes the screen fullscreen
	texture_loading();	// load all the textures into the related arrays
	glutMainLoop(); // starts the main loop
}

// I use this in between levels, dying, game_over cases and when the game starts
// It creates the correct instances of the game, i.e correct lives, blocks etc...
void game_init(int level, int current_lives) {
	show_menu_now = false; // turn menu off
	start = 0;	// don't move the ball, i.e wait for the space bar
	//move = 1;	
	weapon_dir = 1;	// the weapon should always fall down
	collided = false;	// weapon collision 
	fireball_on = false;	// freball ball weapon is false
	baseball = false;	// baseball weapon is false
	cube_size = 0.04; collision_cube_size = 0.03;	// size of the weapon square
	lives = 3;	// initial lives
	level_number = level;	// current level
	new_w = new_h = 0;	// the current window width and height
	lives = current_lives;	// the current lives, overrides init lives
	ball_x = 0.0; ball_y = -0.2;	// translation of the sphere
	window_width = window_height = 1.0;	// for the reshaping function
	move_ball_x = move_ball_y = -1.0;	// move the ball negatively in x and y direction
	ball_speed_x = original_ball_speed_x;	 // for a 1280 x 1024 screen
	ball_speed_y = original_ball_speed_y;	// for a 1280 x 1024 screen
	ball_rad = 0.027;	// the sphere rad
	original_ball_rad = 0.027;	// the original sphere rad, used when you die or finish a level
	blocks = 0;	// no blocks to hit, initially set
	start_row = 0.4; end_row = 0.2;	// where to start building block
	start_col = 0.4; end_col = 0.2;
	paddle_x_left = -0.12; paddle_x_right = 0.12;	// the paddle setup
	paddle_y_top = -0.90; paddle_y_bottom = -0.95;
	paddle_movement = 0.0;	// paddle isn't moving
	original_paddle_length = 0.24;	// used when the paddle is put back to normal when you have died or
									// finished a level
	baseball_amount = fireball_amount = ball_smaller_size_amount = ball_bigger_size_amount = 0;	// no weapons
	paddle_bigger_amount = paddle_smaller_amount = lives_amount = death_amount = 0;	// no weapons....yet
	speed_up_ball_x = speed_up_ball_y = 0.0;	// speed ball up set to 0...this gets changed over time
	get_paddle_length(); // get the current paddle length
	neutralize_weapons(1); // delete any weapons you contain, used when you die or finish a level
	ftime(&t_start);  // start the timer
	

}
void display() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // clear everything on screen


	if ( intro_now == true) {	// if the intro is true, then display the game image for 4 seconds
		intro(show_picture);
		glutTimerFunc(4000,intro_off, 0); // turns off the intro after a few seconds
	}

	else if ( playing ) {	// if we are playing
		sphere();	// draw and move the sphere
		frame();	// draw the frame
		levels();	// set up and draw the correct level
		paddle();	// move and draw the paddle
		collision();	// find out if the ball has collided with anything but the blocks
		collided = false;	// has it collided above
		if ( level_number != 16) { // not the last level
			if ( ball_y > -0.2) {	// if the ball is above the -0.2 line, then call block_collision
									// I try and restrict block collision as it is computing intensive
				block_collision();
				collided = true;
			}
		}
		else {
			block_collision(); // only does this all the time on level 16
		}

		if ( total_blocks == 0) {	// all the blocks are gone
			weapon_falling = false;	// no weapons are falling
			level_number++;	// increase level
			next_level(level_number);	// and go to the next level
		}

		weapon_collision();	// see if the weapon hit something and act upon it

		if ( weapon_falling == true) {	// if a weapon is falling
			show_weapon(weapon_texture[weapon_type], weapon_move_x, weapon_move_y, cube_size); // show it
			weapon_move_x -= 0.0001 * weapon_dir * start;	// and move it downwards
			weapon_move_y -= 0.000615 * start;
		}

		
	}

	else {	// otherwise we are not playing and hence the menu is shown
		if ( show_menu_now == true) {	// either the menu is shown or the trademark is shown
			show_menu();
		}
		else {
			trademark_pic();
			intro_setup(played, finished);
		}
			

	}
	
	glutSwapBuffers();	// swap the back buffers
	glutPostRedisplay();	// redisplay everything

}

void idle() {	// when program is idle
	block_collision();	// do some block collisions
	ftime(&t_current);	// get current time							     
    t_diff = (int) (1000.0 * (t_current.time - t_start.time) + (t_current.millitm - t_start.millitm));
	if ( t_diff % 3000 == 0) {	// if a certain time has passed then call the speed up function
		speed_up(0);
	}


}


void levels(void) {	// the levels drawing
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	blocks = 0; 
	block_row = 0; block_col = 0;
	
	glEnable(GL_TEXTURE_2D);	// enable textures
	// this will loop over each block, assign and draw the correct texture for that block
	// it also counts up the current number of blocks on screen
		for(i = start_row; i > end_row; i-= 0.07) {
			for(j = -start_col; j < end_col; j+= 0.22) {
				if(blocks_touched[block_row][block_col][0] < 1) {
					if(blocks_touched[block_row][block_col][0] == -2) {
						glBindTexture(GL_TEXTURE_2D, block_texture[3]);
					}
					else if (blocks_touched[block_row][block_col][0] == -1) {
						glBindTexture(GL_TEXTURE_2D, block_texture[2]);
					}
					else if (blocks_touched[block_row][block_col][0] == -3) {
						glBindTexture(GL_TEXTURE_2D, block_texture[1]);
					}
					else {
						glBindTexture(GL_TEXTURE_2D, block_texture[0]);

					}
					glColor3f(1.0,1.0,1.0);
						glBegin(GL_QUADS);
								glTexCoord2f(0.0,0.0); glVertex2f(j + 0.02, i - 0.04);
								glTexCoord2f(0.0,1.0); glVertex2f(j + 0.02, i);
								glTexCoord2f(1.0,1.0); glVertex2f(j + 0.219, i);
								glTexCoord2f(1.0,0.0); glVertex2f(j + 0.219, i - 0.04);
						glEnd();
					if (blocks_touched[block_row][block_col][0] == -3) {
					}
					else blocks++;
				}
			block_col++;
			
			}
		block_row++;
		block_col = 0;
		}
		
	total_blocks = blocks;

	glDisable(GL_TEXTURE_2D); // disable texturing, for now
	glFlush();
}


void paddle(void) {	// drawing the paddle
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	
	// using the correct texture we draw the paddle and move it if nessecary
	glColor3f(1.0, 1.0, 1.0);
	glEnable(GL_TEXTURE_2D);	
	glBindTexture(GL_TEXTURE_2D, texture[0]);
	glBegin(GL_QUADS);
		glTexCoord2f(0.0,0.0); glVertex2f(paddle_x1 + paddle_movement, -0.95);
		glTexCoord2f(0.0,1.0); glVertex2f(paddle_x1 + paddle_movement, -0.90);
		glTexCoord2f(1.0,1.0); glVertex2f(paddle_x2 + paddle_movement, -0.90);
		glTexCoord2f(1.0,0.0); glVertex2f(paddle_x2 + paddle_movement, -0.95);	
	glEnd();
	glDisable(GL_TEXTURE_2D);
	glFlush();

	paddle_x1 = -(paddle_length / 2);
	paddle_x2 = (paddle_length / 2);
}

void sphere(void) { // drawing the sphere
	// move the sphere
	ball_x += (ball_speed_x * move_ball_x * start); 
	ball_y += (ball_speed_y * move_ball_y * start); 

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	
	glEnable(GL_LIGHTING);	// use the lighting already set up
	glEnable(GL_LIGHT0);
	glShadeModel(GL_SMOOTH);
	glEnable(GL_DEPTH_TEST);

	 // finds out which color to use and uses it
	if (fireball_on == true) {
		glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, matDiffuse1);
		glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, MatShininess1);
	}
	else {
		glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, matDiffuse0);
		glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, MatShininess0);
	}

	// gives light directions, shine, smoothness etc
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, matAmbient);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, MatSpec);
	
	
	glLightfv(GL_LIGHT0, GL_POSITION, LightPos);
	
	// moves the ball
	glTranslatef(ball_x, ball_y, 0.0);
	glutSolidSphere(ball_rad, 20, 20);

	glDisable(GL_LIGHTING);	// stop the lighting


}


void mouseMotion(int x, int y) {	// called when mouse moves
	// finds out which direction the mouse is going in and then moves the paddle
	// accordingly
	if (x > mouse_temp) {
		if ( start != 0) {
			paddle_movement += 0.048;	// move_right
		}
	}
	else if ( x < mouse_temp) {
		if ( start != 0) {
			paddle_movement -= 0.048;	//move left
		}
	}
	mouse_temp = x;

	paddle_x_left = (paddle_x1 + paddle_movement);
	paddle_x_right = (paddle_x2 + paddle_movement);

}



void start_game(void) {	// start the game
	printf("The Game Has Started\n");
	neutralize_weapons(1);
	play(3);
}

void game_over(int option) {	// if all the lives are up or you finish the game
	// function finds out the correct thing to say to the player
	// it also initialises the game back to the beginning
	if ( option >= 1) {
		played = 0;
	}
	else {
		played = 1;
	}
	if ( option != 2) {
		play(3);
	}
	playing = false;
	neutralize_weapons(1);
	printf("The Game Has Ended\n");
	game_init(1,3);
	level_number = 1;

}
void frame(void) {	// draws the white frame on the screen
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glColor3f(1.0, 1.0, 1.0);
	glLineWidth(3.0);
	glBegin(GL_LINE_STRIP);
		glVertex2f(-1.0, -1.0);
		glVertex2f(-1.0, 0.9);
		glVertex2f(1.0, 0.9);
		glVertex2f(1.0, -1.0);
	glEnd();
	// displays all the info, or Head Up Display (HUD)
	HUD(1, level_number, "Level : ");
	HUD(2, lives, "Lives : ");
	if (start == 0 ) {
		HUD(3, 3,"Press SPACE BAR To Continue");
	}
	

}

void get_paddle_length(void) {	// gets the current paddle length

	// paddle length
	x_1 = paddle_x_left;
	x_2 = paddle_x_right;
	y_1 = paddle_y_bottom;
	y_2 = paddle_y_top;

	paddle_length = sqrt( (( x_2 - x_1)*( x_2 - x_1)) + (( y_2 - y_2)*( y_2 - y_2)));

	printf("the paddle length is %f\n", paddle_length);


}


void keyboard(unsigned char key, int x, int y) {	// function is called when a key is pressed
	// the esc key. if we are not playing, it exits
	if ( key == 27 && playing == false) {
		exit(1);
	}
	// the esc key. if we are playing it exits to the menu
	if (key == 27 && playing == true) {
		game_over(1);
	}
	// the space bar. it moves the sphere initially
	if ( key == 32 && start == 0) {
		start = 1;
		ball_speed_x = original_ball_speed_x;
		ball_speed_y = original_ball_speed_y;
	}
	// the enter key. starts the game
	if ( key == 13 && intro_now == false ) {
		playing = true;
		play(4);
		Sleep(200);
	}
	// toggles the cursor off/on
	if ( key == 'c' || key == 'C' ) {
		if (show_cursor % 2 == 0) {
			ShowCursor(FALSE);
		}
		else {
			ShowCursor(TRUE);
		}
		show_cursor++;
	}
	// pauses the game
	if ( (key == 'p' || key == 'P') && playing == true ) {
		if ( pause_game % 2 == 0) {
			start = 0;
		}
		else start = 1;

		pause_game++;
	}
	// the m key. shows the instructions
	if ( (key == 'm' || key == 'M') && playing == false) {
		if ( show_menu_number % 2 == 0) {
			show_menu_now = true;
		}
		else {
			show_menu_now = false;
			game_over(2);
		}
		show_menu_number++;
	}
	// level skipping. Admin purposes
	if (( key == 'l' || key == 'L') && playing == true) { // remove this
		if ( level_number == 16 ) {
			level_number = 1;
		}
		else {
			level_number = level_number + 1;
		}
		game_init(level_number,lives);
		next_level(level_number);
	}


}





void collision(void) {	// finds if the ball has collided with the frame, paddle or has died

	// the frame for the ball
	if (ball_y <= -1.2 + ball_rad) {	// the bottom
		weapon_falling = false;
		lives--;
		if ( lives == 0) {
			game_over(0);
			return;
		}
		else {
			play(5);
			start = 0;
			ball_x = 0.0; ball_y = -0.2;
			neutralize_weapons(1);
			paddle_x_left = -0.12; paddle_x_right = 0.12;
			paddle_y_top = -0.90; paddle_y_bottom = -0.95;
			paddle_movement = 0.0;
			HUD(2, lives, "Lives : ");
			HUD(3, 1, "Press SPACE BAR To Continue");
			return;
		}
	}
	if (ball_y >= 0.90 - ball_rad) {
		if ( move_ball_y > 0) {
			move_ball_y *= -1;
		}
		return;
	}
	if (ball_x <= -1.00 + ball_rad) {
		if ( move_ball_x < 0) {
			move_ball_x *= -1;
		}
		return;
	}
	if (ball_x >= 1.00 - ball_rad) {
		if ( move_ball_x > 0) {
			move_ball_x *= -1;
		}
		return;
	}
	// paddle frame
	if ( paddle_x_left <= -1.00) {
		paddle_movement = -(1.00 - paddle_x2);
	}

	if ( paddle_x_right >= 1.00) {
		paddle_movement = (1.00 - paddle_x2);
	}

	// the paddle top
	if (ball_x >= paddle_x_left - ball_rad && ball_x <= paddle_x_right + ball_rad && ball_y < paddle_y_top + ball_rad && ball_y > paddle_y_top + ball_rad - ball_speed_y) {
		play(2);
		if ( move_ball_y < 0) {
			move_ball_y *= -1;
			if ( ball_x >= (paddle_x_left - ball_rad + (paddle_length + ball_rad)/2.0)) {
				printf("right\n");
				if ( ball_x == (paddle_x_left - ball_rad + (paddle_length + ball_rad)/2.0)) {        // directly centre
					ball_speed_x = 0.000000;
					if ( move_ball_x < 0) {
						move_ball_x *= -1;
					}
					return;
				}
				else if ( ball_x > (paddle_x_left - ball_rad + (paddle_length + ball_rad)/2) && ball_x <= (paddle_x_left - ball_rad + (paddle_length + ball_rad)/1.8)) {
						ball_speed_x = 0.000070;
						if ( move_ball_x < 0) {
							move_ball_x *= -1;
						}
						return;
				}
				else if ( ball_x > (paddle_x_left - ball_rad + (paddle_length + ball_rad)/1.8) && ball_x <= (paddle_x_left - ball_rad + (paddle_length + ball_rad)/1.6)) {
						ball_speed_x = 0.000150;
						if ( move_ball_x < 0) {
							move_ball_x *= -1;
					}
						return;
				}
				else if ( ball_x > (paddle_x_left - ball_rad + (paddle_length + ball_rad)/1.6) && ball_x <= (paddle_x_left - ball_rad + (paddle_length + ball_rad)/1.4)) {
						ball_speed_x = 0.000230;
						if ( move_ball_x < 0) {
							move_ball_x *= -1;
					}
						return;
				}
				else if ( ball_x > (paddle_x_left - ball_rad + (paddle_length + ball_rad)/1.4) && ball_x <= (paddle_x_left - ball_rad + (paddle_length + ball_rad)/1.2)) {
						ball_speed_x = 0.000300;
						if ( move_ball_x < 0) {
							move_ball_x *= -1;
					}
						return;
				}
				else if ( ball_x > (paddle_x_left - ball_rad + (paddle_length + ball_rad)/1.2) && ball_x <= (paddle_x_left - ball_rad + (paddle_length + ball_rad)/1.0)) {
						ball_speed_x = 0.000400;
						if ( move_ball_x < 0) {
							move_ball_x *= -1;
					}
						return;
				}
				else {
					ball_speed_x = 0.000400;
						if ( move_ball_x < 0) {
							move_ball_x *= -1;
					}
						return;
				}
			}
			else {
				printf("LEFT\n");
				if ( ball_x >= (paddle_x_left - ball_rad + ((paddle_length + ball_rad)/2)*0.8)) {
						ball_speed_x =0.000070;
						if ( move_ball_x > 0) {
							move_ball_x *= -1;
						}
						return;
				}
				else if ( ball_x >= (paddle_x_left - ball_rad + ((paddle_length + ball_rad)/2)*0.6)) {
						ball_speed_x = 0.000150;
						if ( move_ball_x > 0) {
							move_ball_x *= -1;
					}
						return;
				}
				else if ( ball_x >= (paddle_x_left - ball_rad + ((paddle_length + ball_rad)/2)*0.4)) {
						ball_speed_x = 0.000230;
						if ( move_ball_x > 0) {
							move_ball_x *= -1;
					}
						return;
				}
				else if ( ball_x >= (paddle_x_left - ball_rad + ((paddle_length + ball_rad)/2)*0.2)) {
						ball_speed_x = 0.000300;
						if ( move_ball_x > 0) {
							move_ball_x *= -1;
					}
						return;
				}
				else if ( ball_x >= (paddle_x_left - ball_rad)) {
						ball_speed_x = 0.000400;
						if ( move_ball_x > 0) {
							move_ball_x *= -1;
					}
					return;
				}
				else {
					ball_speed_x = 0.000400;
						if ( move_ball_x > 0) {
							move_ball_x *= -1;
						}
					return;
				}
			}
		}
		printf("paddle top\n");
	}
		
		
	// the paddle left
	if (ball_y < paddle_y_top + ball_rad && ball_y > paddle_y_bottom - ball_rad && ball_x > paddle_x_left - ball_rad && ball_x < paddle_x_left - ball_rad + ball_speed_x) {
		if ( move_ball_x > 0) {
			move_ball_x *= -1;
			return;
		}
		play(2);
		printf("paddle left\n");	
	}
	// the paddle right
	else if (ball_y < paddle_y_top + ball_rad && ball_y > paddle_y_bottom - ball_rad && ball_x < paddle_x_right + ball_rad && ball_x > paddle_x_right + ball_rad - ball_speed_x) {
		if ( move_ball_x < 0) {
			move_ball_x *= -1;
			return;
		}
		play(2);
		printf("paddle right\n");
	}
}

void block_collision() {	// finds if the sphere has hit the blocks and acts on it
	block_row = 0;
	block_col = 0;
	if ( collided == false) {
	for(i = start_row; i > end_row; i-= 0.07) {
			for(j = -start_col; j < end_col; j+= 0.22) {
				if (ball_x > j + 0.02 - ball_rad && ball_x < j + 0.219 + ball_rad && ball_y < i + ball_rad && ball_y > i + ball_rad - ball_speed_y) { 
					if(blocks_touched[block_row][block_col][0] < 1) {
						if ( move_ball_y < 0 && baseball == false) {
							move_ball_y *= -1;
						}
						else if (baseball == true){
							blocks_touched[block_row][block_col][0] = 1;
						}
						if (blocks_touched[block_row][block_col][0] != -3) {
							weapons(blocks_touched[block_row][block_col][1], i, j);
							blocks_touched[block_row][block_col][1] = -1;
							if (fireball_on == true) {
								fireball(block_row, block_col);
							}
							else play(1);
						}
						else play(8);
						
					}
					if (blocks_touched[block_row][block_col][0] != -3) {
						block_update(block_row,block_col);
					}
						
					
				}
				else if (ball_y < i + ball_rad && ball_y > i - 0.02 - ball_rad && ball_x > j + 0.02 - ball_rad && ball_x < j + 0.02 - ball_rad + ball_speed_x*2) {
					if(blocks_touched[block_row][block_col][0] < 1) {
						if ( move_ball_x > 0 && baseball == false) {
							move_ball_x *= -1;
						}
						else if (baseball == true){
							blocks_touched[block_row][block_col][0] = 1;
						}
						if (blocks_touched[block_row][block_col][0] != -3) {
							weapons(blocks_touched[block_row][block_col][1], i, j);
							blocks_touched[block_row][block_col][1] = -1;
							if (fireball_on == true) {
								fireball(block_row, block_col);
							}
							else play(1);
						}
						else play(8);
						
					}
					if (blocks_touched[block_row][block_col][0] != -3) {
						block_update(block_row,block_col);
					}
					
				}	
				else if (ball_y < i + ball_rad && ball_y > i - 0.04 - ball_rad && ball_x < j + 0.219 + ball_rad && ball_x > j + 0.219 + ball_rad - ball_speed_x*2) {
					if(blocks_touched[block_row][block_col][0] < 1) {
						if ( move_ball_x < 0 && baseball == false) {
							move_ball_x *= -1;
						}
						else if (baseball == true){
							blocks_touched[block_row][block_col][0] = 1;
						}
						if (blocks_touched[block_row][block_col][0] != -3) {
							weapons(blocks_touched[block_row][block_col][1], i, j);
							blocks_touched[block_row][block_col][1] = -1;
							if (fireball_on == true) {
								fireball(block_row, block_col);
							}
							else play(1);
						}
						else play(8);

					}
					if (blocks_touched[block_row][block_col][0] != -3) {
						block_update(block_row,block_col);
					}
					
				}
				else if (ball_x > j + 0.02 - ball_rad && ball_x < j + 0.219 + ball_rad && ball_y > i - 0.04 - ball_rad && ball_y < i - 0.04 - ball_rad + ball_speed_y) {
					if(blocks_touched[block_row][block_col][0] < 1) {
						if ( move_ball_y > 0 && baseball == false) {
							move_ball_y *= -1;
						}
						else if (baseball == true) {
							blocks_touched[block_row][block_col][0] = 1;
						}
						if (blocks_touched[block_row][block_col][0] != -3) {
							weapons(blocks_touched[block_row][block_col][1], i, j);
							blocks_touched[block_row][block_col][1] = -1;
							if (fireball_on == true) {
								fireball(block_row, block_col);
							}
							else play(1);
						}
						else play(8);
					}
					if (blocks_touched[block_row][block_col][0] != -3) {
						block_update(block_row,block_col);
					}
				}
			block_col++;
			}
		block_row++;
		block_col = 0;
		}
	}

}


void reshape(GLsizei w, GLsizei h) { // resize viewport to new canvas size
	
	width = w;
	height = h;

	glViewport(0, 0, w, h);
	// change clipping region to have same w:h ratio as canvas
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if (w <= h) {
		gluOrtho2D(-1.0, 1.0, -1.0 * h/w, 1.0 * h/w);
	}
	else {
		gluOrtho2D(-1.0 * w/h, 1.0 * w/h, -1.0, 1.0);
	}

	// changes the ball speed according to dimensions of the screen.
	// I only take care of the 3 basic screen dimensions with the screen
	// the Screen size of 1280 x 1024 is hardcoded already into the code

// the width
	if ( w >= 700 && w < 900 ) {
		ball_speed_x = 0.000281;
		original_ball_speed_x = 0.000281;
	}
	if ( w >= 900 && w < 1100 ) {
		ball_speed_x = 0.000381;
		original_ball_speed_x = 0.000331;
	}
	if ( w >= 400 && w < 700 ) {
		ball_speed_x = 0.000121;
		original_ball_speed_x = 0.000121;
	}
// the height
	if ( h >= 500 && h < 700 ) {
		ball_speed_y = 0.000331;
		original_ball_speed_y = 0.000331;
	}
	if ( h >= 700 && h < 900 ) {
		ball_speed_y = 0.000428;
		original_ball_speed_y = 0.000428;
	}
	if ( h >= 300 && h < 500 ) {
		ball_speed_y = 0.000251;
		original_ball_speed_y = 0.000251;
	}
	
	if ( w == 800 && h == 600 ) {
		ball_speed_x = 0.000281;	 // for a 800 x 600 screen
		ball_speed_y = 0.000381;	// for a 800 x 600 screen
		original_ball_speed_x = 0.000281;	// for a 800 x 600 screen
		original_ball_speed_y = 0.000381;	// for a 800 x 600 screen
	}

	else if ( w == 1024 && h == 768 ) {
		ball_speed_x = 0.00036;	 // for a 1024 x 768 screen
		ball_speed_y = 0.000488;	// for a 1024 x 768 screen
		original_ball_speed_x = 0.000360;	// for a 1024 x 768 screen
		original_ball_speed_y = 0.000488;	// for a 1024 x 768 screen
	}
	
}


void weapons(int weapon, float i, float j) {	// starts the init position of the weapon and calls,  
												// indirectly, the weapon moving function
	if ( weapon == -1) {
		return;
	}
	else if ( weapon_falling == false) {
			weapon_type = weapon;
			weapon_falling = true;
			weapon_move_x = j;
			weapon_move_y = i;
		}
}

void weapon_collision(void) {	// finds if the weapon has collided with the paddle and acts upon it
					
	// top of the paddle
	if (weapon_move_x >= paddle_x_left - collision_cube_size && weapon_move_x <= paddle_x_right + collision_cube_size && weapon_move_y <= paddle_y_top + collision_cube_size && weapon_move_y >= paddle_y_top ) {
		if ( weapon_falling == true ) {
			play(7);
			take_effect(weapon_type);
			weapon_falling = false;
		}
	}
	// left of the paddle
	if (weapon_move_y <= paddle_y_top + collision_cube_size && weapon_move_y >= paddle_y_top - collision_cube_size && weapon_move_x >= paddle_x_left - collision_cube_size - (collision_cube_size/4) && weapon_move_x <= paddle_x_left - collision_cube_size ) {
		if ( weapon_falling == true ) {
			play(7);
			take_effect(weapon_type);
			weapon_falling = false;
		}
	}
	// right of the paddle
	if (weapon_move_y <= paddle_y_top + collision_cube_size && weapon_move_y >= paddle_y_top - collision_cube_size && weapon_move_x <= paddle_x_right + collision_cube_size + (collision_cube_size/4) && weapon_move_x >= paddle_x_right + collision_cube_size ) {
		if ( weapon_falling == true ) {
			play(7);
			take_effect(weapon_type);
			weapon_falling = false;
		}
	}

	// weapon fell below paddle
	if (weapon_move_y < -1.2 ) {
		weapon_falling = false;
	}
	// bounce weapon off the frame
	if ( weapon_move_x < -1.00 + collision_cube_size || weapon_move_x > 1.00 - collision_cube_size  ) {
		weapon_dir *= -1;
	}


}


void take_effect(int weapon_type) {	// if the paddle caught the weapon then act upon it

	if ( weapon_type == -1) {
		return;
	}

	if ( weapon_type == 0 ) {	// death
		lives--;
		play(5);
		start = 0;
		ball_x = 0.0; ball_y = -0.2;
		move_ball_x = move_ball_y = -1.0;
		neutralize_weapons(1);
		paddle_x_left = -0.12; paddle_x_right = 0.12;
		paddle_y_top = -0.90; paddle_y_bottom = -0.95;
		paddle_movement = 0.0;

		HUD(2, lives, "Lives : ");
		HUD(3, 1, "Press SPACE BAR To Continue");
	}
	if ( weapon_type == 1 ) {	// increase paddle
		if ( paddle_length < 0.80 ) {
			paddle_length *= 2;
		}
	}
	if ( weapon_type == 2 ) {	// decrease paddle
		if ( paddle_length > 0.11 ) {
			paddle_length /= 2;
		}
	}
	if ( weapon_type == 3) {	// ball bigger
		if ( ball_rad <= original_ball_rad) {
			ball_rad *= 2;
		}
	}
	if ( weapon_type == 4) {	// ball smaller
		if ( ball_rad >= original_ball_rad) {
			ball_rad /= 2;
		}
	}
	if ( weapon_type == 5) {	// fireball
		fireball_on = true;
	}
	if ( weapon_type == 6) {	// baseball
		baseball = true;
	}
	if ( weapon_type == 7) {	// increase lives
		lives++;
	}
}


void fireball(int row, int col) {	// if the ball was a fireball, then more blocks should get hit
	
	if (blocks_touched[row][col][0] == -3) {
		return;
	}
	else {
		play(6);	// the sound
		if ( (col - 1) >= 0 && blocks_touched[row][col-1][0] != -3) { 
			blocks_touched[row][col-1][0] += 1;
		}
		if ( (row - 1) >= 0 && blocks_touched[row-1][col][0] != -3) {
			blocks_touched[row-1][col][0] += 1;
		}
		if ( (col + 1) < 100 && blocks_touched[row][col+1][0] != -3) {
			blocks_touched[row][col+1][0] += 1;
		}
	}
}

void neutralize_weapons(int option) {	// deletes all weapons from the user
	// it simply resets everything
	weapon_falling = false;
	fireball_on = false;
	baseball = false;

	if (option == 1) {
		paddle_length = original_paddle_length;
	}
	ball_rad = original_ball_rad;
	
}

void texture_loading() {	// loads the textures in the arrays
	// various Textures
	AUX_RGBImageRec *texture1;
	AUX_RGBImageRec *texture2;
	AUX_RGBImageRec *texture3;
	AUX_RGBImageRec *texture4;
	AUX_RGBImageRec *texture5;
	// weapon textures
	AUX_RGBImageRec *texture6;
	AUX_RGBImageRec *texture7;
	AUX_RGBImageRec *texture8;
	AUX_RGBImageRec *texture9;
	AUX_RGBImageRec *texture10;
	AUX_RGBImageRec *texture11;
	AUX_RGBImageRec *texture12;
	AUX_RGBImageRec *texture13;
	AUX_RGBImageRec *texture14;
	AUX_RGBImageRec *texture15;
	AUX_RGBImageRec *texture16;

	AUX_RGBImageRec *texture17;
	AUX_RGBImageRec *texture18;


	texture1 = auxDIBImageLoad(L"paddle.bmp");
	texture2 = auxDIBImageLoad(L"normal_block.bmp");
	texture3 = auxDIBImageLoad(L"marx_game.bmp");

	texture6 = auxDIBImageLoad(L"death.bmp");
	texture7 = auxDIBImageLoad(L"paddle_bigger.bmp");
	texture8 = auxDIBImageLoad(L"paddle_smaller.bmp");
	texture9 = auxDIBImageLoad(L"ball_bigger.bmp");
	texture10 = auxDIBImageLoad(L"ball_smaller.bmp");
	texture11 = auxDIBImageLoad(L"fireball.bmp");
	texture12 = auxDIBImageLoad(L"baseball.bmp");
	texture13 = auxDIBImageLoad(L"health.bmp");

	texture14 = auxDIBImageLoad(L"indestruct_block.bmp");
	texture15 = auxDIBImageLoad(L"block_phase_1.bmp");
	texture16 = auxDIBImageLoad(L"block_phase_2.bmp");

	texture17 = auxDIBImageLoad(L"title.bmp");
	texture18 = auxDIBImageLoad(L"instructions_use.bmp");

	if (!texture1 || !texture2 || !texture3
		|| !texture6 || !texture7 || !texture8 || !texture9 || !texture10
		|| !texture11 || !texture12 || !texture13 || !texture14 || !texture15 || !texture16
		|| !texture17) {
		printf("Texture load fault\n");
		exit(1);
	}
	// Create Textures
	glGenTextures(1, &texture[0]);
	glBindTexture(GL_TEXTURE_2D, texture[0]);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, texture1->sizeX, texture1->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, texture1->data);
	glGenTextures(1, &block_texture[0]);
	glBindTexture(GL_TEXTURE_2D, block_texture[0]);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, texture2->sizeX, texture2->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, texture2->data);
	glGenTextures(1, &texture[2]);
	glBindTexture(GL_TEXTURE_2D, texture[2]);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, texture3->sizeX, texture3->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, texture3->data);
	glGenTextures(1, &texture[3]);
	glGenTextures(1, &weapon_texture[0]);
	glBindTexture(GL_TEXTURE_2D, weapon_texture[0]);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, texture6->sizeX, texture6->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, texture6->data);
	glGenTextures(1, &weapon_texture[1]);
	glBindTexture(GL_TEXTURE_2D, weapon_texture[1]);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, texture7->sizeX, texture7->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, texture7->data);
	glGenTextures(1, &weapon_texture[2]);
	glBindTexture(GL_TEXTURE_2D, weapon_texture[2]);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, texture8->sizeX, texture8->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, texture8->data);
	glGenTextures(1, &weapon_texture[3]);
	glBindTexture(GL_TEXTURE_2D, weapon_texture[3]);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, texture9->sizeX, texture9->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, texture9->data);
	glGenTextures(1, &weapon_texture[4]);
	glBindTexture(GL_TEXTURE_2D, weapon_texture[4]);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, texture10->sizeX, texture10->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, texture10->data);
	glGenTextures(1, &weapon_texture[5]);
	glBindTexture(GL_TEXTURE_2D, weapon_texture[5]);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, texture11->sizeX, texture11->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, texture11->data);
	glGenTextures(1, &weapon_texture[6]);
	glBindTexture(GL_TEXTURE_2D, weapon_texture[6]);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, texture12->sizeX, texture12->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, texture12->data);
	glGenTextures(1, &weapon_texture[7]);
	glBindTexture(GL_TEXTURE_2D, weapon_texture[7]);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, texture13->sizeX, texture13->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, texture13->data);
	glGenTextures(1, &block_texture[1]);
	glBindTexture(GL_TEXTURE_2D, block_texture[1]);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, texture14->sizeX, texture14->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, texture14->data);
	glGenTextures(1, &block_texture[2]);
	glBindTexture(GL_TEXTURE_2D, block_texture[2]);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, texture15->sizeX, texture15->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, texture15->data);
	glGenTextures(1, &block_texture[3]);
	glBindTexture(GL_TEXTURE_2D, block_texture[3]);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, texture16->sizeX, texture16->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, texture16->data);
	glGenTextures(1, &pictures[0]);
	glBindTexture(GL_TEXTURE_2D, pictures[0]);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, texture17->sizeX, texture17->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, texture17->data);
	glGenTextures(1, &pictures[1]);
	glBindTexture(GL_TEXTURE_2D, pictures[1]);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, texture18->sizeX, texture18->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, texture18->data);

	
}



void trademark_pic(void) { // my trademark pic displayed on screen
	
	glClear (GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glColor3f(1.0, 1.0, 1.0);
	glEnable(GL_TEXTURE_2D);	
	glBindTexture(GL_TEXTURE_2D, texture[2]);
	glBegin(GL_QUADS);
		glTexCoord2f(0.0,0.0); glVertex2f(-1.0,0.0);
		glTexCoord2f(0.0,1.0); glVertex2f(-1.0,1.0);
		glTexCoord2f(1.0,1.0); glVertex2f(1.0,1.0);
		glTexCoord2f(1.0,0.0); glVertex2f(1.0,0.0);	
	glEnd();
	glDisable(GL_TEXTURE_2D);
	glFlush();



}


void block_update(int row, int col) {	// decreases the respected blocks by 1
	
	if (blocks_touched[row][col][0] == 0) {
		blocks_touched[row][col][0] = 1;
	}
	else if (blocks_touched[row][col][0] == -1) {
		blocks_touched[row][col][0] = 0;
	}
	else if (blocks_touched[row][col][0] == -2) {
		blocks_touched[row][col][0] = -1;
	}
	
	

}

void next_level(int level) {	// sets up the next level
	neutralize_weapons(1);
	if (level == 1) {
		game_init(1,lives);
		start_row = 0.4; end_row = 0.2;
		start_col = 0.4; end_col = 0.2;
		clean_array();
		start = 0;
	}
	if (level == 2) {
		game_init(2,lives);
		start_row = 0.6; end_row = 0.2;
		start_col = 0.6; end_col = 0.4;
		clean_array();
		start = 0;
	}
	else if ( level == 3) {
		game_init(3, lives);
		start_row = 0.6; end_row = 0.2;
		start_col = 0.9; end_col = 0.7;
		clean_array();
		start = 0;
	}
	else if ( level == 4) {
		game_init(4, lives);
		start_row = 0.8; end_row = 0.2;
		start_col = 0.9; end_col = 0.7;
		clean_array();
		start = 0;
	}
	else if ( level == 5 ) {
		game_init(5, lives);
		start_row = 0.8; end_row = 0.0;
		start_col = 0.9; end_col = 0.7;
		clean_array();
		start = 0;
	}
	else if ( level == 6) {
		game_init(6, lives);
		start_row = 0.8; end_row = 0.0;
		start_col = 0.7; end_col = 0.5;
		clean_array();
		start = 0;
	}
	else if ( level == 7) {
		game_init(7, lives);
		start_row = 0.8; end_row = 0.0;
		start_col = 0.9; end_col = 0.7;
		clean_array();
		start = 0;
	}
	else if ( level == 8) {
		game_init(8, lives);
		start_row = 0.8; end_row = -0.1;
		start_col = 0.9; end_col = 0.7;
		clean_array();
		start = 0;
	}
	else if ( level == 9) {
		game_init(9, lives);
		start_row = 0.8; end_row = -0.1;
		start_col = 0.9; end_col = 0.7;
		clean_array();
		start = 0;
	}
	else if ( level == 10) {
		game_init(10, lives);
		start_row = 0.8; end_row = -0.1;
		start_col = 0.9; end_col = 0.7;
		clean_array();
		start = 0;
	}
	else if ( level == 11) {
		game_init(11, lives);
		start_row = 0.8; end_row = -0.12;
		start_col = 0.9; end_col = 0.7;
		clean_array();
		start = 0;
	}
	else if ( level == 12) {
		game_init(12, lives);
		start_row = 0.8; end_row = -0.1;
		start_col = 0.9; end_col = 0.7;
		clean_array();
		start = 0;
	}
	else if ( level == 13) {
		game_init(13, lives);
		start_row = 0.8; end_row = -0.1;
		start_col = 0.9; end_col = 0.7;
		clean_array();
		start = 0;
	}
	else if ( level == 14) {
		game_init(14, lives);
		start_row = 0.8; end_row = -0.1;
		start_col = 0.9; end_col = 0.7;
		clean_array();
		start = 0;
	}
	else if ( level == 15) {
		game_init(15, lives);
		start_row = 0.8; end_row = -0.1;
		start_col = 0.9; end_col = 0.7;
		clean_array();
		start = 0;
	}
	else if ( level == 16) {
		game_init(16, lives);
		start_row = 0.8; end_row = -0.8;
		start_col = 0.9; end_col = 0.7;
		clean_array();
		start = 0;
	}
	else {
		playing = false;
		finished = 2;
		clean_array();
		game_over(0);
	}

}

void clean_array(void) {	// assigns weapons to the blocks and configures the correct level
	
	srand(time(NULL));
	int random;
	int seed = 987;
	// assign block untouched and weapon with block
	for ( w = 0; w < 100; w++) {
		for( q = 0; q < 100; q ++) {
			for ( k = 0; k < 2; k++) {
				if (  k == 1) {
					// decide if w weapon is assigned to the block
					random = (int) (((float) rand() / RAND_MAX) * seed) % 5;
					if ( random >= 3) {
						// need to make weapons 0 - 4 more probable
						random = (int) (((float) rand() / RAND_MAX) * seed) % 7;
						if ( random == 5) {
							// one of the better weapons get in here
							random = (int) (((float) rand() / RAND_MAX) * seed) % 3;
							random += 5;
						}
						else if ( random == 6 ) {
							random = 0; // death again i.e. harder
						}

					}
					else random = -1;
					blocks_touched[w][q][1] = random;
				}
				else {
					if (level_number < 3) {
						blocks_touched[w][q][0] = 0;
					}
					else if ( level_number == 3) {
						if ( w == 0 || q == 0 || q == 7) {
							blocks_touched[w][q][0] = -1;
						}
						else blocks_touched[w][q][0] = 0;
					}
					else if ( level_number == 4) {
						if ( w == 0 || w == 1 || q == 0 || q == 7) {
							blocks_touched[w][q][0] = -2;
						}
						else if ( w == 8 || w == 7) {
							blocks_touched[w][q][0] = -1;
						}
						else blocks_touched[w][q][0] = 0;
					}
					else if ( level_number == 5) {
						if ( w == 0 || w == 1 || w == 2 || q == 0 || q == 7) {
							blocks_touched[w][q][0] = -2;
						}
						else blocks_touched[w][q][0] = -1;
					}

					else if (level_number == 6) {
						if ((w >= 10 || w < 2) || (q < 1 || q == 5 )) { // frame resistance
							blocks_touched[w][q][0] = -1;
						}
						else blocks_touched[w][q][0] = -2;
					}
					else if (level_number == 7) { // random resistance resistance
						if ( w == 8 || w == 9 || w == 0 || w == 1) {
							if ( q >= 1 && q <= 6) {
								blocks_touched[w][q][0] = -3;
							}
							else {
								blocks_touched[w][q][0] = 0;
							}
						}
						else if ( q == 3 || q == 4) {
							blocks_touched[w][q][0] = -2;
						}
						else if ( q == 2 || q == 5) {
							blocks_touched[w][q][0] = -1;
						}
						else blocks_touched[w][q][0] = 0;
					}
					else if ( level_number == 8) {
						if ( w == 0 || w == 1) {
							blocks_touched[w][q][0] = -2;
						}
						else if ( w == 2 || w == 3) {
							if ( q >= 1 && q <= 6) {
								blocks_touched[w][q][0] = -3;
							}
							else {
								blocks_touched[w][q][0] = 0;
							}

						}
						else if ( q == 3 || q == 4 ) {
							blocks_touched[w][q][0] = -3;
						}
						else if (w == 4 || w == 5) {
							if ( q == 0 || q == 7) {
								blocks_touched[w][q][0] = 0;
							}
							else if ( q == 2 || q == 5 ) {
								blocks_touched[w][q][0] = -2;
							}
							else {
								blocks_touched[w][q][0] = -1;
							}
						}
						else if (w == 6 || w == 7) {
							if ( q >= 1 && q <= 6) {
								blocks_touched[w][q][0] = -3;
							}
							else {
								blocks_touched[w][q][0] = 0;
							}
						}
						else if ( q == 2 || q == 5 ) {
							blocks_touched[w][q][0] = -2;
						}
						
						else if ( q == 1 || q == 6) {
							blocks_touched[w][q][0] = -1;
						}
						else blocks_touched[w][q][0] = 0;
					}
					else if ( level_number == 9) {
						if ( q % 4 == 0) {
							blocks_touched[w][q][0] = -3;
						}
						else if ( q % 4 == 1) {
							blocks_touched[w][q][0] = -2;
						}
						else if ( q % 4 == 2) {
							blocks_touched[w][q][0] = -1;
						}
						else if ( q % 4 == 3) {
							blocks_touched[w][q][0] = 0;
						}

					}
					else if ( level_number == 10) {
						if ( q == 0 || q == 7 ) {
							blocks_touched[w][q][0] = 0;
						}
						else if ( w >= 10 || (q > 2 && q < 5)) {
							blocks_touched[w][q][0] = -3;
						}
						else if ( q == 2 || q == 5 ) {
							blocks_touched[w][q][0] = -2;
						}
						else if ( q == 1 || q == 6 ) {
							blocks_touched[w][q][0] = -1;
						}

					}
					else if ( level_number == 11 ) { 
						if( w == 0 || w == 1 || w == 13 || w == 12 || q == 0 || q == 7) {
							blocks_touched[w][q][0] = -2;
						}
						else if( w == 2 || w == 3 || w == 11 || w == 10 || q == 1 || q == 6) {
							blocks_touched[w][q][0] = -1;
						}
						else if( w == 4 || w == 5 || w == 9 || w == 8 || q == 2 || q == 5) {
							blocks_touched[w][q][0] = 0;
						}
						else if( w == 6 || w == 7 || q == 3 || q == 4) {
							blocks_touched[w][q][0] = -3;
						}

					}
					else if ( level_number == 12 ) {	// the M
							if ((q == 0 || q == 7) 
								|| ((w == 1 || w == 2) && (q == 1 || q == 6))
								|| ((w == 3 || w == 4) && (( q == 1 || q == 2) || ( q == 5 || q == 6)))
								|| (w >= 5 && w <= 7) && (( q >= 2 && q <= 5))
								|| ((w >= 8 && w <= 10) && (( q >= 3 && q <= 4)))
								) {
									blocks_touched[w][q][0] = 0;
							}
							else {
								blocks_touched[w][q][0] = 1;
								}
					}
					else if ( level_number == 13 ) { // the A
						if (	  ((w == 2 || w == 3) && (q >= 3 && q <= 4))
							|| (( w == 4) && ( q >= 2 && q <= 5))
							|| (( w == 5) && (( q >= 1 && q <= 2) || ( q >= 5 && q <= 6)))
							|| (( w == 6 || w== 10 || w == 11 || w == 12) && (( q >= 0 && q <= 2) || ( q>= 5 && q <= 7)))
							|| ( w == 7 || w == 8 || w == 9)
								) {
									blocks_touched[w][q][0] = -1;
						}
						else {
							blocks_touched[w][q][0] = 1;
						}

					}
					else if ( level_number == 14 ) { // the R
						if (	  ((w == 1) && (q >= 3 && q <= 4))
							|| ((w == 2) && (q >= 2 && q <= 4))
							|| ((w == 3) && (q == 2 || q == 5))
							|| ((w == 4) && (q == 1 || q == 2 || q == 5))
							|| (( w == 5) && (( q >= 1 && q <= 2)|| (q >= 4 && q <= 5)))
							|| ((w == 6) && (q >= 1 && q <= 4))
							|| ((w == 7) && (q >= 1 && q <= 3))
							|| ((w == 8) && (q >= 1 && q <= 5))
							|| (( w == 9 || w == 10) && (( q >= 1 && q <= 2) || ( q >= 4 && q <= 5)))
							|| (( w == 11) && (( q >= 1 && q <= 1) || ( q >= 5 && q <= 6)))
							|| (( w == 12) && (( q >= 1 && q <= 1) || ( q >= 5 && q <= 6)))
								) {
									blocks_touched[w][q][0] = -2;
						}
						else {
							blocks_touched[w][q][0] = 1;
						}
					}
					else if ( level_number == 15 ) { // the X
						if (	 (( w == 0 || w == 12) && ( q == 0 || q == 7))
							|| (( w == 1 || w == 11) && (( q >= 0 && q <= 1) || ( q >= 6 && q <= 7)))
							|| (( w == 2 || w == 10) && (( q >= 0 && q <= 1) || ( q >= 6 && q <= 7)))
							|| (( w == 3 || w == 9) && (( q >= 1 && q <= 2) || ( q >= 5 && q <= 6)))
							|| (( w == 4 || w == 8) && (( q >= 1 && q <= 2) || ( q >= 5 && q <= 6)))
							|| (( w == 5 || w == 7) && (( q >= 2 && q <= 3) || ( q >= 4 && q <= 5)))
							|| (( w == 6) && (( q >= 3 && q <= 4)))

								) {
									blocks_touched[w][q][0] = -2;
						}
						else {
							blocks_touched[w][q][0] = 1;
						}
					}
					else if (level_number == 16 ) { 
						if ( w >= 0 && w <= 3) {
							blocks_touched[w][q][0] = -2;
						}
						else if ( w == 4 || w == 5) {
							if ( q == 3 || q == 4) {
								blocks_touched[w][q][0] = -3;
							}
							else blocks_touched[w][q][0] = -1;
						}
						else if ( w == 6 || w == 7 || w == 8 || w == 9) {
							if ( q >= 1 && q <= 6) {
								blocks_touched[w][q][0] = -3;
							}
							else blocks_touched[w][q][0] = -1;
						}
						else if ( w >= 10 && w <= 11) {
							if ( q == 3 || q == 4) {
								blocks_touched[w][q][0] = -3;
							}
							else blocks_touched[w][q][0] = -1;
						}
						else if ( (w >= 12 && w <= 21) && ( q >= 2 && q <= 5)) {
								blocks_touched[w][q][0] = 1;
						}
						else if ( w >= 22 ) {
							blocks_touched[w][q][0] = 1;
						}
						else blocks_touched[w][q][0] = -2;
					}

					seed++;
				}
			}
		}
	}
}

void setup_lights(void) {	// sets up all the lights used
	glClearColor (0.0, 0.0, 0.0, 0.0);
		
	glShadeModel (GL_SMOOTH);
		glEnable(GL_DEPTH_TEST);
		// set up light 0
		GLfloat position0[] = {1.0, 1.0, 1.0, 0.0};
		GLfloat diffuse0[] = {1.0, 1.0, 1.0, 1.0};
		GLfloat specular0[] = {1.0, 1.0, 1.0, 1.0};
		GLfloat ambient0[] = {0.1, 0.1, 0.1, 1.0};
		glEnable(GL_LIGHTING);
		glEnable(GL_LIGHT0);
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glLightfv(GL_LIGHT0, GL_POSITION, position0);
		glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse0);
		glLightfv(GL_LIGHT0, GL_SPECULAR, specular0);
		glLightfv(GL_LIGHT0, GL_AMBIENT, ambient0);
		// define current material
		GLfloat matAmbient[] = {0.33, 0.22, 0.03, 1.0};
		GLfloat matDiffuse[] = {0.78, 0.57, 0.11, 1.0};
		GLfloat matSpecular[] = {0.99, 0.91, 0.81, 1.0};
		GLfloat matShininess = 27.8;
		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, matAmbient);
		glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, matDiffuse);
		glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, matSpecular);
		glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, matShininess);

}


void intro(int option) {	// the intro screen
	// its basically a massive texture
	glClear (GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glColor3f(1.0, 1.0, 1.0);
	glEnable(GL_TEXTURE_2D);	
	glBindTexture(GL_TEXTURE_2D, pictures[0]);



	glBegin(GL_QUADS);
		glTexCoord2f(0.0,0.0); glVertex2f(-1.0,-1.0);
		glTexCoord2f(0.0,1.0); glVertex2f(-1.0,1.0);
		glTexCoord2f(1.0,1.0); glVertex2f(1.0,1.0);
		glTexCoord2f(1.0,0.0); glVertex2f(1.0,-1.0);	
	glEnd();
	glDisable(GL_TEXTURE_2D);
	glFlush();

}
	



void intro_off(int value) { // turn the intro off after 4 secs ( done above in the display())
	show_picture++;
	if (show_picture == 3) {
		intro_now = false;
	}

}


void show_menu(void) { // show the menu
	played = 0;
	finished = 0;
	glClear (GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glColor3f(1.0, 1.0, 1.0);
	glEnable(GL_TEXTURE_2D);	
	glBindTexture(GL_TEXTURE_2D, pictures[1]);
	glBegin(GL_QUADS);
		glTexCoord2f(0.0,0.0); glVertex2f(-1.0,-1.0);
		glTexCoord2f(0.0,1.0); glVertex2f(-1.0,1.0);
		glTexCoord2f(1.0,1.0); glVertex2f(1.0,1.0);
		glTexCoord2f(1.0,0.0); glVertex2f(1.0,-1.0);	
	glEnd();
	glDisable(GL_TEXTURE_2D);
	glFlush();

}

void speed_up(int value) {	// speeds up the ball by a fraction every so often
	if ( value == 0 && playing == true && start != 0) {
		if ( width < 1280 ) {
			ball_speed_x *= 1.00133 * ( 1280 / width);		
		}
		if ( height < 1024 ) {	
			ball_speed_y *= 1.00133 * ( 1024 / height);
		}
		if ( width > 1280 ) {
			ball_speed_x *= 1.00133 * ( 1280 / width);		
		}
		if ( height > 1024 ) {	
			ball_speed_y *= 1.00133 * ( 1024 / height);
		}
		else {
			ball_speed_x *= 1.00133;		
			ball_speed_y *= 1.00133;
		}

	}

}

