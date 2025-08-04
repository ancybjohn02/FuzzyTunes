#include "ClassificationTree.hpp"
#include <iostream>

ClassificationTree::ClassificationTree() {
    root = std::make_shared<ClassificationNode>("ROOT");
}

void ClassificationTree::add_song(const std::shared_ptr<Song>& song,
    const std::string& genre,
    const std::string& subgenre,
    const std::string& mood,
    const std::string& artist) {
auto genre_node = root->add_child(genre);
auto subgenre_node = genre_node->add_child(subgenre);
auto mood_node = subgenre_node->add_child(mood);
auto artist_node = mood_node->add_child(artist);
artist_node->songs.push_back(song); // Add song to leaf node
}


std::vector<std::string> ClassificationTree::get_all_genres() const {
    std::vector<std::string> result;
    for (auto& child : root->getChildren()) {
        result.push_back(child->name);
    }
    return result;
}

std::vector<std::string> ClassificationTree::get_all_subgenres(const std::string& genre) const {
    std::vector<std::string> result;
    auto genre_node = root->find_child(genre);
    if (!genre_node) return result;

    for (auto& sub : genre_node->getChildren()) {
        result.push_back(sub->name);
    }
    return result;
}

std::vector<std::string> ClassificationTree::get_all_moods(const std::string& genre, const std::string& subgenre) const {
    std::vector<std::string> result;
    auto genre_node = root->find_child(genre);
    if (!genre_node) return result;

    auto subgenre_node = genre_node->find_child(subgenre);
    if (!subgenre_node) return result;

    for (auto& mood : subgenre_node->getChildren()) {
        result.push_back(mood->name);
    }
    return result;
}

std::vector<std::shared_ptr<Song>> ClassificationTree::get_songs(
    const std::string& genre,
    const std::string& subgenre,
    const std::string& mood) const {

    std::vector<std::shared_ptr<Song>> allSongs;

    auto genre_node = root->find_child(genre);
    if (!genre_node) return allSongs;

    // If subgenre is empty, return all songs under this genre
    if (subgenre.empty()) {
        for (const auto& sub : genre_node->getChildren()) {
            for (const auto& mood_node : sub->getChildren()) {
                for (const auto& artist_node : mood_node->getChildren()) {
                    const auto& songs = artist_node->getSongs();
                    allSongs.insert(allSongs.end(), songs.begin(), songs.end());
                }
            }
        }
        return allSongs;
    }

    auto subgenre_node = genre_node->find_child(subgenre);
    if (!subgenre_node) return allSongs;

    // If mood is empty, return all songs under this subgenre
    if (mood.empty()) {
        for (const auto& mood_node : subgenre_node->getChildren()) {
            for (const auto& artist_node : mood_node->getChildren()) {
                const auto& songs = artist_node->getSongs();
                allSongs.insert(allSongs.end(), songs.begin(), songs.end());
            }
        }
        return allSongs;
    }

    auto mood_node = subgenre_node->find_child(mood);
    if (!mood_node) return allSongs;

    // Return songs at the mood level
    for (const auto& artist_node : mood_node->getChildren()) {
        const auto& songs = artist_node->getSongs();
        allSongs.insert(allSongs.end(), songs.begin(), songs.end());
    }

    return allSongs;
}


void ClassificationTree::explore_classification() const {
    auto genres = get_all_genres();
    if (genres.empty()) {
        std::cout << "No genres found.\n";
        return;
    }

    std::cout << "\nGenres:\n";
    for (size_t i = 0; i < genres.size(); ++i) {
        std::cout << i + 1 << ". " << genres[i] << "\n";
    }

    int genreChoice;
    std::cout << "Select a genre: ";
    std::cin >> genreChoice;
    std::cin.ignore();

    if (genreChoice < 1 || genreChoice > (int)genres.size()) {
        std::cout << "Invalid genre selection.\n";
        return;
    }

    std::string selectedGenre = genres[genreChoice - 1];
    auto subgenres = get_all_subgenres(selectedGenre);
    if (subgenres.empty()) {
        std::cout << "No subgenres found under " << selectedGenre << ".\n";
        return;
    }

    std::cout << "\nSubgenres in " << selectedGenre << ":\n";
    for (size_t i = 0; i < subgenres.size(); ++i) {
        std::cout << i + 1 << ". " << subgenres[i] << "\n";
    }

    int subChoice;
    std::cout << "Select a subgenre: ";
    std::cin >> subChoice;
    std::cin.ignore();

    if (subChoice < 1 || subChoice > (int)subgenres.size()) {
        std::cout << "Invalid subgenre selection.\n";
        return;
    }

    std::string selectedSubgenre = subgenres[subChoice - 1];
    auto moods = get_all_moods(selectedGenre, selectedSubgenre);
    if (moods.empty()) {
        std::cout << "No moods found under " << selectedSubgenre << ".\n";
        return;
    }

    std::cout << "\nMoods in " << selectedSubgenre << ":\n";
    for (size_t i = 0; i < moods.size(); ++i) {
        std::cout << i + 1 << ". " << moods[i] << "\n";
    }

    int moodChoice;
    std::cout << "Select a mood: ";
    std::cin >> moodChoice;
    std::cin.ignore();

    if (moodChoice < 1 || moodChoice > (int)moods.size()) {
        std::cout << "Invalid mood selection.\n";
        return;
    }

    std::string selectedMood = moods[moodChoice - 1];
    auto songs = get_songs(selectedGenre, selectedSubgenre, selectedMood);

    if (songs.empty()) {
        std::cout << "No songs found for this selection.\n";
        return;
    }

    std::cout << "\nSongs under " << selectedGenre << " > " << selectedSubgenre
              << " > " << selectedMood << ":\n";

    for (size_t i = 0; i < songs.size(); ++i) {
        std::cout << i + 1 << ". " << songs[i]->getTitle()
                  << " by " << songs[i]->getArtist()
                  << " (" << songs[i]->getDuration() << "s)\n";
    }
}

/*
Data Structure Used: Multi-level N-ary Tree (4-level hierarchy: Genre > Subgenre > Mood > Artist)

General Time and Space Complexity:

- add_song():              O(1) avg, O(d) worst (d = depth of tree, fixed here at 4)
- get_songs():             O(k), where k = number of matching songs under the specified path
- get_all_genres():        O(g), g = number of genres
- get_all_subgenres():     O(s), s = number of subgenres under given genre
- get_all_moods():         O(m), m = moods under subgenre
- explore_classification(): O(k) in worst case (based on number of songs shown at end)

Space Complexity:
- O(n), where n = total number of songs added
  (Each node holds pointers and possibly a vector of songs; overhead per node is small)

Notes:
- All add/search operations are shallow (max depth = 4), so traversal is lightweight in practice.
*/
