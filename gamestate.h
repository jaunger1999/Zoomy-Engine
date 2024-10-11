#ifndef RAYLIB
#define RAYLIB
#include "raylib.h"
#endif

typedef struct InputMap {
	GamepadButton jump;
	GamepadButton crouch;
	GamepadButton attack;
	GamepadButton cameraLock;
} InputMap;

typedef struct Input {
	Vector2 movement;
	Vector2 camera;

	bool jumpDown;
	bool crouchDown;
	bool attackDown;
	bool cameraLockDown;

	bool jumpPressed;
	bool crouchPressed;
	bool attackPressed;
	bool cameraLockPressed;
} Input;


typedef struct Object {
	Vector3 position;
	Vector3 velocity;
	Vector3 acceleration;
} Object;

typedef struct GameState {
	int totalObjects;
	Object objects[];
} GameState;

typedef struct ValidatedVector3 {
	bool valid;
	Vector3 vector;
} ValidatedVector3;

Input GetInputState(InputMap inputMap);

Object CreateNextGameState(Input const input, Object const objs[], int const totalObjs);
