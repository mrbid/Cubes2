/*
--------------------------------------------------
    James William Fletcher (james@voxdsp.com)
        October 2021 - esAux2.h v2.0
--------------------------------------------------

    Requires:
        - vec.h: https://gist.github.com/mrbid/77a92019e1ab8b86109bf103166bd04e
        - mat.h: https://gist.github.com/mrbid/cbc69ec9d99b0fda44204975fcbeae7c

    v2.0:
        - added support for fullbright texture mapping

    v1.0:
        The shaders are the product of a little help from:
        http://www.cs.toronto.edu/~jacobson/phong-demo/
        https://www.mathematik.uni-marburg.de/~thormae/lectures/graphics1/code/WebGLShaderLightMat/ShaderLightMat.html
        https://www.gsn-lib.org/docs/nodes/ShaderPluginNode.php
        https://www.khronos.org/registry/OpenGL/specs/es/2.0/GLSL_ES_Specification_1.00.pdf
        https://www.khronos.org/opengles/sdk/docs/reference_cards/OpenGL-ES-2_0-Reference-card.pdf
        https://www.khronos.org/registry/OpenGL-Refpages/es2.0/

        The phong uses BlinnPhong by default, if you wish to use
        vanilla phong just specify the following definition in
        your source file: #define REGULAR_PHONG
*/

#ifndef AUX_H
#define AUX_H

#include "vec.h"
#include "mat.h"

//*************************************
// MATRIX
//*************************************

// structures
typedef struct
{
    GLuint vid; // Vertex Array Buffer ID
    GLuint iid;	// Index Array Buffer ID
    GLuint cid;	// Colour Array Buffer ID
    GLuint nid;	// Normal Array Buffer ID
    GLuint tid;	// TexCoord Array Buffer ID
} ESModel;

//*************************************
// UTILITY
//*************************************

GLuint esRand(const GLuint min, const GLuint max);
GLfloat esRandFloat(const GLfloat min, const GLfloat max);
void esBind(const GLenum target, GLuint* buffer, const void* data, const GLsizeiptr datalen, const GLenum usage);
void esBindModel(ESModel* model, const GLfloat* vertices, const GLsizei vertlen, const GLushort* indices, const GLsizei indlen);
GLuint esLoadTexture(const GLuint w, const GLuint h, const unsigned char* data);
GLuint esLoadTextureA(const GLuint w, const GLuint h, const unsigned char* data);

//*************************************
// SHADER
//*************************************

void makeAllShaders();

void makeFullbright();
void makeLambert();
void makeLambert1();
void makeLambert2();
void makeLambert3();
void makePhong();
void makePhong1();
void makePhong2();
void makePhong3();

void shadeFullbrightT(GLint* position, GLint* projection, GLint* modelview, GLint* texcoord, GLint* sampler);                             // texture + no shading
void shadeFullbright(GLint* position, GLint* projection, GLint* modelview, GLint* color, GLint* opacity);                                 // solid color + no shading

void shadeLambert(GLint* position, GLint* projection, GLint* modelview, GLint* lightpos, GLint* color, GLint* opacity);                   // solid color + no normals
void shadeLambert1(GLint* position, GLint* projection, GLint* modelview, GLint* lightpos, GLint* normal, GLint* color, GLint* opacity);   // solid color + normals
void shadeLambert2(GLint* position, GLint* projection, GLint* modelview, GLint* lightpos, GLint* color, GLint* opacity);                  // colors + no normals
void shadeLambert3(GLint* position, GLint* projection, GLint* modelview, GLint* lightpos, GLint* normal, GLint* color, GLint* opacity);   // colors + normals

void shadePhong(GLint* position, GLint* projection, GLint* modelview, GLint* normalmat, GLint* lightpos, GLint* color, GLint* opacity);                   // solid color + no normals
void shadePhong1(GLint* position, GLint* projection, GLint* modelview, GLint* normalmat, GLint* lightpos, GLint* normal, GLint* color, GLint* opacity);   // solid color + normals
void shadePhong2(GLint* position, GLint* projection, GLint* modelview, GLint* normalmat, GLint* lightpos, GLint* color, GLint* opacity);                  // colors + no normals
void shadePhong3(GLint* position, GLint* projection, GLint* modelview, GLint* normalmat, GLint* lightpos, GLint* normal, GLint* color, GLint* opacity);   // colors + normals

//*************************************
// UTILITY CODE
//*************************************

