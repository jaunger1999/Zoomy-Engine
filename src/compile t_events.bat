gcc t_events.c g_events.c d_dict.c d_queue.c -o ../bin/t_events.exe -g3 -O1 -Wall -std=c99 -Wno-missing-braces -msse4.1 -I ../include/ -L ../lib/ -lraylib -llua -lfluidsynth -lpcg_random -lopengl32 -lgdi32 -lwinmm

cmd /k
