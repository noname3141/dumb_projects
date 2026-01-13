#include <stdio.h>
#include <raylib.h>

// Ball
typedef struct {
    float x, y;
    int speed_x, speed_y;
    int rad;
} Ball;

Ball ball;

void DrawBall(Ball *ball){
    DrawCircle(ball->x, ball->y, ball->rad, WHITE);
}

void BallUpdate(Ball *b){
    b->x += b->speed_x;
    b->y += b->speed_y;
}

//Paddle
typedef struct{
    float x, y;
    int speed;
    int h, w;
} Paddle;

Paddle Pad1;
Paddle Pad2;

void DrawPaddle(Paddle *Pad){
    DrawRectangle(Pad->x, Pad->y, Pad->w, Pad->h, WHITE);
}

void PadUpdate(Paddle *Pad){
    if(IsKeyDown(KEY_UP) && Pad->y >= 20){
        Pad->y = Pad->y - Pad->speed;
    }
    else if(IsKeyDown(KEY_DOWN) && Pad->y <= (GetScreenHeight() - Pad->h - 20)){
        Pad->y = Pad->y + Pad->speed;
    }
}

void AIUpdate(Paddle *Pad, Ball *ball){
    if(ball->speed_x < 0) return;
    int padcenter = Pad->y + Pad->h/2;
    if(ball->y + 10 >= padcenter && Pad->y <= (GetScreenHeight() - (Pad->h + 20))){
        Pad->y += Pad->speed;
    }
    
    if(ball->y - 10 <= padcenter && Pad->y >= 20){
        Pad->y -= Pad->speed;
    }
    
    if (Pad->y < 20)
    Pad->y = 20;
    
    if (Pad->y > GetScreenHeight() - Pad->h - 20)
    Pad->y = GetScreenHeight() - Pad->h - 20;

}

int main(){
    const int width = 1280, height = 800;
    //score
    int Player = 0;
    int CPU = 0;

    //ball
    ball.rad = 20;
    ball.x = width/2;
    ball.y = height/2;
    ball.speed_x = 10;
    ball.speed_y = 10;

    //paddles
    Pad1.h = 120;
    Pad1.w = 25;
    Pad1.x = 10;
    Pad1.y = height/2 - Pad1.h/2;
    Pad1.speed = 10;
    Pad2.h = 120;
    Pad2.w = 25;
    Pad2.x = width - (Pad1.w + 10);
    Pad2.y = height/2 - Pad1.h/2;
    Pad2.speed = 8;

    InitWindow(width, height, "My Pong game");
    SetTargetFPS(60);
    
    while(WindowShouldClose() == false){
        ClearBackground(BLACK);
        BeginDrawing();
        
        DrawPaddle(&Pad1);
        DrawPaddle(&Pad2);
        DrawLine(width/2, 0, width/2, height, GRAY);
        DrawBall(&ball);

        BallUpdate(&ball);
        PadUpdate(&Pad1);
        AIUpdate(&Pad2, &ball);
        
        if(ball.x <= ball.rad || ball.x >= (GetScreenWidth() - ball.rad)){
            ball.speed_x = -ball.speed_x;
            if(ball.x < GetScreenWidth()/2){
                CPU += 1;
            }
            else{
                Player += 1;
            }
        }
        DrawText(TextFormat("AI: %d", CPU), GetScreenWidth()/2 + 30, 20, 30, WHITE);
        DrawText(TextFormat("P1: %d", Player), GetScreenWidth()/2 - 95, 20, 30, WHITE);
        
        if(ball.y <= ball.rad || ball.y >= (GetScreenHeight() - ball.rad)){
            ball.speed_y = -ball.speed_y;
        }

        if(Pad1.y <= (ball.y + ball.rad) && (ball.y - ball.rad)<= (Pad1.y + Pad1.h) && (ball.x - ball.rad) <= (10 + Pad1.w)){
            ball.speed_x = -ball.speed_x;
        }
        if(Pad2.y <= (ball.y + ball.rad)  && (ball.y - ball.rad) <= (Pad2.y + Pad2.h) && (ball.x + ball.rad) >= (GetScreenWidth() - (10 + Pad2.w))){
            ball.speed_x = -ball.speed_x;
        }
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
