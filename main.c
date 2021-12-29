/*
    James William Fletcher (james@voxdsp.com)
        December 2021

---------------------------

    (was going to be...)
    A successor to a Razor1911 original game (https://www.pouet.net/prod.php?which=12116).

---------------------------

    This is cool because it has CPU calculated "voxel" dynamic lighting. (lol)

    ---

    Keyboard Mappings:

    On land:
        [LEFT, RIGHT] Move Left / Right
        [UP] JUMP / DOUBLE JUMP

    In space:
        [LEFT, RIGHT, UP, DOWN] Move in direction

    On land & In space:
        [SPACE] Shoot

    ---

    (none of the below materialied, it became a different game, most of the assets I modelled
    did not get used, this is a prime example bad planning and execution)

    Player Indicators / status bars:
    - [Orange] Ammo
    - [Turquoise] Double Jump
    - [Purple] Fast Move
    - [Dark] Invincibility

    Pickups:
    - Ammo
    - Score
    - Nebulae Crystal (teleports to space, lasts for 64 rows)
    - Turbine (Forward Momentum Boost)

    Powerups:
    - [Turquoise] Double Jump
    - [Purple] Fast Player Movement
    - [Dark Matter] Invincibility

    Obstacles:
    - Cubes / Asteroids (shoot and destroy them to instantly step the momentum forwards
      one block with chance of pickup/powerup drop)

    Enemies:
    - Space Orbs (they will shoot directly in their line of sight, dodge their projectiles,
      shoot and destroy them to instantly step the momentum forwards one block with chance
      of pickup/powerup drop)

    Notes:
    - avoid holes on the ground (instant death)
    - do not collide into obstacles (instant death)
    - when in space; asteroids and space orbs have equal chance of dropping any pickup/powerup
      but when on land the drops become tiered based on height:

    Tier 1 drops (ground height cubes and above)
    - ammo
    - point energy

    Tier 2 drops (jump height cubes and above)
    - double jump
    - speed boost
    - fast move

    Tier 3 drops (double jump height cubes and above)
    - instant space mode
    - invincible

    When transitioning to space the player lerps to the central block to indicate a new range of movement.

---------------------------

    I am not affiliated with Razor1911 and I do not agree with or idolise any of their
    activites, I just thought the game "Cubes" was a cool little game and inspired me
    to create this game based on soley that game idea. There are other games like Cubes
    such as AudioSurf, Guitar Hero, and probably others, but it was only really Cubes
    that inspired me to create this.

    For historical purposes, the original Razor1911 game release was attributed to a
    member called "red" (2004).

    I tracked down the original author of this game to the DelphiGL.com forum where
    the user posted under an account named "red", having started the following forum
    thread: https://delphigl.com/forum/viewtopic.php?f=13&t=2034

    DelphiGL has been excluded from archiving by Archive.org but that didn't stop me
    making an archive of the original thread here; https://archive.ph/5Pwf6

    In this original thread you can see that Red is German and specifies that he is
    from Cologne, including what is assumably an image of himself as his profile picture.
    (https://delphigl.com/forum/download/file.php?avatar=139.gif)

    The original thread is dated Tue Oct 14, 2003, making him 18 years old at the time.

    Looking deeper into who red is, we can see that the original link provided to his
    game "Cubes" is hosted by the website "omfg.biz" a quick lookup on archive.org
    reveals that red was born in May 1985.

    The full blurb: (https://web.archive.org/web/20031129135243/http://omfg.biz/)

        "Not much to say about me, i'm just a nerd. born in May 1985, i'm still going to school.
        my passions can be seen in computer "art" - or however you'd like to call those things.
        there still is some of my "real life" left. at least i hope so... sometimes :)

        my internet-nickname is "red-", so whenever you see that guy on efnet somewhere you can
        be pretty sure that it's me. if you'd like to contact me, write a mail to red[at]omfg.biz
        - just replace the [at] with something more useable :)"

    This about section also includes an image of red, achived here:
    https://web.archive.org/web/20031207042253im_/http://www.omfg.biz/reddordark.gif

    Archive.org stops achiving content after 2017, although red seems to retain control of this
    domain via the hosting service antagus.de.

    2008 - 2013 :: omfg.biz hosted an image of a cat, mouth wide open, with the caption "omfg".
    2014 - 2017 :: omfg.biz started to redirect to simon.ley.so which shares more personal
                   information about the original author "red", where he now describes himself
                   as a musician.

    As posted on simon.ley.so:
    Simon Ley aka "red" / "reddor"
    Mainzer Str. 40
    55411 Bingen am Rhein
    simon.ley@gmail.com
    https://soundcloud.com/simon-ley
    https://twitter.com/reddor
    https://www.youtube.com/user/reddor
    https://github.com/reddor

    Links on simon.ley.so to YouTube content he was involved in the production of:
    https://www.youtube.com/watch?v=WBuoyegCeXI (luma - mercury | 64k | Final)
    https://www.youtube.com/watch?v=3ECyVfmRsko (Mercury - Shine)
    https://www.youtube.com/watch?v=3SCs5Cvk1eM (Headcrash - Convolutional Structure)
    https://www.youtube.com/watch?v=tpOQ72ZzKXA (Stroboholics - 905509)
    https://www.youtube.com/watch?v=OqFNbwFTdpU (Mercury - The Timeless)
    https://www.youtube.com/watch?v=YQtoZetjrFs (Stroboholics - Libidinal bribes)
    https://www.youtube.com/watch?v=JTgJwjIlE4M (Stroboholics - Simon Ritter von Stampfer)
    https://www.youtube.com/watch?v=g_Zxp2PW7Ok (Deluxe & Premium - Aarhus)

    files.scene.org reports the total download count since cubes official release date of
    2004-04-16 23:04:24 at 5,700 downloads, at the time of writing this, 2021-12-25 07:22.

    This makes the original Cubes game quite a niche game averaging ~326 downloads a year
    over 17.5 years.

---------------------------

    Notes:

        In this game I have included 4 source images all 1920x~1280 and ~20mb per image
        uncompressed RGB byte data. I could have ZLIB'd these but I'm not going to because
        of my intention to UPX the binary. If I was including a lot of high resolution
        assets I would certainly ZLIB them all independently, but in this case, I would
        probably get a slightly better compression ratio from a UPX on the final output
        binary because it would take into consideration all of the images in the final
        RLE table or whatever compression method UPX utilises. Packing 100 MB of asset
        data into a single binary file is a little much, but it's ok. Not looking forward
        to watching UPX compress this binary on an ARM64 processor however.

*/

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define uint GLushort
#define f32 GLfloat

