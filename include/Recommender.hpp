#pragma once
#include <vector>
#include <memory>
#include <unordered_set>
#include "Song.hpp"
#include "PlaybackStack.hpp"
#include "Playlist.hpp"
#include "RatingsBST.hpp"
#include "ClassificationTree.hpp"

class Recommender {
public:
    Recommender(std::shared_ptr<PlaybackStack> playbackHistory,
                std::shared_ptr<Playlist> globalLibrary,
                std::shared_ptr<SongRatingTree> ratingsTree,
                std::shared_ptr<ClassificationTree> classificationTree);

    std::vector<std::shared_ptr<Song>> recommend(int num_songs = 5);

private:
    std::shared_ptr<PlaybackStack> history;
    std::shared_ptr<Playlist> library;
    std::shared_ptr<SongRatingTree> ratings;
    std::shared_ptr<ClassificationTree> classification;

    bool is_similar(const std::shared_ptr<Song>& a, const std::shared_ptr<Song>& b);
};
