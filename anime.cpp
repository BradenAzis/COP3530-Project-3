//
// Created by alexk on 12/2/2024.
//

#include "anime.h"
#include <iostream>

anime::anime(std::string name, set<std::string> genres, std::string type, int length, int startYear, int viewers, float rating, bool ongoing) {
    this->name = name;
    this->genres = genres;
    this->type = type;
    this->length = length;
    this->startYear = startYear;
    this->viewers = viewers;
    maxViewers = 200000;
    minViewers = 40000;
    this->rating = rating;
    this->ongoing = ongoing;
    similarity = 0;
}

string anime::getName() {
    return name;
}
set<string> anime::getGenres() {
    return genres;
}
string anime::getType() {
    return type;
}
int anime::getLength() {
    return length;
}
int anime::getStartYear() {
    return startYear;
}
int anime::getViewers() {
    return viewers;
}
float anime::getRating() {
    return rating;
}
bool anime::getOngoing() {
    return ongoing;
}
float anime::getSimilarity() {
    return similarity;
}
int anime::getMaxViewers() {
    return maxViewers;
}
int anime::getMinViewers() {
    return minViewers;
}
void anime::setViewers(int viewers) {
    this->viewers = viewers;
}
void anime::incrementViewers() {
    viewers++;
}
void anime::setMaxViewers(int viewers) {
    maxViewers = viewers;
}
void anime::setMinViewers(int viewers) {
    minViewers = viewers;
}
set<string> anime::intersection(set<std::string> s1, set<std::string> s2) {
    set<string> intersect;
    set_intersection(s1.begin(), s1.end(), s2.begin(), s2.end(),
                     inserter(intersect, intersect.begin()));
    return intersect;
}
float anime::jacard_index(set<std::string> s1, set<std::string> s2) {
    // Sizes of both the sets
    float size_s1 = s1.size();
    float size_s2 = s2.size();

    // Get the intersection set
    set<string> intersect = intersection(s1, s2);

    // Size of the intersection set
    float size_in = intersect.size();

    // Calculate the Jaccard index
    // using the formula
    float jaccard_in = size_in/ (size_s1 + size_s2 - size_in);

    // Return the Jaccard index
    return jaccard_in;
}
void anime::calculateSimilarity(anime selected) {
    //standard deviations
    float sigmaLength = 10; //moderate tolerance for differences in episode count. Consider 15-20 for more broad range
    float sigmaYear = 5;
    float sigmaViewers = 1000; //unsure what to set this at TODO: set this once we have viewer numbers
    float sigmaRating = 3; //TODO ask chatGPT about this value
    //similarity score metrics
    float genreSim = jacard_index(genres, selected.getGenres());
    float typeSim = (type == selected.getType()) ? 1.0 : 0.0;
    float lengthSim = exp(-(pow(length - selected.getLength(), 2) / (2 * sigmaLength * sigmaLength)));
    float yearSim = exp(-(pow(startYear - selected.startYear, 2) / (2 * sigmaYear * sigmaYear)));
    float viewerSim = exp(-(pow(viewers - selected.getViewers(), 2) / (2 * sigmaViewers * sigmaViewers)));
    float ratingSim = exp(-(pow(rating - selected.getRating(), 2) / (2 * sigmaRating * sigmaRating)));
    float ongoingSim = (ongoing == selected.getOngoing()) ? 1.0 : 0.0;
    float viewerScore = (viewers - minViewers) / (maxViewers - minViewers);
    float ratingScore = rating / 10.0;
    //total similarity score with weights
    float weightedSim =
            0.3*genreSim +
            0.1*typeSim +
            0.2*lengthSim +
            0.1*yearSim +
            0.05*ongoingSim +
            0.1*viewerSim +
            0.1*ratingSim;
    //adjust for popularity
    float popularityFactor = (viewerScore + ratingScore) / 2;
    similarity = weightedSim * popularityFactor;
}