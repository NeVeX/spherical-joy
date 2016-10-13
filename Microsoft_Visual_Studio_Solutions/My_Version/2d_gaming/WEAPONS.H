

void show_weapon(int weapon, float weapon_move_x, float weapon_move_y, float cube_size) {
	// displays the falling weapon on screen, uses textures
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	
	glColor3f(1.0, 1.0, 1.0);
	glEnable(GL_TEXTURE_2D);	
	glBindTexture(GL_TEXTURE_2D, weapon);
	glBegin(GL_QUADS);
		glTexCoord2f(0.0,0.0); glVertex2f(weapon_move_x - cube_size, weapon_move_y - cube_size);
		glTexCoord2f(0.0,1.0); glVertex2f(weapon_move_x - cube_size, weapon_move_y + cube_size);
		glTexCoord2f(1.0,1.0); glVertex2f(weapon_move_x + cube_size, weapon_move_y + cube_size);
		glTexCoord2f(1.0,0.0); glVertex2f(weapon_move_x + cube_size, weapon_move_y - cube_size);	
	glEnd();
	glDisable(GL_TEXTURE_2D);
	glFlush();

}

