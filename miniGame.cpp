#include <raylib.h>

class player {
public:
	const int playerRadius = 20;
	float playerposx = 300;
	float playerposy = 300;
};

struct colorpallets {
	Color circleColor = BLUE;

	colorpallets() {
		int r = GetRandomValue(50, 255);
		int g = GetRandomValue(50, 255);
		int b = GetRandomValue(50, 255);

		circleColor.r = r;
		circleColor.g = g;
		circleColor.b = b;
		circleColor.a = 255;
	}
};

void DrawingOnScreen(float &playerposx, float &playerposy, const int &playerRadius, Color& circleColor, int& score, int &scoreMissed, Vector2& mousePos) {
	DrawText(TextFormat("Hit: %d ", score), 10, 10, 20, GREEN);
	DrawText(TextFormat("Missed: %d ", scoreMissed), 490, 10, 20, RED);

	DrawCircle(playerposx, playerposy, playerRadius, circleColor);

	int crosshairSize = 6;
	DrawLine(mousePos.x - crosshairSize, mousePos.y, mousePos.x + crosshairSize, mousePos.y, WHITE);
	DrawLine(mousePos.x, mousePos.y - crosshairSize, mousePos.x, mousePos.y + crosshairSize, WHITE);
}

int main() {
	const float screenWidth = 600;
	const float screenHeight = 600;

	player player;
	colorpallets pallet;
	Color circleColor = pallet.circleColor;

	InitWindow(screenWidth, screenHeight, "Tracking Lab Learning");
	DisableCursor();

	int score = 0;
	int scoreMissed = 0;

	bool gamestarted = false;
	float countdown = 3.0f;

	float timer = 0.0f;
	float interval = 1.0f;


	InitAudioDevice();

	Sound bgsound = LoadSound("sounds/tapsound.mp3");
	Sound bgmusic = LoadSound("sounds/cosy.mp3");

	PlaySound(bgmusic);

	SetSoundVolume(bgsound, 1.0f);
	SetSoundVolume(bgmusic, 0.4f);

	SetTargetFPS(60);


	while (!WindowShouldClose()) {
		float deltaTime = GetFrameTime();

		if (!gamestarted) {
			countdown -= deltaTime;

			int displayCountdown = (int)countdown + 1;
			if (displayCountdown > 0) {
				const char* text = TextFormat("Starting in: %d", (int)countdown + 1);
				int fontsize = 50;
				int textWidth = MeasureText(text, fontsize);
				int x = (screenWidth / 2) - (textWidth / 2);
				int y = 200;

				BeginDrawing();
				ClearBackground(BLACK);
				DrawText(text, x, y, fontsize, YELLOW);
				EndDrawing();
			}
			else {
				gamestarted = true;
			}
			continue;
		}

		timer += deltaTime;

		if (timer >= interval) {
			player.playerposx = GetRandomValue(player.playerRadius, screenWidth - player.playerRadius);
			player.playerposy = GetRandomValue(player. playerRadius, screenHeight - player.playerRadius);

			scoreMissed++;
			timer = 0.0f;
		}

		Vector2 mousePos = GetMousePosition();

		if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
			float dx = mousePos.x - player.playerposx;
			float dy = mousePos.y - player.playerposy;

			if ((dx * dx + dy * dy) <= (player.playerRadius * player.playerRadius)) {
				score++;

				pallet = colorpallets();
				circleColor = pallet.circleColor;

				PlaySound(bgsound);
				timer = 0.0f;
				player.playerposx = GetRandomValue(player.playerRadius, screenWidth - player.playerRadius);
				player.playerposy = GetRandomValue(player.playerRadius, screenHeight - player.playerRadius);
			}
		}
		BeginDrawing();
		ClearBackground(BLACK);

		DrawingOnScreen(player.playerposx, player.playerposy, player.playerRadius, circleColor, score, scoreMissed, mousePos);

		EndDrawing();
	}
	CloseAudioDevice();
	CloseWindow();

	return 0;
}