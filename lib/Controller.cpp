#include "Controller.h"

void UpdateScreen(Data data) {
    auto start = std::chrono::system_clock::now();
    auto finish = std::chrono::system_clock::now();
    auto different_time = std::chrono::duration_cast<std::chrono::seconds>(finish - start);
    while (true) {
        if (GetAsyncKeyState(VK_ESCAPE)) {
            break;
        }
        finish = std::chrono::system_clock::now();
        different_time = std::chrono::duration_cast<std::chrono::seconds>(finish - start);
        if (different_time.count() % data.GetFrequency() == 0) {
            data.UpdateWeather();
        }
    }
}

void Output(Data data) {
    size_t index_day = 0;
    size_t number_of_days = 3;

    auto screen = ScreenInteractive::TerminalOutput();
    auto renderer = Renderer([&data, &index_day, &number_of_days] {
        return DrowTown(data, index_day, number_of_days);
    });

    auto component = CatchEvent(renderer, [&](const Event& event) {
        if (event == Event::Escape) {
            screen.ExitLoopClosure()();
            return true;
        } else if (event == Event::Character('n')) {
            index_day = (index_day + 1) % data.GetSizeTowns();
            return true;
        } else if (event == Event::Character('p')) {
            index_day = (index_day - 1) % data.GetSizeTowns();
            return true;
        } else if (event == Event::Character('+')) {
            number_of_days++;
            number_of_days = (number_of_days < data.GetDays() ? number_of_days : data.GetDays());
            return true;
        } else if (event == Event::Character('-')) {
            number_of_days--;
            number_of_days = (number_of_days > 1 ? number_of_days : 1);
            return true;
        }
        return false;
    });

    screen.Loop(component);
}

void Parse(const std::string& path) {
    Data data(path);
    std::thread f1(Output, std::ref(data));
    std::thread f2(UpdateScreen, std::ref(data));
    f1.join();
    f2.join();
}
