#ifndef MUSIC_PLAYER_FACADE_H
#define MUSIC_PLAYER_FACADE_H

#include "../managers/playlistManager.h"
#include "../managers/strategyManager.h"
#include "../managers/deviceManager.h"
#include "../device/audioEngine.h"

class MusicPlayerFacade {
private:
    PlaylistManager playlistManager;
    StrategyManager strategyManager;
    DeviceManager deviceManager;
    AudioEngine audioEngine;

public:
    void createPlaylist(string name) {
        playlistManager.createPlaylist(name);
    }

    void addSongToPlaylist(string playlistName, Song song) {
        playlistManager.addSongToPlaylist(playlistName, song);
    }

    void selectPlaylist(string name) {
        playlistManager.selectPlaylist(name);
        PlayList* pl = playlistManager.getCurrentPlaylist();
        if (pl) {
            // Default to sequential strategy when playlist is selected
            setStrategy(StrategyType::SEQUENTIAL);
        }
    }

    void setStrategy(StrategyType type) {
        PlayStrategy* strategy = strategyManager.getStrategy(type);
        if (strategy) {
            PlayList* pl = playlistManager.getCurrentPlaylist();
            if (pl) {
                strategy->setPlayList(*pl);
                audioEngine.setStrategy(strategy);
            }
        }
    }

    void setCustomOrder(const std::vector<int>& order) {
        PlayStrategy* strategy = strategyManager.getStrategy(StrategyType::CUSTOM);
        if (strategy) {
            static_cast<CustomPlayStrategy*>(strategy)->setCustomOrder(order);
        }
    }

    void selectDevice(DeviceType type) {
        deviceManager.selectDevice(type);
        audioEngine.setDevice(deviceManager.getCurrentDevice());
    }

    void play() {
        audioEngine.play();
    }

    void next() {
        audioEngine.next();
    }

    void previous() {
        audioEngine.previous();
    }
};

#endif // MUSIC_PLAYER_FACADE_H