GLuint esRand(const GLuint min, const GLuint max)
{
    static GLfloat rndmax = (GLfloat)RAND_MAX;
    return ((((GLfloat)rand())+1e-7f) / rndmax) * ((max+1)-min) + min;
}

GLfloat esRandFloat(const GLfloat min, const GLfloat max)
{
    static GLfloat rndmax = (GLfloat)RAND_MAX;
    return ( ((((GLfloat)rand())+1e-7f) / rndmax) * (max-min) ) + min;
}

void esBind(const GLenum target, GLuint* buffer, const void* data, const GLsizeiptr datalen, const GLenum usage)
{
    glGenBuffers(1, buffer);
    glBindBuffer(target, *buffer);
    glBufferData(target, datalen, data, usage);
}

void esBindModel(ESModel* model, const GLfloat* vertices, const GLsizei vertlen, const GLushort* indices, const GLsizei indlen)
{
    esBind(GL_ARRAY_BUFFER, &model->vid, vertices, vertlen * sizeof(GLfloat) * 3, GL_STATIC_DRAW);
    esBind(GL_ARRAY_BUFFER, &model->iid, indices, indlen * sizeof(GLushort), GL_STATIC_DRAW);
}

GLuint esLoadTexture(const GLuint w, const GLuint h, const unsigned char* data)
{
   GLuint textureId;

   // Use tightly packed data
   glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

   // Generate a texture object
   glGenTextures(1, &textureId);

   // Bind the texture object
   glBindTexture(GL_TEXTURE_2D, textureId);

   // Load the texture
   glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, w, h, 0, GL_RGB, GL_UNSIGNED_BYTE, data);

   // Set the filtering mode
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

   return textureId;
}

GLuint esLoadTextureA(const GLuint w, const GLuint h, const unsigned char* data)
{
   GLuint textureId;
   glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
   glGenTextures(1, &textureId);
   glBindTexture(GL_TEXTURE_2D, textureId);
   glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
   return textureId;
}

//*************************************
// SHADER CODE
//*************************************

const GLchar* vt0 =
    "#version 100\n"
    "uniform mat4 modelview;\n"
    "uniform mat4 projection;\n"
    "attribute vec4 position;\n"
    "attribute vec2 texcoord;\n"
    "varying vec2 vtc;\n"
    "void main()\n"
    "{\n"
        "vtc = texcoord;\n"
        "gl_Position = projection * modelview * position;\n"
    "}\n";

const GLchar* ft0 =
    "#version 100\n"
    "precision mediump float;\n"
    "varying vec2 vtc;\n"
    "uniform sampler2D tex;\n"
    "void main()\n"
    "{\n"
        "gl_FragColor = texture2D(tex, vtc);\n"
    "}\n";

//

const GLchar* v0 =
    "#version 100\n"
    "uniform mat4 modelview;\n"
    "uniform mat4 projection;\n"
    "uniform vec3 color;\n"
    "uniform float opacity;\n"
    "attribute vec4 position;\n"
    "varying vec3 vertCol;\n"
    "varying float vertOpa;\n"
    "void main()\n"
    "{\n"
        "vertCol = color;\n"
        "vertOpa = opacity;\n"
        "gl_Position = projection * modelview * position;\n"
    "}\n";

const GLchar* f0 =
    "#version 100\n"
    "precision mediump float;\n"
    "varying vec3 vertCol;\n"
    "varying float vertOpa;\n"
    "void main()\n"
    "{\n"
        "gl_FragColor = vec4(vertCol, vertOpa);\n"
    "}\n";

//

// solid color + no normals
const GLchar* v1 =
    "#version 100\n"
    "uniform mat4 modelview;\n"
    "uniform mat4 projection;\n"
    "uniform vec3 color;\n"
    "uniform float opacity;\n"
    "uniform vec3 lightpos;\n"
    "attribute vec4 position;\n"
    "varying vec3 vertPos;\n"
    "varying vec3 vertNorm;\n"
    "varying vec3 vertCol;\n"
    "varying float vertOpa;\n"
    "varying vec3 vlightPos;\n"
    "void main()\n"
    "{\n"
        "vec4 vertPos4 = modelview * position;\n"
        "vertPos = vec3(vertPos4) / vertPos4.w;\n"
        "vertNorm = vec3(modelview * vec4(position.xyz, 0.0));\n"
        "vertCol = color;\n"
        "vertOpa = opacity;\n"
        "vlightPos = lightpos;\n"
        "gl_Position = projection * modelview * position;\n"
    "}\n";

