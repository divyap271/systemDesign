#ifndef PLAYLIST_MANAGER_H
#define PLAYLIST_MANAGER_H

#include "../models/playlist.h"
#include <map>

class PlaylistManager {
private:
    std::map<string, PlayList> playlists;
    PlayList* currentPlaylist;

public:
    PlaylistManager() : currentPlaylist(nullptr) {}

    void createPlaylist(string name) {
        PlayList pl;
        pl.name = name;
        playlists[name] = pl;
    }

    void addSongToPlaylist(string playlistName, Song song) {
        playlists[playlistName].addSong(song);
    }

    void selectPlaylist(string name) {
        if (playlists.find(name) != playlists.end()) {
            currentPlaylist = &playlists[name];
        }
    }

    PlayList* getCurrentPlaylist() {
        return currentPlaylist;
    }
};

#endif // PLAYLIST_MANAGER_H