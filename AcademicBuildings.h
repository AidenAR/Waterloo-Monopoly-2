//
// Created by aiden on 03/04/2023.
//

#ifndef ACADEMICBUILDINGS_H
#define ACADEMICBUILDINGS_H
#include "ownable.h"
#include <unordered_map>
#include "info.h"
#include "player.h"
#include "state.h"
#include "info.h"
#include "observer.h"
#include "subject.h"
#include <map>


class AcademicBuildings: public Ownable {
public:
    std::map<std::string, std::tuple<std::string,
    int, int, int, int, int, int, int, int>> academic_buildings = {
            //name,faculty,purch,improv,imp0,imp1,imp3,imp4,imp5
            //Arts 1
            {"AL", {"Arts1", 40, 50, 2, 10, 30, 90, 160, 250}},
            {"ML", {"Arts1", 60, 50, 4, 20, 60, 180, 320, 450}},

            //Arts2
            {"ECH", {"Arts2", 100, 50, 6, 30, 90, 270, 400, 550}},
            {"PAS", {"Arts2", 100, 50, 6, 30, 90, 270, 400, 550}},
            {"HH", {"Arts2", 120, 50, 8, 40, 100, 300, 450, 600}},

            //Eng
            {"RCH", {"Eng", 140, 100, 10, 50, 150, 450, 625, 750}},
            {"DWE", {"Eng", 140, 100, 10, 50, 150, 450, 625, 750}},
            {"CPH", {"Eng", 160, 100, 12, 60, 180, 500, 700, 900}},

            // Health Monopoly
            {"LHI", {"Health", 180, 100, 14, 70, 200, 550, 750, 950}},
            {"BMH", {"Health", 180, 100, 14, 70, 200, 550, 750, 950}},
            {"OPT", {"Health", 200, 100, 16, 80, 220, 600, 800, 1000}},

            // Environment Monopoly
            {"EV1", {"Env", 220, 150, 18, 90, 250, 700, 875, 1050}},
            {"EV2", {"Env", 220, 150, 18, 90, 250, 700, 875, 1050}},
            {"EV3", {"Env", 240, 150, 20, 100, 300, 750, 925, 1100}},

            // Science 1 Monopoly
            {"PHYS",{"Sci1", 260, 150, 22, 110, 330, 800, 975, 1150}},
            {"B1", {"Sci1", 260, 150, 22, 110, 330, 800, 975, 1150}},
            {"B2", {"Sci1", 280, 150, 24, 120, 360, 850, 1025, 1200}},

            // Science 2 Monopoly
            {"EIT", {"Sci2", 300, 200, 26, 130, 390, 900, 1100, 1275}},
            {"ESC", {"Sci2", 300, 200, 26, 130, 390, 900, 1100, 1275}},
            {"C2", {"Sci2", 320, 200, 28, 150, 450, 1000, 1200, 1400}},

            // Math Monopoly
            {"MC", {"Math", 350, 200, 35, 175, 500, 1100, 1300, 1500}},
            {"DC", {"Math", 400, 200, 50, 200, 600, 1400, 1700, 2000}}
    };
    /*
    const int NumArts1 = 2;
    const int NumArts3 = 3;
    const int NumEng = 3;
    const int NumHealth = 3;
    const int NumEnv = 3;
    const int NumSci1 = 3;
    const int NumSci2 = 3;
    const int NumMath = 2;
*/
    AcademicBuildings(Board &b, std::string name, int pos, int i, int j, bool ownable, OwnableType otype, int price);
    ~AcademicBuildings();
    void sellImprovement() override;
    void buyImprovement() override;
    std::string getFacultyName(const std::string& buildingName);
    void payTuition(Player *p) override;
    void mortgage() override;
    void unMortgage() override;
    void notify(std::shared_ptr<Subject<Info, State>> whoFrom) override;
};


#endif //ACADEMICBUILDINGS_H
