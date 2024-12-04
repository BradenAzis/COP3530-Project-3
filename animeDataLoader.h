//
// Created by Brade on 12/4/2024.
//

#ifndef COP3530_PROJECT_3_ANIMEDATALOADER_H
#define COP3530_PROJECT_3_ANIMEDATALOADER_H

#include "animeList.h"
#include <unordered_set>
#include <string>

void loadAnimeData(const std::string& filePath, animeList& animeCollection, std::unordered_set<std::string>& animeSet);


#endif //COP3530_PROJECT_3_ANIMEDATALOADER_H
