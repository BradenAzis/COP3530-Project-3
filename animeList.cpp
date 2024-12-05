//
// Created by alexk on 12/2/2024.
//

#include "animeList.h"

animeList::animeList() {
    list = {};
}
void animeList::addToList(anime anime) {
    list.push_back(anime);
}
vector<anime>& animeList::getList() {
    return list;
}
void animeList::copy(animeList animeList){
    list = {};
    for(anime a : animeList.list){
        list.push_back(a);
    }
}
void animeList::setSimilarity(anime selected) {
    for(anime &a : list) {
        if (a.getName() != selected.getName()) {
            a.calculateSimilarity(selected);
        }
        else{
            a.setSimilarity(0);
        }
    }
}
//merge and mergeSort algorithms modeled after code found at geeksforgeeks.org
void animeList::merge(vector<anime> &vec, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    // Create temp vectors
    vector<anime> L, R;

    // Copy data to temp vectors L[] and R[]
    for (int i = 0; i < n1; i++)
        L.push_back(vec[left + i]);
    for (int j = 0; j < n2; j++)
        R.push_back(vec[mid + 1 + j]);

    int i = 0, j = 0;
    int k = left;

    // Merge the temp vectors back
    // into arr[left..right]
    while (i < n1 && j < n2) {
        if (L[i].getSimilarity() >= R[j].getSimilarity()) {
            vec[k] = L[i];
            i++;
        }
        else {
            vec[k] = R[j];
            j++;
        }
        k++;
    }

    // Copy the remaining elements of L[],
    // if there are any
    while (i < n1) {
        vec[k] = L[i];
        i++;
        k++;
    }

    // Copy the remaining elements of R[],
    // if there are any
    while (j < n2) {
        vec[k] = R[j];
        j++;
        k++;
    }
}
void animeList::mergeSort(vector<anime> &vec, int left, int right) {
    if (left >= right)
        return;

    int mid = left + (right - left) / 2;
    mergeSort(vec, left, mid);
    mergeSort(vec, mid + 1, right);
    merge(vec, left, mid, right);
}

//partion and quickSort algorithms modeled after code found at geeksforgeeks.org
int animeList::partition(vector<anime> &vec, int low, int high) {
    // Random pivot selection
    int pivotIndex = low + rand() % (high - low + 1); // Random index between low and high
    swap(vec[pivotIndex], vec[high]); // Move random pivot to the end
    float pivot = vec[high].getSimilarity();

    int i = (low - 1);

    for (int j = low; j <= high - 1; j++) {
        if (vec[j].getSimilarity() >= pivot) {
            i++;
            swap(vec[i], vec[j]);
        }
    }

    swap(vec[i + 1], vec[high]);
    return (i + 1);
}
void animeList::quickSort(vector<anime> &vec, int low, int high) {
    // Base case: This part will be executed till the starting
    // index low is lesser than the ending index high
    if (low < high) {

        // pi is Partitioning Index, arr[p] is now at
        // right place
        int pi = partition(vec, low, high);

        // Separately sort elements before and after the
        // Partition Index pi
        quickSort(vec, low, pi - 1);
        quickSort(vec, pi + 1, high);
    }
}