#include "gl.h"
#define GLFW_INCLUDE_NONE
#include "glfw3.h"

#ifndef __x86_64__ 
    #define NOSSE
#endif
#define SEIR_RAND
#include "esAux2.h"

#include "res.h"
#include "assets/cube.h"

//*************************************
// globals
//*************************************
GLFWwindow* window;
uint winw = 1024;
uint winh = 768;
double t = 0;   // time
double dt = 0;  // delta time
double fc = 0;  // frame count
double lfct = 0;// last frame count time
f32 aspect;
double x,y;
double rww, ww, rwh, wh, ww2, wh2;
double uw, uh, uw2, uh2; // normalised pixel dpi

// render state id's
GLint projection_id;
GLint modelview_id;
GLint position_id;
GLint lightpos_id;
GLint solidcolor_id;
GLint color_id;
GLint opacity_id;
GLint normal_id;

// render state matrices
mat projection;
mat view;
mat model;
mat modelview;
mat viewrot;

// render state inputs
vec lightpos = {0.f, 0.f, 0.f};

// models
uint bindstate = 0;
ESModel mdlCube;

// game vars
#define NEWGAME_SEED 1337
#define FAR_DISTANCE 512.f

#define ARRAY_MAX 32
typedef struct
{
    uint health;
    vec pos;
    f32 r,g,b;
} gi;
gi array_cube[ARRAY_MAX];
vec array_bullet[ARRAY_MAX];

vec pp;
int score = 0;
uint hit = 0, loss = 0;


//*************************************
// utility functions
//*************************************
void timestamp(char* ts)
{
    const time_t tt = time(0);
    strftime(ts, 16, "%H:%M:%S", localtime(&tt));
}

static inline f32 nsat(f32 f)
{
    if(f > 1.f){f = 1.f;}
    else if(f < 0.f){f = 0.f;}
    return f;
}

