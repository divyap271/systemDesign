#include "core/musicPlayerFacade.h"
#include <iostream>
#include <vector>

int main() {
    MusicPlayerFacade player;

    // Create a playlist and add songs
    player.createPlaylist("My Favorite Songs");
    player.addSongToPlaylist("My Favorite Songs", {"Song 1", "Artist A", "/path/1"});
    player.addSongToPlaylist("My Favorite Songs", {"Song 2", "Artist B", "/path/2"});
    player.addSongToPlaylist("My Favorite Songs", {"Song 3", "Artist C", "/path/3"});
    player.addSongToPlaylist("My Favorite Songs", {"Song 4", "Artist D", "/path/4"});

    // Select playlist and device
    player.selectPlaylist("My Favorite Songs");
    player.selectDevice(DeviceType::HEADPHONES);

    std::cout << "--- Sequential Play ---" << std::endl;
    player.setStrategy(StrategyType::SEQUENTIAL);
    player.play(); // Song 1
    player.next(); // Song 2

    std::cout << "\n--- Random Play ---" << std::endl;
    player.setStrategy(StrategyType::RANDOM);
    player.play(); 
    player.next();

    std::cout << "\n--- Custom Play (Order: 3, 0, 2, 1) ---" << std::endl;
    player.setStrategy(StrategyType::CUSTOM);
    player.setCustomOrder({3, 0, 2, 1});
    player.play(); // Song 4
    player.next(); // Song 1
    player.next(); // Song 3
    player.next(); // Song 2

    return 0;
}