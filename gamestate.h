#ifndef RAYLIB
#define RAYLIB
#include "raylib.h"
#endif

typedef struct Input {
	Vector2 const movement;
	Vector2 const camera;
	bool const cameraLock;
	bool const jump;
	bool const attack;
	bool const crouch;
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

 Object CreateNextGameState(Input, Object objs[], int totalObjs);