// solid color + normal array
const GLchar* v11 =
    "#version 100\n"
    "uniform mat4 modelview;\n"
    "uniform mat4 projection;\n"
    "uniform vec3 color;\n"
    "uniform float opacity;\n"
    "uniform vec3 lightpos;\n"
    "attribute vec4 position;\n"
    "attribute vec3 normal;\n"
    "varying vec3 vertPos;\n"
    "varying vec3 vertNorm;\n"
    "varying vec3 vertCol;\n"
    "varying float vertOpa;\n"
    "varying vec3 vlightPos;\n"
    "void main()\n"
    "{\n"
        "vec4 vertPos4 = modelview * position;\n"
        "vertPos = vec3(vertPos4) / vertPos4.w;\n"
        "vertNorm = vec3(modelview * vec4(normal.xyz, 0.0));\n"
        "vertCol = color;\n"
        "vertOpa = opacity;\n"
        "vlightPos = lightpos;\n"
        "gl_Position = projection * modelview * position;\n"
    "}\n";

// color array + normal array
const GLchar* v12 =
    "#version 100\n"
    "uniform mat4 modelview;\n"
    "uniform mat4 projection;\n"
    "uniform float opacity;\n"
    "uniform vec3 lightpos;\n"
    "attribute vec4 position;\n"
    "attribute vec3 normal;\n"
    "attribute vec3 color;\n"
    "varying vec3 vertPos;\n"
    "varying vec3 vertNorm;\n"
    "varying vec3 vertCol;\n"
    "varying float vertOpa;\n"
    "varying vec3 vlightPos;\n"
    "void main()\n"
    "{\n"
        "vec4 vertPos4 = modelview * position;\n"
        "vertPos = vec3(vertPos4) / vertPos4.w;\n"
        "vertNorm = vec3(modelview * vec4(normal.xyz, 0.0));\n"
        "vertCol = color;\n"
        "vertOpa = opacity;\n"
        "vlightPos = lightpos;\n"
        "gl_Position = projection * modelview * position;\n"
    "}\n";

// color array + no normals
const GLchar* v13 =
    "#version 100\n"
    "uniform mat4 modelview;\n"
    "uniform mat4 projection;\n"
    "uniform float opacity;\n"
    "uniform vec3 lightpos;\n"
    "attribute vec4 position;\n"
    "attribute vec3 color;\n"
    "varying vec3 vertPos;\n"
    "varying vec3 vertNorm;\n"
    "varying vec3 vertCol;\n"
    "varying float vertOpa;\n"
    "varying vec3 vlightPos;\n"
    "void main()\n"
    "{\n"
        "vec4 vertPos4 = modelview * position;\n"
        "vertPos = vec3(vertPos4) / vertPos4.w;\n"
        "vertNorm = vec3(modelview * vec4(position.xyz, 0.0));\n"
        "vertCol = color;\n"
        "vertOpa = opacity;\n"
        "vlightPos = lightpos;\n"
        "gl_Position = projection * modelview * position;\n"
    "}\n";

const GLchar* f1 =
    "#version 100\n"
    "precision mediump float;\n"
    "varying vec3 vertPos;\n"
    "varying vec3 vertNorm;\n"
    "varying vec3 vertCol;\n"
    "varying float vertOpa;\n"
    "varying vec3 vlightPos;\n"
    "void main()\n"
    "{\n"
        "vec3 ambientColor = vertCol * 0.148;\n"
        "vec3 diffuseColor = vertCol;\n"
        "vec3 normal = normalize(vertNorm);\n"
        "vec3 lightDir = normalize(vlightPos - vertPos);\n"
        "float lambertian = max(dot(lightDir,normal), 0.0);\n"
        "gl_FragColor = vec4(ambientColor + lambertian*diffuseColor, vertOpa);\n"
    "}\n";

const GLchar* v2 = 
    "#version 100\n" 
    "uniform mat4 modelview;\n"
    "uniform mat4 projection;\n"
    "uniform mat4 normalmat;\n"
    "uniform float opacity;\n"
    "uniform vec3 lightpos;\n"
    "uniform vec3 color;\n"
    "attribute vec4 position;\n"
    "varying vec3 normalInterp;\n"
    "varying vec3 vertPos;\n"
    "varying vec3 vertCol;\n"
    "varying float vertOpa;\n"
    "varying vec3 vlightPos;\n"
    "void main()\n"
    "{\n"
        "vec4 vertPos4 = modelview * position;"
        "vertPos = vec3(vertPos4) / vertPos4.w;"
        "vertCol = color;\n"
        "vertOpa = opacity;\n"
        "vlightPos = lightpos;\n"
        "normalInterp = vec3(normalmat * vec4(position.xyz, 0.0));"
        "gl_Position = projection * modelview * position;"
    "}\n";

