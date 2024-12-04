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

#define PI_OVER_2 1.57079632679489661923f

#define STICK_SMASH_THRESHOLD 0.7f

#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>

#ifndef RAYLIB
#define RAYLIB
#define VECTOR3

#include "raylib.h"
#include "raymath.h"
#endif

#ifndef COLLISION 
#define COLLISION
#include "m_raytriangleintersection.h"
#endif

#include "d_dict.h"
#include "d_queue.h"

#include "m_vector.h"

#include "g_attributes.h"
#include "g_physics.h"
#include "g_events.h"
#include "g_health.h"
#include "g_statemachines.h"

#include "gamestate.h"

#include "f_objparser.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>
#include <string.h>

#include <xmmintrin.h>
#include <smmintrin.h>

// Program main entry point
Vector3 position = { 0.0f, 0.0f, 0.0f }; // Set model position

int PhysProp_GetNextState(char const * const args, unsigned int const id, void* ppOut);

int main(void) {
	E_Init();
	int totalObjs = 0;

	E_AddObj(totalObjs);

	totalObjs++;

	time_t sec;
	time(&sec);

	Attributes playerAttributes = GetAttributes(
			1.0f,  // jump height
			0.5f,  // time to apex
			1.0f, // movement speed
			10.0f, // acceleration
			3.0f,  // terminal velocity
			3.0f   // neutral jump distance
		);
	
	// Initialization
	const int screenWidth  = 800;
	int const screenHeight = 450;

	InitWindow(screenWidth, screenHeight, "raylib [models] example - model animation");
	
	Model level = LoadModel("../a big jump/models/obj/myplane.obj");
	CollisionMesh cMesh = GetCollisionMesh("../a big jump/models/obj/myplane.obj");
	printf("%f\n", cMesh.vertices[0].x);
	printf("%d %d\n", cMesh.faces[0].a, cMesh.faces[0].nA);
	Model model = LoadModel("../a big jump/models/iqm/guy.iqm");                    // Load the animated model mesh and basic data
	Texture2D texture = LoadTexture("../a big jump/models/iqm/guytex.png");         // Load model texture and set material
	SetMaterialTexture(&model.materials[0], MATERIAL_MAP_DIFFUSE, texture);     // Set model material map texture
	
	// Load animation data
	int animsCount = 0;
	ModelAnimation *anims = LoadModelAnimations("../a big jump/models/iqm/guyanim.iqm", &animsCount);
	int animFrameCounter = 0;

	printf("gravity: %f\n", playerAttributes.gravity);
	DisableCursor();                    // Catch cursor
	SetTargetFPS(60);                   // Set our game to run at 60 frames-per-second
	PhysicalProperties obj = (PhysicalProperties){ (Vector3){6.5f,7,0},(Vector3){0,0,0},(Vector3){0,0,0}};

	InputMap const inputMap = {
		GAMEPAD_BUTTON_RIGHT_FACE_DOWN,  // jump
		GAMEPAD_BUTTON_LEFT_TRIGGER_1,   // crouch
		GAMEPAD_BUTTON_RIGHT_FACE_LEFT,  // attack
		GAMEPAD_BUTTON_RIGHT_TRIGGER_1,  // camera lock
	};

	Camera const camera = {
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
		camera         // Camera 
	};

	Vector2 oldMovement = { 0 };
	Vector2 oldCameraMovement = { 0 };

	// Allow for arbitrary gravity vectors.
	Vector3 g = (Vector3) { 0, -1, 0 };
	Quaternion q = QuaternionFromGravityVector(&g);
	Vector3 xAxis = Vector3RotateByQuaternion((Vector3) { 1, 0, 0 }, q);
	Vector3 yAxis = Vector3RotateByQuaternion((Vector3) { 0, 1, 0 }, q);
	printf("%f %f %f\n", xAxis.x, xAxis.y, xAxis.z);
	printf("%f %f %f\n", yAxis.x, yAxis.y, yAxis.z);

	// Main game loop
	while (!WindowShouldClose()) { // Detect window close button or ESC key
		// Update
		float delta = GetFrameTime();

		Vector2 const pPos  = { obj.position.x, obj.position.z };
		Vector2 const cPos  = { oldCameraState.camera.position.x, oldCameraState.camera.position.z };
		float   const angle = Vector2LineAngle(pPos, cPos)  + PI_OVER_2;
        	Input   const input = GetInputState(&inputMap, &oldMovement, &oldCameraMovement, angle); // Player movement input is relative to this angle.

		E_Register(PhysProp_GetNextState, PLAYER_MOVE, 0, 5, &input, &playerAttributes, &cMesh, &obj, delta);

		for (int id = 0; id < totalObjs; id++) {
			Event* e = E_GetNext(id);

			while (e) {
				PhysicalProperties out;
				e->function(e->args, id, &out);

				// this is hardcoded and assumes theres only one event type PLAYER_MOVE
				obj = out;
				
				e = E_GetNext(id);
			}
		}

		CameraState const newCameraState = GetNextCameraState(&oldCameraState, &obj, &input, delta);
		Camera const newCamera = newCameraState.camera;

        	// Draw
		BeginDrawing();

			ClearBackground(RAYWHITE);

			BeginMode3D(newCamera);
				DrawModel(level, position, 1.0f, WHITE);

				DrawModelEx(model, obj.position, (Vector3){ 1.0f, 0.0f, 0.0f }, -90.0f, (Vector3){ 1.0f, 1.0f, 1.0f }, WHITE);

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

CameraState GetNextCameraState(CameraState const * const cameraState, PhysicalProperties const * const playerState, Input const * const input, float const delta) {
	Camera const camera = cameraState->camera;

	float const rotation              = delta * cameraState->radiansPerSecond * input->cameraMovement.x;
	Vector3 const relativePosition    = Vector3Subtract(camera.position, playerState->position);
	Vector3 const newRelativePosition = Vector3RotateByAxisAngle(relativePosition, camera.up, rotation);
	Vector3 const newPosition         = Vector3Add(newRelativePosition, playerState->position);

	Camera const newCamera = {
		newPosition,                      // Camera position
		playerState->position,            // Camera looking at point
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

// args == Input const * const input, Attributes const * const attributes, CollisionMesh const * const mesh, PhysicalProperties const * const currState, float const delta
int PhysProp_GetNextState(char const * const args, unsigned int const id, void* ppOut) {
	// Our parameters for this function.
	Input*              input;
	Attributes*         attributes;
	CollisionMesh*      mesh;
	PhysicalProperties* currState;
	float               delta;

	// Set our parameters stored in args.
	#define COPY_ARG(argName)\
		memcpy(&argName, args + offset, sizeof(argName));\
		offset += sizeof(argName);

	int offset = 0;

	COPY_ARG(input)
	COPY_ARG(attributes)
	COPY_ARG(mesh)
	COPY_ARG(currState)
	COPY_ARG(delta)

	Vector3 newVelocity;
	Vector3 const gravity = (Vector3){ 0, -attributes->gravity * delta, 0 };
	Vector3 const toVelocity = (Vector3){ attributes->speed * input->movement.x, 0, attributes->speed * input->movement.y };

	if (1 - Vector2LengthSqr(input->movement) < EPSILON && Vector2LengthSqr(input->oldMovement) < STICK_SMASH_THRESHOLD && fabs(Vector3LengthSqr(currState->velocity)) < EPSILON) {
		newVelocity = Vector3Add(toVelocity, gravity);
	}
	else {
		/*Vector3 const diff = Vector3Subtract(toVelocity, currState->velocity);
		Vector3 const acceleration = 
			Vector3Scale(
				Vector3Normalize(diff),          // direction between our desired and current velocity.
				attributes->acceleration * delta
			);*/

		// We don't want to go past our target velocity so check if we'll go past by adding acceleration.
		//if (Vector3LengthSqr(diff) > Vector3LengthSqr(acceleration)) {
		//	newVelocity = Vector3Add(currState->velocity, acceleration); 
		//}
		//else {
			newVelocity = Vector3Add(toVelocity, gravity);
		//}
	}
	
	newVelocity = Vector3Add(newVelocity, currState->velocity);

	bool collision = false;
	Vector3 toTryVelocity = Vector3Scale(newVelocity, delta);

	for (int i = 0; i < mesh->faceCount && !collision; i++) {
		// check if we're hitting the outside of a surface
		if (Vector3Angle(toTryVelocity, mesh->surfaceNormals[i]) < PI_OVER_2) {
			continue;
		}

		Vector3 const a = mesh->vertices[mesh->faces[i].a];
		Vector3 const b = mesh->vertices[mesh->faces[i].b];
		Vector3 const c = mesh->vertices[mesh->faces[i].c];

		Ray const r = (Ray){ currState->position, Vector3Normalize(toTryVelocity) };
		OptionHit hit = Intersect(&r, &a, &b, &c); 
		collision = hit.valid && hit.t * hit.t < Vector3LengthSqr(toTryVelocity);

		if (collision) {
			Vector3 planeVector = VectorComponentAlongPlane(&newVelocity, &mesh->surfaceNormals[i]);
			//printf("Plane Vector: %f %f %f\n\n", planeVector.x, planeVector.y, planeVector.z);
			//printf("Surface Normal: %f %f %f\n\n", mesh->surfaceNormals[i].x, mesh->surfaceNormals[i].y, mesh->surfaceNormals[i].z);
			newVelocity = planeVector;
			toTryVelocity = Vector3Scale(newVelocity, delta);
		}
	}

	Vector3 const newPosition = Vector3Add(currState->position, toTryVelocity);

	*(PhysicalProperties*)ppOut = (PhysicalProperties) {
		newPosition,
		newVelocity,
		currState->acceleration
	};

	return 1;
}

OptionVector3 WrapOptionVector3(Vector3 const vector) {
	return (OptionVector3){ true, vector };
}

Attributes GetAttributes(float const jumpHeight, float const timeToApex, float const movementSpeed, float const acceleration, float const terminalVelocity, float const neutralJumpDistance) {
	float const gravity = (2 * jumpHeight) / (timeToApex * timeToApex);
	float const initJumpSpeed = -sqrt(2 * gravity * jumpHeight);
	//float const airSpeed = neutralJumpDistance / (2 * timeToApex);

	Attributes attributes = {
		movementSpeed,
		acceleration,
		gravity,
		terminalVelocity,
		initJumpSpeed
	};

	return attributes;
}
