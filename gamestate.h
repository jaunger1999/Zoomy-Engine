#ifndef RAYLIB
#define RAYLIB
#include "raylib.h"
#endif

typedef struct InputMap {
	GamepadButton const jump;
	GamepadButton const crouch;
	GamepadButton const attack;
	GamepadButton const cameraLock;
} InputMap;

typedef struct Input {
	Vector2 const movement;
	Vector2 const camera;

	bool const jumpDown;
	bool const crouchDown;
	bool const attackDown;
	bool const cameraLockDown;

	bool const jumpPressed;
	bool const crouchPressed;
	bool const attackPressed;
	bool const cameraLockPressed;

	bool const jumpReleased;
	bool const crouchReleased;
	bool const attackReleased;
	bool const cameraLockReleased;
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

typedef enum {
	FOLLOW = 0,
	LOCK   = 1
} CameraBehaviour;

typedef struct CameraState {
	CameraBehaviour behaviour;
	bool incrementedRotations;
	Camera camera;
} CameraState;

typedef struct OptionVector3 {
	bool const valid;
	Vector3 const vector;
} OptionVector3;

OptionVector3 WrapVector3(Vector3 const vector);

Input GetInputState(InputMap inputMap);

CameraState GetNextCameraState(CameraState const cameraState, Object const playerState, Input const input, float const delta);

Object GetNextPlayerGameState(Input const input, Object const objs[], int const totalObjs, float const delta);