const GLchar* v21 = 
    "#version 100\n" 
    "uniform mat4 modelview;\n"
    "uniform mat4 projection;\n"
    "uniform mat4 normalmat;\n"
    "uniform float opacity;\n"
    "uniform vec3 lightpos;\n"
    "uniform vec3 color;\n"
    "attribute vec4 position;\n"
    "attribute vec3 normal;\n"
    "varying vec3 normalInterp;\n"
    "varying vec3 vertPos;\n"
    "varying vec3 vertCol;\n"
    "varying float vertOpa;\n"
    "varying vec3 vlightPos;\n"
    "void main()\n"
    "{\n"
        "vec4 vertPos4 = modelview * position;"
        "vertPos = vec3(vertPos4) / vertPos4.w;"
        "vertCol = color;\n"
        "vertOpa = opacity;\n"
        "vlightPos = lightpos;\n"
        "normalInterp = vec3(normalmat * vec4(normal.xyz, 0.0));"
        "gl_Position = projection * modelview * position;"
    "}\n";

const GLchar* v22 = 
    "#version 100\n" 
    "uniform mat4 modelview;\n"
    "uniform mat4 projection;\n"
    "uniform mat4 normalmat;\n"
    "uniform float opacity;\n"
    "uniform vec3 lightpos;\n"
    "attribute vec4 position;\n"
    "attribute vec3 color;\n"
    "varying vec3 normalInterp;\n"
    "varying vec3 vertPos;\n"
    "varying vec3 vertCol;\n"
    "varying float vertOpa;\n"
    "varying vec3 vlightPos;\n"
    "void main()\n"
    "{\n"
        "vec4 vertPos4 = modelview * position;"
        "vertPos = vec3(vertPos4) / vertPos4.w;"
        "vertCol = color;\n"
        "vertOpa = opacity;\n"
        "vlightPos = lightpos;\n"
        "normalInterp = vec3(normalmat * vec4(position.xyz, 0.0));"
        "gl_Position = projection * modelview * position;"
    "}\n";

const GLchar* v23 = 
    "#version 100\n" 
    "uniform mat4 modelview;\n"
    "uniform mat4 projection;\n"
    "uniform mat4 normalmat;\n"
    "uniform float opacity;\n"
    "uniform vec3 lightpos;\n"
    "attribute vec4 position;\n"
    "attribute vec3 normal;\n"
    "attribute vec3 color;\n"
    "varying vec3 normalInterp;\n"
    "varying vec3 vertPos;\n"
    "varying vec3 vertCol;\n"
    "varying float vertOpa;\n"
    "varying vec3 vlightPos;\n"
    "void main()\n"
    "{\n"
        "vec4 vertPos4 = modelview * position;"
        "vertPos = vec3(vertPos4) / vertPos4.w;"
        "vertCol = color;\n"
        "vertOpa = opacity;\n"
        "vlightPos = lightpos;\n"
        "normalInterp = vec3(normalmat * vec4(normal.xyz, 0.0));"
        "gl_Position = projection * modelview * position;"
    "}\n";
   
const GLchar* f2 = 
    "#version 100\n" 
    "precision mediump float;\n"
    "varying vec3 normalInterp;\n"
    "varying vec3 vertPos;\n"
    "varying vec3 vertCol;\n"
    "varying float vertOpa;\n"
    "varying vec3 vlightPos;\n"
    "void main()\n"
    "{\n"
        "vec3 ambientColor = vertCol * 0.14;\n"
        "vec3 diffuseColor = vertCol;\n"
        "vec3 specColor = vec3(1.0, 1.0, 1.0);\n"
        "float specAmount = 4.0;\n"
        "vec3 normal = normalize(normalInterp);\n"
        "vec3 lightDir = normalize(vlightPos - vertPos);\n"
        "vec3 viewDir = normalize(-vertPos);\n"
#ifdef REGULAR_PHONG
        "vec3 reflectDir = reflect(-lightDir, normal);\n"
#else
        "vec3 halfDir = normalize(viewDir + lightDir);\n"
