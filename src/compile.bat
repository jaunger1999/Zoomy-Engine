gcc main.c d_dict.c d_queue.c g_events.c m_cylinder.c m_raytriangleintersection.c m_vector.c f_objparser.c -o ../bin/game.exe -g3 -O1 -Wall -std=c99 -Wno-missing-braces -msse4.1 -I ../include/ -L ../lib/ -lraylib -llua -lfluidsynth -lpcg_random -lopengl32 -lgdi32 -lwinmm

cmd /k
