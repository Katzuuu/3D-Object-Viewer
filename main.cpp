#define STB_IMAGE_IMPLEMENTATION

#include <vector>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Window.h"
#include "Camera.h"
#include "Shader.h"
#include "Mesh.h"
#include "Texture.h"

#define WIN_W 800
#define WIN_H 600

std::vector<Mesh*> meshes;
std::vector<Shader*> shaders;

void createObjects() {
    constexpr unsigned int indices[] = {
        0, 3, 1,
        1, 3, 2,
        2, 3, 0,
        0, 1, 2
    };

    constexpr GLfloat vertices[] = {
        -1.0f, -1.0f, 0.0f, 0.0f, 0.0f,
        0.0f, -1.0f, 1.0f, 0.5f, 0.0f,
        1.0f, -1.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 1.0f, 0.0f, 0.5f, 1.0f,
    };

    Mesh *obj1 = new Mesh();
    obj1->CreateMesh(vertices, indices, std::size(vertices), std::size(indices));
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
}

int main() {
    GLdouble deltaTime = 0.0f;
    GLdouble lastTime = 0.0f;

    Window window = Window(WIN_W, WIN_H);
    window.Initialize();

    createObjects();
    createShaders();

    Camera camera = Camera(
        glm::vec3(0.0f, 0.0f, 0.0f),
        glm::vec3(0.0f, 1.0f, 0.0f),
         -90.0f, 0.0f,
        5.0f, 0.4f
    );

    Texture brickTexture = Texture("../textures/brick.png");
    brickTexture.loadTexture();

    Texture dirtTexture = Texture("../textures/dirt.png");
    dirtTexture.loadTexture();

    while(!window.GetShouldClose()) {
        const GLdouble currentTime = glfwGetTime();
        deltaTime = currentTime - lastTime;
        lastTime = currentTime;

        window.PollEvents();
        camera.KeyControl(window.GetKeys(), deltaTime);
        camera.MouseControl(window.GetXChange(), window.GetYChange());

        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        shaders[0]->UseShader();

        // model mat
        glm::mat4 model(1.0f);
        model = glm::translate(model, glm::vec3(0.0f, 0.0f, -2.5f));
        model = glm::scale(model, glm::vec3(0.4f, 0.4f, 1.0f));
        // projection mat
        glm::mat4 projection = glm::perspective(
            45.0f,
            window.GetBufferWidth() / window.GetBufferHeight(),
            0.1f, 100.0f
        );

        glUniformMatrix4fv(shaders[0]->GetModelLocation(), 1, GL_FALSE, glm::value_ptr(model));
        glUniformMatrix4fv(shaders[0]->GetViewLocation(), 1, GL_FALSE, glm::value_ptr(camera.GetViewMatrix()));
        glUniformMatrix4fv(shaders[0]->GetProjectionLocation(), 1, GL_FALSE, glm::value_ptr(projection));

        brickTexture.useTexture();

        for (const Mesh *mesh : meshes)
            mesh->RenderMesh();

        glUseProgram(0);

        window.SwapBuffers();
    }

    cleanup();
    return EXIT_SUCCESS;
}