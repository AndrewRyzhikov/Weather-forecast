#include "Town.h"

void Town::ParseWeather() {
    auto response = cpr::Get(
            cpr::Url{"https://api.open-meteo.com/v1/forecast?latitude=" + std::to_string(latitude_) + "&longitude=" +
                     std::to_string(longitude_) +
                     "&hourly=temperature_2m,precipitation_probability,precipitation,weathercode,visibility,windspeed_10m,apparent_temperature&forecast_days=" + std::to_string(kNumberDays)});

    json info_weather = json::parse(response.text);
    for (int i = 0; i < kNumberDays; ++i) {
        days_[i].date = info_weather["hourly"]["time"][24 * i];
        for (int j = 0; j < Day::kNumberPartsDay; ++j) {
            PartDay partDay = static_cast<PartDay>(j);
            days_[i].part_of_day_[partDay].temperature_ = info_weather["hourly"]["temperature_2m"][23 * i + (5 + 6 * j)];
            days_[i].part_of_day_[partDay].wind_speed_ = info_weather["hourly"]["windspeed_10m"][23 * i + (5 + 6 * j)];
            days_[i].part_of_day_[partDay].precipitation_probability_ = info_weather["hourly"]["precipitation_probability"][23 * i + (5 + 6 * j)];
            days_[i].part_of_day_[partDay].precipitation_ = info_weather["hourly"]["precipitation"][23 * i + (5 + 6 * j)];
            days_[i].part_of_day_[partDay].visibility_ = info_weather["hourly"]["visibility"][23 * i + (5 + 6 * j)];
            days_[i].part_of_day_[partDay].weather_code_ = info_weather["hourly"]["weathercode"][23 * i + (5 + 6 * j)];
            days_[i].part_of_day_[partDay].apparent_temperature_ = info_weather["hourly"]["apparent_temperature"][23 * i + (5 + 6 * j)];
        }
    }
}
