#ifndef COPYOPERATION_H
#define COPYOPERATION_H

#include <iostream>
#include <fstream>
#include <filesystem>
#include "IOperation.h"

class CopyOperation : public IOperation 
{
    public:
	    std::string doOperation(const std::string &filePath) override {
		    std::filesystem::path sourcePath(filePath);

		if (!std::filesystem::exists(sourcePath)) {
			std::cerr << "Error: Source file does not exist - " << filePath << std::endl;
			return "";
		}

		std::filesystem::path destinationPath = sourcePath.parent_path() / (sourcePath.stem().string() + "_copy" + sourcePath.extension().string());

		try {
			std::filesystem::copy_file(sourcePath, destinationPath, std::filesystem::copy_options::overwrite_existing);
			return destinationPath.string();
		} catch (const std::filesystem::filesystem_error &e) {
			std::cerr << "File copy error: " << e.what() << std::endl;
			return "";
		}
	}
};

#endif // COPYOPERATION_H
