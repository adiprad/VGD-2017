#include "utils.h"
#include "sprite.h"

const char *vSource = "#version 330 core\n"
  "layout (location = 0) in vec2 vertices;\n"
  "layout (location = 1) in vec2 texCoord;\n"
  "uniform mat4 transform;\n"
  "uniform vec4 spriteSheetData;\n"
  "out vec2 TexCoord;\n"
  "void main() {\n"
  "   gl_Position = transform * vec4(vertices.xy, 0.0, 1.0);\n"
  "   TexCoord = (texCoord / spriteSheetData.xy) + (spriteSheetData.zw / spriteSheetData.xy);\n"
  "}\0";

const char *fSource = "#version 330 core\n"
  "out vec4 FragColor;\n"
  "uniform sampler2D tex;\n"
  "in vec2 TexCoord;\n"
  "void main() {\n"
  "   FragColor = texture(tex, TexCoord);\n"
  "}\0";

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
  if(key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    glfwSetWindowShouldClose(window, GLFW_TRUE);
}

int main(int argc, char const *argv[]) {
  GLFWwindow* window = configureGL("", 640, 640, key_callback, argv[0]);

  GLuint shader = createShaderProgram(vSource, fSource);

  glUseProgram(shader);

  GLuint transformLoc = glGetUniformLocation(shader, "transform");
  GLuint spriteSheetDataLoc = glGetUniformLocation(shader, "spriteSheetData");

  Sprite ball; Sprite_ctor(&ball, 1, 1, 0, 0);

  Sprite man; Sprite_ctor(&man, 4, 1, 0, 0);

  Sprite_scale(&ball, 0.2, 0.2);
  Sprite_scale(&man, 0.2, 0.2);

  //load texture
  GLuint ballTex = createTexture("res/ball.png");
  //load texture

  //load texture
  GLuint manTex = createTexture("res/player.png");
  //load texture

  double ms = glfwGetTime();
  while (!glfwWindowShouldClose(window)) {
    glClearColor(0.2f, 0.4f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    if(glfwGetTime()-ms>=0.25) {
      man.spriteSheetData[2]++;
      ms = glfwGetTime();
    }

    Sprite_move(&man, -0.001, 0);
    Sprite_rot(&ball, (M_PI*glfwGetTime())/1000);

    glBindTexture(GL_TEXTURE_2D, ballTex);
    Sprite_render(&ball, transformLoc, spriteSheetDataLoc);

    glBindTexture(GL_TEXTURE_2D, manTex);
    Sprite_render(&man, transformLoc, spriteSheetDataLoc);

    glfwSwapBuffers(window);
    glfwPollEvents();
  }
  glfwTerminate();
  return 0;
}