#endif
        "float lumosity = dot(lightDir, normal);\n" // [0] you can max this or
        "vec3 specular = diffuseColor;\n"
        "if(lumosity > 0.0)\n"
        "{\n"
#ifdef REGULAR_PHONG
            "float specAngle = max(dot(reflectDir, viewDir), 0.0);\n"
#else
            "float specAngle = max(dot(halfDir, normal), 0.0);\n"
#endif
            "specular += pow(specAngle, specAmount) * specColor;\n"
        "}\n"
        "gl_FragColor = vec4(ambientColor + max(specular * lumosity, 0.0), vertOpa);\n" // [0] .. you can max this
    "}\n";

//

GLuint shdFullbrightT;
GLint  shdFullbrightT_position;
GLint  shdFullbrightT_projection;
GLint  shdFullbrightT_modelview;
GLint  shdFullbrightT_texcoord;
GLint  shdFullbrightT_sampler;
GLuint shdFullbright;
GLint  shdFullbright_position;
GLint  shdFullbright_projection;
GLint  shdFullbright_modelview;
GLint  shdFullbright_color;
GLint  shdFullbright_opacity;
GLuint shdLambert;
GLint  shdLambert_position;
GLint  shdLambert_projection;
GLint  shdLambert_modelview;
GLint  shdLambert_lightpos;
GLint  shdLambert_color;
GLint  shdLambert_opacity;
GLuint shdLambert1;
GLint  shdLambert1_position;
GLint  shdLambert1_projection;
GLint  shdLambert1_modelview;
GLint  shdLambert1_lightpos;
GLint  shdLambert1_color;
GLint  shdLambert1_normal;
GLint  shdLambert1_opacity;
GLuint shdLambert2;
GLint  shdLambert2_position;
GLint  shdLambert2_projection;
GLint  shdLambert2_modelview;
GLint  shdLambert2_lightpos;
GLint  shdLambert2_color;
GLint  shdLambert2_normal;
GLint  shdLambert2_opacity;
GLuint shdLambert3;
GLint  shdLambert3_position;
GLint  shdLambert3_projection;
GLint  shdLambert3_modelview;
GLint  shdLambert3_lightpos;
GLint  shdLambert3_color;
GLint  shdLambert3_opacity;
GLuint shdPhong;
GLint  shdPhong_position;
GLint  shdPhong_projection;
GLint  shdPhong_modelview;
GLint  shdPhong_normalmat;
GLint  shdPhong_lightpos;
GLint  shdPhong_color;
GLint  shdPhong_opacity;
GLuint shdPhong1;
GLint  shdPhong1_position;
GLint  shdPhong1_projection;
GLint  shdPhong1_modelview;
GLint  shdPhong1_normalmat;
GLint  shdPhong1_lightpos;
GLint  shdPhong1_color;
GLint  shdPhong1_normal;
GLint  shdPhong1_opacity;
GLuint shdPhong2;
GLint  shdPhong2_position;
GLint  shdPhong2_projection;
GLint  shdPhong2_modelview;
GLint  shdPhong2_normalmat;
GLint  shdPhong2_lightpos;
GLint  shdPhong2_color;
GLint  shdPhong2_opacity;
GLuint shdPhong3;
GLint  shdPhong3_position;
GLint  shdPhong3_projection;
GLint  shdPhong3_modelview;
GLint  shdPhong3_normalmat;
GLint  shdPhong3_lightpos;
GLint  shdPhong3_color;
GLint  shdPhong3_normal;
GLint  shdPhong3_opacity;

//
void makeFullbrightT()
{
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vt0, NULL);
    glCompileShader(vertexShader);

    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &ft0, NULL);
    glCompileShader(fragmentShader);

    shdFullbrightT = glCreateProgram();
        glAttachShader(shdFullbrightT, vertexShader);
        glAttachShader(shdFullbrightT, fragmentShader);
    glLinkProgram(shdFullbrightT);

    shdFullbrightT_position   = glGetAttribLocation(shdFullbrightT,  "position");
    shdFullbrightT_texcoord   = glGetAttribLocation(shdFullbrightT,  "texcoord");

    shdFullbrightT_projection = glGetUniformLocation(shdFullbrightT, "projection");
    shdFullbrightT_modelview  = glGetUniformLocation(shdFullbrightT, "modelview");
    shdFullbrightT_sampler    = glGetUniformLocation(shdFullbrightT, "tex");
}


