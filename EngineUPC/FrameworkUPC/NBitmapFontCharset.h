#pragma once

#include <string>
#include <vector>
#include "NBitmapFontCharDescriptor.h"
#include "NBitmapFontPage.h"
#include "NBitmapFontKerning.h"

struct NBitmapFontCharset {
	static const int CHAR_DESCRIPTOR_SIZE = 256;

	// info
	std::string fontName;
	float size;
	bool bold;
	bool italic;
	std::string charset;
	bool unicode;
	int stretchH;
	bool smooth;
	bool aa;
	std::vector<int> padding;
	std::vector<int> spacing;
	bool outline;

	// common
	int lineHeight;
	int Base;
	int scaleWidth;
	int scaleHeight;
	int pages;
	bool packed;
	int alphaChnl;
	int redChnl;
	int greenChnl;
	int blueChnl;

	// pages
	std::vector<NBitmapFontPage> fontPages;

	// kerning
	std::vector<NBitmapFontKerning> kernings;

	NBitmapFontCharDescriptor getCharDescriptor(int charUnicode) {
		return fontPages[0].chars[charUnicode];
	}

	bool existsChar(int charUnicode) {
		if ((charUnicode - 1) < fontPages[0].charArraySize) {
			return true;
		}

		return false;
	}

	float getKerning(int unicodeFirst, int unicodeSecond) {
		float amountResult = 0;
		int kerningCount = kernings.size();

		if (kerningCount == 0) {
			return amountResult;
		}

		for (int i = 0; i < kerningCount; i++) {
			NBitmapFontKerning _kerning = kernings[i];

			if (_kerning.first == unicodeFirst && _kerning.second == unicodeSecond) {
				amountResult = _kerning.amount;
				break;
			}
		}

		return amountResult;
	}
};