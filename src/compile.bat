gcc main.c raytriangleintersection.c f_objparser.c -o ../bin/game.exe -g3 -O1 -Wall -std=c99 -Wno-missing-braces -msse4.1 -I ../include/ -L ../lib/ -lraylib -llua -lfluidsynth -lopengl32 -lgdi32 -lwinmm

cmd /k