#include "../include/Song.hpp"

int Song::next_id = 0;
std::set<int> Song::available_ids;

Song::Song(const std::string& id, const std::string& title, const std::string& artist, int duration,
    const std::string& genre, const std::string& subgenre, const std::string& mood)
: song_id(id), title(title), artist(artist), duration(duration),
genre(genre), subgenre(subgenre), mood(mood), prev(nullptr), next(nullptr) {}


std::string Song::getID() const { return song_id; }
std::string Song::getGenre() const { return genre; }
std::string Song::getSubgenre() const { return subgenre; }
std::string Song::getMood() const { return mood; }

std::string Song::generate_id() {
    int id;
    if (!available_ids.empty()) {
        id = *available_ids.begin();
        available_ids.erase(available_ids.begin());
    } else {
        id = next_id++;
    }
    return std::to_string(id);
}

void Song::release_id(int id) {
    available_ids.insert(id);
}

std::string Song::getTitle() const { return title; }
std::string Song::getArtist() const { return artist; }
int Song::getDuration() const { return duration; }

void Song::setPrev(std::shared_ptr<Song> prevSong) { prev = prevSong; }
void Song::setNext(std::shared_ptr<Song> nextSong) { next = nextSong; }
std::shared_ptr<Song> Song::getPrev() const { return prev; }
std::shared_ptr<Song> Song::getNext() const { return next; }
