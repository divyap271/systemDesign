#ifndef RANDOM_PLAY_STRATEGY_H
#define RANDOM_PLAY_STRATEGY_H

#include "playStrategy.h"
#include <algorithm>
#include <random>

class RandomPlayStrategy : public PlayStrategy {
private:
    PlayList playList;
    std::vector<int> shuffledIndices;
    int currentIndex;
    std::mt19937 rng;
public:
    RandomPlayStrategy() : currentIndex(0), rng(std::random_device{}()) {}
    void setPlayList(PlayList playList) override {
        this->playList = playList;
        shuffledIndices.clear();
        for (int i = 0; i < playList.getSongs().size(); ++i) {
            shuffledIndices.push_back(i);
        }
        std::shuffle(shuffledIndices.begin(), shuffledIndices.end(), rng);
    }
    bool hasNext() override {
        return currentIndex < shuffledIndices.size() - 1;
    }
    void next() override {
        if (hasNext()) {
            currentIndex++;
        }
    }
    bool hasPrevious() override {
        return currentIndex > 0;
    }
    void previous() override {
        if (hasPrevious()) {    
            currentIndex--;
        }
    }
    void addToNext(Song song) override {
        playList.addSong(song);
    }
    Song getCurrentSong() override {
        if (playList.getSongs().empty() || shuffledIndices.empty()) return Song();
        return playList.getSongs()[shuffledIndices[currentIndex]];
    }
};

#endif // RANDOM_PLAY_STRATEGY_H