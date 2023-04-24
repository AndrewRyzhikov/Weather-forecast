#include "Data.h"

using namespace ftxui;

void Data::UpdateWeather() {
    for (auto& town: towns_) {
        town.ParseWeather();
    }
}