//*************************************
// render functions
//*************************************

void rCube(f32 x, f32 y, f32 z, f32 lightness, uint light_mode, f32 r, f32 g, f32 b)
{
    // transform
    mIdent(&model);
    mTranslate(&model, x, y, z);
    if(light_mode == 4)
    {
        const f32 s = 0.5f - (fabs(z) / 128.f);
        mScale(&model, s, s, s);
        light_mode = 2;
    }
    mMul(&modelview, &model, &view);
    glUniformMatrix4fv(projection_id, 1, GL_FALSE, (f32*) &projection.m[0][0]);
    glUniformMatrix4fv(modelview_id, 1, GL_FALSE, (f32*) &modelview.m[0][0]);
    glUniform3f(lightpos_id, lightpos.x, lightpos.y, lightpos.z);
    glUniform1f(opacity_id, 1.0f);
    
    // compute lightness
    f32 lf = fabs(sinf(t+r+g+b)); // it's the `+r+g+b` causing the light strobe to de-synchronise from the cube color strobe, but meh it's a game not a simulation. I prefer it this way, the game actually has a very subtle uneasy feeling to it due to these mild oddities.
    if(lf < 0.3f){lf = 0.3f;}
    lightness /= 6.f * lf;
    if(lightness > 2.f)
        lightness = 2.f;
    lightness = 2.f-lightness;

    // shading
    if(light_mode == 0)
    {
        f32 r0 = nsat(sinf(x+t*0.3f));
        f32 g0 = nsat(cosf(y+t*0.3f));
        f32 b0 = nsat(cosf(z+t*0.3f));
        if(r0 <= 0.f){r0 = 0.1f;}
        if(g0 <= 0.f){g0 = 0.1f;}
        if(b0 <= 0.f){b0 = 0.1f;}
        glUniform3f(color_id, r0 * 0.2f + (r0 * lightness), g0 * 0.2f + (g0 * lightness), b0 * 0.2f + (b0 * lightness));
    }
    else if(light_mode == 1)
        glUniform3f(color_id, r * lightness, g * lightness, b * lightness);
    else if(light_mode == 2)
        glUniform3f(color_id, r, g, b);

    // bind
    if(bindstate != 1)
    {
        glBindBuffer(GL_ARRAY_BUFFER, mdlCube.vid);
        glVertexAttribPointer(position_id, 3, GL_FLOAT, GL_FALSE, 0, 0);
        glEnableVertexAttribArray(position_id);

        glBindBuffer(GL_ARRAY_BUFFER, mdlCube.nid);
        glVertexAttribPointer(normal_id, 3, GL_FLOAT, GL_FALSE, 0, 0);
        glEnableVertexAttribArray(normal_id);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mdlCube.iid);
        bindstate = 1;
    }

    // draw
    glDrawElements(GL_TRIANGLES, cube_numind, GL_UNSIGNED_SHORT, 0);
}

//*************************************
// game functions
//*************************************
void rndCube(uint i, f32 far)
{
    array_cube[i].health = 1;
    array_cube[i].pos = (vec){(1 + esRand(0, 14)) * 2, (1 + esRand(0, 8)) * 2, far, 1.f + randf()*9.f};
    array_cube[i].r = randf();
    array_cube[i].g = randf();
    array_cube[i].b = randf();
}

void newGame()
{
    char strts[16];
    timestamp(&strts[0]);
    printf("[%s] Game Start.\n", strts);
    
    glfwSetWindowTitle(window, "Cube Shooter");

    score = 0;
    hit = 0;
    loss = 0;
    pp = (vec){16, 4, -6};

    for(uint i = 0; i < ARRAY_MAX; i++)
        rndCube(i, esRandFloat(-64.f, -FAR_DISTANCE));
}

