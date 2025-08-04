#include "ClassificationNode.hpp"

ClassificationNode::ClassificationNode(const std::string& label) : name(label) {}

std::shared_ptr<ClassificationNode> ClassificationNode::add_child(const std::string& label) {
    auto existing = find_child(label);
    if (existing) return existing;

    auto newChild = std::make_shared<ClassificationNode>(label);
    children.push_back(newChild);
    return newChild;
}

std::shared_ptr<ClassificationNode> ClassificationNode::find_child(const std::string& label) {
    for (auto& child : children) {
        if (child->name == label) return child;
    }
    return nullptr;
}

std::vector<std::shared_ptr<ClassificationNode>> ClassificationNode::getChildren() const {
    return children;
}

std::vector<std::shared_ptr<Song>> ClassificationNode::getSongs() const {
    return songs;
}

void ClassificationNode::add_song(const std::shared_ptr<Song>& song,
    const std::vector<std::string>& levels,
    size_t levelIndex) {
// Base case: all levels consumed
if (levelIndex >= levels.size()) {
songs.push_back(song);
return;
}

const std::string& label = levels[levelIndex];
auto child = add_child(label);  // will create if doesn't exist

// Recurse to next level
child->add_song(song, levels, levelIndex + 1);
}

