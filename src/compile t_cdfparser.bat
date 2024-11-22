gcc t_cdfparser.c d_dict_s.c d_string.c f_cdfparser.c g_statemachines.c hash.c -o ../bin/t_cdfparser.exe -g3 -O1 -Wall -std=c99 -Wno-missing-braces -msse4.1 -I ../include/ -L ../lib/ -lraylib -llua -lfluidsynth -lpcg_random -lopengl32 -lgdi32 -lwinmm
cmd /k
