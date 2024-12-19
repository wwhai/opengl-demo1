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

#ifndef SDL2_GL_UTILS_H
#define SDL2_GL_UTILS_H

#include <SDL2/SDL.h>
#include <GL/glew.h>

typedef struct SDLDisplay {
    SDL_Window *window;
    SDL_GLContext glContext;
    int width;
    int height;
} SDLDisplay;

int Gl_Init(SDLDisplay *display, const char *title, int width, int height);
GLuint LoadShaders(const char *vertex_file_path, const char *fragment_file_path);
void Gl_Cleanup(SDLDisplay *display);

#endif // SDL2_GL_UTILS_H
