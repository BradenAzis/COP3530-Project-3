#include <iostream>
#include "anime.h"
#include "animeList.h"
#include "string"
#include "chrono"
#include "unordered_map"
#include "unordered_set"
#include "animeDataLoader.h"
using namespace std;
using namespace std::chrono;
int main() {
    //setup for testing
//    anime cowboyBebop = anime("Cowboy Bebop", {"Action", "Award Winning", "Sci-Fi"}, "TV", 26, 1998, 100000, 8.75, false);
//    anime trigun = anime("Trigun", {"Action", "Adventure", "Sci-Fi"}, "TV", 26, 1998, 80000, 8.22, false);
//    anime schoolRumble = anime("School Rumble", {"Comedy", "Romance"}, "TV", 26, 2004, 70000, 7.89, false);
//    anime EVA = anime("Neon Genesis Evangelion", {"Action", "Avant Garde","Award Winning", "Drama", "Sci-Fi", "Suspense"}, "TV", 26, 1995, 200000, 8.35, false);
//    anime finalApproach = anime("Final Approach", {"Comedy", "Romance" "Drama"}, "TV", 13, 2004, 40000, 6.62, false);
//    animeList myAnimeList;
//    myAnimeList.addToList(cowboyBebop);
//    myAnimeList.addToList(trigun);
//    myAnimeList.addToList(schoolRumble);
//    myAnimeList.addToList(EVA);
//    myAnimeList.addToList(finalApproach);
//    animeMap["Cowboy Bebop"] = 100000;
//    animeMap["Trigun"] = 80000;
//    animeMap["School Rumble"] = 70000;
//    animeMap["Neon Genesis Evangelion"] = 200000;
//    animeMap["Final Approach"] = 40000;

    //TODO: Implement the following
    // Adjust weights
    // Verify quick sort and merge sort are at the most efficient implementations
    cout<<"Starting up...";
    animeList myAnimeList;
    unordered_set<string> animeSet;
    // Path to the dataset
    std::string datasetPath = "formatted-anime-dataset.csv";

    // Load the dataset
    loadAnimeData(datasetPath, myAnimeList, animeSet);

//    // Print all anime names in the list
//    for (anime a : myAnimeList.getList()) {
//        std::cout << "Anime: " << a.getName() << ", Viewers: " << a.getViewers() << std::endl;
//    }
//
//    cout << myAnimeList.getList().size() << endl; // Currently has 13585/24906 anime
    cout <<
            "                                                               \n"
            " __ __                _____     _              __    _     _   \n"
            "|  |  |___ _ _ ___   |  _  |___|_|_____ ___   |  |  |_|___| |_ \n"
            "|_   _| . | | |  _|  |     |   | |     | -_|  |  |__| |   | '_|\n"
            "  |_| |___|___|_|    |__|__|_|_|_|_|_|_|___|  |_____|_|_|_|_,_|\n"
            "                                                               " << endl;
    cout<<"Welcome! \n"
          "The purpose of this application is to recommend you new anime to watch given one you already like." << endl;

    bool quit = false;
    while (!quit){
        cout<<"Please enter the name of an anime (note that title may be in romanji):";
        string inputAnime;
        getline(cin, inputAnime);
        while(animeSet.find(inputAnime) == animeSet.end()){ // O(1) lookup
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
        int numResults = 10;
        int moreResults = 0;
        animeList myAnimeList_Quick;
        animeList myAnimeList_Merge;
        myAnimeList_Quick.copy(myAnimeList);
        myAnimeList_Merge.copy(myAnimeList);
        auto start = high_resolution_clock::now();
        int size = myAnimeList_Quick.getList().size();
        myAnimeList_Quick.quickSort(myAnimeList_Quick.getList(), 0, size-1);
        auto stop = high_resolution_clock::now();
        auto duration_quick = duration_cast<nanoseconds>(stop - start);
        auto start1 = high_resolution_clock::now();
        myAnimeList_Merge.mergeSort(myAnimeList_Merge.getList(), 0, size-1);
        auto stop1 = high_resolution_clock::now();
        auto duration_merge = duration_cast<nanoseconds>(stop1 - start1);
        cout << endl;
        string sameResult = myAnimeList_Merge.compareLists(myAnimeList_Quick) ? "Yes" : "No";
        cout << "Merge and Quick sort results same: " << sameResult << endl;
        // Convert nanoseconds to seconds
        auto quick_sort_time_seconds = std::chrono::duration_cast<std::chrono::duration<double>>(duration_quick);
        auto merge_sort_time_seconds = std::chrono::duration_cast<std::chrono::duration<double>>(duration_merge);
        std::cout << "Quick Sort time: " << quick_sort_time_seconds.count() << " seconds" << std::endl; //FIXME: Quick Sort much longer? (19s compared to 0.44s)
        std::cout << "Merge Sort time: " << merge_sort_time_seconds.count() << " seconds" << std::endl;
        cout << endl;
        cout<<"Recommendations:"<<endl;
        for(int i = 0; i<numResults; i++){
            cout<< i+1 << ". " << myAnimeList_Quick.getList()[i].getName()<<" "<<myAnimeList_Quick.getList()[i].getSimilarity()<<endl;
        }
        while(true){
            cout << endl <<
                 "To load more recommendations, type: more\n"
                 "To input a new anime, type: new\n"
                 "To quit the program, type: quit\n";
            string input;
            getline(cin, input);
            while(input != "more" && input != "new" && input != "quit"){ // O(1) lookup
                cout << "Invalid input \n"
                        "Please enter a valid option:";
                getline(cin, input);
            }
            if (input == "more"){
                for(int i = numResults+moreResults; i<numResults+moreResults+10; i++){
                    cout<< i+1 << ". " << myAnimeList_Quick.getList()[i].getName()<<" "<<myAnimeList_Quick.getList()[i].getSimilarity()<<endl;
                }
                moreResults+=10;
            }
            else if(input == "new"){
                break;
            }
            else if(input == "quit"){
                cout<<"Thank you for using Your Anime Link!";
                quit = true;
                break;
            }
        }
    }
    return 0;
}

