
// displays all the info at the top of the screen
void HUD(int position, int info, char *string) {
	
	char *c;
	char my_string[10];

	sprintf_s(my_string, "  %d", info);

	if ( position == 1 ) {
		glRasterPos2f(-0.97, 0.93);  // levels
			for (c = string; *c != '\0'; c++) {
				glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *c);
		}
		glRasterPos2f(-0.85, 0.93);
			for (c = my_string; *c != '\0'; c++) {
				glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *c);
		}
			
	}
	else if ( position == 2) {
		glRasterPos2f(0.8, 0.93);	// lives
		  for (c = string; *c != '\0'; c++) {
				glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *c);
		  }
		  glRasterPos2f(0.92, 0.93);
		  for (c = my_string; *c != '\0'; c++) {
				glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *c);
		  }
	}
	else if ( position == 3) {
		glColor3f(0.9, 0.0, 0.0);
				glRasterPos2f(-0.3, -0.3);	// space bar notification
				  for (c = string; *c != '\0'; c++) {
						glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *c);
				  }
	}

	if (position == 5) {
		glRasterPos2f(-0.15, 0.00);
		for (c =string; *c != '\0'; c++) {
			glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *c);
		}

	}



	glFlush();

}
