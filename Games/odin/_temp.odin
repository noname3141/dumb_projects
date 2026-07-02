package main

import rl "vendor:raylib"
import "core:math/rand"

GRAVITY :: 900
JUMP_VEL :: -300
MOVE_SPEED::180

SCREEN_W::640
SCREEN_H::480

PLAYER_SIZE::50
PIPE_W::50

Pipe :: struct{
	pos:f32,
	gap:f32,
}

main :: proc(){
	rl.InitWindow(640,480,"flappy bird")
	rl.SetTargetFPS(60)

	player_pos: f32 =0
	player_vel: f32 =0
	player_alive:=true

	pipe_timer:f32=0.0
	pipe_list: [dynamic]Pipe

	for !rl.WindowShouldClose(){

		dt:=rl.GetFrameTime()

		if player_alive {            
			if rl.IsKeyPressed(.SPACE){
				player_vel=JUMP_VEL
			}else{player_vel+=GRAVITY*dt}

			player_pos+=player_vel*dt

			if player_pos > (SCREEN_H-PLAYER_SIZE){
				player_alive=false
			}

			pipe_timer+=dt

			if pipe_timer > 1.5 {
				append (&pipe_list, Pipe{
					pos = SCREEN_W,
					gap = rand.float32_range(20,SCREEN_H-120)
				})
				pipe_timer=0
			}

			#reverse for &pipe,i in pipe_list{
				pipe.pos -= MOVE_SPEED*dt

				if pipe.pos< -PIPE_W {
					unordered_remove(&pipe_list,i)
				}
			}



		} else {
			if rl.IsKeyPressed(.SPACE) {
				player_pos = (SCREEN_H-PLAYER_SIZE)*0.5
				player_vel = JUMP_VEL
				player_alive = true
			}
		}


		rl.BeginDrawing()
		rl.ClearBackground(rl.BLACK)

		rl.DrawRectangle(50, i32(player_pos), PLAYER_SIZE,PLAYER_SIZE, rl.RED)

		for pipe in pipe_list {
			rl.DrawRectangle(i32(pipe.pos),0,PIPE_W,i32(pipe.gap),rl.GREEN)
			rl.DrawRectangle(i32(pipe.pos),i32(pipe.gap)+100,PIPE_W,SCREEN_H-i32(pipe.gap),rl.GREEN)
		}

		if !player_alive {
			rl.DrawText("You Died",50,SCREEN_H*0.5-20,40,rl.RED)
			rl.DrawText("(Jump to Respawn)",50,SCREEN_H*0.5+40,40,rl.RED)
		}

		rl.EndDrawing()
	}

	rl.CloseWindow()

}
