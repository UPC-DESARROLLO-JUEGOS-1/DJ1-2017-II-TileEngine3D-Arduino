#include "NBitmapFontParser.h"

bool NBitmapFontParser::finish = false;
int NBitmapFontParser::mNBitmapFontPageIndexTemp = 0;
int NBitmapFontParser::mNBitmapFontCharIndexTemp = 0;
int NBitmapFontParser::mNBitmapFontKerningIndexTemp = 0;
NBitmapFontCharset* NBitmapFontParser::mFontCharset = nullptr;
NBitmapFontPage NBitmapFontParser::mNBitmapFontPageTemp;

std::array<char, 4> NBitmapFontParser::ASCIIFilter = {
	EnumNCharacterUnicode::NOTHING,
	EnumNCharacterUnicode::BACKSLASH,
	EnumNCharacterUnicode::QUOTATION_MARK,
	EnumNCharacterUnicode::WHITE_SPACE
};
