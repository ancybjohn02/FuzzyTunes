#pragma once
#include <string>
#include <vector>
#include <memory>
#include "Song.hpp"

class ClassificationNode {
public:
    std::string name;
    std::vector<std::shared_ptr<ClassificationNode>> children; // Store children here
    std::vector<std::shared_ptr<Song>> songs; // Only for leaf nodes

    ClassificationNode(const std::string& name);

    std::shared_ptr<ClassificationNode> add_child(const std::string& label);
    std::shared_ptr<ClassificationNode> find_child(const std::string& label);

    std::vector<std::shared_ptr<ClassificationNode>> getChildren() const;
    std::vector<std::shared_ptr<Song>> getSongs() const;
    void add_song(const std::shared_ptr<Song>& song, const std::vector<std::string>& levels, size_t levelIndex);

};
