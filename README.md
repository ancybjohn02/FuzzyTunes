## FuzzyTunes

### A modular C++ console-based music player that allows you to manage playlists, rate songs, sort them by title or duration, and explore music by genre, mood, or artist. Designed with object-oriented principles and custom data structures like doubly linked lists, stacks, binary search trees, and classification trees.

- **Language**: C++
- **Data Structures**: Doubly Linked List, Stack, Binary Search Tree, Map, Classification Tree
- **Sorting**: Merge Sort (for stability and performance with linked list conversion)

### PLAYWISE Project Structure

```
PLAYWISE/
├── .vscode/
├── build/
├── docs/
│   ├── Modules.png
│   ├── SongMap_pseudocode.md
│   └── songRating_pseudocode.md
├── include/
│   ├── ClassificationNode.hpp
│   ├── ClassificationTree.hpp
│   ├── FuzzyHelper.hpp
│   ├── PlaybackStack.hpp
│   ├── Playlist.hpp
│   ├── RatingsBST.hpp
│   ├── Recommender.hpp
│   ├── Snapshot.hpp
│   ├── Song.hpp
│   ├── SongMap.hpp
│   ├── Sort.hpp
│   └── utils.hpp
├── output/
│   └── dashboard.png
├── src/
│   ├── ClassificationNode.cpp
│   ├── ClassificationTree.cpp
│   ├── FuzzyHelper.cpp
│   ├── PlaybackStack.cpp
│   ├── PlaybackStack.o
│   ├── Playlist.cpp
│   ├── Playlist.o
│   ├── RatingsBST.cpp
│   ├── RatingsBST.o
│   ├── Recommender.cpp
│   ├── Snapshot.cpp
│   ├── Snapshot.o
│   ├── Song.cpp
│   ├── Song.o
│   ├── SongMap.cpp
│   ├── SongMap.o
│   ├── Sort.cpp
│   └── Sort.o
```

The rating tree intends us to use tree alone, no map 
- also in this we've to manage scrnarios of duplication like the same song being rated twice
- scenarios where the rating has been changed so when searched by rating it shd only appear in the new rating list not in the old one
- not just delet in place but also delete that node itself to clean up memory space

When songs were removed from a playlist or rating tree, the program crashed with a std::length_error. This typically happens when we access or print a std::string from a pointer that was deleted or never properly initialized. In our case, the error occurred because a Song* pointer inside the rating tree became dangling-either due to deletion or invalid memory access.
When working with raw pointers like Song*, especially when the same object is referenced in multiple places (playlist, rating tree), you must be very careful about ownership and deletion. If you delete a pointer in one place but try to access it from another, it will crash your program.
Whenever you have the same object being used in multiple places, don’t manually delete it. Let C++ manage it using shared_ptr. It’ll save you from crashes like this. Also, always check if a pointer is null before using it.

before implementing the song map, i.e., instant lookup using map, the addition of songs was like : 
std::make_shared<Song>("Shape of You", "Ed Sheeran", 240);
 but then to support instant lookup, i had to assign unique id's to each song and use that as key for the std::map.

DLL is for ordered playlist storage and hash maps as indexing system

fuzzy logic to handle cases in instant lookup : 
- a user might search a word not the whole title
- typos
- capitalisation issues
- partial words
So, we'll follow the following approach : 
* normalise input
* try exact match first->O(1)
* If not found, do a fuzzy search
    * loop through keys, compute similarity or substring    presence
- to handle typos we can use Levenshtein distance
  - If distance ≤ 2 or similarity ≥ 0.8 → return it.

time complexity for lookup : 
| Step                    | Time Complexity       |
| ----------------------- | --------------------- |
| Index parsing/playlist  | O(1)                  |
| Title/ID Hashmap lookup | O(1) avg, O(n) worst  |
| Fuzzy match fallback    | O(n × m × k)          |
| Rating lookup           | O(log r + s) → ≈ O(1) |

We'll go with merge sort for sorting, as it is stable and good for linked lists. 
If using Merge Sort:
* Stable, so song titles with same rating stay in order.
* Always O(n log n) time.
* Doesn’t degrade even if songs are already partially sorted.

If using Quick Sort:
* Unstable: May reorder equal elements (e.g., same rating but different songs).
* Worst-case time is O(n²).
* Needs extra care to avoid worst-case via pivot selection.

If sorting directly on the DLL, Merge Sort is clearly superior, because:
* It works well on linked lists (no need for random access).
* Can be done in O(1) space on lists.
* In-place merge sort for DLLs is clean and efficient.



the three kinds of sorting needed are : 
* sorting by title(alphabetical order)
* duration
* recently added

we don't need to worry abt text separately coz C++ takes care of ASCII comparison in std::string

- traditional sorting algorithms like merge sort, quick sort, and heap sort work best on random-access containers like arrays or vectors.

while these can be applied to dll directly as well but : 
* More complex to implement and maintain
* Trickier to handle ascending/descending toggle cleanly
* we lose easy comparator-based sorting flexibility
Converting to a vector avoids the overhead of repeatedly traversing nodes in DLLs during sort.

for 15th option, if we type in a non-integer value, it will cause an infinite loop, - bad input crashing cin : 
* cin will:
  * go into a fail state,
  * skip all further inputs silently,
  * and thus cause an infinite loop of the same question or   bad behavior.

* For recommendation system, some unplayed songs shd be left in the playlist, to play songs one by one, go to option 11. Lookup Song by Title or ID, here it will ask if to play that song, so the current implementation of recommendation system would not recommend any songs if all songs have already been played.

To run the code :
* navigate to the folder where code is cloned,
```bash
mkdir build
cd build
cmake ..
make
./PLAYWISE
```


