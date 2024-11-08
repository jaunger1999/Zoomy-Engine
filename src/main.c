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

#define STICK_SMASH_THRESHOLD 0.7f

#ifndef RAYLIB
#define RAYLIB
#define VECTOR3

#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>

#include "raylib.h"
#include "raymath.h"
#endif

#ifndef COLLISION 
#define COLLISION
#include "raytriangleintersection.h"
#endif

#ifndef GAMESTATE
#define GAMESTATE
#include "gamestate.h"
#endif

#include "f_objparser.h"

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include <xmmintrin.h>
#include <smmintrin.h>

// Program main entry point
Vector3 position = { 0.0f, 0.0f, 0.0f };            // Set model position

int main(void) {
	Attributes playerAttributes = GetAttributes(
			1.0f,  // jump height
			0.5f,  // time to apex
			10.0f, // movement speed
			10.0f, // acceleration
			3.0f,  // terminal velocity
			3.0f   // neutral jump distance
		);
	
	Attributes attributes[1] = {
		playerAttributes
	};
	// Initialization
	const int screenWidth  = 800;
	int const screenHeight = 450;

	InitWindow(screenWidth, screenHeight, "raylib [models] example - model animation");
	
	Model level = LoadModel("../resources/models/obj/slope.obj");
	CollisionMesh cMesh = GetCollisionMesh("../resources/models/obj/slope.obj");
	printf("%f\n", cMesh.vertices[0].x);
	printf("%d %d\n", cMesh.faces[0].a, cMesh.faces[0].nA);
	Model model = LoadModel("../resources/models/iqm/guy.iqm");                    // Load the animated model mesh and basic data
	Texture2D texture = LoadTexture("../resources/models/iqm/guytex.png");         // Load model texture and set material
	SetMaterialTexture(&model.materials[0], MATERIAL_MAP_DIFFUSE, texture);     // Set model material map texture
	
	// Load animation data
	int animsCount = 0;
	ModelAnimation *anims = LoadModelAnimations("../resources/models/iqm/guyanim.iqm", &animsCount);
	int animFrameCounter = 0;

	printf("gravity: %f\n", playerAttributes.gravity);
	DisableCursor();                    // Catch cursor
	SetTargetFPS(60);                   // Set our game to run at 60 frames-per-second
	int totalObjs = 1;
	Object obj = (Object){ PLAYER, (Vector3){6.5f,7,0},(Vector3){0,0,0},(Vector3){0,0,0}};
	Object objs[] = { obj, obj };
	InputMap const inputMap = {
		GAMEPAD_BUTTON_RIGHT_FACE_DOWN,  // jump
		GAMEPAD_BUTTON_LEFT_TRIGGER_1,   // crouch
		GAMEPAD_BUTTON_RIGHT_FACE_LEFT,  // attack
		GAMEPAD_BUTTON_RIGHT_TRIGGER_1,  // camera lock
	};

	Camera const newCamera = {
		(Vector3){  0.0f, 10.0f, 10.0f }, // Camera position
		(Vector3){  0.0f,  0.0f,  0.0f }, // Camera looking at point
		(Vector3){  0.0f,  2.0f,  0.0f }, // Camera up vector (rotation towards target)
		90.0f,                            // Camera field-of-view Y
		CAMERA_PERSPECTIVE                // Camera mode type
	};

	CameraState oldCameraState = {
		FOLLOW,        // Behaviour
		10,            // Radians Per Second
		false,         // Incremented Rotations
		newCamera      // Camera 
	};

	Vector2 oldMovement = { 0 };
	Vector2 oldCameraMovement = { 0 };

	// Main game loop
	while (!WindowShouldClose()) { // Detect window close button or ESC key
		// Update
		float delta = GetFrameTime();

		Vector2 const pPos = { objs[0].position.x, objs[0].position.z };
		Vector2 const cPos = { oldCameraState.camera.position.x, oldCameraState.camera.position.z };
		float const angle = Vector2LineAngle(pPos, cPos)  + PI / 2;
        	Input const input = GetInputState(&inputMap, &oldMovement, &oldCameraMovement, angle); // Player movement input is relative to this angle. 

		Object const playerState = GetNextPlayerGameState(&input, &attributes[objs[0].type], &cMesh, objs, totalObjs, delta);
		objs[0] = playerState;
		
		CameraState const newCameraState = GetNextCameraState(&oldCameraState, &playerState, &input, delta);
		Camera const newCamera = newCameraState.camera;

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
		
		// Give the next iteration of the loop access to the previous frame' state.
		oldCameraState = newCameraState;
		oldMovement = input.movement;
		oldCameraMovement = input.cameraMovement;
	}

    // De-Initialization
    UnloadTexture(texture);                     // Unload texture
    UnloadModelAnimations(anims, animsCount);   // Unload model animations data
    UnloadModel(model);                         // Unload model
    CloseWindow();                              // Close window and OpenGL context

    return 0;
}

