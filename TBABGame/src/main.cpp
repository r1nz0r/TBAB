#include "core/DataManager.h"
#include <iostream>
#include <filesystem>

#include "core/Weapon.h"

// Эта функция находит абсолютный путь к папке с ресурсами (data)
// Она делает это, отталкиваясь от расположения текущего исходного файла (__FILE__)
// Это самый надежный способ, который будет работать независимо от того,
// откуда вы запускаете исполняемый файл.
std::filesystem::path get_data_directory()
{
    // __FILE__ - это макрос, который превращается в путь к текущему файлу (main.cpp)
    std::filesystem::path source_file_path(__FILE__);
    // Нам нужна папка, в которой лежит main.cpp (src), поэтому берем parent_path()
    std::filesystem::path src_path = source_file_path.parent_path();
    // Папка с данными находится внутри src, так что добавляем "data"
    return src_path / "data";
}


// Точка входа в нашу программу
int main()
{
    // 1. Получаем надежный, абсолютный путь к папке с данными.
    const std::filesystem::path dataDirectory = get_data_directory();
    std::cout << "Looking for data in: " << dataDirectory.string() << std::endl;

    // 2. Создаем экземпляр нашего менеджера данных.
    TBAB::DataManager dataManager;

    // 3. Вызываем загрузку, передавая путь.
    // DataManager'у все равно, откуда пришел этот путь. Он просто его использует.
    dataManager.LoadFromFiles(dataDirectory);
    
    std::cout << "\nGame loaded successfully. Ready to start.\n";

    // Здесь в будущем будет основной игровой цикл.
    // Например, мы можем создать тестовое оружие:
    auto sword = dataManager.CreateWeapon("WEAPON_DAGGERR");
    if (sword)
    {
        std::cout << "Successfully created a test weapon: " << sword->GetName() << "\n";
    }

    return 0;
}

