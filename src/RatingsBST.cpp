#include "RatingsBST.hpp"
#include <iostream>

// Constructor for RatingTreeNode
RatingTreeNode::RatingTreeNode(int r)
    : rating(r), left(nullptr), right(nullptr) {}

// Constructor for the tree
SongRatingTree::SongRatingTree() : root(nullptr) {}

std::shared_ptr<RatingTreeNode> SongRatingTree::insert(
    std::shared_ptr<RatingTreeNode> node, std::shared_ptr<Song> song, int rating) {
    
    if (!node) {
        auto newNode = std::make_shared<RatingTreeNode>(rating);
        newNode->songs.push_back(song);
        return newNode;
    }

    if (rating < node->rating) {
        node->left = insert(node->left, song, rating);
    } else if (rating > node->rating) {
        node->right = insert(node->right, song, rating);
    } else {
        for (const auto& s : node->songs) {
            if (s->getTitle() == song->getTitle()) {
                return node; // prevent duplicate song titles at same rating
            }
        }
        node->songs.push_back(song);
    }

    return node;
}

void SongRatingTree::remove_from_all(
    std::shared_ptr<RatingTreeNode> node, const std::string& title, bool& removed) {
    
    if (!node) return;

    for (auto it = node->songs.begin(); it != node->songs.end(); ++it) {
        if ((*it)->getTitle() == title) {
            node->songs.erase(it);
            removed = true;
            break;
        }
    }

    remove_from_all(node->left, title, removed);
    remove_from_all(node->right, title, removed);
}

void SongRatingTree::insert_song(std::shared_ptr<Song> song, int rating) {
    bool removed = false;
    remove_from_all(root, song->getTitle(), removed);
    root = insert(root, song, rating);
}

std::shared_ptr<RatingTreeNode> SongRatingTree::search(
    std::shared_ptr<RatingTreeNode> node, int rating) {
    
    if (!node) return nullptr;
    if (rating == node->rating) return node;
    return rating < node->rating ? search(node->left, rating) : search(node->right, rating);
}

std::vector<std::shared_ptr<Song>> SongRatingTree::search_by_rating(int rating){
    auto node = search(root, rating);
    return node ? node->songs : std::vector<std::shared_ptr<Song>>();
}

std::shared_ptr<RatingTreeNode> SongRatingTree::delete_song(
    std::shared_ptr<RatingTreeNode> node, const std::string& title, bool& deleted) {
    
    if (!node) return nullptr;

    for (auto it = node->songs.begin(); it != node->songs.end(); ++it) {
        if ((*it)->getTitle() == title) {
            node->songs.erase(it);
            deleted = true;
            break;
        }
    }

    if (deleted && node->songs.empty()) {
        if (!node->left) {
            return node->right;
        } else if (!node->right) {
            return node->left;
        } else {
            auto minNode = node->right;
            while (minNode->left) minNode = minNode->left;

            node->rating = minNode->rating;
            node->songs = minNode->songs;

            bool dummy = false;
            node->right = delete_song(node->right, minNode->songs[0]->getTitle(), dummy);
        }
    }

    if (!deleted) {
        node->left = delete_song(node->left, title, deleted);
        if (!deleted) {
            node->right = delete_song(node->right, title, deleted);
        }
    }

    return node;
}

bool SongRatingTree::delete_song(const std::string& title) {
    bool deleted = false;
    root = delete_song(root, title, deleted);
    return deleted;
}

void collect_inorder(std::shared_ptr<RatingTreeNode> node, std::vector<std::shared_ptr<Song>>& result) {
    if (!node) return;

    collect_inorder(node->left, result);

    for (const auto& song : node->songs) {
        result.push_back(song);
    }

    collect_inorder(node->right, result);
}

std::vector<std::shared_ptr<Song>> SongRatingTree::get_all_rated_songs() const {
    std::vector<std::shared_ptr<Song>> result;
    collect_inorder(root, result);
    return result;
}

void SongRatingTree::print_grouped_by_rating() const {
    print_inorder_grouped(root);
}

void SongRatingTree::print_inorder_grouped(std::shared_ptr<RatingTreeNode> node) const {
    if (!node) return;

    print_inorder_grouped(node->left);

    std::cout << "Rating " << node->rating << ":" << std::endl;
    for (const auto& song : node->songs) {
        std::cout << "  - " << song->getTitle() << " by " << song->getArtist() << std::endl;
    }

    print_inorder_grouped(node->right);
}

/*
Each BST node (RatingTreeNode) holds:
- A unique rating (int)
- A list of songs (vector<shared_ptr<Song>>) sharing that rating

General Time and Space Complexity:

- insert_song():               O(h + m) 
    where h = height of the tree, m = songs at same rating
- delete_song(title):          O(n + h + m)
    (search by title: O(n), possible deletion fix-up: O(h), vector erase: O(m))
- search_by_rating():          O(h)
- get_all_rated_songs():       O(n)
- print_grouped_by_rating():   O(n)
- remove_from_all():           O(n)
- Internal song list ops (push_back, erase): O(1) to O(m), where m is the number of songs at a rating

Notes:
- In worst-case, h = O(n) (unbalanced tree), but average is O(log n) if balanced.
- Title-based uniqueness is enforced per rating bucket during insertion.
*/
