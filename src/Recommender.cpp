#include "../include/Recommender.hpp"
#include <algorithm>
#include "ClassificationTree.hpp"
#include <unordered_set>
#include <stack>
#include <iostream>


Recommender::Recommender(std::shared_ptr<PlaybackStack> playbackHistory,
    std::shared_ptr<Playlist> globalLibrary,
    std::shared_ptr<SongRatingTree> ratingsTree,
    std::shared_ptr<ClassificationTree> classificationTree)
: history(playbackHistory),
library(globalLibrary),
ratings(ratingsTree),
classification(classificationTree) {}

bool Recommender::is_similar(const std::shared_ptr<Song>& a, const std::shared_ptr<Song>& b) {
return (a->getGenre() == b->getGenre() ||
a->getSubgenre() == b->getSubgenre() ||
a->getMood() == b->getMood());
}

std::vector<std::shared_ptr<Song>> Recommender::recommend(int num_songs) {
std::vector<std::shared_ptr<Song>> recommendations;
std::unordered_set<std::string> played_ids;

std::stack<std::shared_ptr<Song>> temp_stack = history->get_history();
std::vector<std::shared_ptr<Song>> recent_songs;

while (!temp_stack.empty()) {
auto s = temp_stack.top(); temp_stack.pop();
recent_songs.push_back(s);
played_ids.insert(s->getID());
}

// For each recent song, try finding similar songs from classification tree
for (const auto& recent : recent_songs) {
auto similar_songs = classification->get_songs(recent->getGenre(),
    "",    // leave subgenre blank
    "");   // leave mood blank
    std::cout << "Recent: " << recent->getTitle() << " | Genre: " << recent->getGenre()
    << " | Subgenre: " << recent->getSubgenre() << " | Mood: " << recent->getMood() << "\n";
std::cout << "Similar songs fetched: " << similar_songs.size() << "\n";

for (const auto& candidate : similar_songs) {
if (played_ids.count(candidate->getID()) == 0 && is_similar(candidate, recent)) {
recommendations.push_back(candidate);
played_ids.insert(candidate->getID()); // avoid duplicates
if (recommendations.size() >= static_cast<size_t>(num_songs))
return recommendations;
}
}
}

// Fallback: Top rated songs not yet played
for (int r = 5; r >= 1 && recommendations.size() < static_cast<size_t>(num_songs); --r) {
auto rated = ratings->search_by_rating(r);
for (const auto& candidate : rated) {
if (played_ids.count(candidate->getID()) == 0) {
recommendations.push_back(candidate);
played_ids.insert(candidate->getID());
if (recommendations.size() >= static_cast<size_t>(num_songs))
break;
}
}
}

return recommendations;
}