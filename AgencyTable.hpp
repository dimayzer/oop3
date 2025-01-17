#pragma once
#include "Agency.hpp"
#include "PublishingMedia.hpp"
#include "RadioStation.hpp"
#include "TVCompany.hpp"

class AgencyTable {
private:
    struct TableEntry {
        char* name;
        Agency* agency;
        bool occupied;
        
        TableEntry(): name(nullptr), agency(nullptr), occupied(false) {}
    };
    
    TableEntry* table;
    size_t size;
    size_t capacity;
    const double LOAD_FACTOR_THRESHOLD = 0.7;

    unsigned int hash_func(const char* key);
    void resize();

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

};
