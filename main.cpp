#include "SongMap.hpp"
#include "FuzzyHelper.hpp"
#include "Playlist.hpp"
#include "PlaybackStack.hpp"
#include "RatingsBST.hpp"
#include "Sort.hpp"
#include "Snapshot.hpp"
#include "ClassificationTree.hpp"
#include "Song.hpp"
#include "Recommender.hpp"
#include <iostream>
#include <limits>
using namespace std;

void print_menu() {
    cout << "\n===== Music Player Menu =====\n";
    cout << "1. View Playlist\n";
    cout << "2. Add Song\n";
    cout << "3. Remove Song\n";
    cout << "4. Shuffle Playlist\n";
    cout << "5. Play All Songs\n";
    cout << "6. Repeat Last Played\n";
    cout << "7. Rate a Song from Playlist\n";
    cout << "8. Search Songs by Rating\n";
    cout << "9. Delete Rated Song by Number\n";
    cout << "10. Display All Rated Songs\n";
    cout << "11. Lookup Song by Title or ID\n";
    cout << "12. Sort Playlist\n";
    cout << "13. Export Snapshot\n";
    cout << "14. Move Song\n";
    cout << "15. Explore Songs by Genre > Subgenre > Mood > Artist \n(Pls enter no. not Text)\n";
    cout << "16. Recommended Songs based on Playback History\n";
    cout << "0. Exit\n";
    cout << "Choose an option: ";
    
}


void displayPlaylist(std::shared_ptr<Song> head){
    int index = 0;
    while (head) {
        std::cout << index++ << ". " << head->getTitle() << " by " << head->getArtist() 
                  << " (" << head->getDuration() << "s)" << std::endl;
        head = head->getNext();
    }
}

