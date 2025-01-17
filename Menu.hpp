#pragma once
#include "Agency.hpp"
#include "AgencyTable.hpp"
#include "RegionIterator.hpp"
#include "includes.hpp"

class Menu {
private:
    AgencyTable& agencies;
    
    void display_menu() const;
    Agency* create_agency() const;
    void register_new_agency();
    void modify_agency_info();
    void display_agencies_by_type() const;
    void revoke_license();
    void display_agencies_by_region() const;
    void display_all_agencies() const;
    std::vector<Agency*> get_all_agencies() const;

public:
    Menu(AgencyTable& agencies): agencies(agencies) {}
    void run();
};
