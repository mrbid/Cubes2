clang main_fullbright.c glad_gl.c -Ofast -lglfw -lm -o cubes2_fullbright
i686-w64-mingw32-gcc main_fullbright.c glad_gl.c -Ofast -Llib -lglfw3dll -lm -o cubes2_fullbright.exe
upx cubes2_fullbright
upx cubes2_fullbright.exe