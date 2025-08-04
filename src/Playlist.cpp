#include "../include/Playlist.hpp"
#include <iostream>
#include<algorithm>
#include<random>

using namespace std;

Playlist::Playlist() : head(nullptr), tail(nullptr) {}

void Playlist::add_song(const string& title, const string& artist, int duration) {
    std::string id = Song::generate_id();
    std::shared_ptr<Song> newSong = std::make_shared<Song>(id, title, artist, duration);
    if (!head) {
        head = tail = newSong;
    } else {
        tail->setNext(newSong);
        newSong->setPrev(tail);
        tail = newSong;
    }
}

void Playlist::delete_song(int index) {
    if (!head) return;

    std::shared_ptr<Song> temp = head;
    int i = 0;
    while (temp && i < index) {
        temp = temp->getNext();
        i++;
    }
    if (!temp) return;

    if (temp == head) head = temp->getNext();
    if (temp == tail) tail = temp->getPrev();
    if (temp->getPrev()) temp->getPrev()->setNext(temp->getNext());
    if (temp->getNext()) temp->getNext()->setPrev(temp->getPrev());

}

void Playlist::move_song(int from_index, int to_index) {
    if (from_index == to_index) return;

    std::shared_ptr<Song> moving = head;
    int i = 0;
    while (moving && i < from_index) {
        moving = moving->getNext();
        i++;
    }
    if (!moving) return;

    // Unlink
    if (moving == head) head = moving->getNext();
    if (moving == tail) tail = moving->getPrev();
    if (moving->getPrev()) moving->getPrev()->setNext(moving->getNext());
    if (moving->getNext()) moving->getNext()->setPrev(moving->getPrev());

    // Insert at new position
    std::shared_ptr<Song> temp = head;
    int k = 0;
    while (temp && k < to_index) {
        temp = temp->getNext();
        k++;
    }

    if (!temp) {
        // Insert at end
        moving->setNext(nullptr);
        moving->setPrev(tail);
        if (tail) tail->setNext(moving);
        tail = moving;
    } else if (temp == head) {
        moving->setPrev(nullptr);
        moving->setNext(head);
        head->setPrev(moving);
        head = moving;
    } else {
        moving->setPrev(temp->getPrev());
        moving->setNext(temp);
        temp->getPrev()->setNext(moving);
        temp->setPrev(moving);
    }
}

void Playlist::reverse_playlist() {
    std::shared_ptr<Song> current = head;
    std::shared_ptr<Song> prevNode = nullptr;

    while (current) {
        std::shared_ptr<Song> nextNode = current->getNext();
        current->setNext(current->getPrev());
        current->setPrev(nextNode);
        prevNode = current;
        current = nextNode;
    }

    swap(head, tail);
}

void Playlist::shuffle_playlist() {
    if (!head || head == tail) return; // 0 or 1 song → nothing to shuffle

    // Step 1: Extract all nodes into a vector
    std::vector<std::shared_ptr<Song>> nodeList;
    std::shared_ptr<Song> current = head;
    while (current) {
        nodeList.push_back(current);
        current = current->getNext();
    }

    // Step 2: Shuffle the vector
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(nodeList.begin(), nodeList.end(), g);

    // Step 3: Rebuild the DLL
    head = nodeList[0];
    head->setPrev(nullptr);
    for (size_t i = 0; i < nodeList.size() - 1; ++i) {
        nodeList[i]->setNext(nodeList[i + 1]);
        nodeList[i + 1]->setPrev(nodeList[i]);
    }
    tail = nodeList.back();
    tail->setNext(nullptr);
}

std::shared_ptr<Song> Playlist::get_song(int index) const {
    std::shared_ptr<Song> temp = head;
    int i = 0;
    while (temp && i < index) {
        temp = temp->getNext();
        ++i;
    }
    return temp;
}


void Playlist::print_playlist() {
    std::shared_ptr<Song> temp = head;
    int index = 0;
    while (temp) {
        cout << index++ << ". " << temp->getTitle() << " by " << temp->getArtist() << " (" << temp->getDuration() << "s)" << endl;
        temp = temp->getNext();
    }
}

int Playlist::size() const {
    int count = 0;
    std::shared_ptr<Song> temp = head;
    while (temp) {
        ++count;
        temp = temp->getNext();
    }
    return count;
}

std::shared_ptr<Song> Playlist::get_head() const {
    return head;
}

void Playlist::set_head(std::shared_ptr<Song> newHead) {
    head = newHead;

    // Recalculate tail to stay consistent
    tail = newHead;
    while (tail && tail->getNext()) {
        tail = tail->getNext();
    }
}

std::vector<std::shared_ptr<Song>> Playlist::get_all_songs() const {
    std::vector<std::shared_ptr<Song>> songs;
    std::shared_ptr<Song> current = head;
    while (current) {
        songs.push_back(current);
        current = current->getNext();
    }
    return songs;
}


Playlist::~Playlist() = default;

/*
General Time Complexity Summary:

- Addition (at end):         O(1)
- Deletion (by index):       O(n)
- Access (by index):         O(n)
- Move (by indices):         O(n)
- Reverse:                   O(n)
- Shuffle:                   O(n) time, O(n) space (uses a temporary vector)
- Size calculation:          O(n)
- Printing/Traversal:        O(n)
- get_all_songs():           O(n) time and O(n) space (copies pointers to a vector)

Note:
- The use of smart pointers (`std::shared_ptr`) handles memory management automatically.
- Playlist maintains both `head` and `tail` pointers for efficient end insertions.
*/