Input GetInputState(InputMap const * const inputMap, Vector2 const * const oldMovement, Vector2 const * const oldCameraMovement, float const cameraYaw) {
	Vector2 const rawMovement           = { GetGamepadAxisMovement(0, GAMEPAD_AXIS_LEFT_X),  GetGamepadAxisMovement(0, GAMEPAD_AXIS_LEFT_Y) };
	Vector2 const adjustedMovement      = Vector2Rotate(rawMovement, -cameraYaw);
	Vector2 const cameraMovement        = { GetGamepadAxisMovement(0, GAMEPAD_AXIS_RIGHT_X),  GetGamepadAxisMovement(0, GAMEPAD_AXIS_RIGHT_Y) };

	bool const jumpButtonDown           = IsGamepadButtonDown(0, inputMap->jump);
	bool const crouchButtonDown         = IsGamepadButtonDown(0, inputMap->crouch);
	bool const attackButtonDown         = IsGamepadButtonDown(0, inputMap->attack);
	bool const cameraLockButtonDown     = IsGamepadButtonDown(0, inputMap->cameraLock);

	bool const jumpButtonPressed        = IsGamepadButtonPressed(0, inputMap->jump);
	bool const crouchButtonPressed      = IsGamepadButtonPressed(0, inputMap->crouch);
	bool const attackButtonPressed      = IsGamepadButtonPressed(0, inputMap->attack);
	bool const cameraLockButtonPressed  = IsGamepadButtonPressed(0, inputMap->cameraLock);

	bool const jumpButtonReleased       = IsGamepadButtonReleased(0, inputMap->jump);
	bool const crouchButtonReleased     = IsGamepadButtonReleased(0, inputMap->crouch);
	bool const attackButtonReleased     = IsGamepadButtonReleased(0, inputMap->attack);
	bool const cameraLockButtonReleased = IsGamepadButtonReleased(0, inputMap->cameraLock);

        Input const input = {
		adjustedMovement,
		cameraMovement,
		
		*oldMovement,
		*oldCameraMovement,

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

	return input;
}

CameraState GetNextCameraState(CameraState const * const cameraState, Object const * const playerState, Input const * const input, float const delta) {
	Camera const camera = cameraState->camera;

	float const rotation              = delta * cameraState->radiansPerSecond * input->cameraMovement.x;
	Vector3 const relativePosition    = Vector3Subtract(camera.position, playerState->position);
	Vector3 const newRelativePosition = Vector3RotateByAxisAngle(relativePosition, camera.up, rotation);
	Vector3 const newPosition         = Vector3Add(newRelativePosition, playerState->position);

	Camera const newCamera = {
		newPosition, // Camera position
		playerState->position,             // Camera looking at point
		(Vector3){  0.0f,  1.0f,  0.0f }, // Camera up vector (rotation towards target)
		90.0f,                            // Camera field-of-view Y
		CAMERA_PERSPECTIVE                // Camera mode type
	};

	CameraState const nextCameraState = {
		cameraState->behaviour,
		cameraState->radiansPerSecond,
		cameraState->incrementedRotations,
		newCamera
	};

	return nextCameraState;
}

Object GetNextPlayerGameState(Input const * const input, Attributes const * const attributes, CollisionMesh const * const mesh, Object const objs[], int const totalObjs, float const delta) {
	Vector3 newVelocity;
	Vector3 const gravity = (Vector3){ 0, -attributes->gravity * delta, 0 };
	Vector3 const toVelocity = (Vector3){ attributes->speed * input->movement.x, objs[0].velocity.y, attributes->speed * input->movement.y };

	if (1 - Vector2LengthSqr(input->movement) < EPSILON && Vector2LengthSqr(input->oldMovement) < STICK_SMASH_THRESHOLD && abs(Vector3LengthSqr(objs[0].velocity)) < EPSILON) {
		newVelocity = Vector3Add(toVelocity, gravity);
	}
	else {
		/*Vector3 const diff = Vector3Subtract(toVelocity, objs[0].velocity);
		Vector3 const acceleration = 
			Vector3Scale(
				Vector3Normalize(diff),          // direction between our desired and current velocity.
				attributes->acceleration * delta
			);*/

		// We don't want to go past our target velocity so check if we'll go past by adding acceleration.
		//if (Vector3LengthSqr(diff) > Vector3LengthSqr(acceleration)) {
		//	newVelocity = Vector3Add(objs[0].velocity, acceleration); 
		//}
		//else {
			newVelocity = Vector3Add(toVelocity, gravity);
		//}
	}
	
	bool collision = false;
	Vector3 toTryVelocity = Vector3Scale(newVelocity, delta);

	for (int i = 0; i < mesh->faceCount && !collision; i++) {
		Vector3 const a = mesh->vertices[mesh->faces[i].a];
		Vector3 const b = mesh->vertices[mesh->faces[i].b];
		Vector3 const c = mesh->vertices[mesh->faces[i].c];

		Ray const r = (Ray){ objs[0].position, Vector3Normalize(toTryVelocity) };
		OptionHit hit = Intersect(&r, &a, &b, &c); 
		collision = hit.valid && hit.t * hit.t < Vector3LengthSqr(toTryVelocity);
	}

	Vector3 const newPosition = Vector3Add(objs[0].position, toTryVelocity);

	if (collision) {
		Object const object = {
			objs[0].type,
			objs[0].position,
			objs[0].velocity,
			objs[0].acceleration
		};
	    
		return object;
	}
	else {
		Object const object = {
			objs[0].type,
			newPosition,
			newVelocity,
			objs[0].acceleration
		};
	    
		return object;
	}
}

OptionVector3 WrapOptionVector3(Vector3 const vector) {
	return (OptionVector3){ true, vector };
}

Attributes GetAttributes(float const jumpHeight, float const timeToApex, float const movementSpeed, float const acceleration, float const terminalVelocity, float const neutralJumpDistance) {
	float const gravity = (2 * jumpHeight) / (timeToApex * timeToApex);
	float const initJumpSpeed = -sqrt(2 * gravity * jumpHeight);
	float const airSpeed = neutralJumpDistance / (2 * timeToApex);

	Attributes attributes = {
		movementSpeed,
		acceleration,
		airSpeed,
		gravity,
		terminalVelocity,
		initJumpSpeed
	};

	return attributes;
}
