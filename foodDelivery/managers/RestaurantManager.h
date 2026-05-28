#ifdef RESTAURANTMANAGER_H
#define RESTAURANTMANAGER_H

#include <vector>
#include <string>
#include <algorithm>
#include "../models/Restaurant.h"

using namespace std;

class RestaurantManager
{
    private:
        vector<Restaurant *> restaurants;
        static RestaurantManager *instance;

        RestaurantManager() {}

    public:
        static RestaurantManager *getInstance()
        {
            if (!instance)
            {
                instance = new RestaurantManager();
            }
            return instance;
        }

        void addRestaurant(Restaurant *restaurant)
        {
            restaurants.push_back(restaurant);
        }

        vector<Restaurant *> searchByLocation(string loc){
            vector<Restaurant *> result;
            transform(loc.begin(), loc.end(), loc.begin(), ::tolower);
            for (auto restaurant : restaurants)
            {
                string restaurantLocation = restaurant->getLocation();
                transform(restaurantLocation.begin(), restaurantLocation.end(), restaurantLocation.begin(), ::tolower);
                if (restaurantLocation == loc)
                {
                    result.push_back(restaurant);
                }
            }
            return result;
        }
};

RestaurantManager *RestaurantManager::instance = nullptr;
#endif // RESTAURANTMANAGER_H