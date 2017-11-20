#pragma once

#include <string>
#include <vector>
#include <FrameworkUPC\pugixml.hpp>
#include <FrameworkUPC\FatalError.h>
#include <FrameworkUPC\NCommon.h>

#include "TB3D_WorldConfig.h"

class TB3D_Configuration 
{
public:
	static TB3D_Configuration* GetInstance();

	TB3D_WorldConfig* GetWorld(std::string identifier) {
		TB3D_WorldConfig* result = nullptr;

		for (int i = 0, length = mWorlds.size(); i < length; i++) {
			if (mWorlds[i]->Identifier() == identifier) {
				result = mWorlds[i];
				break;
			}
		}

		return result;
	}

	/*TB3D_Configuration(TB3D_Configuration const&) = delete;
	void operator=(TB3D_Configuration const&) = delete;*/
private:
	static TB3D_Configuration* M_INSTANCE;

	std::vector<TB3D_WorldConfig*> mWorlds;

	std::vector<int> CastVecToIntPtr(std::vector<std::string> source) {
		int vecSize = source.size();
		std::vector<int> result;
		result.resize(vecSize);

		for (int i = 0; i < vecSize; i++) { 
			result[i] = std::stoi(source[i]); 
		}

		return result;
	}

	TB3D_Configuration() : 
		mWorlds() {
		
		const char* xmlPath = "Xml/TB3D_WorldConfig.xml";
		
		pugi::xml_document xDoc;
		pugi::xml_parse_result xmlResult = xDoc.load_file(xmlPath);

		if (xmlResult.status == pugi::status_ok) {
			pugi::xml_node xData = xDoc.child("data");
			pugi::xml_node xLevel = xData.child("level");

			while (xLevel != nullptr) {
				std::string xAttr_id = std::string(xLevel.attribute("id").as_string());
				float xAttr_tileSize = xLevel.attribute("tileSize").as_float();
				std::vector<std::vector<int>> xAttr_worldCollisions;

				pugi::xml_node xLevelRow = xLevel.child("row");

				while (xLevelRow != nullptr) {
					std::string xAttr_LevelRowData = std::string(xLevelRow.attribute("data").as_string());
					std::vector<std::string> splittedLevelRow = NCommon::SplitString(xAttr_LevelRowData, ',');
					std::vector<int> outputLevelRow = TB3D_Configuration::CastVecToIntPtr(splittedLevelRow);

					// push it
					xAttr_worldCollisions.push_back(outputLevelRow);

					// Next node
					xLevelRow = xLevelRow.next_sibling();
				}

				// initiliaze world
				TB3D_WorldConfig* worldConfig = new TB3D_WorldConfig();
				worldConfig->SetValues(xAttr_id, xAttr_tileSize, xAttr_worldCollisions);

				// push it
				mWorlds.push_back(worldConfig);

				// Next node
				xLevel = xLevel.next_sibling();
			}
		}
		else {
			std::string errorMessage = "TB3D_Configuration::Load Error: " + 
				std::string(xmlResult.description());

			FatalError(errorMessage);
		}
	}

	TB3D_Configuration(TB3D_Configuration const&);  // Not implemented
	void operator=(TB3D_Configuration const&); // Not implemented
};