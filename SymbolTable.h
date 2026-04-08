#ifndef SYMBOLTABLE_H
#define SYMBOLTABLE_H

#include <string>
#include <vector>
#include <iostream>

class SymbolTable {
public:
    // Структура записи таблицы символов (пока только имя)
    struct TableRecord {
        std::string _name;

        // Конструктор для удобства
        TableRecord(const std::string& name = "") : _name(name) {}

        // Оператор сравнения для тестов
        bool operator==(const TableRecord& other) const {
            return _name == other._name;
        }
    };

protected:
    std::vector<TableRecord> _records;   // хранилище записей

public:
    // Доступ по индексу (только чтение)
    const TableRecord& operator[](int index) const;

    // Добавить новую запись с именем, если её ещё нет; вернуть индекс
    int add(const std::string& name);

    // Вывод всей таблицы в поток (формат: "индекс имя")
    friend std::ostream& operator<<(std::ostream& os, const SymbolTable& st);
};

#endif
