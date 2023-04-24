#include <cpr/cpr.h>
#include <nlohmann/json.hpp>

using json = nlohmann::json;


struct Weather {
    float temperature_;
    float wind_speed_;
    uint8_t weather_code_;
    uint8_t visibility_;
    float precipitation_probability_;
    float precipitation_;
    float apparent_temperature_;
};

enum PartDay {
    MORNING = 0,
    AFTERNOON = 1,
    EVENING = 2,
    NIGHT = 3
};

struct Day {
    constexpr static const uint8_t kNumberPartsDay = 4;

    Day() = default;

    std::map<PartDay, Weather> part_of_day_;
    std::string date;
};

class Town {
private:
    std::string name_;
    double latitude_;
    double longitude_;
    const uint8_t kNumberDays;
    std::vector<Day> days_;
public:

    Town() = default;

    explicit Town(const std::string& name_town, uint8_t size_days) : name_(name_town), days_(size_days),
                                                                     kNumberDays(size_days) {

        auto response = cpr::Get(cpr::Url{"https://api.api-ninjas.com/v1/city?name=" + name_town},
                                 cpr::Header{{"X-Api-Key", "B6jODhE+3eydVpnwvc1wSg==kgXbNsZ3R6DYRHz6"}});
        json j_txt = json::parse(response.text.substr(1, response.text.length() - 2));

        latitude_ = j_txt["latitude"];
        longitude_ = j_txt["longitude"];
    }

    std::string GetName() {
        return name_;
    }

    Day GetDay(size_t index_day) {
        return days_[index_day];
    }

    void ParseWeather();
};