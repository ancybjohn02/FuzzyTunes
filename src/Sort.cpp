#include "../include/Sort.hpp"
#include <algorithm>

namespace {

// ---------- Internal Merge Logic ----------
void merge(std::vector<std::shared_ptr<Song>>& arr, int left, int mid, int right, bool byTitle, bool ascending) {
    std::vector<std::shared_ptr<Song>> temp(right - left + 1);
    int i = left, j = mid + 1, k = 0;

    auto compare = [&](const std::shared_ptr<Song>& a, const std::shared_ptr<Song>& b) {
        if (byTitle)
            return ascending ? a->getTitle() < b->getTitle() : a->getTitle() > b->getTitle();
        else
            return ascending ? a->getDuration() < b->getDuration() : a->getDuration() > b->getDuration();
    };

    while (i <= mid && j <= right) {
        if (compare(arr[i], arr[j]))
            temp[k++] = arr[i++];
        else
            temp[k++] = arr[j++];
    }

    while (i <= mid) temp[k++] = arr[i++];
    while (j <= right) temp[k++] = arr[j++];

    for (int l = 0; l < k; ++l)
        arr[left + l] = temp[l];
}

void mergeSort(std::vector<std::shared_ptr<Song>>& arr, int left, int right, bool byTitle, bool ascending) {
    if (left >= right) return;

    int mid = left + (right - left) / 2;
    mergeSort(arr, left, mid, byTitle, ascending);
    mergeSort(arr, mid + 1, right, byTitle, ascending);
    merge(arr, left, mid, right, byTitle, ascending);
}

} // end anonymous namespace

// ---------- Core Sorting Functions ----------
void Sort::mergeSortByTitle(std::vector<std::shared_ptr<Song>>& songs, bool ascending) {
    mergeSort(songs, 0, songs.size() - 1, true, ascending);
}

void Sort::mergeSortByDuration(std::vector<std::shared_ptr<Song>>& songs, bool ascending) {
    mergeSort(songs, 0, songs.size() - 1, false, ascending);
}

void Sort::sortByRecentlyAdded(std::vector<std::shared_ptr<Song>>& songs) {
    std::reverse(songs.begin(), songs.end());
}

// ---------- Conversion Helper ----------
std::vector<std::shared_ptr<Song>> Sort::dllToVector(std::shared_ptr<Song> head) {
    std::vector<std::shared_ptr<Song>> songs;
    std::shared_ptr<Song> curr = head;
    while (curr) {
        songs.push_back(curr);
        curr = curr->getNext();
    }
    return songs;
}

// ---------- DLL-based Sorting Wrappers (return only vector) ----------
std::vector<std::shared_ptr<Song>> Sort::sortDllByTitle(std::shared_ptr<Song> head, bool ascending) {
    auto songs = dllToVector(head);
    mergeSortByTitle(songs, ascending);
    return songs;
}

std::vector<std::shared_ptr<Song>> Sort::sortDllByDuration(std::shared_ptr<Song> head, bool ascending) {
    auto songs = dllToVector(head);
    mergeSortByDuration(songs, ascending);
    return songs;
}

std::vector<std::shared_ptr<Song>> Sort::sortDllByRecentlyAdded(std::shared_ptr<Song> head) {
    auto songs = dllToVector(head);
    sortByRecentlyAdded(songs);
    return songs;
}

std::shared_ptr<Song> Sort::vectorToDll(const std::vector<std::shared_ptr<Song>>& songs) {
    if (songs.empty()) return nullptr;

    for (size_t i = 0; i < songs.size(); ++i) {
        songs[i]->setPrev(nullptr);
        songs[i]->setNext(nullptr);
    }

    for (size_t i = 0; i < songs.size() - 1; ++i) {
        songs[i]->setNext(songs[i + 1]);
        songs[i + 1]->setPrev(songs[i]);
    }

    return songs[0];  // head of new DLL
}
