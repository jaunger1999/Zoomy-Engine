#ifndef RAYLIB
#define RAYLIB
#define VECTOR3

#include "raylib.h"
#include "raymath.h"
#endif


typedef enum ObjectType {
	PLAYER = 0
} ObjectType;

typedef enum {
	FOLLOW = 0,
	LOCK   = 1,
	BEHIND = 2,
	TRIPOD = 3
} CameraBehaviour;

typedef struct InputMap {
	GamepadButton const jump;
	GamepadButton const crouch;
	GamepadButton const attack;
	GamepadButton const cameraLock;
} InputMap;

typedef struct Input {
	Vector2 const movement;
	Vector2 const cameraMovement;
	
	Vector2 const oldMovement;
	Vector2 const oldCameraMovement;

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


typedef struct CameraState {
	CameraBehaviour behaviour;
	float radiansPerSecond;
	bool incrementedRotations;
	Camera camera;
} CameraState;

Attributes GetAttributes(float const jumpHeight, float const timeToApex, float const movementSpeed, float const acceleration, float const terminalVelocity, float const neutralJumpDistance);


Input GetInputState(InputMap const * const inputMap, Vector2 const * const oldMovement, Vector2 const * const oldCameraMovement, float const cameraYaw);

CameraState GetNextCameraState(CameraState const * const cameraState, PhysicalProperties const * const playerState, Input const * const input, float const delta);

PhysicalProperties GetNextPlayerGameState(Input const * const input, Attributes const * const attributes, CollisionMesh const * const mesh, PhysicalProperties const objs[], int const totalObjs, float const delta);
