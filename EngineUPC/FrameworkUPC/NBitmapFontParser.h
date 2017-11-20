#pragma once

#include "FatalError.h"
#include "EnumNBitmapFontRawType.h"
#include "EnumNCharacterASCII.h"
#include "EnumNCharacterUnicode.h"
#include "NBitmapFontCharset.h"
#include "NBitmapFontCharDescriptor.h"
#include "NBitmapFontPage.h"
#include "NBitmapFontKerning.h"
#include "NCommon.h"

#include <string>
#include <array>
#include <fstream>
#include <iostream>

class NBitmapFontParser {
private:
	static bool finish;
	static int mNBitmapFontPageIndexTemp;
	static int mNBitmapFontCharIndexTemp;
	static int mNBitmapFontKerningIndexTemp;
	static NBitmapFontCharset* mFontCharset;
	static NBitmapFontPage mNBitmapFontPageTemp;
	
	static std::array<char, 4> ASCIIFilter;
public:

	static NBitmapFontCharset* Load(std::string path) {
		ASCIIFilter[0] = EnumNCharacterUnicode::NOTHING;
		ASCIIFilter[1] = EnumNCharacterUnicode::BACKSLASH;
		ASCIIFilter[2] = EnumNCharacterUnicode::QUOTATION_MARK;
		ASCIIFilter[3] = EnumNCharacterUnicode::WHITE_SPACE;

		// inicializamos
		NBitmapFontParser::finish = false;
		NBitmapFontParser::mNBitmapFontPageIndexTemp = 0;
		NBitmapFontParser::mNBitmapFontCharIndexTemp = 0;
		NBitmapFontParser::mNBitmapFontKerningIndexTemp = 0;
		NBitmapFontParser::mFontCharset = new NBitmapFontCharset();

		std::ifstream fontFile(path);

		// Revisamos si abrir el archivo...
		if (fontFile.fail()) {
			FatalError("NBitmapFontParser::Load> No se pudo abrir el archivo: " + path); 
		}

		std::string readedLine;
		std::string tmpString = "";

		while (std::getline(fontFile, readedLine)) {
			bool findedQuotation = false;
			bool firstRead = true;
			bool finishInternal = false;
			int lineLength = readedLine.size();
			int linePosition = 0;
			EnumNBitmapFontRawType lineType = EnumNBitmapFontRawType::NONE;

			while (!finishInternal) {
				if (linePosition >= lineLength) {
					finishInternal = true;

					if (tmpString.size() > 0) {
						NBitmapFontParser::readingAndSettingValues(lineType, &tmpString);
						tmpString = "";
					}
					break;
				}
				else {
					char letter = readedLine[linePosition];
					bool iss = NBitmapFontParser::IsSeparator(letter);
					bool isQuotation = letter == EnumNCharacterASCII::QUOTATION_MARK;

					if (isQuotation) {
						if (!findedQuotation) { findedQuotation = true; }
						else { findedQuotation = false; }
					}

					iss = findedQuotation ? false : iss;

					if (iss) {
						if (tmpString.size() > 0) {
							if (firstRead) {
								firstRead = false;
								lineType = NBitmapFontParser::getLineType(tmpString);
							}
							else { NBitmapFontParser::readingAndSettingValues(lineType, &tmpString); }

							tmpString = "";
						}
					}
					else { tmpString += letter; }

					linePosition++;
				}
			}
			
		}

		// FINISH THE READ OF FILE
		NBitmapFontParser::finish = true;
		NBitmapFontParser::mNBitmapFontPageIndexTemp = 0;
		NBitmapFontParser::mNBitmapFontCharIndexTemp = 0;
		NBitmapFontParser::mNBitmapFontKerningIndexTemp = 0;

		return NBitmapFontParser::mFontCharset;
	}

	static EnumNBitmapFontRawType getLineType(std::string valueType) {
		EnumNBitmapFontRawType lineType = EnumNBitmapFontRawType::NONE;

		if (valueType == "info") 			lineType = EnumNBitmapFontRawType::INFO; 	
		else if (valueType == "common")  	lineType = EnumNBitmapFontRawType::COMMON; 	
		else if (valueType == "page")  		lineType = EnumNBitmapFontRawType::PAGE; 	
		else if (valueType == "chars")  	lineType = EnumNBitmapFontRawType::CHARS; 	
		else if (valueType == "char")  		lineType = EnumNBitmapFontRawType::CHAR; 	
		else if (valueType == "kerning")	lineType = EnumNBitmapFontRawType::KERNING; 
		else if (valueType == "kernings")	lineType = EnumNBitmapFontRawType::KERNINGS;

		return lineType;
	}

	static bool IsSeparator(char value) {
		//#ifdef _WIN32 return result '\\' == value;
		//#else return '/' == value; 
		//#endif

		//return false;
		return value == ' ';
	} 

