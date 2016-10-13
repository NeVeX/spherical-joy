
// this plays the correct sound when called
// it cannot play 2 sounds simultaneously but it still adds to a nice effect in the game
void play(int select) {
	
	if (select == 1) {
		PlaySound(L"Bang.wav", NULL, SND_ASYNC | SND_FILENAME);
	}
	if (select == 2) {
		PlaySound(L"Boing.wav", NULL, SND_ASYNC | SND_FILENAME);
	}
	if (select == 3) {
		PlaySound(L"game_music.wav", NULL, SND_ASYNC | SND_LOOP | SND_FILENAME);
	}
	if (select == 4) {
		PlaySound(L"marx_pro.wav", NULL, SND_ASYNC | SND_FILENAME);
	}
	if (select == 5) {
		PlaySound(L"death.wav", NULL, SND_ASYNC | SND_FILENAME);
	}
	if (select == 6) {
		PlaySound(L"fireball.wav", NULL, SND_ASYNC | SND_FILENAME);
	}
	if (select == 7) {
		PlaySound(L"weapon_collect.wav", NULL, SND_ASYNC | SND_FILENAME);
	}
	if (select == 8) {
		PlaySound(L"dest_block.wav", NULL, SND_ASYNC | SND_FILENAME);
	}

}

