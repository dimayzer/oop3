#include "../lib/includes.hpp"
#include "../lib/AgencyTable.hpp"
#include <mutex>

unsigned int AgencyTable::hash_func(const char* key) {
    unsigned int hash = 0;
    while(*key) {
        hash = (hash << 5) + *key++;
    }
    return hash % capacity;
}

void AgencyTable::resize() {
	std::lock_guard<std::mutex> lock(table_mutex); // Блокируем таблицу на время изменения
    size_t old_capacity = capacity;
    TableEntry* old_table = table;
    
    capacity *= 2;
    table = new TableEntry[capacity];
    size = 0;

    for(size_t i = 0; i < old_capacity; i++) {
        if(old_table[i].occupied && old_table[i].name != nullptr) {
            insert(old_table[i].name, old_table[i].agency);
            delete[] old_table[i].name;
        }
    }
    delete[] old_table;
}

AgencyTable::AgencyTable(size_t init_capacity): size(0), capacity(init_capacity) {
    table = new TableEntry[capacity];
}

AgencyTable::~AgencyTable() {
    for(size_t i = 0; i < capacity; i++) {
        if(table[i].name != nullptr) {
            delete[] table[i].name;
            delete table[i].agency;
        }
    }
    delete[] table;
}

void AgencyTable::insert(const char* name, Agency* agency) {
	std::lock_guard<std::mutex> lock(table_mutex); // Блокировка
    if(static_cast<double>(size) / capacity >= LOAD_FACTOR_THRESHOLD) {
        resize();
    }

    size_t index = hash_func(name);
    while(table[index].occupied) {
        if(table[index].name != nullptr && strcmp(table[index].name, name) == 0) {
            delete table[index].agency;
            table[index].agency = agency;
            return;
        }
        index = (index + 1) % capacity;
    }

    table[index].name = new char[strlen(name) + 1];
    strcpy(table[index].name, name);
    table[index].agency = agency;
    table[index].occupied = true;
    size++;
}

Agency* AgencyTable::search(const char* name) {
	std::lock_guard<std::mutex> lock(table_mutex); // Блокировка
    size_t index = hash_func(name);
    size_t start_index = index;

    do {
        if(!table[index].occupied) {
            return nullptr;
        }
        if(table[index].name != nullptr && strcmp(table[index].name, name) == 0) {
            return table[index].agency;
        }
        index = (index + 1) % capacity;
    } while(index != start_index);

    return nullptr;
}

bool AgencyTable::remove(const char* name) {
	std::lock_guard<std::mutex> lock(table_mutex); // Блокировка
    size_t index = hash_func(name);
    size_t start_index = index;

    do {
        if(!table[index].occupied) {
            return false;
        }
        if(table[index].name != nullptr && strcmp(table[index].name, name) == 0) {
            delete[] table[index].name;
            delete table[index].agency;
            table[index].name = nullptr;
            table[index].agency = nullptr;
            table[index].occupied = false;
            size--;
            return true;
        }
        index = (index + 1) % capacity;
    } while(index != start_index);

    return false;
}


TableEntry* AgencyTable::getEntry(size_t index) {
	if (index < capacity) {
		return &table[index];
	}
	return nullptr;
}

size_t AgencyTable::getCapacity() const {
	return capacity;
}
