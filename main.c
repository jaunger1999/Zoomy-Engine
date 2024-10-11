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
#include "raymath.h"
#include "gamestate.h"
#include "raytriangleintersection.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include <xmmintrin.h>
#include <smmintrin.h>
#include <x86gprintrin.h>


// Program main entry point
Vector3 position = { 0.0f, 0.0f, 0.0f };            // Set model position

int main(void) {
	// Initialization
	const int screenWidth  = 800;
	int const screenHeight = 450;

	InitWindow(screenWidth, screenHeight, "raylib [models] example - model animation");
	
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
	Object objs[] = { obj, obj };
	InputMap const inputMap = {
		GAMEPAD_BUTTON_RIGHT_FACE_DOWN,  // jump
		GAMEPAD_BUTTON_LEFT_TRIGGER_1,   // crouch
		GAMEPAD_BUTTON_RIGHT_FACE_LEFT,  // attack
		GAMEPAD_BUTTON_RIGHT_TRIGGER_1,  // camera lock
	};

	// Main game loop
	while (!WindowShouldClose()) { // Detect window close button or ESC key
		// Update
        	Input const newInput = GetInputState(inputMap); 

		Object const playerState = CreateNextGameState(newInput, objs, totalObjs);
		objs[0] = playerState;
	        // Play animation when spacebar is held down
		if (IsKeyDown(KEY_SPACE)) {
			animFrameCounter++;
			UpdateModelAnimation(model, anims[0], animFrameCounter);

			if (animFrameCounter >= anims[0].frameCount) {
				animFrameCounter = 0;
			}
        	}

		Camera const newCamera = {
			(Vector3){ 10.0f, 10.0f, 10.0f }, // Camera position
			playerState.position,             // Camera looking at point
			(Vector3){  0.0f,  1.0f,  0.0f }, // Camera up vector (rotation towards target)
			90.0f,                            // Camera field-of-view Y
			CAMERA_PERSPECTIVE                // Camera mode type
		};



        	// Draw
		BeginDrawing();

			ClearBackground(RAYWHITE);

			BeginMode3D(newCamera);
				DrawModel(level, position, 1.0f, WHITE);

				DrawModelEx(model, playerState.position, (Vector3){ 1.0f, 0.0f, 0.0f }, -90.0f, (Vector3){ 1.0f, 1.0f, 1.0f }, WHITE);

				for (int i = 0; i < model.boneCount; i++) {
					DrawCube(anims[0].framePoses[animFrameCounter][i].translation, 0.2f, 0.2f, 0.2f, RED);
				}

				DrawGrid(10, 1.0f);         // Draw a grid

			EndMode3D();

			DrawText("PRESS SPACE to PLAY MODEL ANIMATION", 10, 10, 20, MAROON);
			DrawText("(c) Guy IQM 3D model by @culacant", screenWidth - 200, screenHeight - 20, 10, GRAY);

		EndDrawing();
	
	}

    // De-Initialization
    UnloadTexture(texture);                     // Unload texture
    UnloadModelAnimations(anims, animsCount);   // Unload model animations data
    UnloadModel(model);                         // Unload model
    CloseWindow();                              // Close window and OpenGL context

    return 0;
}

Input GetInputState(InputMap inputMap) {
	Vector2 const movement              = { GetGamepadAxisMovement(0, GAMEPAD_AXIS_LEFT_X),  GetGamepadAxisMovement(0, GAMEPAD_AXIS_LEFT_Y) };
	Vector2 const cameraMovement        = { GetGamepadAxisMovement(0, GAMEPAD_AXIS_RIGHT_X),  GetGamepadAxisMovement(0, GAMEPAD_AXIS_RIGHT_Y) };

	bool const jumpButtonDown           = IsGamepadButtonDown(0, inputMap.jump);
	bool const crouchButtonDown         = IsGamepadButtonDown(0, inputMap.crouch);
	bool const attackButtonDown         = IsGamepadButtonDown(0, inputMap.attack);
	bool const cameraLockButtonDown     = IsGamepadButtonDown(0, inputMap.cameraLock);

	bool const jumpButtonPressed        = IsGamepadButtonPressed(0, inputMap.jump);
	bool const crouchButtonPressed      = IsGamepadButtonPressed(0, inputMap.crouch);
	bool const attackButtonPressed      = IsGamepadButtonPressed(0, inputMap.attack);
	bool const cameraLockButtonPressed  = IsGamepadButtonPressed(0, inputMap.cameraLock);

	bool const jumpButtonReleased       = IsGamepadButtonReleased(0, inputMap.jump);
	bool const crouchButtonReleased     = IsGamepadButtonReleased(0, inputMap.crouch);
	bool const attackButtonReleased     = IsGamepadButtonReleased(0, inputMap.attack);
	bool const cameraLockButtonReleased = IsGamepadButtonReleased(0, inputMap.cameraLock);

        Input const newInput = {
		movement,
		cameraMovement,

		jumpButtonDown,
		crouchButtonDown,
		attackButtonDown,
		cameraLockButtonDown,

		jumpButtonPressed,
		crouchButtonPressed,
		attackButtonPressed,
		cameraLockButtonPressed,

		jumpButtonReleased,
		crouchButtonReleased,
		attackButtonReleased,
		cameraLockButtonReleased
        };

	return newInput;
}

Object CreateNextGameState(Input const input, Object const objs[], int const totalObjs) {
    Vector3 newVelocity = (Vector3){ input.movement.x, input.movement.y, objs[0].velocity.z };
    Object const object = {
	    (Vector3){ objs[0].position.x + newVelocity.x, objs[0].position.y + newVelocity.y, objs[0].velocity.z },
	    newVelocity,
	    objs[0].acceleration
    };
    
    return object;
}

OptionVector3 WrapOptionVector3(Vector3 const vector) {
	return (OptionVector3){ true, vector };
}

OptionVector3 Intersect(Ray const ray, Triangle const triangle) {
	Vector3 const edge1      = Vector3Subtract(triangle.b, triangle.a);
	Vector3 const edge2      = Vector3Subtract(triangle.c, triangle.a);
	Vector3 const rayCrossE2 = Vector3CrossProduct(ray.direction, edge2);
	float const det          = Vector3DotProduct(edge1, rayCrossE2);
	
	if (det > -EPSILON && det < EPSILON) {
		return (OptionVector3){ false };
	}
	
	float const invDet = 1.0f / det;
	Vector3 const s    = Vector3Subtract(ray.position, triangle.a);
	float const u      = invDet * Vector3DotProduct(s, rayCrossE2);
	
	if (u < 0.0f || u > 1.0f) {		
		return (OptionVector3){ false };
	}
	
	Vector3 const sCrossE1 = Vector3CrossProduct(s, edge1);
	float const v          = invDet * Vector3DotProduct(edge2, sCrossE1);
	
	if (v < 0.0f || u + v > 1.0f) {
		return (OptionVector3){ false };
	}
	
	float const t = invDet * Vector3DotProduct(edge2, sCrossE1);
	
	if (t > EPSILON) {
		Vector3 const intersectionPoint = Vector3Add(ray.position, Vector3Scale(ray.direction, t));
		return (OptionVector3){ true, intersectionPoint };
	}
	
	// This means that there is a line intersection but not a ray intersection.
	return (OptionVector3){ false };
}
