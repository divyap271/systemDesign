#ifndef PLAYLIST_H
#define PLAYLIST_H

#include <string>
#include <vector>
#include "song.h"

using namespace std;

class PlayList {
public:
    string name;
    vector<Song> songs;
    void addSong(Song song) {
        songs.push_back(song);
    }
    vector<Song> getSongs() {
        return songs;
    }
};

#endif // PLAYLIST_H