gcc hashGenerator.c hash.c -o ../bin/hashGenerator.exe -g3 -O1 -Wall -std=c99 -Wno-missing-braces -msse4.1 -I ../include/ -L ../lib/ -lraylib -llua -lfluidsynth -lpcg_random -lopengl32 -lgdi32 -lwinmm
cmd /k
