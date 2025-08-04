// Sort.hpp
#pragma once
#include <vector>
#include <memory>
#include "Song.hpp"

class Sort {
public:
    static void mergeSortByTitle(std::vector<std::shared_ptr<Song>>& songs, bool ascending);
    static void mergeSortByDuration(std::vector<std::shared_ptr<Song>>& songs, bool ascending);
    static void sortByRecentlyAdded(std::vector<std::shared_ptr<Song>>& songs);

    static std::vector<std::shared_ptr<Song>> dllToVector(std::shared_ptr<Song> head);
    static std::shared_ptr<Song> vectorToDll(const std::vector<std::shared_ptr<Song>>& songs);


    // NEW: return sorted vector directly instead of converting back to DLL
    static std::vector<std::shared_ptr<Song>> sortDllByTitle(std::shared_ptr<Song> head, bool ascending);
    static std::vector<std::shared_ptr<Song>> sortDllByDuration(std::shared_ptr<Song> head, bool ascending);
    static std::vector<std::shared_ptr<Song>> sortDllByRecentlyAdded(std::shared_ptr<Song> head);
};