void makeFullbright()
{
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &v0, NULL);
    glCompileShader(vertexShader);

    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &f0, NULL);
    glCompileShader(fragmentShader);

    shdFullbright = glCreateProgram();
        glAttachShader(shdFullbright, vertexShader);
        glAttachShader(shdFullbright, fragmentShader);
    glLinkProgram(shdFullbright);

    shdFullbright_position = glGetAttribLocation(shdFullbright, "position");
    
    shdFullbright_projection = glGetUniformLocation(shdFullbright, "projection");
    shdFullbright_modelview = glGetUniformLocation(shdFullbright, "modelview");
    shdFullbright_color = glGetUniformLocation(shdFullbright, "color");
    shdFullbright_opacity = glGetUniformLocation(shdFullbright, "opacity");
}

void makeLambert()
{
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &v1, NULL);
    glCompileShader(vertexShader);

    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &f1, NULL);
    glCompileShader(fragmentShader);

    shdLambert = glCreateProgram();
        glAttachShader(shdLambert, vertexShader);
        glAttachShader(shdLambert, fragmentShader);
    glLinkProgram(shdLambert);

    shdLambert_position = glGetAttribLocation(shdLambert, "position");
    
    shdLambert_projection = glGetUniformLocation(shdLambert, "projection");
    shdLambert_modelview = glGetUniformLocation(shdLambert, "modelview");
    shdLambert_lightpos = glGetUniformLocation(shdLambert, "lightpos");
    shdLambert_color = glGetUniformLocation(shdLambert, "color");
    shdLambert_opacity = glGetUniformLocation(shdLambert, "opacity");
}

void makeLambert1()
{
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &v11, NULL);
    glCompileShader(vertexShader);

    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &f1, NULL);
    glCompileShader(fragmentShader);

    shdLambert1 = glCreateProgram();
        glAttachShader(shdLambert1, vertexShader);
        glAttachShader(shdLambert1, fragmentShader);
    glLinkProgram(shdLambert1);

    shdLambert1_position = glGetAttribLocation(shdLambert1, "position");
    shdLambert1_normal = glGetAttribLocation(shdLambert1, "normal");
    
    shdLambert1_projection = glGetUniformLocation(shdLambert1, "projection");
    shdLambert1_modelview = glGetUniformLocation(shdLambert1, "modelview");
    shdLambert1_lightpos = glGetUniformLocation(shdLambert1, "lightpos");
    shdLambert1_color = glGetUniformLocation(shdLambert1, "color");
    shdLambert1_opacity = glGetUniformLocation(shdLambert1, "opacity");
}

void makeLambert2()
{
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &v1, NULL);
    glCompileShader(vertexShader);

    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &f1, NULL);
    glCompileShader(fragmentShader);

    shdLambert3 = glCreateProgram();
        glAttachShader(shdLambert3, vertexShader);
        glAttachShader(shdLambert3, fragmentShader);
    glLinkProgram(shdLambert3);

    shdLambert3_position = glGetAttribLocation(shdLambert3, "position");
    shdLambert3_color = glGetAttribLocation(shdLambert3, "color");
    
    shdLambert3_projection = glGetUniformLocation(shdLambert3, "projection");
    shdLambert3_modelview = glGetUniformLocation(shdLambert3, "modelview");
    shdLambert3_lightpos = glGetUniformLocation(shdLambert3, "lightpos");
    shdLambert3_opacity = glGetUniformLocation(shdLambert3, "opacity");
}

void makeLambert3()
{
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &v12, NULL);
    glCompileShader(vertexShader);

    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &f1, NULL);
    glCompileShader(fragmentShader);

    shdLambert2 = glCreateProgram();
        glAttachShader(shdLambert2, vertexShader);
        glAttachShader(shdLambert2, fragmentShader);
    glLinkProgram(shdLambert2);

    shdLambert2_position = glGetAttribLocation(shdLambert2, "position");
    shdLambert2_normal = glGetAttribLocation(shdLambert2, "normal");
    shdLambert2_color = glGetAttribLocation(shdLambert2, "color");
    
    shdLambert2_projection = glGetUniformLocation(shdLambert2, "projection");
    shdLambert2_modelview = glGetUniformLocation(shdLambert2, "modelview");
    shdLambert2_lightpos = glGetUniformLocation(shdLambert2, "lightpos");
    shdLambert2_opacity = glGetUniformLocation(shdLambert2, "opacity");
}

