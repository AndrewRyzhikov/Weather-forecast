#include "View.h"
Element SetPicture(uint8_t code) {
    Element element;
    if (code == 0 or code == 1) {
        element = vbox({
                               text("      \\   /      "),
                               text("       .-.        "),
                               text("    ― (   ) ―    "),
                               text("       `-’        "),
                               text("      /   \\      ")
                       }) ;
    } else if (code == 2) {
        element = vbox({
                               text("   .( ).           "),
                               text("  (_._)_) .(  )    "),
                               text("         (_.)_._)  ")
                       });
    } else if (code == 3) {
        element = vbox({
                               text("          .--.     "),
                               text("      .-( --- ).   "),
                               text("    (___.__)__)    ")
                       });
    } else if (code == 45 or code == 48) {
        element = vbox({
                               text("   _   -_   _-     "),
                               text("  -_   -  _ -- _   "),
                               text("    _  -  _- -_    "),
                               text("   - _-  _ _- -    ")
                       });
    } else if (code == 51 or code == 53 or code == 55 or
               code == 56 or code == 57 or code == 61 or
               code == 63 or code == 66) {
        element = vbox({
                               text("   .( ).           "),
                               text("  (_._)_)  .(  )   "),
                               text("  ' '   ' (_.)_._) "),
                               text("   '   '    '  '   "),
                               text("          '  '   ' ")
                       });
    } else if (code == 65 or code == 67 or code == 80 or
               code == 81 or code == 82) {
        element = vbox({
                               text("         .--.      "),
                               text("     .-( --- ).    "),
                               text("    (___.__)__)    "),
                               text("     / /  /  /     "),
                               text("    / /  /  /      ")
                       });
    } else if (code == 71 or code == 73) {
        element = vbox({
                               text("   .( ).           "),
                               text("  (_._)_)  .(  )   "),
                               text("  *   *  (_.)_._)  "),
                               text("     *    *    *   "),
                               text("        *    *     ")
                       });
    } else if (code == 75 or code == 85 or code == 86) {
        element = vbox({
                               text("         .--.      "),
                               text("     .-( --- ).    "),
                               text("    (___.__)__)    "),
                               text("    * *  * * *     "),
                               text("   * * * * * *     ")
                       });
    } else if (code == 77) {
        element = vbox({
                               text("          .--.      "),
                               text("      .-( --- ).    "),
                               text("     (___.__)__)    "),
                               text("     o   0   o      "),
                               text("   o   o     o     "),
                       });
    } else if (code == 95) {
        element = vbox({
                               text("         .--.      "),
                               text("     .-( --- ).    "),
                               text("    (___.__)__)    "),
                               text("      _/  _/       "),
                               text("     /   /         ")
                       });
    } else if (code == 96 or code == 99) {
        element = vbox({
                               text("         .--.      "),
                               text("     .-( --- ).    "),
                               text("    (___.__)__)    "),
                               text("    o  _/  _/      "),
                               text("      / o /  o     "),
                       });
    }
    return element;
}


Element SetPartDay(const Weather& weather, const std::string& partDay) {
    Element picture = SetPicture(weather.weather_code_);
    std::string temperature = std::to_string(static_cast<int>(weather.temperature_));
    std::string apparent_temperature = std::to_string(static_cast<int>(weather.apparent_temperature_));
    std::string visibility = std::to_string(static_cast<size_t>((weather.visibility_)));
    std::string wind_speed = std::to_string(static_cast<size_t>(weather.wind_speed_ ));
    std::string precipitation = std::to_string(static_cast<size_t>(weather.precipitation_));
    std::string precipitation_probability = std::to_string(static_cast<size_t>(weather.precipitation_probability_));

    Element window_part_day = border(vbox(text(partDay) | bold | hcenter | vcenter, separator(),
                                          hbox(picture, vbox(text(weather_code[weather.weather_code_]),
                                                             text(temperature + '(' + apparent_temperature + ')' + "°С"),
                                                             text(wind_speed + " km/h"), text(visibility + " km"), text(precipitation + " mm " + "| " + precipitation_probability + " %")))));
    return window_part_day;
}

Element DrowTown(const Data& data, size_t index_town, size_t number_of_days) {
    Elements res;
    for (int i = 0; i < number_of_days; ++i) {
        Element morning = SetPartDay(data.GetTown(index_town).GetDay(i).part_of_day_[MORNING], "Morning");
        Element afternoon = SetPartDay(data.GetTown(index_town).GetDay(i).part_of_day_[AFTERNOON], "Afternoon");
        Element evening = SetPartDay(data.GetTown(index_town).GetDay(i).part_of_day_[EVENING], "Evening");
        Element night = SetPartDay(data.GetTown(index_town).GetDay(i).part_of_day_[NIGHT], "Night");

        Element parts_day = hbox(morning, afternoon, evening, night);

        Element all_day = vbox(text(data.GetTown(index_town).GetDay(i).date.substr(0, 10)) | bold, parts_day);

        res.push_back(all_day);
    }

    Element town = vbox(text(data.GetTown(index_town).GetName()) | hcenter | bold, (vbox(std::move(res))));
    return town;
}