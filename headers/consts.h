#pragma once
// Defini��es
#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 420
#define PADDLE_WIDTH 10
#define PADDLE_HEIGHT 60
#define BALL_SIZE 10
#define FPS 30
#define OFFSET 60

#define KEY_SEEN     1
#define KEY_RELEASED 2
// Estruturas
typedef struct {
    float x, y;
    float speedY;
} Paddle;

typedef struct {
    float x1, y1;
    float x2, y2;
} Button;

typedef struct {
    float x, y;
    float speedX, speedY;
} Ball;