	static void readingAndSettingValues(EnumNBitmapFontRawType lineType, std::string* tmpString) {
		std::string propertyType = "";
		std::string propertyValue = "";

		int charPos = tmpString->find(EnumNCharacterUnicode::EQUALS_SIGN);
		propertyType = tmpString->substr(0, charPos);
		propertyValue = tmpString->substr(charPos + 1);
		propertyValue = NCommon::ReplaceString(propertyValue, &EnumNCharacterUnicode::QUOTATION_MARK,
			&EnumNCharacterUnicode::NOTHING);
		propertyValue = NCommon::ReplaceString(propertyValue, &EnumNCharacterUnicode::BACKSLASH,
			&EnumNCharacterUnicode::NOTHING);

		// TEMP VARIABLES
		NBitmapFontCharDescriptor charDescTemp;

		if (lineType == EnumNBitmapFontRawType::INFO) {
			if (propertyType == "face")  			NBitmapFontParser::mFontCharset->fontName = NCommon::EraseCharsInString<4>(propertyValue, NBitmapFontParser::ASCIIFilter);
			else if (propertyType == "size") 		NBitmapFontParser::mFontCharset->size = std::stoi(propertyValue);
			else if (propertyType == "bold") 		NBitmapFontParser::mFontCharset->bold = propertyValue == "0" ? false : true;
			else if (propertyType == "italic") 		NBitmapFontParser::mFontCharset->italic = propertyValue == "0" ? false : true;
			else if (propertyType == "charset") 	NBitmapFontParser::mFontCharset->charset = NCommon::EraseCharsInString<4>(propertyValue, NBitmapFontParser::ASCIIFilter);
			else if (propertyType == "unicode") 	NBitmapFontParser::mFontCharset->unicode = propertyValue == "0" ? false : true;
			else if (propertyType == "stretchH") 	NBitmapFontParser::mFontCharset->stretchH = std::stoi(propertyValue);
			else if (propertyType == "smooth") 		NBitmapFontParser::mFontCharset->smooth = propertyValue == "0" ? false : true;
			else if (propertyType == "aa") 			NBitmapFontParser::mFontCharset->aa = propertyValue == "0" ? false : true;
			else if (propertyType == "padding") {
				std::vector<std::string> propPaddings = NCommon::SplitString(propertyValue, NCommon::SPLITTER_COMMA);

				NBitmapFontParser::mFontCharset->padding.push_back(std::stoi(propPaddings[0])); 
				NBitmapFontParser::mFontCharset->padding.push_back(std::stoi(propPaddings[1]));
				NBitmapFontParser::mFontCharset->padding.push_back(std::stoi(propPaddings[2])); 
				NBitmapFontParser::mFontCharset->padding.push_back(std::stoi(propPaddings[3]));
			}
			else if (propertyType == "spacing") {
				// only temporal implementation, needs to find an equivalent for: char.ConvertFromUtf32

				NBitmapFontParser::mFontCharset->spacing.push_back(0);
				NBitmapFontParser::mFontCharset->spacing.push_back(0);
				//NBitmapFontParser::mFontCharset->spacing.push_back(std::stoi(char.ConvertFromUtf32(propertyValue[0])));
				//NBitmapFontParser::mFontCharset->spacing.push_back(std::stoi(char.ConvertFromUtf32(propertyValue[2])));
			}
			else if (propertyType == "outline") NBitmapFontParser::mFontCharset->outline = propertyValue == "0" ? false : true;
		}
		else if (lineType == EnumNBitmapFontRawType::COMMON) {
			if (propertyType == "lineHeight")	NBitmapFontParser::mFontCharset->lineHeight = std::stoi(propertyValue);  
			else if (propertyType == "base") 	NBitmapFontParser::mFontCharset->Base = std::stoi(propertyValue);
			else if (propertyType == "scaleW") 	NBitmapFontParser::mFontCharset->scaleWidth = std::stoi(propertyValue);
			else if (propertyType == "scaleH") 	NBitmapFontParser::mFontCharset->scaleHeight = std::stoi(propertyValue);
			else if (propertyType == "pages") {
				mFontCharset->pages = std::stoi(propertyValue);
				mFontCharset->fontPages.reserve(NBitmapFontParser::mFontCharset->pages);

				// Initialize pages
				for (int i = 0; i < mFontCharset->pages; i++)
				{
					NBitmapFontPage page;
					mFontCharset->fontPages.push_back(page);
				}
			}
			else if (propertyType == "packed") 		NBitmapFontParser::mFontCharset->packed = propertyValue == "0" ? false : true;
			else if (propertyType == "alphaChnl") 	NBitmapFontParser::mFontCharset->alphaChnl = std::stoi(propertyValue); 			
			else if (propertyType == "redChnl") 	NBitmapFontParser::mFontCharset->redChnl = std::stoi(propertyValue); 			
			else if (propertyType == "greenChnl") 	NBitmapFontParser::mFontCharset->greenChnl = std::stoi(propertyValue); 			
			else if (propertyType == "blueChnl") 	NBitmapFontParser::mFontCharset->blueChnl = std::stoi(propertyValue); 			
		}
		else if (lineType == EnumNBitmapFontRawType::PAGE) {
			NBitmapFontPage NBFPage;

			for (int i = 0; i < mFontCharset->fontPages.size(); i++) {
				NBFPage = mFontCharset->fontPages[i];

				//if (!NBFPage.isInitialized) {
					if (propertyType == "id") {
						NBFPage.id = std::stoi(propertyValue); 
					}
					else if (propertyType == "file") {
						NBFPage.path = NCommon::EraseCharsInString<4>(propertyValue, NBitmapFontParser::ASCIIFilter);
						NBFPage.isInitialized = true;

						// THIS ARE TEMPORAL VARIABLES FOR THE PAGES
						NBitmapFontParser::mNBitmapFontCharIndexTemp = 0;
						NBitmapFontParser::mNBitmapFontPageIndexTemp = i;
						NBitmapFontParser::mNBitmapFontPageTemp = NBFPage;
					}

					mFontCharset->fontPages[i] = NBFPage;
				//}
			}
		}
		else if (lineType == EnumNBitmapFontRawType::CHARS) {
			if (propertyType == "count") {
				mNBitmapFontCharIndexTemp = -1;
				mNBitmapFontPageTemp.charCount = std::stoi(propertyValue);
				
				mNBitmapFontPageTemp.charArraySize = NBitmapFontCharset::CHAR_DESCRIPTOR_SIZE;

				for (int i = 0; i < mNBitmapFontPageTemp.charArraySize; i++)
				{
					NBitmapFontCharDescriptor charDesc;
					mNBitmapFontPageTemp.chars.push_back(charDesc);
				}

				mFontCharset->fontPages[mNBitmapFontPageIndexTemp] = mNBitmapFontPageTemp;
			}
		}
		else if (lineType == EnumNBitmapFontRawType::CHAR) {
			bool skip = false;

			if (mNBitmapFontCharIndexTemp != -1) {
				if (mNBitmapFontCharIndexTemp < NBitmapFontCharset::CHAR_DESCRIPTOR_SIZE) {
					charDescTemp = mNBitmapFontPageTemp.chars[mNBitmapFontCharIndexTemp];
				}
				else { skip = true; }
			}

			if (!skip) {
				if (propertyType == "id") {
					charDescTemp.id = std::stoi(propertyValue);
					mNBitmapFontCharIndexTemp = charDescTemp.id;
				}
				else if (propertyType == "x") {
					charDescTemp.x = std::stoi(propertyValue);
				}
				else if (propertyType == "y") {
					charDescTemp.y = std::stoi(propertyValue);
				}
				else if (propertyType == "width") {
					charDescTemp.width = std::stoi(propertyValue);
					charDescTemp.textureU = charDescTemp.width;
				}
				else if (propertyType == "height") {
					charDescTemp.height = std::stoi(propertyValue);
					charDescTemp.textureV = charDescTemp.height;
				}
				else if (propertyType == "xoffset") {
					charDescTemp.xOffset = std::stoi(propertyValue);
				}
				else if (propertyType == "yoffset") {
					charDescTemp.yOffset = std::stoi(propertyValue);
				}
				else if (propertyType == "xadvance") {
					charDescTemp.xAdvance = std::stoi(propertyValue);
				}
				else if (propertyType == "page") {
					charDescTemp.page = std::stoi(propertyValue);
				}
				else if (propertyType == "chnl") {
					charDescTemp.chnl = std::stoi(propertyValue);
				}

				if (mNBitmapFontCharIndexTemp < NBitmapFontCharset::CHAR_DESCRIPTOR_SIZE) {
					mNBitmapFontPageTemp.chars[mNBitmapFontCharIndexTemp] = charDescTemp;

					mFontCharset->fontPages[mNBitmapFontPageIndexTemp] = mNBitmapFontPageTemp;
				}
				else {
					std::cout << "NBitmapFontParser::readingAndSettingValues> In the Font: '" <<
						mFontCharset->fontName << "' the char index: " + mNBitmapFontCharIndexTemp <<
						" is out of the range of the default size of the char description: " <<
						NBitmapFontCharset::CHAR_DESCRIPTOR_SIZE;
				}
			}
		}
		else if (lineType == EnumNBitmapFontRawType::KERNINGS) {
			mNBitmapFontKerningIndexTemp = 0;

			int kerningCount = std::stoi(propertyValue);

			for (int i = 0; i < kerningCount; i++)
			{
				NBitmapFontKerning kerning;
				mFontCharset->kernings.push_back(kerning);
			}
		}
		else if (lineType == EnumNBitmapFontRawType::KERNING) {
			bool incrementKerningReader = false;
			NBitmapFontKerning kerningTemp = mFontCharset->kernings[mNBitmapFontKerningIndexTemp];

			if (propertyType == "first")		kerningTemp.first = std::stoi(propertyValue);
			else if (propertyType == "second") 	kerningTemp.second = std::stoi(propertyValue);
			else if (propertyType == "amount") {
				incrementKerningReader = true;
				kerningTemp.amount = std::stoi(propertyValue);
			}

			mFontCharset->kernings[mNBitmapFontKerningIndexTemp] = kerningTemp;

			if (incrementKerningReader) {
				// GO TO NEXT KERNING NODE
				mNBitmapFontKerningIndexTemp++;
			}
		}
	}

};