//*************************************
// update & render
//*************************************
void main_loop()
{
//*************************************
// time delta for interpolation
//*************************************
    
    // dilate time
    t += sinf(t * 0.05f) * 10.f;

    // calc delta time
    static double lt = 0;
    dt = t-lt;
    lt = t;

//*************************************
// camera
//*************************************
    mIdent(&view);
    mTranslate(&view, -16.f, -9.f, -15.f);

//*************************************
// begin render
//*************************************
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

//*************************************
// main render
//*************************************

    // player
    // glfwGetCursorPos(window, &x, &y);
    // x = 2 + (x * rww) * 30;
    // y = 18 + (y * rwh) * -18;
    // if(x < 2.0){x = 2.0;}
    // else if(x > 30.0){x = 30.0;}
    // if(y < 2.0){y = 2.0;}
    // else if(y > 18.0){y = 18.0;}
    // x = floor(x+0.5);
    // y = floor(y+0.5);
    // const double x2 = x / 2;
    // const double y2 = y / 2;
    // if(x2-floor(x2) != 0){x += 1;}
    // if(y2-floor(y2) != 0){y += 1;}
    // rCube(x, y, pp.z, 0.f, 2, 1.f,1.f,0.f);

    const f32 red = nsat(1.f - ((f32)loss / (f32)hit)); // you are the health bar
    rCube(pp.x, pp.y, pp.z, 0.f, 2, 1.f,red,0.f);

    // bullets
    for(uint i = 0; i < ARRAY_MAX; i++)
    {
        // is bullet alive
        if(array_bullet[i].z != 0.f)
        {
            // simulate bullet
            array_bullet[i].z += -30.f * dt;

            // check collisions with cubes
            for(uint j = 0; j < ARRAY_MAX; j++)
            {
                if(array_cube[j].health == 0 || array_cube[j].health == 1337){continue;}
                
                if( array_bullet[i].x == array_cube[j].pos.x && 
                    array_bullet[i].y == array_cube[j].pos.y &&
                    array_bullet[i].z < array_cube[j].pos.z )
                {
                    array_cube[j].health = 0;
                    array_bullet[i].z = 0.f;
                    //rndCube(j, -FAR_DISTANCE);

                    score++;
                    hit++;
                    char title[256];
                    sprintf(title, "Cube Shooter - SCORE %i - HIT %u - LOSS %u", score, hit, loss);
                    glfwSetWindowTitle(window, title);

                    char strts[16];
                    timestamp(&strts[0]);
                    printf("[%s] Plus Score: %i\n", strts, score);
                }  
            }

            // check bullet death and draw
            if(array_bullet[i].z < -64.f)
                array_bullet[i].z = 0.f;
            else if(array_bullet[i].z != 0.f)
                rCube(array_bullet[i].x, array_bullet[i].y, array_bullet[i].z, 0.f, 4, 1.f, 1.f, 0.f);
        }
    }

    // simulate cubes
    for(uint i = 0; i < ARRAY_MAX; i++)
    {
        // simuate
        array_cube[i].pos.z += array_cube[i].pos.w * dt;
        if(array_cube[i].pos.z > 20.f || array_cube[i].pos.y < 2.f) // cube reset condition
            rndCube(i, -FAR_DISTANCE);

        // on cube death make it nose dive
        if(array_cube[i].health == 0)
            array_cube[i].pos.y -= array_cube[i].pos.w * dt;

        // cube got past you alive
        if(array_cube[i].health == 1 && array_cube[i].pos.z > -6.f)
        {
            array_cube[i].health = 1337;
            score--;
            loss++;
            char title[256];
            sprintf(title, "Cube Shooter - SCORE %i - HIT %u - LOSS %u", score, hit, loss);
            glfwSetWindowTitle(window, title);
            char strts[16];
            timestamp(&strts[0]);
            printf("[%s] Minus Score: %i\n", strts, score);
        }
        
        // draw cube red if its past you, or original colour if not
        if(array_cube[i].pos.z > -6.f && array_cube[i].health != 0)
            rCube(array_cube[i].pos.x, array_cube[i].pos.y, array_cube[i].pos.z, 3.f, 1, 1.f,0.f,0.f);
        else
            rCube(array_cube[i].pos.x, array_cube[i].pos.y, array_cube[i].pos.z, 3.f, 1, array_cube[i].r, array_cube[i].g, array_cube[i].b);
    }

    // draw grid [per wall](find nearest light source, render cube)
    for(uint x = 0; x < 17; x++)
    {
        for(uint y = 0; y < 32; y++)
        {
            const float fx = 2.0f * x;
            const float fy = -2.0f * y;

            f32 l = 60.f;
            for(uint i = 0; i < ARRAY_MAX; i++)
            {
                f32 nl = vDist((vec){fx, 0.f, fy}, array_cube[i].pos);
                if(nl < l)
                    l = nl;
                
                if(array_bullet[i].z != 0.f)
                {
                    nl = vDist((vec){fx, 0.f, fy}, array_bullet[i]);
                    if(nl < l)
                        l = nl;
                }
            }
            rCube(fx, 0.f, fy, l, 0, 0.f,0.f,0.f);

            l = 60.f;
            for(uint i = 0; i < ARRAY_MAX; i++)
            {
                f32 nl = vDist((vec){fx, 20.f, fy}, array_cube[i].pos);
                if(nl < l)
                    l = nl;

                if(array_bullet[i].z != 0.f)
                {
                    nl = vDist((vec){fx, 20.f, fy}, array_bullet[i]);
                    if(nl < l)
                        l = nl;
                }
            }
            rCube(fx, 20.f, fy, l, 0, 0.f,0.f,0.f);

            l = 60.f;
            for(uint i = 0; i < ARRAY_MAX; i++)
            {
                f32 nl = vDist((vec){0.f, fx, fy}, array_cube[i].pos);
                if(nl < l)
                    l = nl;

                if(array_bullet[i].z != 0.f)
                {
                    nl = vDist((vec){0.f, fx, fy}, array_bullet[i]);
                    if(nl < l)
                        l = nl;
                }
            }
            rCube(0.f, fx, fy, l, 0, 0.f,0.f,0.f);

            l = 60.f;
            for(uint i = 0; i < ARRAY_MAX; i++)
            {
                f32 nl = vDist((vec){32.f, fx, fy}, array_cube[i].pos);
                if(nl < l)
                    l = nl;

                if(array_bullet[i].z != 0.f)
                {
                    nl = vDist((vec){32.f, fx, fy}, array_bullet[i]);
                    if(nl < l)
                        l = nl;
                }
            }
            rCube(32.f, fx, fy, l, 0, 0.f,0.f,0.f);
        }
    }

//*************************************
// swap buffers / display render
//*************************************
    glfwSwapBuffers(window);
}

