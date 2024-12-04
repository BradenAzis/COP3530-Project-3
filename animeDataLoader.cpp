#include "animeDataLoader.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <regex>

std::string sanitizeString(const std::string& input) { // Remove non-ASCII characters
    std::string output;
    for (char c : input) {
        if (static_cast<unsigned char>(c) <= 127) {
            output += c;
        }
    }
    return output;
}

bool isNumeric(const std::string& str) {
    return !str.empty() && std::all_of(str.begin(), str.end(), ::isdigit);
}

std::vector<std::string> parseCSVLine(const std::string& line) {
    std::vector<std::string> result;
    std::regex regex(R"((?:\"([^\"]*)\")|([^,]+))");
    std::smatch match;

    std::string::const_iterator searchStart(line.cbegin());
    while (regex_search(searchStart, line.cend(), match, regex)) {
        if (match[1].matched) {
            result.push_back(match[1].str()); // Quoted field
        } else {
            result.push_back(match[2].str()); // Unquoted field
        }
        searchStart = match.suffix().first;
    }

    return result;
}

void loadAnimeData(const std::string& filePath, animeList& animeCollection, std::unordered_set<std::string>& animeSet) {
    std::ifstream file(filePath);
    if (!file.is_open()) {
        std::cerr << "Failed to open file: " << filePath << std::endl;
        return;
    }

    std::string line;
    // Ignore header/format line
    std::getline(file, line);

    int maxViewers = 0;
    int minViewers = 0;
    while (std::getline(file, line)) {
        auto fields = parseCSVLine(line);
        if (fields.size() < 7) {
            std::cerr << "Skipping malformed line: " << line << std::endl;
            continue;
        }

        try {
            std::string name = fields[0];
            std::string genres = fields[1];
            std::string type = fields[2];
            int episodes = fields[3].empty() ? 0 : std::stoi(fields[3]);
            std::string aired = fields[4];
            int members = fields[5].empty() ? 0 : std::stoi(fields[5]);
            float score = fields[6].empty() ? 0.0f : std::stof(fields[6]);

            bool ongoing = aired.find("to Present") != std::string::npos;

            anime newAnime(name, {genres}, type, episodes, 0, members, score, ongoing);
            animeCollection.addToList(newAnime);
            animeSet.insert(name); // Log the anime name for quick lookup

//            std::cout << "Parsed Name: " << name << ", Members: " << members << std::endl; //FIXME: Remove debug output

        } catch (const std::exception& e) {
            //std::cerr << "Error processing line: " << line << " - " << e.what() << std::endl;
            continue; // Skip malformed lines
        }
    }
    file.close();
}