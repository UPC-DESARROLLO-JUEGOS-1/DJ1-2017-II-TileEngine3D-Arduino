#pragma once

#include <string>
#include <sstream>
#include <vector>
#include <array>
#include <iterator>
#include <algorithm>

class NCommon {
private:
	template<typename Out>
	void static Interal_SplitString(const std::string &s, char delim, Out result) {
		std::stringstream ss;
		ss.str(s);
		std::string item;
		while (std::getline(ss, item, delim)) {
			*(result++) = item;
		}
	}

public:
	static const char SPLITTER_COMMA = ',';

	int static UTF8ToUnicode(char value) {
		return static_cast<int>(value);
	}

	std::string static UnicodeToUTF8(unsigned int codepoint)
	{
		std::string out;

		if (codepoint <= 0x7f)
			out.append(1, static_cast<char>(codepoint));
		else if (codepoint <= 0x7ff)
		{
			out.append(1, static_cast<char>(0xc0 | ((codepoint >> 6) & 0x1f)));
			out.append(1, static_cast<char>(0x80 | (codepoint & 0x3f)));
		}
		else if (codepoint <= 0xffff)
		{
			out.append(1, static_cast<char>(0xe0 | ((codepoint >> 12) & 0x0f)));
			out.append(1, static_cast<char>(0x80 | ((codepoint >> 6) & 0x3f)));
			out.append(1, static_cast<char>(0x80 | (codepoint & 0x3f)));
		}
		else
		{
			out.append(1, static_cast<char>(0xf0 | ((codepoint >> 18) & 0x07)));
			out.append(1, static_cast<char>(0x80 | ((codepoint >> 12) & 0x3f)));
			out.append(1, static_cast<char>(0x80 | ((codepoint >> 6) & 0x3f)));
			out.append(1, static_cast<char>(0x80 | (codepoint & 0x3f)));
		}
		return out;
	}

	std::string static ReplaceString(std::string subject, const std::string& search,
		const std::string& replace) {
		
		size_t pos = 0;

		while ((pos = subject.find(search, pos)) != std::string::npos) {
			subject.replace(pos, search.length(), replace);
			pos += replace.length();
		}

		return subject;
	}

	std::vector<std::string> static SplitString(const std::string &s, char delim) {
		std::vector<std::string> elems;
		NCommon::Interal_SplitString(s, delim, std::back_inserter(elems));
		return elems;
	}

	/*template<typename C1, typename C2>
	void static CastVectorContainer(const std::vector<C1>& source, std::vector<C2>& destination) {
		destination.resize(source.size());
		
		std::transform(source.begin(), source.end(), destination.begin(), 
			[](C1 c) { return reinterpret_cast<C2>(c); });
	}*/

	template<size_t N>
	std::string static EraseCharsInString(std::string baseString, std::array<char, N> asciiChars) {
		for (int i = 0; i < N; i++) {
			std::string stringData;
			stringData.push_back(asciiChars[i]);
			baseString = NCommon::ReplaceString(baseString, stringData, "");
		}

		return baseString;
	}
};