//*************************************
// Input Handelling
//*************************************
static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    // control
    if(action == GLFW_PRESS || action == GLFW_REPEAT)
    {
        if(key == GLFW_KEY_LEFT){ pp.x -= 2.f; if(pp.x < 2.f){pp.x = 2.f;} }
        else if(key == GLFW_KEY_RIGHT){ pp.x += 2.f; if(pp.x > 30.f){pp.x = 30.f;} }
        else if(key == GLFW_KEY_UP){ pp.y += 2.f; if(pp.y > 18.f){pp.y = 18.f;} }
        else if(key == GLFW_KEY_DOWN){ pp.y -= 2.f; if(pp.y < 2.f){pp.y = 2.f;} }

        // fire bullet
        else if(key == GLFW_KEY_SPACE)
        {
            for(uint i = 0; i < ARRAY_MAX; i++)
            {
                if(array_bullet[i].z == 0.f)
                {
                    array_bullet[i].x = pp.x;
                    array_bullet[i].y = pp.y;
                    array_bullet[i].z = -8.f;
                    break;
                }
            }
        }

        // random seed
        else if(key == GLFW_KEY_R)
        {
            const unsigned int nr = time(0);
            srand(t*100);
            srandf(t*100);
            char strts[16];
            timestamp(&strts[0]);
            printf("[%s] New Random Seed: %u\n", strts, nr);

            for(uint i = 0; i < ARRAY_MAX; i++)
                rndCube(i, esRandFloat(-64.f, -FAR_DISTANCE));
        }
    }
    // else if(action == GLFW_RELEASE)
    // {
    //     //
    // }

    // show average fps
    if(key == GLFW_KEY_F)
    {
        if(t-lfct > 2.0)
        {
            char strts[16];
            timestamp(&strts[0]);
            printf("[%s] FPS: %g\n", strts, fc/(t-lfct));
            lfct = t;
            fc = 0;
        }
    }

    // quit
    if(key == GLFW_KEY_ESCAPE)
        glfwSetWindowShouldClose(window, GLFW_TRUE);
}

