#include "NPrimitivePlane3D.h"

#include "GameFramework.h"
#include "ShaderManager.h"
#include "PrimitiveShaderColor3D.h"
#include "dtPositionNormalColorVertex.h"
#include "BasicLightingShader.h"

void NPrimitivePlane3D::SetColor(NColor color) {
	mColor = color;

	float hsx = mSizeX / 2.0f;
	float hsy = mSizeY / 2.0f;

	dtPositionNormalColorVertex* vertexData = new dtPositionNormalColorVertex[4];

	GLubyte r = mColor.r;
	GLubyte g = mColor.g;
	GLubyte b = mColor.b;
	GLubyte a = mColor.a;

	// front face
	vertexData[0].SetPositionAndColor(-hsx, -hsy, 0, r, g, b, a); // up-left-front
	vertexData[1].SetPositionAndColor(-hsx, hsy, 0, r, g, b, a);  // down-left-front
	vertexData[2].SetPositionAndColor(hsx, -hsy, 0, r, g, b, a);  // up-right-front
	vertexData[3].SetPositionAndColor(hsx, hsy, 0, r, g, b, a);   // down-right-front
	dtPositionNormalColorVertex::ProcessNormal(&vertexData[0], &vertexData[1], &vertexData[2]); // normal
	dtPositionNormalColorVertex::ProcessNormal(&vertexData[1], &vertexData[3], &vertexData[2]); // normal

	int size = ((sizeof(float) * 3) + (sizeof(float) * 3) + (sizeof(GLbyte) * 4)) * 4;

	glBindBuffer(GL_ARRAY_BUFFER, mVBO_ID);
	glBufferData(GL_ARRAY_BUFFER, size, &vertexData[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void NPrimitivePlane3D::Initialize(float x, float y, float z,
	float sizeX, float sizeY)
{
	Drawable3D::Initialize(x, y, z);

	mSizeX = sizeX;
	mSizeY = sizeY;

	GameFramework* framework = GameFramework::GET_FRAMEWORK();
	ShaderManager* shaderManagment = framework->GetShaderManager();

	const std::string baseShaderPath = "Shaders/BasicLightingShader";
	mCurrentShader = (BaseShader*)shaderManagment->LoadAndGetShader<BasicLightingShader>(baseShaderPath);

	float hsx = mSizeX / 2.0f;
	float hsy = mSizeY / 2.0f;

	dtPositionNormalColorVertex* vertexData = new dtPositionNormalColorVertex[4];

	GLubyte r = mColor.r;
	GLubyte g = mColor.g;
	GLubyte b = mColor.b;
	GLubyte a = mColor.a;

	// plane
	vertexData[0].SetPositionAndColor(-hsx, -hsy, 0, r, g, b, a); // up-left-front
	vertexData[1].SetPositionAndColor(-hsx, hsy, 0, r, g, b, a);  // down-left-front
	vertexData[2].SetPositionAndColor(hsx, -hsy, 0, r, g, b, a);  // up-right-front
	vertexData[3].SetPositionAndColor(hsx, hsy, 0, r, g, b, a);   // down-right-front
	dtPositionNormalColorVertex::ProcessNormal(&vertexData[0], &vertexData[1], &vertexData[2]); // normal
	dtPositionNormalColorVertex::ProcessNormal(&vertexData[1], &vertexData[3], &vertexData[2]); // normal

	int size = ((sizeof(float) * 3) + (sizeof(float) * 3) + (sizeof(GLbyte) * 4)) * 4;

	glBindBuffer(GL_ARRAY_BUFFER, mVBO_ID);
	glBufferData(GL_ARRAY_BUFFER, size, &vertexData[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// indices
	int indicesArraySize = 6 * 1; // 1 faces with (2 triangles = 3 each triangle = 6 indices)
	unsigned int* indicesData = new unsigned int[indicesArraySize];
	// front face
	indicesData[0] = 0; indicesData[1] = 1; indicesData[2] = 2;
	indicesData[3] = 1; indicesData[4] = 3; indicesData[5] = 2;

	int indexDataSize = sizeof(int) * indicesArraySize;

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mIBO_ID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexDataSize, &(indicesData[0]), GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	mIndicesCount = indicesArraySize;
}

void NPrimitivePlane3D::Draw(float dt) {
	mCurrentShader->Use();

	glEnable(GL_DEPTH_TEST);

	// matrix
	GLuint cameraLocation = mCurrentShader->GetUniformLocation("camera");
	GLuint modelLocation = mCurrentShader->GetUniformLocation("model");
	GLuint cameraPositionLocation = mCurrentShader->GetUniformLocation("cameraPosition");

	// matrix
	glUniform3f(cameraPositionLocation, mRenderCamera->GetX(), mRenderCamera->GetY(), mRenderCamera->GetZ());
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, &(worldMatrix[0][0]));
	glUniformMatrix4fv(cameraLocation, 1, GL_FALSE, &(mRenderCamera->GetResultMatrix()[0][0]));

	glBindBuffer(GL_ARRAY_BUFFER, mVBO_ID);

	// Position
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(dtPositionNormalColorVertex),
		(void*)offsetof(dtPositionNormalColorVertex, dtPositionNormalColorVertex::Position));
	// Normal
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(dtPositionNormalColorVertex),
		(void*)offsetof(dtPositionNormalColorVertex, dtPositionNormalColorVertex::Normal));
	// Color
	glVertexAttribPointer(2, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(dtPositionNormalColorVertex),
		(void*)offsetof(dtPositionNormalColorVertex, dtPositionNormalColorVertex::Color));

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mIBO_ID);

	// Esto dibuja en Frame Buffer
	glDrawElements(GL_TRIANGLES, mIndicesCount, GL_UNSIGNED_INT, (void*)0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glDisableVertexAttribArray(0);

	glDisable(GL_DEPTH_TEST);

	mCurrentShader->Stop();
}