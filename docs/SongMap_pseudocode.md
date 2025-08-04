Function add_song(song):
    id_map[song.id] ← song
    title_map[song.title] ← song

Function remove_song_by_id(id):
    if id in id_map:
        title ← id_map[id].title
        remove title_map[title]
        remove id_map[id]

Function remove_song_by_title(title):
    if title in title_map:
        id ← title_map[title].id
        remove id_map[id]
        remove title_map[title]

Function get_by_id(id):
    return id_map[id] if found else null

Function get_by_title(title):
    return title_map[title] if found else null

Function get_all_titles():
    return title_map

## How it aggregates everything?
1. Playlist adds songs → also updates SongMap for ID & title access.
2. RatingTree assigns rating to songs (accesses song via title/ID from SongMap).
3. UI or Recommender modules fetch:
   - song by ID (for playback)
   - song by title (for search/display)
   - full song details from shared_ptr<Song>
     → which includes title, artist, duration, etc.
4. When song is deleted from Playlist or RatingTree → SongMap cleans up from both maps.