int main() {
    Playlist playlist;
    PlaybackStack playback;
    SongRatingTree rating_tree;
    SongMap lookup;
    ClassificationTree tree;

    int choice;

    std::vector<std::shared_ptr<Song>> initialSongs = {
        std::make_shared<Song>("id1", "Alappuzha Mullakal", "Hanan Shaah", 208,"Indian", "Romantic", "Celebratory"),
        std::make_shared<Song>("id2", "Uyiril thodum", "Sushin Shyam", 234,"Indian", "Melodic", "Gentle"),
        std::make_shared<Song>("id3", "Parayuvaan ithu aadyamaayi", "Sid Sriram", 277, "Indian", "Romantic", "Melancholic"),
        std::make_shared<Song>("id4", "Ray", "Sushin Shyam", 358, "Indian", "Electronic-Fusion", "Moody"),
        std::make_shared<Song>("id5", "Aye Sinamika", "A R Rahman", 390, "Indian", "Soft Melody", "Uplifting"),
        std::make_shared<Song>("id6", "Vaathilil aa vaathilil", "Haricharan", 365, "Indian", "Light Classical", "Hopeful")
    };


    for (const auto& song : initialSongs) {
        playlist.add_song(song->getTitle(), song->getArtist(), song->getDuration());
    
        tree.add_song(
            song,
            song->getGenre(),
            song->getSubgenre(),
            song->getMood(),
            song->getArtist()
        );
        
    
        lookup.add_song(song);
    }
    do {
        print_menu();
        std::cin >> choice;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        switch (choice) {
            case 1:
                playlist.print_playlist();
                
                break;

            case 2: {
                std::string title, artist, id;
                int duration;
                cout << "Enter ID: ";
                std::getline(std::cin, id);
                cout << "Enter title: ";
                std::getline(std::cin, title);
                cout << "Enter artist: ";
                std::getline(std::cin, artist);
                cout << "Enter duration (sec): ";
                std::cin >> duration;
                std::cin.ignore();

                auto new_song = std::make_shared<Song>(id, title, artist, duration);
                playlist.add_song(title, artist, duration);
                lookup.add_song(new_song);

                cout << "Song added!\n";
                break;
            }

            case 3: {
                int index;
                playlist.print_playlist();
                cout << "Enter song number to remove: ";
                std::cin >> index;
                std::cin.ignore();
                playlist.delete_song(index - 1);
                cout << "Song removed if number was valid.\n";
                break;
            }

            case 4:
                playlist.shuffle_playlist();
                cout << "Playlist shuffled.\n";
                break;

            case 5:
                for (int i = 0;; ++i) {
                    std::shared_ptr<Song> song = playlist.get_song(i);
                    if (!song) break;
                    cout << "Now playing: " << song->getTitle() << " by " << song->getArtist() << "\n";
                    playback.push(song);
                }
                break;

            case 6: {
                std::shared_ptr<Song> last = playback.peek();
                if (last)
                    cout << "Repeating: " << last->getTitle() << " by " << last->getArtist() << "\n";
                else
                    cout << "No song in history.\n";
                break;
            }

            case 7: {
                int index, rating;
                playlist.print_playlist();
                cout << "Enter song number to rate: ";
                std::cin >> index;
                cout << "Enter rating (1–5): ";
                std::cin >> rating;
                std::cin.ignore();

                std::shared_ptr<Song> song = playlist.get_song(index - 1);
                if (!song) {
                    cout << "Invalid song number.\n";
                    break;
                }

                if (rating < 1 || rating > 5) {
                    cout << "Rating must be between 1 and 5.\n";
                    break;
                }

                rating_tree.insert_song(song, rating);
                cout << "Rated and added to rating tree.\n";
                break;
            }

            case 8: {
                int rating;
                cout << "Enter rating (1–5) to search: ";
                std::cin >> rating;
                std::cin.ignore();

                auto results = rating_tree.search_by_rating(rating);
                if (results.empty()) {
                    cout << "No songs with this rating.\n";
                } else {
                    cout << "Songs with rating " << rating << ":\n";
                    for (size_t i = 0; i < results.size(); ++i) {
                        auto& song = results[i];
                        cout << i + 1 << ". " << song->getTitle() << " by " << song->getArtist() << "\n";
                    }
                }
                break;
            }

            case 9: {
                auto allRated = rating_tree.get_all_rated_songs();
                if (allRated.empty()) {
                    cout << "No rated songs to delete.\n";
                    break;
                }


                cout << "\nRated Songs:\n";
                for (size_t i = 0; i < allRated.size(); ++i) {
                    cout << i + 1 << ". " << allRated[i]->getTitle() << " by " << allRated[i]->getArtist() << "\n";
                }

                int toDelete;
                cout << "Enter number of song to delete: ";
                std::cin >> toDelete;
                std::cin.ignore();

                if (toDelete < 1 || toDelete > static_cast<int>(allRated.size())) {
                    cout << "Invalid selection.\n";
                } else {
                    std::string title = allRated[toDelete - 1]->getTitle();
                    rating_tree.delete_song(title);
                    cout << "Deleted \"" << title << "\" from rating tree.\n";
                }
                break;
            }

            case 10: {
                std::cout << "\nSongs grouped by rating:\n";
                rating_tree.print_grouped_by_rating();
                break;
            }
            
            
            case 11: {
                cout << "Enter Song Title or ID to look up: ";
                std::string inputStr;
                std::getline(std::cin >> std::ws, inputStr);  // read full line after trimming whitespace
            
                std::shared_ptr<Song> song = nullptr;
            
                // Try to interpret as index
                try {
                    int index = std::stoi(inputStr);
                    if (index >= 0 && index < playlist.size()) {
                        song = playlist.get_song(index);
                    } else {
                        cout << "Invalid index.\n";
                        break;
                    }
                } catch (...) {
                    // Not a valid number, treat as title or ID
                    song = lookup.get_by_title(inputStr);
                    if (!song) song = lookup.get_by_id(inputStr);
                    if (!song) song = FuzzySearchHelper::fuzzy_match(inputStr, lookup.get_title_map());
                }
            
                if (!song) {
                    cout << "Song not found.\n";
                    break;
                }
            
                // Print song details
                cout << "Found: " << song->getTitle() << " by " << song->getArtist()
                          << "\nDuration: " << song->getDuration() << " seconds\n";
            
                // Search rating from SongRatingTree
                int found_rating = -1;
                for (int r = 1; r <= 5; ++r) {
                    auto songs_in_rating = rating_tree.search_by_rating(r);
                    for (const auto& s : songs_in_rating) {
                        if (s->getID() == song->getID()) {
                            found_rating = r;
                            break;
                        }
                    }
                    if (found_rating != -1) break;
                }
            
                if (found_rating != -1) {
                    cout << "Rating: " << found_rating << " stars\n";
                } else {
                    cout << "Rating: Not found.\n";
                }
                
                char playChoice;
                cout << "Do you want to play this song now? (y/n): ";
                cin >> playChoice;
                cin.ignore();

                if (playChoice == 'y' || playChoice == 'Y') {
                    cout << "Now playing: " << song->getTitle() << " by " << song->getArtist() << "\n";
                    playback.push(song);
                }
                break;
            }
            
            case 12: {
                auto currentHead = playlist.get_head();
                if (!currentHead) {
                    std::cout << "Playlist is empty.\n";
                    break;
                }
            
                int sortChoice;
                std::cout << "\n--- Sort Playlist ---\n";
                std::cout << "1. Sort by Title (ascending)\n";
                std::cout << "2. Sort by Duration (ascending)\n";
                std::cout << "3. Sort by Recently Added (latest first)\n";
                std::cout << "Enter choice: ";
                std::cin >> sortChoice;
            
                // Convert DLL to vector
                auto songsVec = Sort::dllToVector(currentHead);
            
                switch (sortChoice) {
                    case 1:
                        Sort::mergeSortByTitle(songsVec, true);  // ascending title
                        break;
                    case 2:
                        Sort::mergeSortByDuration(songsVec, true);  // ascending duration
                        break;
                    case 3:
                        Sort::sortByRecentlyAdded(songsVec);  // most recent first
                        break;
                    default:
                        std::cout << "Invalid sort option.\n";
                        break;
                }
            
                // Display sorted result
                std::cout << "\nSorted Playlist (Temporary View):\n";
                for (size_t i = 0; i < songsVec.size(); ++i) {
                    std::cout << i+1 << ". " << songsVec[i]->getTitle()
                              << " by " << songsVec[i]->getArtist()
                              << " (" << songsVec[i]->getDuration() << "s)" << std::endl;
                }
            
                // Ask user whether to save the new sorted order
                char saveChoice;
                std::cout << "\nDo you want to save this sorted order to the playlist? (y/n): ";
                std::cin >> saveChoice;
            
                if (saveChoice == 'y' || saveChoice == 'Y') {
                    auto newHead = Sort::vectorToDll(songsVec);
                    playlist.set_head(newHead);
                    std::cout << "Playlist has been updated with the new sorted order.\n";
                } else {
                    std::cout << "Original playlist was not changed.\n";
                }
            
                break;
            }
            
            case 13: {
                Snapshot snapshot(playlist, rating_tree);
                snapshot.export_snapshot();
                break;
            }
            
            case 14: {
                playlist.print_playlist();
                int from_index, to_index;
                cout << "Enter index of the song to move: ";
                cin >> from_index;
                cout << "Enter new index to move it to: ";
                cin >> to_index;
                cin.ignore();
            
                playlist.move_song(from_index, to_index);
                cout << "Song moved from position " << from_index << " to " << to_index << ".\n";
                break;
            }

            case 15: {
                tree.explore_classification();
                break;
            }
            
            case 16: {
                int num_songs;
                std::cout << "\nEnter number of recommendations you want: ";
                std::cin >> num_songs;
            
                // Assuming these are already your actual instances (not new ones)
                std::shared_ptr<PlaybackStack> playback_ptr = std::make_shared<PlaybackStack>();
                *playback_ptr = playback;
            
                std::shared_ptr<Playlist> playlist_ptr = std::make_shared<Playlist>();
                *playlist_ptr = playlist;
            
                std::shared_ptr<SongRatingTree> rating_ptr = std::make_shared<SongRatingTree>();
                *rating_ptr = rating_tree;
            
                std::shared_ptr<ClassificationTree> classification_ptr = std::make_shared<ClassificationTree>();
                *classification_ptr = tree;
            
                Recommender recommender(playback_ptr, playlist_ptr, rating_ptr, classification_ptr);
                auto recommendations = recommender.recommend(num_songs);
            
                if (recommendations.empty()) {
                    std::cout << "\nSorry, no recommendations available right now.\n";
                } else {
                    std::cout << "\n🎵 Recommended Songs for You 🎵\n";
                    for (const auto& song : recommendations) {
                        std::cout << "• " << song->getTitle()
                                  << " by " << song->getArtist()
                                  << " | Genre: " << song->getGenre()
                                  << " | Mood: " << song->getMood() << "\n";
                    }
                }
            
                break;
            }
            
            
            
            case 0:
                cout << "Exiting music player. Bye!\n";
                break;

            default:
                cout << "Invalid option!\n";
        }

    } while (choice != 0);

    return 0;
}


