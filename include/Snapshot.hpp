#pragma once

#include <vector>
#include <unordered_map>
#include <memory>
#include <string>
#include "Song.hpp"
#include "Playlist.hpp"
#include "RatingsBST.hpp"

class Snapshot {
public:
    Snapshot(const Playlist& playlistRef, const SongRatingTree& ratingTreeRef);

    std::vector<std::shared_ptr<Song>> getTopLongestSongs(int n = 5) const;
    std::vector<std::shared_ptr<Song>> getRecentlyPlayedSongs(int n = 5) const;
    std::unordered_map<int, int> getSongCountByRating() const;

    void export_snapshot() const;

private:
    const Playlist& playlist;
    const SongRatingTree& ratingTree;
};
