#ifndef SPRITE_H
#define SPRITE_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef struct {
  GLfloat verts[16];
  GLfloat matrix[16];
  GLfloat spriteSheetData[4];

  GLuint VAO;
  GLuint VBO;
} Sprite;

void Sprite_ctor(Sprite *spr, GLfloat sizeX, GLfloat sizeY, GLfloat frameX, GLfloat frameY);

void Sprite_move(Sprite *spr, GLfloat x, GLfloat y);
void Sprite_rot(Sprite *spr, GLfloat angle);
void Sprite_scale(Sprite *spr, GLfloat x, GLfloat y);

void Sprite_render(Sprite *spr, GLuint transformLoc, GLuint spriteSheetDataLoc);

#endif
