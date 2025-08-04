#pragma once
#include <string>
#include <vector>
#include <memory>
#include "ClassificationNode.hpp"
#include "Song.hpp"

class ClassificationTree {
private:
    std::shared_ptr<ClassificationNode> root;

public:
    ClassificationTree();

    void add_song(const std::shared_ptr<Song>& song,
        const std::string& genre,
        const std::string& subgenre,
        const std::string& mood,
        const std::string& artist);


    std::vector<std::string> get_all_genres() const;
    std::vector<std::string> get_all_subgenres(const std::string& genre) const;
    std::vector<std::string> get_all_moods(const std::string& genre, const std::string& subgenre) const;
    std::vector<std::shared_ptr<Song>> get_songs(const std::string& genre,
                                                 const std::string& subgenre,
                                                 const std::string& mood) const;
    void explore_classification() const;

};
