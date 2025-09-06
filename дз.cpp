#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <thread>
#include <chrono>
#include <conio.h> // Для _kbhit() и _getch()

using namespace std;

/// <summary>
/// Получить содержимое файла
/// </summary>
/// <param name="filename">Имя считываемого файла</param>
/// <returns>Содержимое файла</returns>
string getFileContent(string filename)
{
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "Ошибка открытия файла: " << filename << endl;
        return "";
    }

    string content(
        (istreambuf_iterator<char>(file)),
        istreambuf_iterator<char>());
    file.close();
    return content;
}

vector<string> split(string content, string delimeter)
{
    vector<string> parts;
    int start = 0;
    int end = content.find(delimeter);

    while (end != string::npos)
    {
        parts.push_back(content.substr(start, end - start));
        start = end + delimeter.length();
        end = content.find(delimeter, start);
    }
    parts.push_back(content.substr(start));
    return parts;
}

/// <summary>
/// Воспроизведение анимации
/// </summary>
/// <param name="filename">Имя файла с анимацией</param>
/// <param name="frameDelay">Задержка между кадрами в миллисекундах</param>
void playAnimation(string filename, int frameDelay = 33)
{
    string content = getFileContent(filename);
    if (content.empty()) {
        cout << "Файл пуст или не найден: " << filename << endl;
        this_thread::sleep_for(chrono::seconds(2));
        return;
    }

    vector<string> frames = split(content, "FRAME");

    cout << "Воспроизведение анимации: " << filename << endl;
    cout << "Нажмите любую клавишу для возврата в меню..." << endl;
    this_thread::sleep_for(chrono::seconds(1));

    while (true)
    {
        for (string frame : frames)
        {
            // Проверяем, была ли нажата клавиша
            if (_kbhit()) {
                _getch(); // Считываем нажатую клавишу
                return; // Возвращаемся в меню
            }

            system("cls");
            cout << frame << endl;
            this_thread::sleep_for(chrono::milliseconds(frameDelay));
        }
    }
}

/// <summary>
/// Отображение главного меню
/// </summary>
void showMenu()
{
    system("cls");
    cout << "=== ВЫБОР АНИМАЦИИ ===" << endl;
    cout << "1. Анимация 1 (animation.txt)" << endl;
    cout << "2. Анимация 2 (animation2.txt)" << endl;
    cout << "3. Анимация 3 (animation3.txt)" << endl;
    cout << "4. Выход" << endl;
    cout << "======================" << endl;
    cout << "Выберите номер анимации: ";
}

int main()
{
    setlocale(LC_ALL, "rus");
    int choice = 0;

    while (true)
    {
        showMenu();
        cin >> choice;

        // Очищаем буфер ввода
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch (choice)
        {
        case 1:
            playAnimation("animation.txt");
            break;
        case 2:
            playAnimation("animation2.txt");
            break;
        case 3:
            playAnimation("animation3.txt");
            break;
        case 4:
            cout << "Выход из программы..." << endl;
            return 0;
        default:
            cout << "Неверный выбор! Попробуйте снова." << endl;
            this_thread::sleep_for(chrono::seconds(1));
            break;
        }
    }

    return 0;
}