// ------------------------
// --- General constants --
// ------------------------
#define SCREEN_WIDTH (2048 / 2)
#define SCREEN_HEIGHT (1535 / 2)

// ------------------------
// ---- Menu constants ----
// ------------------------
// Title/Background constants
#define BACKGROUND_FILENAME "../assets/background-small.png"
#define BACKGROUND_X 0
#define BACKGROUND_Y 0
#define TITLE_FILENAME "../assets/title-small.png"
#define TITLE_WIDTH 588
#define TITLE_X (0.5 * (SCREEN_WIDTH - TITLE_WIDTH))
#define TITLE_Y (0.05 * SCREEN_HEIGHT)
// Play/quit constants
#define PLAY_FILENAME "../assets/play-small.png"
#define PLAY_WIDTH 122
#define PLAY_X (0.25 * SCREEN_WIDTH - 0.5 * PLAY_WIDTH)
#define PLAY_Y (0.45 * SCREEN_HEIGHT)
#define QUIT_FILENAME "../assets/quit-small.png"
#define QUIT_WIDTH 160
#define QUIT_X (0.75 * SCREEN_WIDTH - 0.5 * QUIT_WIDTH)
#define QUIT_Y (0.45 * SCREEN_HEIGHT)
// Difficulty constants
#define DIFFICULTY_FILENAME "../assets/difficulty-small.png"
#define DIFFICULTY_WIDTH 325
#define DIFFICULTY_X (0.5 * SCREEN_WIDTH - 0.5 * DIFFICULTY_WIDTH)
#define DIFFICULTY_Y (0.7 * SCREEN_HEIGHT)
#define EASY_FILENAME "../assets/easy-small.png"
#define EASY_WIDTH 103
#define EASY_X (0.5 * SCREEN_WIDTH - 1.5 * EASY_WIDTH)
#define EASY_Y (0.85 * SCREEN_HEIGHT)
#define MEDIUM_FILENAME "../assets/medium-small.png"
#define MEDIUM_WIDTH 118
#define MEDIUM_X ((0.5 * SCREEN_WIDTH - 1.35 * MEDIUM_WIDTH) + EASY_WIDTH)
#define MEDIUM_Y (0.85 * SCREEN_HEIGHT)
#define HARD_FILENAME "../assets/hard-small.png"
#define HARD_WIDTH 86
#define HARD_X ((0.5 * SCREEN_WIDTH - 1.8 * HARD_WIDTH) + EASY_WIDTH + MEDIUM_WIDTH)
#define HARD_Y (0.85 * SCREEN_HEIGHT)
// Menu sound constants
#define MENU_MUSIC "../assets/menu_music.mp3"
#define MENU_SELECT_SOUND "../assets/menu_select_music.mp3"

// ------------------------
// ---- Game constants ----
// ------------------------
// Obstacles constants
#define NUM_SECTIONS 6
#define ROTATION_SPEED 0.01
#define ROTATION_MIN_TIME 4000
#define ROTATION_MAX_TIME 12000
// Arc constants
#define ARC_INITIAL_RADIUS 800
#define ARC_MIN_RADIUS 50
#define ARC_SPEED_MIN 3
#define ARC_SPEED_MAX 6
#define ARC_THICKNESS 10
#define ARC_NUM 6
// Player cursor constants
#define CIRCLE_RADIUS 50
#define TRIANGLE_SIZE 15
#define TRIANGLE_OFFSET 8
#define TRIANGLE_MOVE_ANGLE 10.0
// Game sound constants
#define GAME_MUSIC "../assets/game_music.mp3"
#define GAME_OVER_SOUND "../assets/game_over_music.mp3"
// Sprites
#define GAME_DIGITS "../assets/digits-small.png"