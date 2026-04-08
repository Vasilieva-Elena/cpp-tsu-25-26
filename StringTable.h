#ifndef STRINGTABLE_H
#define STRINGTABLE_H

#include <string>
#include <vector>
#include <iostream>

class StringTable {
protected:
    std::vector<std::string> _strings;   // хранит все строки (имена)

public:
    // Доступ по индексу (только чтение)
    const std::string& operator[](int index) const;

    // Добавить строку, если её ещё нет; вернуть её индекс
    int add(const std::string& name);

    // Вывод всей таблицы в поток (формат: "индекс имя")
    friend std::ostream& operator<<(std::ostream& os, const StringTable& st);
};

#endif
