#pragma once
#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include "../Profile/Profile.h"

class CofReader
{
public:
	CofReader();

	bool SaveConfig(Profile profile);

	std::vector<Profile> LoadConfig();
};
