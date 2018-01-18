#ifndef UTILS_H
#define UTILS_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char gamePath[1024];

GLFWwindow* configureGL(const char *title, int width, int height, GLFWkeyfun key_callback, const char *argvPath);

GLuint createShaderProgram(const char *vertexShaderSource, const char *fragmentShaderSource);

GLuint createTexture(const char *resPath);

#endif
