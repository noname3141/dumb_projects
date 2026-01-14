#include <stdio.h>
#include <raylib.h>
#include <time.h>

typedef struct{
    int x, y;
    int length;
    int speed_x;
    int speed_y;
} Snake;

typedef struct{
    int x, y;
    bool eaten;
} Fruit;

//Location of fruit
void Loc(Fruit *fru){
    fru->x = GetRandomValue(1, GetScreenWidth()/10);
    fru->y = GetRandomValue(1, GetScreenHeight()/10);
}

//Movement
void Update(Snake* S){
    if(IsKeyDown(KEY_UP)){
        S->speed_y = -10;
        S->speed_x = 0;
    }
    else if(IsKeyDown(KEY_DOWN)){
        S->speed_y = +10;
        S->speed_x = 0;
    }
    else if(IsKeyDown(KEY_LEFT)){
        S->speed_x = -10;
        S->speed_y = 0;
    }
    else if(IsKeyDown(KEY_RIGHT)){
        S->speed_x = +10;
        S->speed_y = 0;
    }
}

//Draw
void DrawSnake(Snake *S){
    DrawRectangle(S->x+1, S->y+1, 9, 9, WHITE);
}


void DrawFruit(Fruit* fru){
    int px = fru->x * 10;
    int py = fru->y * 10;
    DrawCircle(px + 5, py + 5, 5, WHITE);
}

int main(){
    const int Length = 1280, Width = 800;
    InitWindow(Length, Width, "Snake.io");
    SetTargetFPS(10);
    
    int i=1;
    //Snake
    Snake S;
    S.x = 10;
    S.y = 10;
    S.length = 1;
    S.speed_x = 0;
    S.speed_y = 0;
    //Fruit
    Fruit F;
    F.eaten = false;
    Loc(&F);

    while(!WindowShouldClose()){
        BeginDrawing();
        if(i>=S.length+1){
            ClearBackground(BLACK);
            i=1;
        }
        i++;
        //Snake logic
        DrawSnake(&S);

        //Fruit logic
        if((F.x*10) == S.x && (F.y*10) == S.y){
            F.eaten = true;
            S.length ++;
        }
        if(F.eaten == true){
            Loc(&F);
            F.eaten = false;
        }
        DrawFruit(&F);
        
        //Snake moving logic
        Update(&S);
        S.x += S.speed_x;
        S.y += S.speed_y;
        if(S.x < 0) S.x=(GetScreenWidth()-10);
        if(S.x > GetScreenWidth() - 10) S.x=(0);
        if(S.y < 0) S.y=(GetScreenHeight()-10);
        if(S.y > GetScreenHeight() - 10) S.y=(0);

        EndDrawing();
    }

    CloseWindow();
}
