#pragma once

#include "Vector2.h"
#include "BaseContent.h"
#include "ContentManager.h"
#include "NBitmapFontCharset.h"

class FontContent : public BaseContent
{
public:
	FontContent(ContentManager* contentManager);
	~FontContent();

	NBitmapFontCharset* GetCharset() { return mCharset; }

	void Initialize();
	bool Load(const std::string path);

	Vector2 MeasureString(std::string text);
	float MeasureStringLineal(std::string text);
	float GetKerning(int unicodeFirst, int unicodeSecond);
	bool ExistChar(int charUnicode);
	NBitmapFontCharDescriptor GetCharDescriptor(int charUnicode);
	ImageContent* GetImageContent(int page);
private:
	NBitmapFontCharset* mCharset;
	std::vector<ImageContent*> mImageContents;
};

