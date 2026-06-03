# ifndef PLAY_STRATEGY_H
# define PLAY_STRATEGY_H

# include "../enum/strategyType.h"
# include "../models/playlist.h"

class PlayStrategy {
public:
    virtual ~PlayStrategy() {}
    virtual void setPlayList(PlayList playList) = 0;
    virtual bool hasNext() = 0;
    virtual void next() = 0;
    virtual bool hasPrevious() = 0;
    virtual void previous() = 0;
    virtual void addToNext(Song song) = 0;
    virtual Song getCurrentSong() = 0;
};

# endif // PLAY_STRATEGY_H