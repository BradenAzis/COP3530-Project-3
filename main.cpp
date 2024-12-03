#include <iostream>
#include "anime.h"
#include "animeList.h"
#include "anime.h"
#include "string"
#include "vector"
#include "set"
#include "algorithm"
#include "cmath"
#include "chrono"

using namespace std;
using namespace std::chrono;
int main() {
    anime cowboyBebop = anime("Cowboy Bebop", {"Action", "Award Winning", "Sci-Fi"}, "TV", 26, 1998, 100000, 8.75, false);
    anime trigun = anime("Trigun", {"Action", "Adventure", "Sci-Fi"}, "TV", 26, 1998, 80000, 8.22, false);
    anime schoolRumble = anime("School Rumble", {"Comedy", "Romance"}, "TV", 26, 2004, 70000, 7.89, false);
    anime EVA = anime("Neon Genesis Evangelion", {"Action", "Avant Garde","Award Winning", "Drama", "Sci-Fi", "Suspense"}, "TV", 26, 1995, 200000, 8.35, false);
    anime finalApproach = anime("Final Approach", {"Comedy", "Romance" "Drama"}, "TV", 13, 2004, 40000, 6.62, false);
    animeList myAnimeList_Quick;
    myAnimeList_Quick.addToList(cowboyBebop);
    myAnimeList_Quick.addToList(trigun);
    myAnimeList_Quick.addToList(schoolRumble);
    myAnimeList_Quick.addToList(EVA);
    myAnimeList_Quick.addToList(finalApproach);
    myAnimeList_Quick.setSimilarity(cowboyBebop);
    animeList myAnimeList_Merge;
    myAnimeList_Merge.copy(myAnimeList_Quick);
    auto start = high_resolution_clock::now();
    myAnimeList_Quick.quickSort(myAnimeList_Quick.getList(), 0, 4);
    auto stop = high_resolution_clock::now();
    auto duration_quick = duration_cast<nanoseconds>(stop - start);
    start = high_resolution_clock::now();
    myAnimeList_Merge.mergeSort(myAnimeList_Merge.getList(), 0, 4);
    stop = high_resolution_clock::now();
    auto duration_merge = duration_cast<nanoseconds>(stop - start);
    cout<<"List:"<<endl;
    for(anime a : myAnimeList_Quick.getList()){
        cout<<a.getName()<<" "<<a.getSimilarity()<<endl;
    }
    cout << "Merge sort result same: " << myAnimeList_Merge.compareLists(myAnimeList_Quick);
    cout << "Quick Sort time: " << duration_quick.count() << endl;
    cout << "Merge Sort time: " << duration_merge.count() << endl;
}

