Курсов проект по ООП към ФМИ-София

Тема: Управление на Бази от данни

Проекта е разработен на C++ и поддържа команди като:

- `open`, `save`, `saveas`, `close`, `insert`, `print`, `select`, `update` и др.


GitHub хранилище: https://github.com/Kris040805/Database-Project-OOP.git

Документация: docs -> html -> index.html

Стартиране:

- Главната програма:
- - компилираш с: g++ -std=c++17 -I./include src/*.cpp main.cpp -o main
- - стартираш с: ./main

- Tестовете:
- - компилираш с: g++ -std=c++17 -I./include -I./external tests/test_cells.cpp src/*.cpp -o tests
- - стартираш с: ./tests