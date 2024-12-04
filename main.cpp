#include <iostream>
#include "anime.h"
#include "anime.cpp"
#include "animeList.cpp"
#include "animeList.h"
#include "string"
#include "chrono"
#include "unordered_map"
using namespace std;
using namespace std::chrono;
int main() {
    //setup for testing
    anime cowboyBebop = anime("Cowboy Bebop", {"Action", "Award Winning", "Sci-Fi"}, "TV", 26, 1998, 100000, 8.75, false);
    anime trigun = anime("Trigun", {"Action", "Adventure", "Sci-Fi"}, "TV", 26, 1998, 80000, 8.22, false);
    anime schoolRumble = anime("School Rumble", {"Comedy", "Romance"}, "TV", 26, 2004, 70000, 7.89, false);
    anime EVA = anime("Neon Genesis Evangelion", {"Action", "Avant Garde","Award Winning", "Drama", "Sci-Fi", "Suspense"}, "TV", 26, 1995, 200000, 8.35, false);
    anime finalApproach = anime("Final Approach", {"Comedy", "Romance" "Drama"}, "TV", 13, 2004, 40000, 6.62, false);
    animeList myAnimeList;
    myAnimeList.addToList(cowboyBebop);
    myAnimeList.addToList(trigun);
    myAnimeList.addToList(schoolRumble);
    myAnimeList.addToList(EVA);
    myAnimeList.addToList(finalApproach);
    unordered_map<string, int> animeMap;
    animeMap["Cowboy Bebop"] = 100000;
    animeMap["Trigun"] = 80000;
    animeMap["School Rumble"] = 70000;
    animeMap["Neon Genesis Evangelion"] = 200000;
    animeMap["Final Approach"] = 40000;

    cout <<
            "                                                               \n"
            " __ __                _____     _              __    _     _   \n"
            "|  |  |___ _ _ ___   |  _  |___|_|_____ ___   |  |  |_|___| |_ \n"
            "|_   _| . | | |  _|  |     |   | |     | -_|  |  |__| |   | '_|\n"
            "  |_| |___|___|_|    |__|__|_|_|_|_|_|_|___|  |_____|_|_|_|_,_|\n"
            "                                                               " << endl;
    cout<<"Welcome! \n"
          "The purpose of this application is to recommend you new anime to watch given one you already like. \n"
          "Please enter the name of an anime:";
    string inputAnime;
    getline(cin, inputAnime);
    while(animeMap.find(inputAnime) == animeMap.end()){
        cout << "Sorry, we could not find that anime in our database. \n"
                "Please enter another name:";
        getline(cin, inputAnime);
    }
    for(anime a : myAnimeList.getList()){
        if (a.getName() == inputAnime){
            myAnimeList.setSimilarity(a);
            break;
        }
    }
    animeList myAnimeList_Quick;
    animeList myAnimeList_Merge;
    myAnimeList_Quick.copy(myAnimeList);
    myAnimeList_Merge.copy(myAnimeList);
    auto start = high_resolution_clock::now();
    int size = myAnimeList_Quick.getList().size();
    myAnimeList_Quick.quickSort(myAnimeList_Quick.getList(), 0, size-1);
    auto stop = high_resolution_clock::now();
    auto duration_quick = duration_cast<nanoseconds>(stop - start);
    start = high_resolution_clock::now();
    myAnimeList_Merge.mergeSort(myAnimeList_Merge.getList(), 0, size-1);
    stop = high_resolution_clock::now();
    auto duration_merge = duration_cast<nanoseconds>(stop - start);
    string sameResult = myAnimeList_Merge.compareLists(myAnimeList_Quick) ? "Yes" : "No";
    cout << "Merge and Quick sort results same: " << sameResult << endl;
    cout<<"List:"<<endl;
    for(anime a : myAnimeList_Quick.getList()){
        cout<<a.getName()<<" "<<a.getSimilarity()<<endl;
    }
    cout << "Quick Sort time: " << duration_quick.count() << endl;
    cout << "Merge Sort time: " << duration_merge.count() << endl;
}

