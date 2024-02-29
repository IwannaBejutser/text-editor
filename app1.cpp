#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <locale>

void displayFileContents(const std::string &filename)
{
    std::ifstream file_in(filename);
    if (!file_in.is_open())
    {
        std::cerr << "Не удалось открыть файл " << filename << std::endl;
        return;
    }

    std::string line;
    int lineNumber = 1;
    std::cout << "Содержимое файла " << filename << ":" << std::endl;
    while (std::getline(file_in, line))
    {
        std::cout << lineNumber << ". " << line << std::endl;
        lineNumber++;
    }
    file_in.close();
}

void insertTextIntoFile(const std::string &filename)
{
    std::fstream file(filename, std::ios::in | std::ios::out);
    if (!file.is_open())
    {
        std::cerr << "Не удалось открыть файл " << filename << std::endl;
        return;
    }

    displayFileContents(filename); // Отображение содержимого файла

    std::vector<std::string> lines;
    std::string line;
    while (std::getline(file, line))
    {
        lines.push_back(line);
    }

    size_t lineNumber;
    std::cout << "Введите номер строки, куда нужно вставить текст: ";
    std::cin >> lineNumber;
    if (lineNumber < 1 || lineNumber > lines.size() + 1)
    {
        std::cerr << "Неверный номер строки" << std::endl;
        return;
    }

    std::cin.ignore(); // Очищаем буфер ввода

    std::string newText;
    std::cout << "Введите текст для вставки в файл (введите 'exit' для завершения):" << std::endl;
    while (true)
    {
        std::getline(std::cin, newText);

        if (newText == "exit")
        {
            break;
        }

        lines.insert(lines.begin() + lineNumber - 1, newText);
        lineNumber++;
    }

    file.close();

    std::ofstream file_out(filename);
    if (!file_out.is_open())
    {
        std::cerr << "Не удалось открыть файл " << filename << " для записи" << std::endl;
        return;
    }

    for (const auto &l : lines)
    {
        file_out << l << std::endl;
    }
    file_out.close();

    std::cout << "Текст успешно добавлен в файл." << std::endl;
}

void deleteTextFromFile(const std::string &filename)
{
    displayFileContents(filename);

    std::vector<std::string> lines;
    std::ifstream file_in(filename);
    if (!file_in.is_open())
    {
        std::cerr << "Не удалось открыть файл " << filename << std::endl;
        return;
    }

    std::string line;
    while (std::getline(file_in, line))
    {
        lines.push_back(line);
    }
    file_in.close();

    int lineNumber;
    std::cout << "Введите номер строки, которую нужно удалить: ";
    std::cin >> lineNumber;
    if (lineNumber < 1 || lineNumber > lines.size())
    {
        std::cerr << "Неверный номер строки" << std::endl;
        return;
    }

    lines.erase(lines.begin() + lineNumber - 1);

    std::ofstream file_out(filename);
    if (!file_out.is_open())
    {
        std::cerr << "Не удалось открыть файл " << filename << " для записи" << std::endl;
        return;
    }

    for (const auto &l : lines)
    {
        file_out << l << std::endl;
    }
    file_out.close();
    std::cout << "Строка успешно удалена из файла." << std::endl;
}

void editTextInFile(const std::string &filename)
{
    displayFileContents(filename);

    std::vector<std::string> lines;
    std::ifstream file_in(filename);
    if (!file_in.is_open())
    {
        std::cerr << "Не удалось открыть файл " << filename << std::endl;
        return;
    }

    std::string line;
    while (std::getline(file_in, line))
    {
        lines.push_back(line);
    }
    file_in.close();

    int lineNumber;
    std::cout << "Введите номер строки, которую нужно отредактировать: ";
    std::cin >> lineNumber;
    if (lineNumber < 1 || lineNumber > lines.size())
    {
        std::cerr << "Неверный номер строки" << std::endl;
        return;
    }

    std::string newText;
    std::cout << "Введите новый текст для строки " << lineNumber << ": ";
    std::cin.ignore(); // Игнорируем символ новой строки после ввода номера строки
    std::getline(std::cin, newText);

    lines[lineNumber - 1] = newText;

    std::ofstream file_out(filename);
    if (!file_out.is_open())
    {
        std::cerr << "Не удалось открыть файл " << filename << " для записи" << std::endl;
        return;
    }

    for (const auto &l : lines)
    {
        file_out << l << std::endl;
    }
    file_out.close();
    std::cout << "Текст успешно отредактирован в файле." << std::endl;
}

int main()
{
    setlocale(LC_ALL, "ru_RU.UTF-8");

    std::string filename;
    std::cout << "Введите имя файла: ";
    std::cin >> filename;

    while (true)
    {
        std::cout << "Выберите действие:\n1. Посмотреть файл\n2. Вставить текст\n3. Удалить текст\n4. Редактировать текст\n5. Выйти\n";
        int choice;
        std::cin >> choice;

        if (choice == 1)
        {
            displayFileContents(filename);
        }
        else if (choice == 2)
        {
            insertTextIntoFile(filename);
        }
        else if (choice == 3)
        {
            deleteTextFromFile(filename);
        }
        else if (choice == 4)
        {
            editTextInFile(filename);
        }
        else if (choice == 5)
        {
            break;
        }
        else
        {
            std::cout << "Неверный выбор действия." << std::endl;
        }
    }

    return 0;
}
