#include "Data.h"
#include <ftxui/dom/elements.hpp>
#include <ftxui/screen/screen.hpp>
#include "ftxui/screen/box.hpp"
#include "ftxui/component/component.hpp"
#include "ftxui/component/screen_interactive.hpp"
#include "libraries.h"

Element SetPicture(uint8_t code);

Element SetPartDay(const Weather& weather, const std::string& partDay);

Element DrowTown(const Data& data, size_t index_town, size_t number_of_days);
