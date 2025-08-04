## SongRatingTree - Core Logic (Pseudocode)

### insert_song(song, rating)
1. Remove the song from any previous rating bucket (entire tree traversal).
2. Traverse the BST to find the correct rating node:
   - If not found, create a new node with this rating and add the song.
   - If found:
     - Check for duplicate by title.
     - If not duplicate, add song to the node's song list.

---

### remove_from_all(node, title, removed_flag)
1. If node is null, return.
2. Check if any song in the node has the given title.
   - If found, remove it and mark `removed_flag = true`.
3. Recurse on left and right children.

---

### search_by_rating(rating)
1. Traverse BST to find the node with matching rating.
2. If found, return its song list.
3. Else, return empty list.

---

### delete_song(title)
1. Start from the root.
2. For each node:
   - Check for matching title in its song list.
     - If found, remove the song.
     - If song list becomes empty, remove the entire BST node:
       - If node has one child, return that child.
       - If node has two children:
         - Replace with in-order successor.
         - Move the successor’s rating and songs here.
         - Recursively delete successor’s original node.
3. If not found, recurse left and right.
4. Return true if deleted, else false.

---

### get_all_rated_songs()
1. Perform in-order traversal of the BST.
2. Append each song from each node to the result list.

---

### print_grouped_by_rating()
1. In-order traversal of the BST.
2. At each node:
   - Print the rating.
   - Print each song under it.
