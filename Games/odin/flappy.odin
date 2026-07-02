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

AABB :: struct{
    min: [2]f32,
    max: [2]f32,
}

background_png_data := #load("bg.png")
game_over_png_data := #load("game_over.png")

gen_aabb :: proc(pos, size: [2]f32) -> AABB{
    return {pos, pos + size};
}

aabb_vs_aabb :: proc(a,b:AABB)->bool{
    range_overlap :: proc(a_min, a_max, b_min, b_max: f32)->bool{
        return a_max > b_min && b_max > a_min
    }

    return range_overlap(a.min.x, a.max.x, b.min.x, b.max.x) &&
           range_overlap(a.min.y, a.max.y, b.min.y, b.max.y)

}
main :: proc(){
	rl.InitWindow(640,480,"flappy bird")
	rl.SetTargetFPS(60)
    
    count := 0

	player_pos: f32 =0
	player_vel: f32 =0
	player_alive:=true

	pipe_timer:f32=0.0
	pipe_list: [dynamic]Pipe
    
    back_offset : f32
    BG_SPEED :: 50

    gb_texture := rl.LoadTextureFromImage(
            rl.LoadImageFromMemory(
                ".png", raw_data(background_png_data), i32(len(background_png_data))
            )
    )

    game_over_texture := rl.LoadTextureFromImage(
            rl.LoadImageFromMemory(
                ".png", raw_data(game_over_png_data), i32(len(game_over_png_data))
            )
    )

	for !rl.WindowShouldClose(){

		dt:=rl.GetFrameTime()

		if player_alive {            
			if rl.IsKeyPressed(.SPACE){
				player_vel=JUMP_VEL
			}else{player_vel+=GRAVITY*dt}

			player_pos+=player_vel*dt

            player_box := gen_aabb({50, player_pos}, PLAYER_SIZE)

            if(player_pos < 0){
            player_pos = 0;
            player_vel = 0;
            }
			else if player_pos > (SCREEN_H-PLAYER_SIZE){
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

                pipe_box_upper := gen_aabb({pipe.pos, 0}, {PIPE_W, pipe.gap})
                pipe_box_lower := gen_aabb({pipe.pos, pipe.gap + 100}, {PIPE_W, SCREEN_H - pipe.gap})
			    
                if aabb_vs_aabb(player_box, pipe_box_upper) || aabb_vs_aabb(player_box, pipe_box_lower)
                {
                    player_alive = false
                    break;
                }
                
            }


            back_offset += BG_SPEED * dt;
            if back_offset > SCREEN_W {
                back_offset = 0
            }

		} else {
			if rl.IsKeyPressed(.SPACE) {
                clear(&pipe_list)
				player_pos = (SCREEN_H-PLAYER_SIZE)*0.5
				player_vel = JUMP_VEL
				player_alive = true
			}
		}


		rl.BeginDrawing()
		rl.ClearBackground(rl.BLACK)
        

        rl.DrawTexture(gb_texture, i32(-back_offset), 0, rl.WHITE)
        rl.DrawTexture(gb_texture, i32(-back_offset) + SCREEN_W, 0, rl.WHITE)

		rl.DrawRectangle(50, i32(player_pos), PLAYER_SIZE,PLAYER_SIZE, rl.RED)

		for pipe in pipe_list {
			rl.DrawRectangle(i32(pipe.pos),0,PIPE_W,i32(pipe.gap),rl.GREEN)
			rl.DrawRectangle(i32(pipe.pos),i32(pipe.gap)+100,PIPE_W,SCREEN_H-i32(pipe.gap),rl.GREEN)
		}

		if !player_alive {
            rl.DrawTexture(game_over_texture, 0, 0, rl.WHITE)
		}

		rl.EndDrawing()
	}

	rl.CloseWindow()

}
