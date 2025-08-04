#ifndef SONG_HPP
#define SONG_HPP

#include <set>
#include <string>
#include <memory>

class Song {
private:
    std::string song_id;
    std::string title;
    std::string artist;
    int duration; // in seconds

    std::string genre;
    std::string subgenre;
    std::string mood;

    static int next_id;
    static std::set<int> available_ids;

    std::shared_ptr<Song> prev;
    std::shared_ptr<Song> next;

public:
Song(const std::string& id, const std::string& title, const std::string& artist, int duration,
    const std::string& genre = "", const std::string& subgenre = "", const std::string& mood = "");

    std::string getID() const;
    std::string getTitle() const;
    std::string getArtist() const;
    int getDuration() const;

    std::string getGenre() const;
    std::string getSubgenre() const;
    std::string getMood() const;


    static std::string generate_id();
    static void release_id(int id);

    void setPrev(std::shared_ptr<Song> prevSong);
    void setNext(std::shared_ptr<Song> nextSong);
    std::shared_ptr<Song> getPrev() const;
    std::shared_ptr<Song> getNext() const;
};

#endif
