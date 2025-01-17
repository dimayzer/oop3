#pragma once
#include "Agency.hpp"
#include "PublishingMedia.hpp"
#include "RadioStation.hpp"
#include "TVCompany.hpp"
#include "RegionIterator.hpp"
#include <mutex> // Подключение для использования std::mutex
#include <thread>
#include <vector>
#include <unordered_map>

struct TableEntry {
        char* name;
        Agency* agency;
        bool occupied;
        
        TableEntry(): name(nullptr), agency(nullptr), occupied(false) {}
    };

class AgencyTable {

private:
    
    
    TableEntry* table;
    size_t size;
    size_t capacity;
    const double LOAD_FACTOR_THRESHOLD = 0.7;

    unsigned int hash_func(const char* key);
    void resize();
    mutable std::mutex table_mutex; // Добавляем мьютекс для синхронизации
	mutable std::mutex region_count_mutex; // Мьютекс для синхронизации подсчета регионов

public:
    AgencyTable(size_t init_capacity = 10);
    ~AgencyTable();

    void insert(const char* name, Agency* agency);
    Agency* search(const char* name);
    bool remove(const char* name);
    size_t get_size() const { return size; }
    size_t get_capacity() const { return capacity; }
    const TableEntry* get_table() const { return table; }
    
    bool add(Agency* agency) {
        if (!agency) return false;
        insert(agency->get_name().c_str(), agency);
        return true;
    }

    Agency* find(const char* name) {
        return search(name);
    }

	TableEntry* getEntry(size_t index); // Получить запись по индексу
	size_t getCapacity() const;         // Получить емкость таблицы
	std::unordered_map<std::string, int> countAgenciesByRegion() const;
	std::vector<Agency*> getAllAgencies() const;
};
