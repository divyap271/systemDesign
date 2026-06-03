#ifndef CUSTOM_PLAY_STRATEGY_H
#define CUSTOM_PLAY_STRATEGY_H
#include "playStrategy.h"

class CustomPlayStrategy : public PlayStrategy {
private:
    PlayList playList;
    std::vector<int> customOrder;
    int currentIndex;
public:
    CustomPlayStrategy() : currentIndex(0) {}
    void setPlayList(PlayList playList) override {
        this->playList = playList;
        customOrder.clear();
        for (int i = 0; i < playList.getSongs().size(); ++i) {
            customOrder.push_back(i);
        }
    }
    bool hasNext() override {
        return currentIndex < customOrder.size() - 1;
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
        customOrder.push_back(playList.getSongs().size() - 1);
    }
    Song getCurrentSong() override {
        if (playList.getSongs().empty() || customOrder.empty()) return Song();
        return playList.getSongs()[customOrder[currentIndex]];
    }
    void setCustomOrder(const std::vector<int>& order) {
        customOrder = order;
    }
};

#endif // CUSTOM_PLAY_STRATEGY_H