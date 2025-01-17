#ifndef AGENCY_TABLE_ITERATOR_HPP
#define AGENCY_TABLE_ITERATOR_HPP

#include "AgencyTable.hpp"

class AgencyTableIterator {
private:
    AgencyTable& table; // Ссылка на таблицу
    size_t index;       // Текущий индекс

public:
    explicit AgencyTableIterator(AgencyTable& t) : table(t), index(0) {}

    // Проверяет, есть ли еще элементы
    bool hasNext() {
        while (index < table.getCapacity()) {
            TableEntry* entry = table.getEntry(index);
            if (entry && entry->occupied) {
                return true;
            }
            ++index;
        }
        return false;
    }

    // Возвращает следующий элемент
    Agency* next() {
        if (hasNext()) {
            return table.getEntry(index++)->agency;
        }
        return nullptr;
    }
};

#endif // AGENCY_TABLE_ITERATOR_HPP
