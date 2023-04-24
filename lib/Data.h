#include "Town.h"
#include <ftxui/dom/elements.hpp>
#include <ftxui/screen/screen.hpp>
#include "ftxui/screen/box.hpp"
#include "ftxui/component/component.hpp"
#include "ftxui/component/screen_interactive.hpp"

using namespace ftxui;

class Data {
public:
    Data(const std::string& path) {
        std::ifstream file;
        file.open(path);
        json info_towns = json::parse(file);

        towns_.reserve(info_towns["towns"].size());
        frequency_ = info_towns["frequency"];
        days_ = info_towns["days"];

        for (int i = 0; i < info_towns["towns"].size(); ++i) {
            towns_.emplace_back(info_towns["towns"][i], days_);
            towns_[i].ParseWeather();
        }
    }

    void UpdateWeather();

    Town GetTown(size_t index_town) const {
        return towns_[index_town];
    }

    size_t GetSizeTowns() const {
        return towns_.size();
    }

    size_t GetFrequency() const {
        return frequency_;
    }
    uint8_t GetDays() const {
        return days_;
    }

private:
    std::vector<Town> towns_;
    uint8_t days_;
    size_t frequency_;
};
