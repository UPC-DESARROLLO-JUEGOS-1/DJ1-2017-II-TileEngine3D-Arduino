#include "NPrimitiveCube3D.h"

#include "GameFramework.h"
#include "ShaderManager.h"
#include "PrimitiveShaderColor3D.h"
#include "dtPositionNormalColorVertex.h"
#include "BasicLightingShader.h"

void NPrimitiveCube3D::SetColor(NColor color) {
	mColor = color;

	float hsx = mSizeX / 2.0f;
	float hsy = mSizeY / 2.0f;
	float hsz = mSizeZ / 2.0f;

	dtPositionNormalColorVertex* vertexData = new dtPositionNormalColorVertex[24];

	GLubyte r = mColor.r;
	GLubyte g = mColor.g;
	GLubyte b = mColor.b;
	GLubyte a = mColor.a;

	// front face
	vertexData[0].SetPositionAndColor(-hsx, -hsy, -hsz, r, g, b, a); // up-left-front
	vertexData[1].SetPositionAndColor(-hsx, hsy, -hsz, r, g, b, a);  // down-left-front
	vertexData[2].SetPositionAndColor(hsx, -hsy, -hsz, r, g, b, a);  // up-right-front
	vertexData[3].SetPositionAndColor(hsx, hsy, -hsz, r, g, b, a);   // down-right-front
	dtPositionNormalColorVertex::ProcessNormal(&vertexData[0], &vertexData[1], &vertexData[2]); // normal
	dtPositionNormalColorVertex::ProcessNormal(&vertexData[1], &vertexData[3], &vertexData[2]); // normal

	//left face
	vertexData[4].SetPositionAndColor(-hsx, -hsy, -hsz, r, g, b, a); // up-left-front
	vertexData[5].SetPositionAndColor(-hsx, hsy, -hsz, r, g, b, a);  // down-left-front
	vertexData[6].SetPositionAndColor(-hsx, -hsy, hsz, r, g, b, a); // up-left-back
	vertexData[7].SetPositionAndColor(-hsx, hsy, hsz, r, g, b, a);	// down-left-back						
	dtPositionNormalColorVertex::ProcessNormal(&vertexData[4], &vertexData[5], &vertexData[6]); // normal
	dtPositionNormalColorVertex::ProcessNormal(&vertexData[5], &vertexData[7], &vertexData[6]); // normal

	// right face
	vertexData[8].SetPositionAndColor(hsx, -hsy, -hsz, r, g, b, a);  // up-right-front
	vertexData[9].SetPositionAndColor(hsx, hsy, -hsz, r, g, b, a);   // down-right-front
	vertexData[10].SetPositionAndColor(hsx, -hsy, hsz, r, g, b, a);	// up-right-back
	vertexData[11].SetPositionAndColor(hsx, hsy, hsz, r, g, b, a);	// down-right-back
	dtPositionNormalColorVertex::ProcessNormal(&vertexData[8], &vertexData[9], &vertexData[10]); // normal
	dtPositionNormalColorVertex::ProcessNormal(&vertexData[9], &vertexData[11], &vertexData[10]); // normal															// normal

	// back face
	vertexData[12].SetPositionAndColor(-hsx, -hsy, hsz, r, g, b, a); // up-left-back
	vertexData[13].SetPositionAndColor(-hsx, hsy, hsz, r, g, b, a);	// down-left-back
	vertexData[14].SetPositionAndColor(hsx, -hsy, hsz, r, g, b, a);	// up-right-back
	vertexData[15].SetPositionAndColor(hsx, hsy, hsz, r, g, b, a);	// down-right-back
	dtPositionNormalColorVertex::ProcessNormal(&vertexData[12], &vertexData[13], &vertexData[14]); // normal
	dtPositionNormalColorVertex::ProcessNormal(&vertexData[13], &vertexData[15], &vertexData[14]); // normal	

	// top face
	vertexData[16].SetPositionAndColor(-hsx, -hsy, -hsz, r, g, b, a); // up-left-front
	vertexData[17].SetPositionAndColor(hsx, -hsy, -hsz, r, g, b, a);  // up-right-front
	vertexData[18].SetPositionAndColor(-hsx, -hsy, hsz, r, g, b, a); // up-left-back
	vertexData[19].SetPositionAndColor(hsx, -hsy, hsz, r, g, b, a);	// up-right-back
	dtPositionNormalColorVertex::ProcessNormal(&vertexData[16], &vertexData[17], &vertexData[18]); // normal
	dtPositionNormalColorVertex::ProcessNormal(&vertexData[17], &vertexData[19], &vertexData[18]); // normal	

	// bottom face
	vertexData[20].SetPositionAndColor(-hsx, hsy, -hsz, r, g, b, a);  // down-left-front
	vertexData[21].SetPositionAndColor(hsx, hsy, -hsz, r, g, b, a);   // down-right-front
	vertexData[22].SetPositionAndColor(-hsx, hsy, hsz, r, g, b, a);	// down-left-back
	vertexData[23].SetPositionAndColor(hsx, hsy, hsz, r, g, b, a);	// down-right-back
	dtPositionNormalColorVertex::ProcessNormal(&vertexData[20], &vertexData[21], &vertexData[22]); // normal
	dtPositionNormalColorVertex::ProcessNormal(&vertexData[21], &vertexData[23], &vertexData[22]); // normal

	int size = ((sizeof(float) * 3) + (sizeof(float) * 3) + (sizeof(GLbyte) * 4)) * 24;

	glBindBuffer(GL_ARRAY_BUFFER, mVBO_ID);
	glBufferData(GL_ARRAY_BUFFER, size, &vertexData[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void NPrimitiveCube3D::Initialize(float x, float y, float z,
	float sizeX, float sizeY, float sizeZ)
{
	Drawable3D::Initialize(x, y, z);

	mSizeX = sizeX;
	mSizeY = sizeY;
	mSizeZ = sizeZ;

	GameFramework* framework = GameFramework::GET_FRAMEWORK();
	ShaderManager* shaderManagment = framework->GetShaderManager();

	const std::string baseShaderPath = "Shaders/BasicLightingShader";
	mCurrentShader = (BaseShader*)shaderManagment->LoadAndGetShader<BasicLightingShader>(baseShaderPath);

	float hsx = mSizeX / 2.0f;
	float hsy = mSizeY / 2.0f;
	float hsz = mSizeZ / 2.0f;

	dtPositionNormalColorVertex* vertexData = new dtPositionNormalColorVertex[24];

	GLubyte r = mColor.r;
	GLubyte g = mColor.g;
	GLubyte b = mColor.b;
	GLubyte a = mColor.a;

	// front face
	vertexData[0].SetPositionAndColor(-hsx, -hsy, -hsz, r, g, b, a); // up-left-front
	vertexData[1].SetPositionAndColor(-hsx, hsy, -hsz, r, g, b, a);  // down-left-front
	vertexData[2].SetPositionAndColor(hsx, -hsy, -hsz, r, g, b, a);  // up-right-front
	vertexData[3].SetPositionAndColor(hsx, hsy, -hsz, r, g, b, a);   // down-right-front
	dtPositionNormalColorVertex::ProcessNormal(&vertexData[0], &vertexData[1], &vertexData[2]); // normal
	dtPositionNormalColorVertex::ProcessNormal(&vertexData[1], &vertexData[3], &vertexData[2]); // normal

	//left face
	vertexData[4].SetPositionAndColor(-hsx, -hsy, -hsz, r, g, b, a); // up-left-front
	vertexData[5].SetPositionAndColor(-hsx, hsy, -hsz, r, g, b, a);  // down-left-front
	vertexData[6].SetPositionAndColor(-hsx, -hsy, hsz, r, g, b, a); // up-left-back
	vertexData[7].SetPositionAndColor(-hsx, hsy, hsz, r, g, b, a);	// down-left-back						
	dtPositionNormalColorVertex::ProcessNormal(&vertexData[4], &vertexData[5], &vertexData[6]); // normal
	dtPositionNormalColorVertex::ProcessNormal(&vertexData[5], &vertexData[7], &vertexData[6]); // normal

	// right face
	vertexData[8].SetPositionAndColor(hsx, -hsy, -hsz, r, g, b, a);  // up-right-front
	vertexData[9].SetPositionAndColor(hsx, hsy, -hsz, r, g, b, a);   // down-right-front
	vertexData[10].SetPositionAndColor(hsx, -hsy, hsz, r, g, b, a);	// up-right-back
	vertexData[11].SetPositionAndColor(hsx, hsy, hsz, r, g, b, a);	// down-right-back
	dtPositionNormalColorVertex::ProcessNormal(&vertexData[8], &vertexData[9], &vertexData[10]); // normal
	dtPositionNormalColorVertex::ProcessNormal(&vertexData[9], &vertexData[11], &vertexData[10]); // normal															// normal

	// back face
	vertexData[12].SetPositionAndColor(-hsx, -hsy, hsz, r, g, b, a); // up-left-back
	vertexData[13].SetPositionAndColor(-hsx, hsy, hsz, r, g, b, a);	// down-left-back
	vertexData[14].SetPositionAndColor(hsx, -hsy, hsz, r, g, b, a);	// up-right-back
	vertexData[15].SetPositionAndColor(hsx, hsy, hsz, r, g, b, a);	// down-right-back
	dtPositionNormalColorVertex::ProcessNormal(&vertexData[12], &vertexData[13], &vertexData[14]); // normal
	dtPositionNormalColorVertex::ProcessNormal(&vertexData[13], &vertexData[15], &vertexData[14]); // normal	

	// top face
	vertexData[16].SetPositionAndColor(-hsx, -hsy, -hsz, r, g, b, a); // up-left-front
	vertexData[17].SetPositionAndColor(hsx, -hsy, -hsz, r, g, b, a);  // up-right-front
	vertexData[18].SetPositionAndColor(-hsx, -hsy, hsz, r, g, b, a); // up-left-back
	vertexData[19].SetPositionAndColor(hsx, -hsy, hsz, r, g, b, a);	// up-right-back
	dtPositionNormalColorVertex::ProcessNormal(&vertexData[16], &vertexData[17], &vertexData[18]); // normal
	dtPositionNormalColorVertex::ProcessNormal(&vertexData[17], &vertexData[19], &vertexData[18]); // normal	

	// bottom face
	vertexData[20].SetPositionAndColor(-hsx, hsy, -hsz, r, g, b, a);  // down-left-front
	vertexData[21].SetPositionAndColor(hsx, hsy, -hsz, r, g, b, a);   // down-right-front
	vertexData[22].SetPositionAndColor(-hsx, hsy, hsz, r, g, b, a);	// down-left-back
	vertexData[23].SetPositionAndColor(hsx, hsy, hsz, r, g, b, a);	// down-right-back
	dtPositionNormalColorVertex::ProcessNormal(&vertexData[20], &vertexData[21], &vertexData[22]); // normal
	dtPositionNormalColorVertex::ProcessNormal(&vertexData[21], &vertexData[23], &vertexData[22]); // normal

	int size = ((sizeof(float) * 3) + (sizeof(float) * 3) + (sizeof(GLbyte) * 4)) * 24;

	glBindBuffer(GL_ARRAY_BUFFER, mVBO_ID);
	glBufferData(GL_ARRAY_BUFFER, size, &vertexData[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// indices
	int indicesArraySize = 6 * 6; // 6 faces with (2 triangles = 3 each triangle = 6 indices)
	unsigned int* indicesData = new unsigned int[indicesArraySize];
	// front face
	indicesData[0] = 0; indicesData[1] = 1; indicesData[2] = 2;
	indicesData[3] = 1; indicesData[4] = 3; indicesData[5] = 2;
	// left face
	indicesData[6] = 6; indicesData[7] = 7; indicesData[8] = 4;
	indicesData[9] = 7; indicesData[10] = 5; indicesData[11] = 4;
	// right face
	indicesData[12] = 8; indicesData[13] = 9; indicesData[14] = 10;
	indicesData[15] = 9; indicesData[16] = 11; indicesData[17] = 10;
	// back face
	indicesData[18] = 14; indicesData[19] = 15; indicesData[20] = 12;
	indicesData[21] = 15; indicesData[22] = 13; indicesData[23] = 12;
	// top face
	indicesData[24] = 18; indicesData[25] = 16; indicesData[26] = 19;
	indicesData[27] = 16; indicesData[28] = 17; indicesData[29] = 19;
	// bottom face
	indicesData[30] = 20; indicesData[31] = 22; indicesData[32] = 21;
	indicesData[33] = 22; indicesData[34] = 23; indicesData[35] = 21;

	int indexDataSize = sizeof(int) * indicesArraySize;

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mIBO_ID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexDataSize, &(indicesData[0]), GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	mIndicesCount = indicesArraySize;
}

void NPrimitiveCube3D::Draw(float dt) {
	mCurrentShader->Use();

	glEnable(GL_DEPTH_TEST);

	// matrix
	GLuint cameraLocation = mCurrentShader->GetUniformLocation("camera");
	GLuint modelLocation = mCurrentShader->GetUniformLocation("model");
	GLuint cameraPositionLocation = mCurrentShader->GetUniformLocation("cameraPosition");
	GLuint ambientColorLocation = mCurrentShader->GetUniformLocation("ambientColor");

	glUniform4f(ambientColorLocation, 1.0f, 1.0f, 1.0f, 1.0f);

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