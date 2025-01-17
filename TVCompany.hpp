#pragma once
#include "includes.hpp"
#include "Agency.hpp"

class TVCompany: public Agency {
private:
    std::string channel;

public:
    TVCompany(const std::string& name, const std::string& profile,
              const std::string& license_number, const std::string& location,
              const std::string& channel):
        Agency(name, profile, license_number, location),
        channel(channel) {}
    ~TVCompany() override = default;

    std::string get_type() const override { return "TVCompany"; }
    std::string get_channel() const { return channel; }
    void set_channel(const std::string& new_channel) { channel = new_channel; }
};
