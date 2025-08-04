#ifndef PLAYLIST_HPP
#define PLAYLIST_HPP

#include <memory>
#include<vector>
#include "Song.hpp"

class Playlist {
private:
    std::shared_ptr<Song> head;
    std::shared_ptr<Song> tail;

    std::shared_ptr<Song> get_node_at_index(int index);

public:
    Playlist();
    ~Playlist();

    int size() const;
    void set_head(std::shared_ptr<Song> newHead);
    std::vector<std::shared_ptr<Song>> get_all_songs() const;

    void add_song(const std::string& title, const std::string& artist, int duration);
    std::shared_ptr<Song> get_head() const;
    void delete_song(int index);
    void move_song(int from_index, int to_index);
    void reverse_playlist();
    void print_playlist(); // helper to display contents
    void shuffle_playlist();
    std::shared_ptr<Song> get_song(int index) const;

};

#endif
