#include "../include/SongMap.hpp"

void SongMap::add_song(const std::shared_ptr<Song>& song) {
    id_map[song->getID()] = song;
    title_map[song->getTitle()] = song;
}

void SongMap::remove_song_by_id(const std::string& id) {
    auto it = id_map.find(id);
    if (it != id_map.end()) {
        const std::string& title = it->second->getTitle();
        title_map.erase(title);
        id_map.erase(it);
    }
}

void SongMap::remove_song_by_title(const std::string& title) {
    auto it = title_map.find(title);
    if (it != title_map.end()) {
        const std::string& id = it->second->getID();
        id_map.erase(id);
        title_map.erase(it);
    }
}

std::shared_ptr<Song> SongMap::get_by_id(const std::string& id) const {
    auto it = id_map.find(id);
    return (it != id_map.end()) ? it->second : nullptr;
}

std::shared_ptr<Song> SongMap::get_by_title(const std::string& title) const {
    auto it = title_map.find(title);
    return (it != title_map.end()) ? it->second : nullptr;
}

const std::unordered_map<std::string, std::shared_ptr<Song>>& SongMap::get_title_map() const {
    return title_map;
}

/*
Time and Space Complexity Summary:

- add_song():                   O(1) average
    Inserts into both maps.

- remove_song_by_id():         O(1) average
    Hash lookup and erase from both maps.

- remove_song_by_title():      O(1) average
    Hash lookup and erase from both maps.

- get_by_id():                 O(1) average
- get_by_title():              O(1) average

- get_title_map():             O(1)
    Returns reference; no copy or traversal.

Space Complexity:
- O(n), where n is the number of unique songs.
  Each song is stored twice (by ID and title), but both use pointers, so memory overhead is minimal.

Notes:
- Fast constant-time operations due to hash map usage.
- Assumption : Song IDs and Titles are unique.
*/
