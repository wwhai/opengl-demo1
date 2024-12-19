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
#include <GL/glew.h>
#include <SDL2/SDL.h>
#include <math.h>

static const GLfloat cube_vertices[] = {
    -1.0, -1.0, -1.0,
     1.0, -1.0, -1.0,
     1.0,  1.0, -1.0,
    -1.0,  1.0, -1.0,
    -1.0, -1.0,  1.0,
     1.0, -1.0,  1.0,
     1.0,  1.0,  1.0,
    -1.0,  1.0,  1.0,
};

static const GLuint cube_indices[] = {
    0, 1, 2,  2, 3, 0,  // Back
    4, 5, 6,  6, 7, 4,  // Front
    0, 4, 7,  7, 3, 0,  // Left
    1, 5, 6,  6, 2, 1,  // Right
    3, 7, 6,  6, 2, 3,  // Top
    0, 4, 5,  5, 1, 0   // Bottom
};

int main() {
    SDLDisplay display;
    if (Gl_Init(&display, "3D Cube Demo", 800, 600) != 0) return -1;

    GLuint shader_program = LoadShaders("vertex_shader.glsl", "fragment_shader.glsl");
    glUseProgram(shader_program);

    GLuint vao, vbo, ebo;
    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);
    glGenBuffers(1, &ebo);

    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(cube_vertices), cube_vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(cube_indices), cube_indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void*)0);
    glEnableVertexAttribArray(0);

    glEnable(GL_DEPTH_TEST);

    float angle = 0.0f;

    SDL_Event event;
    int running = 1;
    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) running = 0;
        }

        angle += 0.01f;

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glPushMatrix();
        glRotatef(angle, 1.0f, 1.0f, 0.0f);
        glDrawElements(GL_TRIANGLES, sizeof(cube_indices) / sizeof(GLuint), GL_UNSIGNED_INT, 0);
        glPopMatrix();

        SDL_GL_SwapWindow(display.window);
    }

    Gl_Cleanup(&display);
    return 0;
}
