#include "../include/PlaybackStack.hpp"

void PlaybackStack::push(std::shared_ptr<Song> song) {
    history.push(song);
}

std::shared_ptr<Song> PlaybackStack::pop() {
    if (history.empty()) return nullptr;

    std::shared_ptr<Song> lastSong = history.top();
    history.pop();
    return lastSong;
}

bool PlaybackStack::empty() {
    return history.empty();
}

std::stack<std::shared_ptr<Song>> PlaybackStack::get_history() const {
    return history;
}

/*
General Time and Space Complexity:

- push():             O(1)
- pop():              O(1)
- top() (peek):       O(1)
- empty():            O(1)
- get_history():      O(n) time and O(n) space (returns a copy of the stack)

Note:
- Memory management is handled via shared pointers to avoid ownership issues.
*/
