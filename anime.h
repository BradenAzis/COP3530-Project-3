//
// Created by alexk on 12/2/2024.
//
#ifndef COP3530_PROJECT_3_ANIME_H
#define COP3530_PROJECT_3_ANIME_H
#include "string"
#include "vector"
#include "set"
#include "algorithm"
#include "cmath"

using namespace std;

class anime {

private:
    string name;
    set<string> genres;
    string type;
    int length; //number of episodes
    int startYear; //year it aired
    int viewers;
    int maxViewers; //initialized to 0
    int minViewers; //initialized to 0
    float rating;
    bool ongoing; //still airing?
    float similarity; //initialized to 0


public:
    //constructor
    anime(string name, set<string> genres, string type, int length, int startYear, int viewers, float rating, bool ongoing);
    //getters
    string getName();
    set<string> getGenres();
    string getType();
    int getLength();
    int getStartYear();
    int getViewers();
    float getRating();
    bool getOngoing();
    float getSimilarity();
    void setSimilarity(float sim);
    int getMinViewers();
    int getMaxViewers();
    //setter and incrementer for viewers
    void setViewers(int viewers);
    void incrementViewers(); //increases viewers by 1
    void setMaxViewers(int viewers);
    void setMinViewers(int viewers);
    //similarity calculation
    void calculateSimilarity(anime selected);


    set<string> intersection(set<string> s1, set<string> s2);
    float jacard_index(set<string> s1, set<string> s2);



};


#endif //COP3530_PROJECT_3_ANIME_H
