#include "sprite.h"

void Sprite_ctor(Sprite *spr, GLfloat sizeX, GLfloat sizeY, GLfloat frameX, GLfloat frameY) {
  GLfloat verts[16] = {
      -1.0f, 1.0f, 0.0f, 1.0f,
      1.0f, 1.0f, 1.0f, 1.0f,
      -1.0f, -1.0f, 0.0f, 0.0f,
      1.0f, -1.0f, 1.0f, 0.0f
  };
  GLfloat matrix[16] = {
    1.0, 0.0, 0.0, 0.0,
    0.0, 1.0, 0.0, 0.0,
    0.0, 0.0, 1.0, 0.0,
    0.0, 0.0, 0.0, 1.0
  };
  GLfloat spriteSheetData[4] = {sizeX, sizeY, frameX, frameY};

  memcpy(spr->verts, verts, 16*sizeof(GLfloat));
  memcpy(spr->matrix, matrix, 16*sizeof(GLfloat));
  memcpy(spr->spriteSheetData, spriteSheetData, 4*sizeof(GLfloat));

  glGenVertexArrays(1, &spr->VAO);
  glGenBuffers(1, &spr->VBO);

  glBindVertexArray(spr->VAO);

  glBindBuffer(GL_ARRAY_BUFFER, spr->VBO);
  glBufferData(GL_ARRAY_BUFFER, 16*sizeof(GLfloat), spr->verts, GL_STATIC_DRAW);

  glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4*sizeof(GLfloat), (void*)0);
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4*sizeof(GLfloat), (void*)(2*sizeof(GLfloat)));
  glEnableVertexAttribArray(1);
}
void Sprite_move(Sprite *spr, GLfloat x, GLfloat y) {
  spr->matrix[12] += x;
  spr->matrix[13] += y;
}
void Sprite_rot(Sprite *spr, GLfloat angle) {
  GLfloat rotMat[4] = {
    cos(angle), sin(angle),
   -sin(angle), cos(angle)
  };

  GLfloat mat1 = rotMat[0]*spr->matrix[0]+rotMat[1]*spr->matrix[4];
  GLfloat mat2 = rotMat[0]*spr->matrix[1]+rotMat[1]*spr->matrix[5];
  GLfloat mat3 = rotMat[2]*spr->matrix[0]+rotMat[3]*spr->matrix[4];
  GLfloat mat4 = rotMat[2]*spr->matrix[1]+rotMat[3]*spr->matrix[5];

  spr->matrix[0] = mat1;
  spr->matrix[1] = mat2;
  spr->matrix[4] = mat3;
  spr->matrix[5] = mat4;
}
void Sprite_scale(Sprite *spr, GLfloat x, GLfloat y) {
  spr->matrix[0] = x;
  spr->matrix[5] = y;
}
void Sprite_render(Sprite *spr, GLuint transformLoc, GLuint spriteSheetDataLoc) {
  glUniformMatrix4fv(transformLoc, 1, GL_FALSE, spr->matrix);
  glUniform4fv(spriteSheetDataLoc, 1, spr->spriteSheetData);
  glBindVertexArray(spr->VAO);
  glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
}
