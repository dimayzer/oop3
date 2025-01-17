#pragma once
#include "includes.hpp"
#include "Agency.hpp"

class PublishingMedia: public Agency {
private:
    std::vector<std::string> period;
    int circulation;

public:
    PublishingMedia(const std::string& name, const std::string& profile,
                   const std::string& license_number, const std::string& location,
                   const std::vector<std::string>& period, int circulation):
        Agency(name, profile, license_number, location),
        period(period), circulation(circulation) {}
    ~PublishingMedia() override = default;

    std::string get_type() const override { return "PublishingMedia"; }
    std::vector<std::string> get_period() const { return period; }
    int get_circulation() const { return circulation; }

    void set_period(const std::vector<std::string>& new_period) { period = new_period; }
    void set_circulation(int new_circulation) { circulation = new_circulation; }
};
