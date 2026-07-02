package main

import rl "vendor:raylib"
import "core:math/rand"

GRAVITY :: 1000
JUMP_FORCE :: -400

PIPE_SIZE :: 60;
PIPE_w :: 40;

MOVE_SPEED :: 200;

Pipe :: struct {
    pos : f32,
    gap : f32,
}

main :: proc() {

    rl.InitWindow(800, 600, "Flappy bird")

    px : f32 = 50;
    py : f32 = 275;
    yvel : f32 = 0;
    palive := true;
    pipe_timer : f32= 0;
    pipe_list : [dynamic] Pipe;
    //texture := rl.LoadTexture("~/Downloads/backgr.png");
    //defer rl.CloseWindow();

    for !rl.WindowShouldClose(){
        dt := rl.GetFrameTime();
        rl.SetTargetFPS(60);
        rl.ClearBackground(rl.BLACK);
        //rl.DrawTexture(texture, 0, 0, rl.WHITE);
        
        if palive {
            if(rl.IsKeyPressed(.SPACE)){
                yvel = JUMP_FORCE;
            }
            else{
                yvel += GRAVITY * dt;
            }
            py += yvel * dt;
        } else {
            if(rl.IsKeyPressed(.SPACE)){
                py = 275;
                yvel = JUMP_FORCE;
                palive = true;
            }
        }

        pipe_timer += dt;

        if pipe_timer > 1{
            
            append(&pipe_list, Pipe {
                pos = f32(rl.GetScreenWidth()),
                gap = rand.float32_range(f32(20), f32(rl.GetScreenHeight() - 120))
            })

            pipe_timer = 0;
        }

        #reverse for &pipe, i in pipe_list {
            pipe.pos -= MOVE_SPEED * dt;
            if pipe.pos < -PIPE_w {
                unordered_remove(&pipe_list, i);
            }
        }

        rl.BeginDrawing();
        
        rl.DrawRectangle(i32(px), i32(py), 50, 50, rl.BLUE);
        
        for pipe in pipe_list {
            rl.DrawRectangle(i32(pipe.pos), 0, PIPE_w, i32(pipe.gap), rl.GREEN);
            rl.DrawRectangle(i32(pipe.pos), i32(pipe.gap) + 100, PIPE_w, rl.GetScreenHeight() - i32(pipe.gap) - 100, rl.GREEN);
        }

        if(!palive){
            rl.DrawText("Player Ded", 400, 300 - 10, 20, rl.BLUE);
        }
        
        if(py > f32(rl.GetScreenHeight())){
            palive = false;
        } 
        rl.EndDrawing();

    }

}
