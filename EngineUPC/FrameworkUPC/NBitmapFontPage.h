#pragma once

#include <string>
#include <vector>
#include "NBitmapFontCharDescriptor.h"

struct NBitmapFontPage {
	int id;
	int charCount;
	int charArraySize;
	std::string path;
	bool isInitialized;
	std::vector<NBitmapFontCharDescriptor> chars;
};