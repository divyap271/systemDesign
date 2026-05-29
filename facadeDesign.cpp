// the facade design pattern is a structural design pattern that provide a simplified, higher level interface to a larger, more complex ody of code, such as a class library, a framework, or a complex subsystem of many moving parts

#include <iostream>
#include <string>
#include <memory>

// complex subsystem components
class TheaterLights {
public:
    void dim(int level) { std::cout << "Lights dimming to " << level << "%.\n"; }
    void on() { std::cout << "Lights turned fully ON.\n"; }
};

class Projector {
public:
    void on() { std::cout << "Projector powered ON.\n"; }
    void setInputWideScreen() { std::cout << "Projector aspect ratio set to 16:9 widescreen.\n"; }
    void off() { std::cout << "Projector powered OFF.\n"; }
};

class Amplifier {
public:
    void on() { std::cout << "Amplifier powered ON.\n"; }
    void setStreamingAudio() { std::cout << "Amplifier input channel toggled to Digital Stream.\n"; }
    void setVolume(int level) { std::cout << "Master volume dialed to level " << level << ".\n"; }
    void off() { std::cout << "Amplifier powered OFF.\n"; }
};

// facade
class HomeTheaterFacade {
private:
    // The facade keeps track of all the subsystem dependencies
    std::unique_ptr<TheaterLights> lights;
    std::unique_ptr<Projector> projector;
    std::unique_ptr<Amplifier> amp;

public:
    HomeTheaterFacade() {
        lights = std::make_unique<TheaterLights>();
        projector = std::make_unique<Projector>();
        amp = std::make_unique<Amplifier>();
    }

    // A single simple method replaces a mountain of client-side logic
    void watchMovie() {
        std::cout << "\n--- Preparing theater to watch movie... ---\n";
        lights->dim(15);
        projector->on();
        projector->setInputWideScreen();
        amp->on();
        amp->setStreamingAudio();
        amp->setVolume(25);
        std::cout << "Movie is now playing! Enjoy.\n";
    }

    void endMovie() {
        std::cout << "\n--- Shutting down home theater system... ---\n";
        lights->on();
        projector->off();
        amp->off();
        std::cout << "Theater successfully shut down.\n";
    }
};

// client
int main() {
    // The client interacts ONLY with the simple facade interface
    HomeTheaterFacade smartHomeRemote;

    // Turn everything on with one single call
    smartHomeRemote.watchMovie();

    // ... hours later when the movie ends ...

    // Turn everything off with one single call
    smartHomeRemote.endMovie();

    return 0;
}