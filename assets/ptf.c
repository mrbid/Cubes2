/*
    James William Fletcher (james@voxdsp.com)
        December 2021

    Converts .ply ASCII file to OpenGL buffers

    Designed for small model files with no more than 65,535 vertices
    as GLushort is used for the index buffer and there is a hard coded
    limit on the buffers used to generate the file output (MAX_BUFF).

    This is basically perfect for converting low poly ASCII PLY
    files to C OpenGL buffers for use in OpenGL ES applications.

    I'm not a high poly modeller and I like to target low end hardware.

    Compile: gcc ptf.c -lm -Ofast -o ptf
    Usage: ./ptf filename_noextension

    **********************************************************************
    An older version of this that uses GLuint for the index buffer
    and no fixed output buffers can be found here:
    https://github.com/mrbid/esAux-Menger/blob/main/PTO/pto.c
    but this solution needs to be updated to use the %g format specifier
    and in some instances has the potential to garble file output.
    (Basically it needs some work.)
    **********************************************************************
*/
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#define MAX_BUFF 1048576

int main(int argc, char** argv)
{
    // ensure an input file is specified
    if(argc < 2)
    {
        printf("Please specify an input file.\n");
        return 0;
    }

    // take the input file name and strip any supplied extension
    char name[32] = {0};
    strcat(name, argv[1]);
    char* p = strstr(name, ".");
    if(p != NULL)
        *p = 0x00;

    // generate the read file path (reads .ply files from a local `ply/` directory)
    char readfile[32] = {0};
    strcat(readfile, "ply/");
    strcat(readfile, name);
    strcat(readfile, ".ply");

    // pre-init our buffers
    char vertex_array[MAX_BUFF] = {0};
    char index_array[MAX_BUFF] = {0};
    char normal_array[MAX_BUFF] = {0};
    char color_array[MAX_BUFF] = {0};
    unsigned int numvert=0, numind=0;

    // open our ASCII PLY file for reading
    int mode = 0;
    printf("Open: %s\n", readfile);
    FILE* f = fopen(readfile, "r");
    while(f == NULL)
    {
        f = fopen(readfile, "r");
        sleep(1);
    }

    // do the conversion
    char line[256];
    while(fgets(line, 256, f) != NULL)
    {
        //printf("%s\n",line);
        if(strcmp(line, "end_header\n") == 0)
        {
            mode = 1;
            continue;
        }

        // load index
        if(mode == 2)
        {
            unsigned short n,x,y,z;
            if(sscanf(line, "%hu %hu %hu %hu", &n, &x, &y, &z) == 4)
            {
                char add[256];
                sprintf(add, "%hu,%hu,%hu,", x, y, z);
                strcat(index_array, add);
                numind += 3;
            }
        }

        // load vertex, normal, color
        if(mode == 1)
        {
            float vx,vy,vz,nx,ny,nz,r,g,b;
            if(sscanf(line, "%f %f %f %f %f %f %f %f %f", &vx, &vy, &vz, &nx, &ny, &nz, &r, &g, &b) == 9)
            {
                char add[256];

                sprintf(add, "%g,%g,%g,", vx, vy, vz);
                strcat(vertex_array, add);
                numvert++;

                sprintf(add, "%g,%g,%g,", nx, ny, nz);
                strcat(normal_array, add);

                sprintf(add, "%.3g,%.3g,%.3g,", 0.003921568859f*r, 0.003921568859f*g, 0.003921568859f*b);
                strcat(color_array, add);
            }
            else if(sscanf(line, "%f %f %f %f %f %f", &vx, &vy, &vz, &nx, &ny, &nz) == 6)
            {
                char add[256];
                sprintf(add, "%g,%g,%g,", vx, vy, vz);
                strcat(vertex_array, add);
                numvert++;

                sprintf(add, "%g,%g,%g,", nx, ny, nz);
                strcat(normal_array, add);
            }
            else if(sscanf(line, "%f %f %f", &vx, &vy, &vz) == 3)
            {
                if(vx == 3.0 && vy == 0.0 && vz == 1.0)
                {
                    strcat(index_array, "0,1,2,");
                    numind += 3;
                    mode = 2;
                    continue;
                }

                char add[256];
                sprintf(add, "%g,%g,%g,", vx, vy, vz);
                strcat(vertex_array, add);
                numvert++;
            }
            else
            {
                strcat(index_array, "0,1,2,");
                numind += 3;
                mode = 2;
                continue;
            }
        }

    }
    
    // close PLY file
    fclose(f);
    
    // remove trailng comma's
    if(vertex_array[0] != 0x00)
        vertex_array[strlen(vertex_array)-1] = 0x00;
    if(normal_array[0] != 0x00)
        normal_array[strlen(normal_array)-1] = 0x00;
    if(index_array[0] != 0x00)
        index_array[strlen(index_array)-1] = 0x00;
    if(color_array[0] != 0x00)
        color_array[strlen(color_array)-1] = 0x00;

    // output the resultant file
    char outfile[256];
    sprintf(outfile, "%s.h", name);
    f = fopen(outfile, "w");
    while(f == NULL)
    {
        f = fopen(outfile, "w");
        sleep(1);
    }

    fprintf(f, "\n#ifndef %s_H\n#define %s_H\n\nconst GLfloat %s_vertices[] = {%s};\n", name, name, name, vertex_array);
    if(normal_array[0] != 0x00)
        fprintf(f, "const GLfloat %s_normals[] = {%s};\n", name, normal_array);
    if(color_array[0] != 0x00)
        fprintf(f, "const GLfloat %s_colors[] = {%s};\n", name, color_array);
    fprintf(f, "const GLushort %s_indices[] = {%s};\nconst GLsizeiptr %s_numind = %u;\nconst GLsizeiptr %s_numvert = %u;\n\n#endif\n", name, index_array, name, numind, name, numvert);
    fclose(f);

    printf("Output: %s.h\n", name);
    return 0;
}
