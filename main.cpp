#include <iostream>
#include <vector>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Window.h"
#include "Shader.h"
#include "Mesh.h"

#define WIN_W 800
#define WIN_H 600

Window *window = new Window(WIN_W, WIN_H);
std::vector<Mesh*> meshes;
std::vector<Shader*> shaders;

bool direction = true;
float triOffset = 0.0f;
float triMaxOffset = 360.0f;
float increment = 0.5f;

void createObjects() {
    constexpr unsigned int indices[] = {
        0, 3, 1,
        1, 3, 2,
        2, 3, 0,
        0, 1, 2
    };

    constexpr GLfloat vertices[] = {
        -1.0f, -1.0f, 0.0f,
        0.0f, -1.0f, 1.0f,
        1.0f, -1.0f, 0.0f,
        0.0f, 1.0f, 0.0f
    };

    Mesh *obj1 = new Mesh();
    obj1->CreateMesh(vertices, indices, 12, 12);
    meshes.push_back(obj1);
}

void createShaders() {
    Shader *shader = new Shader();
    shader->CreateFromFiles(
        "../shaders/shader.vert",
        "../shaders/shader.frag"
    );
    shaders.push_back(shader);
}

void cleanup() {
    for (const Mesh* mesh : meshes) delete mesh;
    for (const Shader* shader : shaders) delete shader;
    delete window;
}

int main() {
    window->Initialize();

    createObjects();
    createShaders();

    while(!window->GetShouldClose()) {
        triOffset += direction ? increment : increment * -1;
        if(abs(triOffset) >= triMaxOffset)
            direction = !direction;

        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        shaders[0]->UseShader();

        // model mat
        glm::mat4 model(1.0f);
        model = glm::translate(model, glm::vec3(triOffset / 355, 0.0f, -2.5f));
        model = glm::scale(model, glm::vec3(0.4f, 0.4f, 1.0f));
        // projection mat
        glm::mat4 projection = glm::perspective(
            45.0f,
            window->GetBufferWidth() / window->GetBufferHeight(),
            0.1f, 100.0f
        );

        glUniformMatrix4fv(shaders[0]->GetModelLocation(), 1, GL_FALSE, glm::value_ptr(model));
        glUniformMatrix4fv(shaders[0]->GetProjectionLocation(), 1, GL_FALSE, glm::value_ptr(projection));

        for (const Mesh *mesh : meshes)
            mesh->RenderMesh();

        glUseProgram(0);

        window->SwapBuffers();
        window->PollEvents();
    }

    cleanup();
    return EXIT_SUCCESS;
}