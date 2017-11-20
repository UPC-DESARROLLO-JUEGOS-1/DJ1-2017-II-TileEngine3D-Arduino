#include "NTextfield2D.h"
#include "GameFramework.h"
#include "EnumNCharacterASCII.h"
#include "NCommon.h"
#include "FontShader.h"

void NTextfield2D::SetColor(float r, float g, float b, float a)
{
	mColor.r = r;
	mColor.g = g;
	mColor.b = b;
	mColor.a = a;
}

void NTextfield2D::SetText(std::string phrase) {
	if (PreValidationText(phrase)) {
		mText = phrase;

		mTextQuadCounter = 0;
		mTextPositionRenderX = 0;
		mTextPositionRenderY = 0;

		mTextSize = Vector2::Zero;
		mTextSize.y = mFontCharset->Base;

		int currentCharCount = phrase.size();
		bool needsClearArray = currentCharCount > mCustomQuads.size();
		int offsetSizePlus = 8;

		// clear the vector
		if (needsClearArray) { mCustomQuads.clear(); }

		int oldUnicodeChar = -1;
		int phraseLength = mText.size();
		int oldIndexAfterJumpLine = 0;
		int oldWidthAfterJumpLine = 0;
		bool jumpLineFound = false;
		std::string commandInsideString = "";
		NBitmapFontCharDescriptor charDescriptor;

		for (int i = 0; i < phraseLength; i++) {
			float kerningAmount = 0;
			int unicodeCharFirst = NCommon::UTF8ToUnicode(mText[i]);

			if (unicodeCharFirst == EnumNCharacterASCII::JUMPLINE) {
				jumpLineFound = true;

				std::string newText = mText.substr(oldIndexAfterJumpLine, (i - oldIndexAfterJumpLine));
				oldIndexAfterJumpLine = i + 1;
				int newTextLength = (int)mFontContent->MeasureString(newText).x;

				if (newTextLength > oldWidthAfterJumpLine) {
					oldWidthAfterJumpLine = newTextLength;
					mTextSize.x = oldWidthAfterJumpLine;
				}

				mTextSize.y += mFontCharset->Base;
			}
			else {
				// RETRIEVE KERNING
				if (oldUnicodeChar != -1) {
					kerningAmount = mFontContent->GetKerning(oldUnicodeChar, unicodeCharFirst);
				}

				if (mFontContent->ExistChar(unicodeCharFirst)) {
					// RETRIEVE CHAR DESCRIPTOR
					charDescriptor = mFontContent->GetCharDescriptor(unicodeCharFirst);

					// ADD CHAR QUAD TO RENDER
					AddTextQuad(charDescriptor, kerningAmount, jumpLineFound);

					// STORING OLD VARIABLES
					oldUnicodeChar = unicodeCharFirst;

					jumpLineFound = false;
				}
			}
		}

		// IF NO JUMP LINE IS MADE, SET TEXT SIZE BY DEFAULT
		if (mTextSize.x == 0) {
			Vector2 sizeText = mFontContent->MeasureString(mText);
			sizeText.x += mText.size() * mTrackingQuantity;

			mTextSize.x = sizeText.x;
			mWidth = (int)sizeText.x;
		}
		else { mWidth = (int)mTextSize.x; }

		if (mTextSize.y == 0) {
			mTextSize.y = mFontCharset->Base;
			mHeight = mFontCharset->Base;
		}
		else { mHeight = (int)mTextSize.y; }

		AlignText(mTextAlign);

		// TRANSFORM QUAD DATA TO RENDER ENABLE DATA
		TransformToRender();

		Update(0.01666);

		// now do the scale thing
		//if (mScaleWasModified) { this.scale = mScale; }
	}
}

void NTextfield2D::Initialize(float x, float y, const std::string fontPath)
{
	Drawable2D::Initialize(x, y);

	GameFramework* framework = GameFramework::GET_FRAMEWORK();
	ContentManager* contentManager = framework->GetContentManager();

	mFontContent = contentManager->LoadAndGetContent<FontContent>(fontPath);
	mFontCharset = mFontContent->GetCharset();

	if (mImageContent == nullptr) {
		mImageContent = mFontContent->GetImageContent(0);
		mTextureWidth = mImageContent->GetWidth();
		mTextureHeight = mImageContent->GetHeight();
	}

	const std::string shaderPath = "Shaders/FontShader";

	ShaderManager* shdMng = framework->GetShaderManager();
	mShader = (BaseShader*)shdMng->LoadAndGetShader<FontShader>(shaderPath);

	if (ibo_ID == 0) {
		glGenBuffers(1, &ibo_ID);
	}
}

void NTextfield2D::AddTextQuad(NBitmapFontCharDescriptor charDesc, float kerningAmount,
	bool canJumpLine) {
	
	float tileX = charDesc.x;
	float tileY = charDesc.y;
	float tileWidth = charDesc.textureU;
	float tileHeight = charDesc.textureV;

	if (canJumpLine) {
		mTextPositionRenderX = 0;
		mTextPositionRenderY += mFontCharset->Base;
	}

	float px = (mTextPositionRenderX + charDesc.xOffset + kerningAmount) + (mTrackingQuantity * mTextQuadCounter);
	float py = (mTextPositionRenderY + charDesc.yOffset);

	mTextPositionRenderX += (charDesc.xAdvance + kerningAmount);

	dtPositionTextureColor VPTTopRight;
	dtPositionTextureColor VPTTopLeft;
	dtPositionTextureColor VPTBottomRight;
	dtPositionTextureColor VPTBottomLeft;

	VPTTopRight.SetVertex(px + charDesc.width, py);
	VPTTopLeft.SetVertex(px, py);
	VPTBottomRight.SetVertex(px + charDesc.width, py + charDesc.height);
	VPTBottomLeft.SetVertex(px, py + charDesc.height);

	VPTTopRight.SetUV((tileX + tileWidth) / mTextureWidth, tileY / mTextureHeight);
	VPTTopLeft.SetUV(tileX / mTextureWidth, tileY / mTextureHeight);
	VPTBottomRight.SetUV((tileX + tileWidth) / mTextureWidth, (tileY + tileHeight) / mTextureHeight);
	VPTBottomLeft.SetUV(tileX / mTextureWidth, (tileY + tileHeight) / mTextureHeight);

	VPTTopRight.SetColor(NColor::White);
	VPTTopLeft.SetColor(NColor::White);
	VPTBottomRight.SetColor(NColor::White);
	VPTBottomLeft.SetColor(NColor::White);

	// adding to buffer
	mCustomQuads.push_back(VPTTopRight);
	mCustomQuads.push_back(VPTTopLeft);
	mCustomQuads.push_back(VPTBottomRight);
	mCustomQuads.push_back(VPTBottomLeft);

	mTextQuadCounter++;
}

