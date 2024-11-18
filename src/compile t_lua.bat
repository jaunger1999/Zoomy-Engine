gcc t_lua.c -o ../bin/t_lua.exe -g3 -O1 -Wall -std=c99 -Wno-missing-braces -msse4.1 -I ../include/ -L ../lib/ -lraylib -llua -lfluidsynth -lfluidsynth.dll -lpcg_random -lopengl32 -lgdi32 -lwinmm

cmd /k
