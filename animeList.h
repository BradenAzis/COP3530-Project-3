//
// Created by alexk on 12/2/2024.
//

#ifndef COP3530_PROJECT_3_ANIMELIST_H
#define COP3530_PROJECT_3_ANIMELIST_H
#include "anime.h"
#include "string"
#include "vector"
#include "set"
#include "algorithm"
#include "cmath"

using namespace std;


class animeList {
private:
    vector<anime> list;
public:
    //constructor
    animeList();
    //list management
    void addToList(anime anime);
    void copy(animeList animeList);
    vector<anime>& getList();
    void setSimilarity(anime selected);
    //merge sort
    void merge(vector<anime> &vec, int left, int mid, int right);
    void mergeSort(vector<anime> &vec, int left, int right);
    //quick sort
    int partition(vector<anime> &vec, int low, int high);
    void quickSort(vector<anime> &vec, int low, int high);
    bool compareLists(animeList list2){
        for (int i = 0; i < list.size(); ++i) {
            if(list[i].getName() != list2.list[i].getName()){
                return false;
            }
        }
        return true;
    }
};


#endif //COP3530_PROJECT_3_ANIMELIST_H
