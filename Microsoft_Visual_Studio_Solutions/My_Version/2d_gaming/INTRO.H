

void intro_setup(int played, int finished) {

// the intro setuo and the menu apperance
	// it displays if game is over 
	// of if you finshed the game
	// and also displays the option to select the instructions

	char *c;
	char *intro_string;

	intro_string = "A MarX Production Gaming Experience";

	glColor3f(0.9, 0.0, 0.0);
	glRasterPos2f(-0.35, -0.1); 
			
	for (c = intro_string; *c != '\0'; c++) {
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *c);
		}

	glRasterPos2f(-0.35, -0.2);
	intro_string = "Press the ENTER key to begin....";

	for (c = intro_string; *c != '\0'; c++) {
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *c);
		}
	glRasterPos2f(-0.9, -0.9);
	intro_string = "Press M for Instructions";

	for (c = intro_string; *c != '\0'; c++) {
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *c);
		}


	if ( played == 1) {
	glColor3f(1.0, 1.0, 0.0);
	glRasterPos2f(-0.30, -0.3);
	intro_string = "Game Over.";
		for (c = intro_string; *c != '\0'; c++) {
			glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *c);
		}
	}

	if ( finished == 2) {
	glColor3f(1.0, 1.0, 0.0);
	glRasterPos2f(-0.3, -0.4);
	intro_string = "You Finished The Game.";
		for (c = intro_string; *c != '\0'; c++) {
			glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *c);
		}
	glRasterPos2f(-0.3, -0.5);
	intro_string = "CONGRATULATIONS!";
		for (c = intro_string; *c != '\0'; c++) {
			glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *c);
		}
	}


	



	glFlush();
		

}

