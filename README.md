# spherical-joy
The 2d (C, OpenGL, GLUT) game I made - similar to the Breakout series

## Project Name:	Spherical Joy v1.00a

## OverView:
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

## Notes:
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
	
## Issues (Note this was years ago, before I knew about frame rates correctly)

You will find in these folders that there are TWO versions of everything from source code
to executables.
This is because all testing of the game was done on my personal computer and everything
was working perfectly. But when I tried to execute the game in the college or on another
computer the sphere would move very very slowly [a major annoyance]. You will find out from
playing the game that you need the sphere to move at pace for it to be of any challenge to 
the player.
So when I realized this, the day before it was due to be handed up, I made a second version 
that would execute fine [i.e. the sphere would move at pace]. But it would move so incredibly
fast on my computer. So I am not so sure if the second version [THE COMPATIBLE VERSION] will 
solve all the sphere issues. But if the sphere moves too slow or too fast even after both
version have being tried then you can compile the compatible source codes, 
and in the main.cpp file,
	change the variable 'offset' to something to make the game run correctly.
	i.e. change it to a lower value than 0.0038 if the game moves to fast or change
		it to a higher number if the sphere moves too slow.

The second version has this offset variable coded into it so that you only need to change
one variable once to make everything work and not have to change alot of code.
But this stopped me playing the game properly on my computer, so that's why there is two 
versions.

So to summarize :
	Play My_Version first.
		if that doesn't work correctly
			Play Compatible Version
				If that doesn't work
					Compile Compatible Version source code
					changing the offset variable.
