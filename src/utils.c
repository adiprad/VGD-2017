#include "utils.h"
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

GLFWwindow* configureGL(const char *title, int width, int height, GLFWkeyfun key_callback, const char *argvPath) {
  GLFWwindow* window;

  glfwInit();

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  window = glfwCreateWindow(width, height, title, NULL, NULL);
  if (!window) {
      printf("Failed to create GLFW window.\n");
      glfwTerminate();
      return window;
  }
  glfwSetKeyCallback(window, key_callback);

  glfwMakeContextCurrent(window);
  glfwSetWindowAspectRatio(window, 1, 1);

  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
      printf("Failed to initialize GLAD.\n");
      return window;
  }

  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  //initialize game path
  strcpy(gamePath, argvPath); //set gamePath to argvPath
  char *pEnd = strrchr(gamePath, '/'); //find binary part of path
  if(!pEnd) {
    printf("ERROR: Invalid argvPath %s\n", argvPath);
    exit(-1);
  }
  *pEnd++ = '\0'; //cut off path

  stbi_set_flip_vertically_on_load(1);

  return window;
}
GLuint createShaderProgram(const char *vertexShaderSource, const char *fragmentShaderSource) {
  GLint success;
  char infoLog[512];

  GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
  glCompileShader(vertexShader);
  glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
  if (!success) {
      glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
      printf("Vertex Shader Compilation Failed: \n%s\n", infoLog);
      exit(-1);
  }
  GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
  glCompileShader(fragmentShader);
  glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
  if (!success) {
      glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
      printf("Fragment Shader Compilation Failed: \n%s\n", infoLog);
      exit(-1);
  }
  GLuint program = glCreateProgram();
  glAttachShader(program, vertexShader);
  glAttachShader(program, fragmentShader);
  glLinkProgram(program);
  glGetProgramiv(program, GL_LINK_STATUS, &success);
  if (!success) {
      glGetProgramInfoLog(program, 512, NULL, infoLog);
      printf("Shader Program Linking Failed: \n%s\n", infoLog);
      exit(-1);
  }
  glDeleteShader(vertexShader);
  glDeleteShader(fragmentShader);

  return program;
}
GLuint createTexture(const char *resPath) {
  GLuint tex;
  glGenTextures(1, &tex);
  glBindTexture(GL_TEXTURE_2D, tex);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

  GLint width, height, bpp;
  char pathBuf[1024];
  sprintf(pathBuf, "%s/%s", gamePath, resPath);

  GLubyte *data = stbi_load(pathBuf, &width, &height, &bpp, 0);
  if (data) {
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);
  } else {
    printf("Failed to load texture: %s\n", pathBuf);
  }
  stbi_image_free(data);

  return tex;
}
