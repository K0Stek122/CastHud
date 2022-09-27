#include "CofReader.h"

CofReader::CofReader()
{

}

bool CofReader::SaveConfig(Profile profile)
{
	std::ofstream file;
	file.open("profiles.cof");
	if (!file.is_open())
		return false;
	file << profile.name << ";" << profile.scale << ";" << profile.thickness << ";" << profile.gap << ";" << profile.xOffset << ";" << profile.yOffset << std::endl;
	file.close();
}

std::vector<Profile> LoadConfig()
{
	std::string delimiter = ";";

	std::ifstream file("profiles.cof");
	std::vector<Profile> ret;
	std::vector<std::string> splitConfig;
	std::string line;

	while (std::getline(file, line))
	{
		size_t pos = 0;
		std::string token;
		while ((pos = line.find(delimiter)) != std::string::npos) {
			token = line.substr(0, pos);
			splitConfig.push_back(token);
			line.erase(0, pos + delimiter.length());
		}
	}

	return ret;
}