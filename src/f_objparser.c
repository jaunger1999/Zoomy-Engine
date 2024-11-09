#ifndef RAYLIB
#define RAYLIB
#define VECTOR3

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

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

Face ParseFace(char *line) {
	printf("Parsing Face\n");
	printf("%s\n\n", line);

	char *v = strtok_r(line, " ", &line);
	int vertices[3], normals[3];
	int i = 0;
	
	while (v && i < 3) {
		printf("%s\n", v);

		char *indices = strtok_r(v, "/", &v);

		// -1!!!!!!!! indices start at one in this format. Very annoying bug to track down.
		vertices[i] = strtol(indices, NULL, 10) - 1;

		indices = strtok_r(NULL, "/", &v);
		// skip vertex texture coords.
		indices = strtok_r(NULL, "/", &v);

		// -1!!!!!!
		normals[i] = strtol(indices, NULL, 10) - 1;

		printf("%d %d\n", vertices[i], normals[i]);

		v = strtok_r(NULL, " ", &line);
		i++;
	}

	Face face = { 
		vertices[0], vertices[1], vertices[2], 
		normals[0], normals[1], normals[2], 
	};

	printf("\n\n");

	return face;
}

Vector3 ParseVector3(char *line) {
	// z up is the obj file format standard.
	char *yNumber;
	char *zNumber;
	float x = strtof(line, &yNumber);
	float y = strtof(yNumber, &zNumber);
	float z = strtof(zNumber, NULL);
	
	printf("%s\n", line);
	printf("Parsing Vector3\n");
	printf("%f %f %f\n\n", x, y, z);

	Vector3 vector = { x, y, z };

	return vector;
}

// I'm not good at file parsing so this'll likely need to be rewritten :/
CollisionMesh GetCollisionMesh(char const * const fileName) {
	// start by parsing the file and figuring out how many vertices, normals, and faces we have.
	char *fileText = LoadFileText(fileName);

	unsigned int totalVertices = 0;
	unsigned int totalNormals = 0;
	unsigned int totalFaces = 0;

	char *currLine = strtok(fileText, "\n");

	// first pass
	while (currLine) {
		//figure out what line type we're using.
		if (currLine[0] == 'v') {
			if (currLine[1] == 'n') {
				totalNormals++;
			}
			else if (currLine[1] != 't') { //check this isn't a texture coord.
				totalVertices++;
			}
		}
		else if (currLine[0] == 'f') {
			totalFaces++;
		}

		currLine = strtok(NULL, "\n");
	}

	printf("Vertices, Normals, and Faces\n");
	printf("%d %d %d \n\n", totalVertices, totalNormals, totalFaces);

	// now we can allocate our arrays, because we know how big they need to be.
	Vector3 *vertices = malloc(sizeof(Vector3) * totalVertices);
	Vector3 *vertexNormals = malloc(sizeof(Vector3) * totalNormals);
	Face *faces = malloc(sizeof(Face) * totalFaces);
	unsigned int vI = 0;
	unsigned int nI = 0;
	unsigned int fI = 0;

	// second pass because now we know how big our arrays need to be.
	// this time we parse the data and place them in our arrays.
	// we need to use strtok_r because the face data is written kinda weird.
	// and that means I need to tokenize 2 strings :/
	
	// need to reload the file since strtok destroyed it lol.
	fileText = LoadFileText(fileName);

	currLine = strtok_r(fileText, "\n", &fileText);

	// second pass
	while (currLine) {
		//printf("%s\n\n" , currLine);
		// figure out what line type we're using.
		if (currLine[0] == 'v') {
			// the magic number indices i'm using skip past the data type
			// in the line and go to the number so strtof will work.
			if (currLine[1] == 'n') {
				printf("Normal Vector\n");
				Vector3 normal = ParseVector3(&currLine[2]);
				vertexNormals[nI] = normal;
				nI++;
			}
			else if (currLine[1] != 't') {
				printf("Vertex Vector\n");
				Vector3 vertex = ParseVector3(&currLine[1]);
				vertices[vI] = vertex;
				vI++;
			}
		}
		else if (currLine[0] == 'f') {
			Face face = ParseFace(&currLine[1]);
			faces[fI] = face;
			fI++;
		}

		currLine = strtok_r(NULL, "\n", &fileText);
	}

	// Calculate our surface normals because obj files only contain vertex normals.
	Vector3 *surfaceNormals = malloc(sizeof(Vector3) * totalFaces); 

	for (int i = 0; i < totalFaces; i++) {
		int aI = faces[i].a;
		int bI = faces[i].b;
		int cI = faces[i].c;

		Vector3 a = vertices[aI];
		Vector3 b = vertices[bI];
		Vector3 c = vertices[cI];

		Vector3 edge1 = Vector3Subtract(b, a);
		Vector3 edge2 = Vector3Subtract(c, b);

		surfaceNormals[i] = Vector3Normalize(Vector3CrossProduct(edge1, edge2));
	}

	CollisionMesh mesh = {
		vertices,
		vertexNormals,
		surfaceNormals,

		faces,
		totalFaces
	};
	
	return mesh;
}
