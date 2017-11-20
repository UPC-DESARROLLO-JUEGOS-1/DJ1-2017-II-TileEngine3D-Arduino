#pragma once

#include <string>
#include <vector>

#include "Drawable2D.h"
#include "FontContent.h"
#include "dtPositionTextureColor.h"
#include "EnumTextAlign.h"

class NTextfield2D : public Drawable2D
{
public:
	NTextfield2D() :
		mTextQuadCounter(0), mTextPositionRenderX(0), mTextPositionRenderY(0),
		mTextInternalOffset(0), mText(""), mColor(NColor::White), 
		mTextSize(Vector2::Zero), mTrackingQuantity(0), mOldNumQuads(0),
		mIndicesCount(0), mWidth(0), mHeight(0), mIsTransformed(true),
		ibo_ID(0)
	{}
	~NTextfield2D() {
		mFontContent = nullptr;
		Drawable2D::~Drawable2D();
	}

	void SetText(std::string phrase);
	void SetColor(float r, float g, float b, float a);

	std::string GetText() { return mText; }
	FontContent* GetFontContent() { return mFontContent; }
	ImageContent* GetImageContent() { return mImageContent; }

	void Initialize(float x, float y, const std::string fontPath);

	void AlignText(EnumTextAlign align);
	void SetLetterColor(int charIndex, NColor charColor);

	void Update(float dt);
	void Draw(float dt);

protected:
	FontContent* mFontContent;
	ImageContent* mImageContent;
	NBitmapFontCharset* mFontCharset;
	std::string mText;
	NColor mColor;
	Vector2 mTextSize;
	EnumTextAlign mTextAlign;

	bool PreValidationText(std::string phrase) { return mText != phrase; }
	void AddTextQuad(NBitmapFontCharDescriptor charDesc, float kerningAmount,
		bool canJumpLine);
	void PreCalculateIndices(int numQuads);
	void TransformToRender();

private:
	bool mIsTransformed;
	bool mDrawEnable;
	int mTextQuadCounter;
	int mOldNumQuads;
	int mIndicesCount;
	float mTextPositionRenderX;
	float mTextPositionRenderY;
	float mTextInternalOffset;
	float mTrackingQuantity;
	float mTextureWidth;
	float mTextureHeight;
	float mWidth;
	float mHeight;

	GLuint ibo_ID;

	std::vector<dtPositionTextureColor> mCustomQuads;
	std::vector<unsigned short> mIndices;

	BaseShader* mShader;
};

