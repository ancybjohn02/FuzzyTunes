#ifndef SONG_MAP_HPP
#define SONG_MAP_HPP

#include <unordered_map>
#include <string>
#include <memory>
#include "Song.hpp"

class SongMap {
private:
    std::unordered_map<std::string, std::shared_ptr<Song>> id_map;
    std::unordered_map<std::string, std::shared_ptr<Song>> title_map;

public:
    void add_song(const std::shared_ptr<Song>& song);
    void remove_song_by_id(const std::string& id);
    void remove_song_by_title(const std::string& title);

    std::shared_ptr<Song> get_by_id(const std::string& id) const;
    std::shared_ptr<Song> get_by_title(const std::string& title) const;
    const std::unordered_map<std::string, std::shared_ptr<Song>>& get_title_map() const;

};

#endif
