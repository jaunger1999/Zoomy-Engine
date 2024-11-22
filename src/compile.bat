gcc main.c d_dict.c d_queue.c g_events.c hash.c m_cylinder.c m_raytriangleintersection.c m_vector.c f_objparser.c -o ../bin/game.exe -g3 -Wall -Wextra -pedantic -std=c99 -Wcast-align -Wcast-qual -Wdisabled-optimization -Wformat=2 -Winit-self -Wlogical-op -Wmissing-include-dirs -Wredundant-decls -Wshadow -Wstrict-overflow=5 -Wundef -fdiagnostics-show-option -msse4.1 -I ../include/ -L ../lib/ -lraylib -llua -lfluidsynth -lfluidsynth.dll -lpcg_random -lopengl32 -lgdi32 -lwinmm

cmd /k
