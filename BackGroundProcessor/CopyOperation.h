#ifndef COPYOPERATION_H
#define COPYOPERATION_H

#include <iostream>
#include <fstream>
#include <filesystem>
#include "IOperation.h"
#include "../external/loguru/loguru.hpp"

class CopyOperation : public IOperation 
{
    public:
	    std::string doOperation(const std::string &filePath) override {
		    std::filesystem::path sourcePath(filePath);

		if (!std::filesystem::exists(sourcePath)) {
			LOG_F(ERROR, "Source file does not exist: %s", sourcePath.c_str());
			return "";
		}

		std::filesystem::path destinationPath = sourcePath.parent_path() / (sourcePath.stem().string() + "_copy" + sourcePath.extension().string());

		try {
			std::filesystem::copy_file(sourcePath, destinationPath, std::filesystem::copy_options::overwrite_existing);
			return destinationPath.string();
		} catch (const std::filesystem::filesystem_error &e) {
			LOG_F(ERROR, "Error: Source file does not exist");
			return "";
		}
	}
};

#endif // COPYOPERATION_H
