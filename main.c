/*******************************************************************************************
*
*   raylib [models] example - Load 3d model with animations and play them
*
*   Example originally created with raylib 2.5, last time updated with raylib 3.5
*
*   Example contributed by Culacant (@culacant) and reviewed by Ramon Santamaria (@raysan5)
*
*   Example licensed under an unmodified zlib/libpng license, which is an OSI-certified,
*   BSD-like license that allows static linking with closed source software
*
*   Copyright (c) 2019-2023 Culacant (@culacant) and Ramon Santamaria (@raysan5)
*
********************************************************************************************
*
*   NOTE: To export a model from blender, make sure it is not posed, the vertices need to be 
*         in the same position as they would be in edit mode and the scale of your models is 
*         set to 0. Scaling can be done from the export menu.
*
********************************************************************************************/

#define RAYLIB

#include "raylib.h"
#include "gamestate.h"
#include "raytriangleintersection.h"
#include <stdio.h>
#include <stdlib.h>
#include <xmmintrin.h>
#include <smmintrin.h>
#include <x86gprintrin.h>


//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
Vector3 position = { 0.0f, 0.0f, 0.0f };            // Set model position

int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "raylib [models] example - model animation");

    // Define the camera to look into our 3d world
    Camera camera = { 0 };
    camera.position = (Vector3){ 10.0f, 10.0f, 10.0f }; // Camera position
    camera.target = (Vector3){ 0.0f, 0.0f, 0.0f };      // Camera looking at point
    camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };          // Camera up vector (rotation towards target)
    camera.fovy = 45.0f;                                // Camera field-of-view Y
    camera.projection = CAMERA_PERSPECTIVE;             // Camera mode type

    Model level = LoadModel("resources/models/obj/my_cube.obj");
    Model model = LoadModel("resources/models/iqm/guy.iqm");                    // Load the animated model mesh and basic data
    Texture2D texture = LoadTexture("resources/models/iqm/guytex.png");         // Load model texture and set material
    SetMaterialTexture(&model.materials[0], MATERIAL_MAP_DIFFUSE, texture);     // Set model material map texture
    
    // Load animation data
    int animsCount = 0;
    ModelAnimation *anims = LoadModelAnimations("resources/models/iqm/guyanim.iqm", &animsCount);
    int animFrameCounter = 0;

    DisableCursor();                    // Catch cursor
    SetTargetFPS(60);                   // Set our game to run at 60 frames-per-second
	int totalObjs = 1;
	Object obj = (Object){ (Vector3){0,0,0},(Vector3){0,0,0},(Vector3){0,0,0}};
	Object objs[] = { obj };
	Object gamestate;
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())        // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        //UpdateCamera(&camera, CAMERA_FIRST_PERSON);
        Vector2 movement = { GetGamepadAxisMovement(0, GAMEPAD_AXIS_LEFT_X),  GetGamepadAxisMovement(0, GAMEPAD_AXIS_LEFT_Y) };
        Input input = {
            movement,
            { 0.0f, 0.0f },
            false,
            false,
            false,
            false
        };
	gamestate = CreateNextGameState(input, objs, totalObjs);
	objs[0] = gamestate;
        // Play animation when spacebar is held down
        if (IsKeyDown(KEY_SPACE))
        {
            animFrameCounter++;
            UpdateModelAnimation(model, anims[0], animFrameCounter);
            if (animFrameCounter >= anims[0].frameCount) animFrameCounter = 0;
        }
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(RAYWHITE);

            BeginMode3D(camera);
                DrawModel(level, position, 1.0f, WHITE);

                DrawModelEx(model, gamestate.position, (Vector3){ 1.0f, 0.0f, 0.0f }, -90.0f, (Vector3){ 1.0f, 1.0f, 1.0f }, WHITE);

                for (int i = 0; i < model.boneCount; i++)
                {
                    DrawCube(anims[0].framePoses[animFrameCounter][i].translation, 0.2f, 0.2f, 0.2f, RED);
                }

                DrawGrid(10, 1.0f);         // Draw a grid

            EndMode3D();

            DrawText("PRESS SPACE to PLAY MODEL ANIMATION", 10, 10, 20, MAROON);
            DrawText("(c) Guy IQM 3D model by @culacant", screenWidth - 200, screenHeight - 20, 10, GRAY);

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    UnloadTexture(texture);                     // Unload texture
    UnloadModelAnimations(anims, animsCount);   // Unload model animations data
    UnloadModel(model);                         // Unload model

    CloseWindow();                  // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}

Object CreateNextGameState(Input input, Object objs[], int totalObjs) {
    Object object;
    Vector3 newVelocity = (Vector3) { input.movement.x, input.movement.y, objs[0].velocity.z };
    object.position = (Vector3){ objs[0].position.x + newVelocity.x, objs[0].position.y + newVelocity.y, objs[0].velocity.z };
    object.velocity = newVelocity;
    object.acceleration = objs[0].acceleration;
    
    return object;
}

bool Intersect(CollisionRay const r, PrecomputedTriangle const p, Hit h) {
	const __m128 int_coef = _mm_set_ps(-1, -1, -1, 1); //This can be a parameter: it's a constant.
	const __m128 o        = _mm_load_ps(&r.ox);
	const __m128 d        = _mm_load_ps(&r.dx);
	const __m128 n        = _mm_load_ps(&p.nx);
	const __m128 det      = _mm_dp_ps(n, d, 0x7f);
	const __m128 dett     = _mm_dp_ps(_mm_mul_ps(int_coef, n), o, 0xff);
	const __m128 oldt     = _mm_load_ss(&h.t);
	
	if((_mm_movemask_ps(_mm_xor_ps(dett, _mm_sub_ss(_mm_mul_ss(oldt, det), dett)))&1) == 0) {
		const __m128 detp = _mm_add_ps(_mm_mul_ps(o, det), _mm_mul_ps(dett, d));
		const __m128 detu = _mm_dp_ps(detp, _mm_load_ps(&p.ux), 0xf1);
		
		if((_mm_movemask_ps(_mm_xor_ps(detu, _mm_sub_ss(det, detu)))&1) == 0) {
			const __m128 on   = _mm_dp_ps(o, n, 0x77);
			const __m128 tp   = _mm_sub_ps(d, on);
			const __m128 detv = _mm_dp_ps(tp, _mm_load_ps(&p.vx), 0xf1);
			
			if((_mm_movemask_ps(_mm_xor_ps(detv, _mm_sub_ss(det, _mm_add_ss(detu, detv))))&1) == 0) {
				//I can't find the function used in the paper but this seems to be the equivalent?
				//I guess it doesn't matter because all I need is the collision anyway which we already have here.
				const __m128 inv_det = _mm_rsqrt_ss(det);
				
				_mm_store_ss(&h.t, _mm_mul_ss(dett, inv_det));
				_mm_store_ss(&h.u, _mm_mul_ss(detu, inv_det));
				_mm_store_ss(&h.v, _mm_mul_ss(detv, inv_det));
				_mm_store_ps(&h.px, _mm_mul_ps(detp,
				
				_mm_shuffle_ps(inv_det, inv_det, 0)));
				
				return true;
			}
		}
	}
	return false;
}
