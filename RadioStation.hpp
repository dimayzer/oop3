#pragma once
#include "includes.hpp"
#include "Agency.hpp"

struct Frequency {
    std::string band;
    std::string frequency;
    Frequency(const std::string& band, const std::string& frequency):
        band(band), frequency(frequency) {}
};

class RadioStation: public Agency {
private:
    std::vector<Frequency> frequencies;

public:
    RadioStation(const std::string& name, const std::string& profile,
                const std::string& license_number, const std::string& location,
                const std::vector<Frequency>& frequencies):
        Agency(name, profile, license_number, location),
        frequencies(frequencies) {}
    ~RadioStation() override = default;

    std::string get_type() const override { return "RadioStation"; }
    std::vector<Frequency> get_frequencies() const { return frequencies; }
    void set_frequencies(const std::vector<Frequency>& new_frequencies) { frequencies = new_frequencies; }
};
