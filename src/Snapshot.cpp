#include <algorithm>
#include "Snapshot.hpp"
#include <iostream>

Snapshot::Snapshot(const Playlist& playlistRef, const SongRatingTree& ratingTreeRef)
    : playlist(playlistRef), ratingTree(ratingTreeRef) {}

std::vector<std::shared_ptr<Song>> Snapshot::getTopLongestSongs(int n) const {
    std::vector<std::shared_ptr<Song>> allSongs = playlist.get_all_songs();
    
    std::sort(allSongs.begin(), allSongs.end(), [](const auto& a, const auto& b) {
        return a->getDuration() > b->getDuration();
    });

    if (allSongs.size() > n)
        allSongs.resize(n);

    return allSongs;
}

std::vector<std::shared_ptr<Song>> Snapshot::getRecentlyPlayedSongs(int n) const {
    std::vector<std::shared_ptr<Song>> allSongs = playlist.get_all_songs();

    std::reverse(allSongs.begin(), allSongs.end());  // tail to head
    if (allSongs.size() > n)
        allSongs.resize(n);

    return allSongs;
}

std::unordered_map<int, int> Snapshot::getSongCountByRating() const {
    std::unordered_map<int, int> ratingCount;

    // const_cast to call non-const method on const reference
    SongRatingTree& mutableRatingTree = const_cast<SongRatingTree&>(ratingTree);

    for (int r = 1; r <= 5; ++r) {
        auto vec = mutableRatingTree.search_by_rating(r);
        ratingCount[r] = static_cast<int>(vec.size());
    }

    return ratingCount;
}


void Snapshot::export_snapshot() const {
    std::cout << "=== LIVE SNAPSHOT DASHBOARD ===\n";

    std::cout << "\nTop 5 Longest Songs:\n";
    auto longest = getTopLongestSongs();
    for (const auto& s : longest) {
        std::cout << s->getTitle() << " - " << s->getDuration() << "s\n";
    }

    std::cout << "\nMost Recently Played Songs:\n";
    auto recent = getRecentlyPlayedSongs();
    for (const auto& s : recent) {
        std::cout << s->getTitle() << " by " << s->getArtist() << "\n";
    }

    std::cout << "\nSong Count by Rating:\n";
    auto countMap = getSongCountByRating();
    for (const auto& [rating, count] : countMap) {
        std::cout << rating << " star: " << count << " songs\n";
    }

    std::cout << "===============================\n";
}

