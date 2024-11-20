#include "hash.h"

#define NUM_GAMEPAD_BUTTONS 18

GamepadButton* inputs;

unsigned long unknown;
unsigned long leftFaceUp;
unsigned long leftFaceRight;
unsigned long leftFaceDown;
unsigned long leftFaceLeft;
unsigned long rightFaceUp;
unsigned long rightFaceRight;
unsigned long rightFaceDown;
unsigned long rightFaceLeft;
unsigned long leftTrigger1;
unsigned long leftTrigger2;
unsigned long rightTrigger1;
unsigned long rightTrigger2;
unsigned long middleLeft;
unsigned long middle;
unsigned long middleRight;
unsigned long leftThumb;
unsigned long rightThumb;

void InitInputHashes() {
	unknown        = hash("GAMEPAD_BUTTON_UNKNOWN");
	leftFaceUp     = hash("GAMEPAD_BUTTON_LEFT_FACE_UP");
	leftFaceRight  = hash("GAMEPAD_BUTTON_LEFT_FACE_RIGHT");
	leftFaceDown   = hash("GAMEPAD_BUTTON_LEFT_FACE_DOWN");
	leftFaceLeft   = hash("GAMEPAD_BUTTON_LEFT_FACE_LEFT");
	rightFaceUp    = hash("GAMEPAD_BUTTON_RIGHT_FACE_UP");
	rightFaceRight = hash("GAMEPAD_BUTTON_RIGHT_FACE_RIGHT");
	rightFaceDown  = hash("GAMEPAD_BUTTON_RIGHT_FACE_DOWN");
	rightFaceLeft  = hash("GAMEPAD_BUTTON_RIGHT_FACE_LEFT");
	leftTrigger1   = hash("GAMEPAD_BUTTON_LEFT_TRIGGER_1");
	leftTrigger2   = hash("GAMEPAD_BUTTON_LEFT_TRIGGER_2");
	rightTrigger1  = hash("GAMEPAD_BUTTON_RIGHT_TRIGGER_1");
	rightTrigger2  = hash("GAMEPAD_BUTTON_RIGHT_TRIGGER_2");
	middleLeft     = hash("GAMEPAD_BUTTON_MIDDLE_LEFT");
	middle         = hash("GAMEPAD_BUTTON_MIDDLE");
	middleRight    = hash("GAMEPAD_BUTTON_MIDDLE_RIGHT");
	leftThumb      = hash("GAMEPAD_BUTTON_LEFT_THUMB");
	rightThumb     = hash("GAMEPAD_BUTTON_RIGHT_THUMB");
}

int ParseInputConfigFile(char const * const fileName) {
	char* fileText = LoadFileText(fileName);

	char* currLine = strtok(fileText, "\n");
	unsigned int totalActions = 0;

	//first pass
	while(currLine) {
		if(strcmp(currLine, "") != 0) {
			totalActions++;
		}
	}

	if(totalActions == 0) {
		return -1;
	}

	inputs = malloc(sizeof(int) * totalActions);

	fileText = LoadFileText(fileName);
	int i = 0;

	// second pass
	while(currLine) {
		// Skip empty lines
		if(strcmp(currLine, "") == 0) {
			continue;
		}

		switch(hash(currLine)) {
			case unknown:
				inputs[i] = GAMEPAD_BUTTON_UNKNOWN;
				break;
			case leftFaceUp:
				inputs[i] = GAMEPAD_BUTTON_LEFT_FACE_UP;
				break;
			case leftFaceRight:
				inputs[i] = GAMEPAD_BUTTON_LEFT_FACE_RIGHT;
				break;
			case leftFaceDown:
				inputs[i] = GAMEPAD_BUTTON_LEFT_FACE_DOWN;
				break;
			case leftFaceLeft:
				inputs[i] = GAMEPAD_BUTTON_LEFT_FACE_LEFT;
				break;
			case rightFaceUp:
				inputs[i] = GAMEPAD_BUTTON_RIGHT_FACE_UP;
				break;
			case rightFaceRight:
				inputs[i] = GAMEPAD_BUTTON_RIGHT_FACE_RIGHT;
				break;                                       
			case rightFaceDown:
				inputs[i] = GAMEPAD_BUTTON_RIGHT_FACE_DOWN;
				break;
			case rightFaceLeft:
				inputs[i] = GAMEPAD_BUTTON_RIGHT_FACE_LEFT;
				break;
			case leftTrigger1:
				inputs[i] = GAMEPAD_BUTTON_LEFT_TRIGGER_1;
				break;
			case leftTrigger2:
				inputs[i] = GAMEPAD_BUTTON_LEFT_TRIGGER_2;
				break;
			case rightTrigger1:
				inputs[i] = GAMEPAD_BUTTON_RIGHT_TRIGGER_1;
				break;
			case rightTrigger2:
				inputs[i] = GAMEPAD_BUTTON_RIGHT_TRIGGER_2;
				break;
			case middleLeft:
				inputs[i] = GAMEPAD_BUTTON_MIDDLE_LEFT; 
				break;
			case middle:
				inputs[i] = GAMEPAD_BUTTON_MIDDLE; 
				break;
			case middleRight:
				inputs[i] = GAMEPAD_BUTTON_MIDDLE_RIGHT;
				break;
			case leftThumb:
				inputs[i] = GAMEPAD_BUTTON_LEFT_THUMB;
				break;
			case rightThumb:
				inputs[i] = GAMEPAD_BUTTON_RIGHT_THUMB;
				break;
		}

		i++;
	}
}

// Returns a bit mask of the action events the player input this frame.
unsigned long GetInputEventMask(bool const* const actions) {
	unsigned long mask = 0;
	for (int i = 0; i < NUM_GAMEPAD_BUTTONS; i++) {
		// if actions[i] is false nothing gets added.
		// if it's true, the bit corresponding to the action gets set.
		mask += actions[i] << i;
	}

	return mask;
}
