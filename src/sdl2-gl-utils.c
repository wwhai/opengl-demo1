// Copyright (C) 2024 wwhai
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Affero General Public License as
// published by the Free Software Foundation, either version 3 of the
// License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Affero General Public License for more details.
//
// You should have received a copy of the GNU Affero General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.

#include "sdl2-gl-utils.h"
#include <stdio.h>
#include <stdlib.h>

int Gl_Init(SDLDisplay *display, const char *title, int width, int height) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return -1;
    }

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

    display->window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                                       width, height, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
    if (!display->window) {
        printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        SDL_Quit();
        return -1;
    }

    display->glContext = SDL_GL_CreateContext(display->window);
    if (!display->glContext) {
        printf("OpenGL context could not be created! SDL_Error: %s\n", SDL_GetError());
        SDL_DestroyWindow(display->window);
        SDL_Quit();
        return -1;
    }

    if (SDL_GL_SetSwapInterval(1) < 0) {
        printf("Warning: Unable to set VSync! SDL_Error: %s\n", SDL_GetError());
    }

    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK) {
        printf("GLEW could not be initialized!\n");
        SDL_GL_DeleteContext(display->glContext);
        SDL_DestroyWindow(display->window);
        SDL_Quit();
        return -1;
    }

    display->width = width;
    display->height = height;
    return 0;
}

GLuint LoadShaders(const char *vertex_file_path, const char *fragment_file_path) {
    GLuint VertexShaderID = glCreateShader(GL_VERTEX_SHADER);
    GLuint FragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

    FILE *vertex_file = fopen(vertex_file_path, "r");
    FILE *fragment_file = fopen(fragment_file_path, "r");

    if (!vertex_file || !fragment_file) {
        printf("Failed to open shader files.\n");
        return 0;
    }

    char *vertex_code = (char *)malloc(8192);
    char *fragment_code = (char *)malloc(8192);
    fread(vertex_code, 1, 8192, vertex_file);
    fread(fragment_code, 1, 8192, fragment_file);

    fclose(vertex_file);
    fclose(fragment_file);

    const char *vertex_source = vertex_code;
    const char *fragment_source = fragment_code;

    glShaderSource(VertexShaderID, 1, &vertex_source, NULL);
    glCompileShader(VertexShaderID);

    glShaderSource(FragmentShaderID, 1, &fragment_source, NULL);
    glCompileShader(FragmentShaderID);

    GLuint ProgramID = glCreateProgram();
    glAttachShader(ProgramID, VertexShaderID);
    glAttachShader(ProgramID, FragmentShaderID);
    glLinkProgram(ProgramID);

    glDeleteShader(VertexShaderID);
    glDeleteShader(FragmentShaderID);

    free(vertex_code);
    free(fragment_code);

    return ProgramID;
}

void Gl_Cleanup(SDLDisplay *display) {
    SDL_GL_DeleteContext(display->glContext);
    SDL_DestroyWindow(display->window);
    SDL_Quit();
}
