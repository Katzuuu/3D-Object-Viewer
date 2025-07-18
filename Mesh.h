# pragma once

#include <glad/glad.h>

class Mesh {
    GLuint VAO, VBO, EBO;
    GLsizei indexCount;
public:
    Mesh();
    ~Mesh();
    void CreateMesh(const GLfloat *vertices, const unsigned int *indices, unsigned int numOfVertices, GLsizei numOfIndices);
    void RenderMesh() const;
    void ClearMesh();
};

