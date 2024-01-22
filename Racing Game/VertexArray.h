#pragma once

constexpr float vertices[] = //Define vertices on left,right -top & left,right -bottom & middle of the screen. 
							//They will be used by the indices list to define 2 twiangles that will define a wectangle
							//0 & 1 are UV (texture position)
{
	-0.5f,0.5f,0.0f, //0.0f,0.0f, //Top Left
	0.5f,0.5f,0.0f, //1.0f,0.0f, //Top Right
	0.5f,-0.5f,0.0f, //1.0f,1.0f, //Bottom Right
	-0.5f,-0.5f,0.0f, //0.0f,1.0f //Bottom Left
};

constexpr unsigned int indices[] = //1st Twiangle will be composed of the left,right -top & right-bottom vertices, and the 2nd twiangle is composed of the right, left - bottom & top-left vertices
{
	0,1,2,
	2,3,0
};

class VertexArray
{
public:
	VertexArray(const float* verticesP, unsigned int nbVerticesP, const unsigned int* indicesP, unsigned int nbIndicesP);
	~VertexArray();

	void setActive();
	unsigned int getNbVerctices() const { return nbVertices; }
	unsigned int getNbIndices() const { return nbIndices; }

private:
	unsigned int nbVertices;
	unsigned int nbIndices;

	//OpenGL ID of the vertex array obj
	unsigned int vertexArray;

	//OpenGL ID of the Vertex Buffer <--will store data
	unsigned int vertexbuffer;

	//OpenGL ID of the Index Buffer
	unsigned int indexBuffer;
};
