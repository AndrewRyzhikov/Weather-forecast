
## Описание

Реализация консольного приложение, отображающие прогноз погоды для выбранного списка городов, используя библиотеку [FTXUI](https://github.com/ArthurSonzogni/FTXUI) через подход Model-View-Controller

## Источник данных

- [Open-Meteo](https://open-meteo.com/en/docs#latitude=59.94&longitude=30.31&hourly=temperature_2m&forecast_days=16) для прогноза
- [Api-Ninjas](https://api-ninjas.com/api/city) для определения координат по названию города

## Характеристики

 - Отображение прогноза погоды на несколько дней вперед (значение по умолчанию задается конфигом)
 - Обновление с некоторой частотой (задается конфигом)
 - Переключение между городами с помощью клавиш "n", "p"
 - Окончание работы программы по Esc
 - Увеличение\уменьшение количества дней прогноза по нажатие клавиш "+", "-"

Список городов, частота обновления, количество дней прогноза определяются в конфиге(например в формате OMFL или JSON)











