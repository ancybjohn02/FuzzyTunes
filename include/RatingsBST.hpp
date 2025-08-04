#ifndef RATING_TREE_HPP
#define RATING_TREE_HPP

#include <vector>
#include <string>
#include <memory>
#include <map>  // ⬅️ added for grouped result
#include "Song.hpp"

class RatingTreeNode {
public:
    int rating;  // 1 to 5
    std::vector<std::shared_ptr<Song>> songs;
    std::shared_ptr<RatingTreeNode> left;
    std::shared_ptr<RatingTreeNode> right;

    RatingTreeNode(int r);
};

class SongRatingTree {
private:
    std::shared_ptr<RatingTreeNode> root;

    std::shared_ptr<RatingTreeNode> insert(std::shared_ptr<RatingTreeNode> node, std::shared_ptr<Song> song, int rating);
    std::shared_ptr<RatingTreeNode> search(std::shared_ptr<RatingTreeNode> node, int rating);
    std::shared_ptr<RatingTreeNode> delete_song(std::shared_ptr<RatingTreeNode> node, const std::string& title, bool& deleted);

    void remove_from_all(std::shared_ptr<RatingTreeNode> node, const std::string& title, bool& removed);
    void print_inorder(std::shared_ptr<RatingTreeNode> node) const;

    // ⬇️ helper for grouped songs
    void in_order_grouped(std::shared_ptr<RatingTreeNode> node, std::map<int, std::vector<std::shared_ptr<Song>>>& result) const;

public:
    SongRatingTree();
    void print_grouped_by_rating() const;
    void print_inorder_grouped(std::shared_ptr<RatingTreeNode> node) const;

    void insert_song(std::shared_ptr<Song> song, int rating);
    std::vector<std::shared_ptr<Song>> search_by_rating(int rating);
    bool delete_song(const std::string& title);
    std::vector<std::shared_ptr<Song>> get_all_rated_songs() const;

    // ⬇️ version B: grouped by rating
    std::map<int, std::vector<std::shared_ptr<Song>>> get_all_rated_songs_grouped() const;
};

#endif
