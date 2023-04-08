//
// Created by aiden on 03/04/2023.
//

#include "AcademicBuildings.h"
#include "ownable.h"
#include <unordered_map>
#include "info.h"
#include "player.h"
#include "state.h"
#include "info.h"
#include "observer.h"
#include "subject.h"
using namespace std;


AcademicBuildings::AcademicBuildings(board &b, std::string name, int pos, int i, int j):
    b{b},
    b_name{name},
    pos{pos},
    iCord{i},
    jCord{j} {
}

AcademicBuildings::AcademicBuildings~() {}


std::string AcademicBuildings::getFacultyName(const std::string& buildingName) {
    for (const auto& building : academic_buildings) {
        if (buildingName == building.first) {
            return std::get<0>(building.second);
        }
    }
    return "Building not found.";
}


void AcademicBuildings::buyImprovement() {
    Info info2 = this->getInfo();
    Player *owner = info2.ownedBy;
    string cName = info2.cellName;
    if (isMortgage) {
        cout << "mortgaged property: No improvements Allowed" << endl;
        return;
    }
    string facName = getFacultyName(cName);
    if (owner) {
        owner->partMonopoly();
        if (FacultyMap[facName].second && info2.improveCount < 5) {
            //owner has a monopoly and < 5 built so can buy improvement
            //tuple w costs
            auto building = academic_buildings.find(facName)->second;
            //get cost of curr improvement and subtract
            owner->subFunds(std::get<info2.improveCount>(building));
            if (improveCount < 4) {
                cout << "Installed a Bathroom" << endl;
            } else {
                cout << "Installed a Cafeteria" << endl;
            }
            info2.improveCount++;
        }
    } else {
        cout << "No Ownership:No Improvements allowed" << endl;
    }
}

void AcademicBuildings::sellImprovement(int improvement) {





int AcademicBuildings::improvementCost() {
}


    void payTuition() override;
    void mortgage() override;
    void unMortgage() override;
    void notify(Subject<Info, State> &whoNotified) override;

    std::string getFacultyName();
};











//add to player.h and player.cc

/*
const int NumArts1 = 2;
const int NumArts3 = 3;
const int NumEng = 3;
const int NumHealth = 3;
const int NumEnv = 3;
const int NumSci1 = 3;
const int NumSci2 = 3;
const int NumMath = 2;

bool Player:: partMonopoly(std::unordered_map<std::string) {
    if ((FacultyMap["Arts1"] == NumArts1) ||
    (FacultyMap["Arts2"] == NumArts3) ||
    (FacultyMap["Eng"] == NumEng) ||
    (FacultyMap["Health"] == NumHealth) ||
    (FacultyMap["Env"] == NumEnv) ||
    (FacultyMap["Sci1"] == NumSci1) ||
    (FacultyMap["Sci2"] == NumSci2) ||
    (FacultyMap["Math"] == NumMath)) {
        return true;
    }
    return false;
}
*/


std::unordered_map<std::string, std::pair<int, bool>> FacultyMap =
        {{"Arts1", {0, false}}, {"Arts2", {0, false}}, {"Eng", {0, false}},
         {"Health", {0, false}}, {"Env", {0, false}}, {"Sci1", {0, false}},
         {"Sci2", {0, false}}, {"Math", {0, false}}};

const int NumArts1 = 2;
const int NumArts3 = 3;
const int NumEng = 3;
const int NumHealth = 3;
const int NumEnv = 3;
const int NumSci1 = 3;
const int NumSci2 = 3;
const int NumMath = 2;

void Player:: partMonopoly() {
    if (FacultyMap["Arts1"].first == NumArts1) {
        FacultyMap["Arts1"].second = true;
    }
    if (FacultyMap["Arts2"].first == NumArts3) {
        FacultyMap["Arts2"].second = true;
    }
    if (FacultyMap["Eng"].first == NumEng) {
        FacultyMap["Eng"].second = true;
    }
    if (FacultyMap["Health"].first == NumHealth) {
        FacultyMap["Health"].second = true;
    }
    if (FacultyMap["Env"].first == NumEnv) {
        FacultyMap["Env"].second = true;
    }
    if (FacultyMap["Sci1"].first == NumSci1) {
        FacultyMap["Sci1"].second = true;
    }
    if (FacultyMap["Sci2"].first == NumSci2) {
        FacultyMap["Sci2"].second = true;
    }
    if (FacultyMap["Math"].first == NumMath) {
        FacultyMap["Math"].second = true;
    }
}
