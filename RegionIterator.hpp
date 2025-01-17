#pragma once
#include "Agency.hpp"
#include "includes.hpp"
#include <map>
#include <vector>
#include <string>
#include <utility>

class RegionIterator {
private:
    std::map<std::string, int> location_counts;
    std::map<std::string, int>::iterator current;

public:
    RegionIterator(const std::vector<Agency*>& agencies) {
        for (const auto& agency : agencies) {
            location_counts[agency->get_location()]++;
        }
        current = location_counts.begin();
    }

    bool hasNext() const {
        return current != location_counts.end();
    }

    std::pair<std::string, int> next() {
        auto result = *current;
        ++current;
        return result;
    }
};
