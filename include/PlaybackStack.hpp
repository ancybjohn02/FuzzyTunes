#ifndef PLAYBACKSTACK_HPP
#define PLAYBACKSTACK_HPP

#include <stack>
#include "Song.hpp"
#include<memory>
#include "Playlist.hpp"

class PlaybackStack {
private:
    std::stack<std::shared_ptr<Song>> history;

public:
    void push(std::shared_ptr<Song> song);
    std::shared_ptr<Song> pop();
    bool empty();
    std::shared_ptr<Song> peek() const {
        if (history.empty()) return nullptr;
        return history.top();
    }
    std::stack<std::shared_ptr<Song>> get_history() const;

};

#endif