void makePhong()
{
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &v2, NULL);
    glCompileShader(vertexShader);

    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &f2, NULL);
    glCompileShader(fragmentShader);

    shdPhong = glCreateProgram();
        glAttachShader(shdPhong, vertexShader);
        glAttachShader(shdPhong, fragmentShader);
    glLinkProgram(shdPhong);

    shdPhong_position = glGetAttribLocation(shdPhong, "position");
    
    shdPhong_projection = glGetUniformLocation(shdPhong, "projection");
    shdPhong_modelview = glGetUniformLocation(shdPhong, "modelview");
    shdPhong_normalmat = glGetUniformLocation(shdPhong, "normalmat");
    shdPhong_lightpos = glGetUniformLocation(shdPhong, "lightpos");
    shdPhong_opacity = glGetUniformLocation(shdPhong, "opacity");
    shdPhong_color = glGetUniformLocation(shdPhong, "color");
}

void makePhong1()
{
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &v21, NULL);
    glCompileShader(vertexShader);

    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &f2, NULL);
    glCompileShader(fragmentShader);

    shdPhong1 = glCreateProgram();
        glAttachShader(shdPhong1, vertexShader);
        glAttachShader(shdPhong1, fragmentShader);
    glLinkProgram(shdPhong1);

    shdPhong1_position = glGetAttribLocation(shdPhong1, "position");
    shdPhong1_normal = glGetAttribLocation(shdPhong1, "normal");
    
    shdPhong1_projection = glGetUniformLocation(shdPhong1, "projection");
    shdPhong1_modelview = glGetUniformLocation(shdPhong1, "modelview");
    shdPhong1_normalmat = glGetUniformLocation(shdPhong1, "normalmat");
    shdPhong1_lightpos = glGetUniformLocation(shdPhong1, "lightpos");
    shdPhong1_opacity = glGetUniformLocation(shdPhong1, "opacity");
    shdPhong1_color = glGetUniformLocation(shdPhong1, "color");
}

void makePhong2()
{
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &v22, NULL);
    glCompileShader(vertexShader);

    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &f2, NULL);
    glCompileShader(fragmentShader);

    shdPhong2 = glCreateProgram();
        glAttachShader(shdPhong2, vertexShader);
        glAttachShader(shdPhong2, fragmentShader);
    glLinkProgram(shdPhong2);

    shdPhong2_position = glGetAttribLocation(shdPhong2, "position");
    shdPhong2_color = glGetAttribLocation(shdPhong2, "color");
    
    shdPhong2_projection = glGetUniformLocation(shdPhong2, "projection");
    shdPhong2_modelview = glGetUniformLocation(shdPhong2, "modelview");
    shdPhong2_normalmat = glGetUniformLocation(shdPhong2, "normalmat");
    shdPhong2_lightpos = glGetUniformLocation(shdPhong2, "lightpos");
    shdPhong2_opacity = glGetUniformLocation(shdPhong2, "opacity");
}

void makePhong3()
{
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &v23, NULL);
    glCompileShader(vertexShader);

    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &f2, NULL);
    glCompileShader(fragmentShader);

    shdPhong3 = glCreateProgram();
        glAttachShader(shdPhong3, vertexShader);
        glAttachShader(shdPhong3, fragmentShader);
    glLinkProgram(shdPhong3);

    shdPhong3_position = glGetAttribLocation(shdPhong3, "position");
    shdPhong3_color = glGetAttribLocation(shdPhong3, "color");
    shdPhong3_normal = glGetAttribLocation(shdPhong3, "normal");
    
    shdPhong3_projection = glGetUniformLocation(shdPhong3, "projection");
    shdPhong3_modelview = glGetUniformLocation(shdPhong3, "modelview");
    shdPhong3_normalmat = glGetUniformLocation(shdPhong3, "normalmat");
    shdPhong3_lightpos = glGetUniformLocation(shdPhong3, "lightpos");
    shdPhong3_opacity = glGetUniformLocation(shdPhong3, "opacity");
}

void makeAllShaders()
{
    makeFullbrightT();
    makeFullbright();
    makeLambert();
    makeLambert1();
    makeLambert2();
    makeLambert3();
    makePhong();
    makePhong1();
    makePhong2();
    makePhong3();
}

void shadeFullbrightT(GLint* position, GLint* projection, GLint* modelview, GLint* texcoord, GLint* sampler)
{
    *position = shdFullbrightT_position;
    *projection = shdFullbrightT_projection;
    *modelview = shdFullbrightT_modelview;
    *texcoord = shdFullbrightT_texcoord;
    *sampler = shdFullbrightT_sampler;
    glUseProgram(shdFullbrightT);
}