// void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
// {
//     if(button == GLFW_MOUSE_BUTTON_LEFT)
//     {
//         if(action == GLFW_PRESS)
//         {
//             for(uint i = 0; i < ARRAY_MAX; i++)
//             {
//                 if(array_bullet[i].z == 0.f)
//                 {
//                     array_bullet[i].x = x;
//                     array_bullet[i].y = y;
//                     array_bullet[i].z = -8.f;
//                     break;
//                 }
//             }
//         }
//     }
// }

void window_size_callback(GLFWwindow* window, int width, int height)
{
    winw = width;
    winh = height;

    glViewport(0, 0, winw, winh);
    aspect = (f32)winw / (f32)winh;
    ww = winw;
    wh = winh;
    rww = 1/ww;
    rwh = 1/wh;
    ww2 = ww/2;
    wh2 = wh/2;
    uw = (double)aspect / ww;
    uh = 1 / wh;
    uw2 = (double)aspect / ww2;
    uh2 = 1 / wh2;

    mIdent(&projection);
    mPerspective(&projection, 60.0f, aspect, 1.0f, FAR_DISTANCE); 
}

//*************************************
// Process Entry Point
//*************************************
int main(int argc, char** argv)
{
    // help
    printf("Cube Shooter\n");
    printf("James William Fletcher (james@voxdsp.com)\n\n");
    printf("Use your keyboard arrow keys to move and spacebar to shoot, R for new random seed, F for FPS to console.\n\n");

    // init glfw
    if(!glfwInit()){exit(EXIT_FAILURE);}
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    glfwWindowHint(GLFW_SAMPLES, 16);
    window = glfwCreateWindow(winw, winh, "Cube Shooter", NULL, NULL);
    if(!window)
    {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }
    const GLFWvidmode* desktop = glfwGetVideoMode(glfwGetPrimaryMonitor());
    glfwSetWindowPos(window, (desktop->width/2)-(winw/2), (desktop->height/2)-(winh/2)); // center window on desktop
    glfwSetWindowSizeCallback(window, window_size_callback);
    glfwSetKeyCallback(window, key_callback);
    //glfwSetMouseButtonCallback(window, mouse_button_callback);
    glfwMakeContextCurrent(window);
    gladLoadGL(glfwGetProcAddress);
    glfwSwapInterval(1); // 0 for immediate updates, 1 for updates synchronized with the vertical retrace, -1 for adaptive vsync

    // set icon
    glfwSetWindowIcon(window, 1, &(GLFWimage){16, 16, (unsigned char*)&icon_image.pixel_data});

    // hide cursor
    //glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

    // seed random
    srand(NEWGAME_SEED);

//*************************************
// projection
//*************************************

    window_size_callback(window, winw, winh);

//*************************************
// bind vertex and index buffers
//*************************************

    // ***** BIND CUBE *****
    esBind(GL_ARRAY_BUFFER, &mdlCube.vid, cube_vertices, sizeof(cube_vertices), GL_STATIC_DRAW);
    esBind(GL_ARRAY_BUFFER, &mdlCube.nid, cube_normals, sizeof(cube_normals), GL_STATIC_DRAW);
    esBind(GL_ARRAY_BUFFER, &mdlCube.iid, cube_indices, sizeof(cube_indices), GL_STATIC_DRAW);

//*************************************
// compile & link shader programs
//*************************************

    //makeAllShaders();
    makeLambert1();

//*************************************
// configure render options
//*************************************

    //glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_CULL_FACE);
    glEnable(GL_DEPTH_TEST);
    glClearColor(0.0, 0.0, 0.0, 0.0);
    shadeLambert1(&position_id, &projection_id, &modelview_id, &lightpos_id, &normal_id, &color_id, &opacity_id);

//*************************************
// execute update / render loop
//*************************************

    // init
    newGame();

    // reset
    t = glfwGetTime();
    lfct = t;
    
    // event loop
    while(!glfwWindowShouldClose(window))
    {
        t = glfwGetTime();
        glfwPollEvents();
        main_loop();
        fc++;
    }

    // final score
    char strts[16];
    timestamp(&strts[0]);
    printf("[%s] SCORE %i - HIT %u - LOSS %u\n\n", strts, score, hit, loss);

    // done
    glfwDestroyWindow(window);
    glfwTerminate();
    exit(EXIT_SUCCESS);
    return 0;
}