void NTextfield2D::PreCalculateIndices(int numQuads) {
	if (mOldNumQuads != numQuads) {
		unsigned short indicesCount = 0;
		int indexCounterArray = 0;
		int offsetSizePlus = 0;
		int currentIndicesCount = numQuads * 6;
		bool needsClearArray = currentIndicesCount > mIndices.size();

		if (needsClearArray) { mIndices.clear(); }

		for (int i = 0; i < numQuads; ++i) {
			mIndices.push_back((indicesCount + 2));
			mIndices.push_back((indicesCount + 3));
			mIndices.push_back((indicesCount + 1));
			mIndices.push_back((indicesCount + 2));
			mIndices.push_back((indicesCount + 1));
			mIndices.push_back(indicesCount);
			
			indicesCount += 4;
			indexCounterArray += 6;
		}

		mOldNumQuads = numQuads;
		mIndicesCount = numQuads * 6;
	}
}

void NTextfield2D::SetLetterColor(int charIndex, NColor charColor) {
	int vectorIndex = charIndex * 4;

	mCustomQuads[vectorIndex + 0].SetColor(charColor);
	mCustomQuads[vectorIndex + 1].SetColor(charColor);
	mCustomQuads[vectorIndex + 2].SetColor(charColor);
	mCustomQuads[vectorIndex + 3].SetColor(charColor);

	mIsTransformed = true;
}

void NTextfield2D::AlignText(EnumTextAlign align) {
	mTextAlign = align;
	Vector2 textSizeTemp = (mTextSize * GetScale()) * -1;

	switch (align) {
	case EnumTextAlign::LEFT:
		mTextInternalOffset = 0;
		break;
	case EnumTextAlign::RIGHT:
		mTextInternalOffset = (int)textSizeTemp.x;
		break;
	case EnumTextAlign::CENTER:
		mTextInternalOffset = (int)(textSizeTemp.x / 2.0);
		break;
	}

	mIsTransformed = true;
}

void NTextfield2D::TransformToRender() {
	PreCalculateIndices(mTextQuadCounter);

	mDrawEnable = mTextQuadCounter > 0;

	// For: Vertices
	int size = (sizeof(float) * 8) * mCustomQuads.size();

	glBindBuffer(GL_ARRAY_BUFFER, vbo_ID);
	glBufferData(GL_ARRAY_BUFFER, size, &mCustomQuads[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// For: Indices
	int indexDataSize = sizeof(short) * mIndices.size();

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo_ID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexDataSize, &(mIndices[0]), GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	mIndicesCount = mIndices.size();
}

void NTextfield2D::Update(float dt)
{
	if (mIsTransformed) {
		TransformToRender();
	}

	if (needMatrixUpdate || mIsTransformed)
	{
		glm::mat4 result(1.0f);
		glm::vec3 translate(position.x + mTextInternalOffset, position.y, 0.0f);
		glm::vec3 scale(scale.x, scale.y, 0.0f);
		glm::vec3 rotation(0.0f, 0.0f, 1.0f);

		result = glm::translate(result, translate);
		result = glm::scale(result, scale);
		result = glm::rotate(result, rotationZ, rotation);

		worldMatrix = result;
		needMatrixUpdate = false;
		mIsTransformed = false;
	}
}

void NTextfield2D::Draw(float dt)
{
	if (mDrawEnable && mIndicesCount > 0) {
		mShader->Use();

		GLuint mvpLocation = mShader->GetUniformLocation("wvp");
		
		glm::mat4 cameraMatrix = mRenderCamera->GetResultMatrix();
		glm::mat4 resultMatrix = cameraMatrix * worldMatrix;

		glUniformMatrix4fv(mvpLocation, 1, GL_FALSE, &(resultMatrix[0][0]));

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC0_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		glBindBuffer(GL_ARRAY_BUFFER, vbo_ID);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, mImageContent->GetTextureId());

		// Position
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(dtPositionTextureColor),
			(void*)offsetof(dtPositionTextureColor, dtPositionTextureColor::Vertex));
		// UV
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(dtPositionTextureColor),
			(void*)offsetof(dtPositionTextureColor, dtPositionTextureColor::UV));
		// Color
		glVertexAttribPointer(2, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(dtPositionTextureColor),
			(void*)offsetof(dtPositionTextureColor, dtPositionTextureColor::Color));

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo_ID);

		// Esto dibuja en Frame Buffer
		glDrawElements(GL_TRIANGLES, mIndicesCount, GL_UNSIGNED_SHORT, (void*)0);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		glDisableVertexAttribArray(0);
		glBindTexture(GL_TEXTURE_2D, 0);

		mShader->Stop();
	}
}