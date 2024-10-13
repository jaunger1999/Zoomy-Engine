#ifndef RAYLIB
#define RAYLIB
#include "raylib.h"
#endif

#ifndef COLLISION
#define COLLISION
#include "raytriangleintersection.h"
#endif

typedef enum {
	PLAYER = 0
} ObjectType;

typedef enum {
	FOLLOW = 0,
	LOCK = 1,
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

typedef struct Object {
	ObjectType type;
	Vector3 position;
	Vector3 velocity;
	Vector3 acceleration;
} Object;

typedef struct Attributes {
	float speed;
	float acceleration;
	float airSpeed;
	float gravity;
	float terminalVelocity;
	float initJumpSpeed;
} Attributes;

typedef struct GameState {
	int totalObjects;
	Object objects[];
} GameState;

typedef struct CameraState {
	CameraBehaviour behaviour;
	float radiansPerSecond;
	bool incrementedRotations;
	Camera camera;
} CameraState;


Attributes GetAttributes(float const jumpHeight, float const timeToApex, float const movementSpeed, float const acceleration, float const terminalVelocity, float const neutralJumpDistance);

OptionVector3 WrapVector3(Vector3 const vector);

Input GetInputState(InputMap const inputMap, Vector2 const oldMovement, Vector2 const oldCameraMovement, float const cameraYaw);

CameraState GetNextCameraState(CameraState const cameraState, Object const playerState, Input const input, float const delta);

Object GetNextPlayerGameState(Input const input, Attributes const attributes, CollisionMesh const mesh, Object const objs[], int const totalObjs, float const delta);