void shadeFullbright(GLint* position, GLint* projection, GLint* modelview, GLint* color, GLint* opacity)
{
    *position = shdFullbright_position;
    *projection = shdFullbright_projection;
    *modelview = shdFullbright_modelview;
    *color = shdFullbright_color;
    *opacity = shdFullbright_opacity;
    glUseProgram(shdFullbright);
}

void shadeLambert(GLint* position, GLint* projection, GLint* modelview, GLint* lightpos, GLint* color, GLint* opacity)
{
    *position = shdLambert_position;
    *projection = shdLambert_projection;
    *modelview = shdLambert_modelview;
    *lightpos = shdLambert_lightpos;
    *color = shdLambert_color;
    *opacity = shdLambert_opacity;
    glUseProgram(shdLambert);
}

void shadeLambert1(GLint* position, GLint* projection, GLint* modelview, GLint* lightpos, GLint* normal, GLint* color, GLint* opacity)
{
    *position = shdLambert1_position;
    *projection = shdLambert1_projection;
    *modelview = shdLambert1_modelview;
    *lightpos = shdLambert1_lightpos;
    *color = shdLambert1_color;
    *normal = shdLambert1_normal;
    *opacity = shdLambert1_opacity;
    glUseProgram(shdLambert1);
}

// notice: swapped this from 2 to 3
void shadeLambert3(GLint* position, GLint* projection, GLint* modelview, GLint* lightpos, GLint* normal, GLint* color, GLint* opacity)
{
    *position = shdLambert2_position;
    *projection = shdLambert2_projection;
    *modelview = shdLambert2_modelview;
    *lightpos = shdLambert2_lightpos;
    *color = shdLambert2_color;
    *normal = shdLambert2_normal;
    *opacity = shdLambert2_opacity;
    glUseProgram(shdLambert2);
}

// notice: swapped this from 3 to 2
void shadeLambert2(GLint* position, GLint* projection, GLint* modelview, GLint* lightpos, GLint* color, GLint* opacity)
{
    *position = shdLambert3_position;
    *projection = shdLambert3_projection;
    *modelview = shdLambert3_modelview;
    *lightpos = shdLambert3_lightpos;
    *color = shdLambert3_color;
    *opacity = shdLambert3_opacity;
    glUseProgram(shdLambert3);
}

void shadePhong(GLint* position, GLint* projection, GLint* modelview, GLint* normalmat, GLint* lightpos, GLint* color, GLint* opacity)
{
    *position = shdPhong_position;
    *projection = shdPhong_projection;
    *modelview = shdPhong_modelview;
    *normalmat = shdPhong_normalmat;
    *lightpos = shdPhong_lightpos;
    *color = shdPhong_color;
    *opacity = shdPhong_opacity;
    glUseProgram(shdPhong);
}

void shadePhong1(GLint* position, GLint* projection, GLint* modelview, GLint* normalmat, GLint* lightpos, GLint* normal, GLint* color, GLint* opacity)
{
    *position = shdPhong1_position;
    *projection = shdPhong1_projection;
    *modelview = shdPhong1_modelview;
    *normalmat = shdPhong1_normalmat;
    *lightpos = shdPhong1_lightpos;
    *color = shdPhong1_color;
    *normal = shdPhong1_normal;
    *opacity = shdPhong1_opacity;
    glUseProgram(shdPhong1);
}

void shadePhong2(GLint* position, GLint* projection, GLint* modelview, GLint* normalmat, GLint* lightpos, GLint* color, GLint* opacity)
{
    *position = shdPhong2_position;
    *projection = shdPhong2_projection;
    *modelview = shdPhong2_modelview;
    *normalmat = shdPhong2_normalmat;
    *lightpos = shdPhong2_lightpos;
    *color = shdPhong2_color;
    *opacity = shdPhong2_opacity;
    glUseProgram(shdPhong2);
}

void shadePhong3(GLint* position, GLint* projection, GLint* modelview, GLint* normalmat, GLint* lightpos, GLint* normal, GLint* color, GLint* opacity)
{
    *position = shdPhong3_position;
    *projection = shdPhong3_projection;
    *modelview = shdPhong3_modelview;
    *normalmat = shdPhong3_normalmat;
    *lightpos = shdPhong3_lightpos;
    *color = shdPhong3_color;
    *normal = shdPhong3_normal;
    *opacity = shdPhong3_opacity;
    glUseProgram(shdPhong3);
}

#endif
