#include <iostream>
#include <random>
#include <array>
#include <chrono>
#include <thread>
#include <future>
#include <fstream>
#include <algorithm>
#include <locale>
#include <intrin.h>
#include <ctime>
#include <conio.h>
#include <stdlib.h>
#include <omp.h>
#include <thread>
#include<bits/stdc++.h>
#include <vector>
#include <string>
#include <stdio.h>
#include <stdint.h>
#include <algorithm>
#include <bitset>
#include <climits>

using namespace std::chrono;

#define numRoles    51
#define numFactions     4
#define numAlignments   12
#define maxAttempts     1E+4
#define numSlotTypes 67

const std::string inputFilename = "main_config.txt";
const std::string mainOutputFilename = "main_output.txt";
const std::string profilerFilename = "profiler_data.csv";

int factionLimits[numFactions] = {14, 14, 4, 4};
const int roleLimits[numRoles] = {6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 1, 1, 1, 1, 6, 6, 1, 6, 6, 6, 6, 6, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
const int roleFactions[numRoles] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3};
const int roleAlignments[numRoles] = {0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 2, 2, 2, 2, 3, 3, 3, 3, 4, 4, 4, 4, 5, 5, 5, 5, 6, 6, 6, 6, 7, 7, 7, 7, 8, 8, 8, 9, 9, 9, 10, 10, 10, 10, 10, 11, 11, 11, 11};
const int alignmentNumbers[numAlignments][2] = {{0, 7}, {8, 11}, {12, 15}, {16, 19}, {20, 23}, {24, 27}, {28, 31}, {32, 35}, {36, 38}, {39, 41}, {42, 46}, {47, 50}};
const int factionNumbers[numFactions][2] = {{0, 23}, {24, 31}, {32, 35}, {36, 50}};
const int slotNumbers[numSlotTypes][2] = {{0, 50}, {0, 23}, {24, 35}, {36, 50}, {0, 7}, {8, 11}, {12, 15}, {16, 19}, {20, 23}, {24, 27}, {28, 31}, {32, 35}, {36, 38}, {39, 41}, {42, 46}, {47, 50}, {0, 0}, {1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9}, {10, 10}, {11, 11}, {12, 12}, {13, 13}, {14, 14}, {15, 15}, {16, 16}, {17, 17}, {18, 18}, {19, 19}, {20, 20}, {21, 21}, {22, 22}, {23, 23}, {24, 24}, {25, 25}, {26, 26}, {27, 27}, {28, 28}, {29, 29}, {30, 30}, {31, 31}, {32, 32}, {33, 33}, {34, 34}, {35, 35}, {36, 36}, {37, 37}, {38, 38}, {39, 39}, {40, 40}, {41, 41}, {42, 42}, {43, 43}, {44, 44}, {45, 45}, {46, 46}, {47, 47}, {48, 48}, {49, 49}, {50, 50}};
const std::string slotNames[numSlotTypes] = {"Any", "Random Town", "Random Neutral", "Random Coven", "Town Investigative", "Town Protective", "Town Killing", "Town Support", "Town Power", "Neutral Evil", "Neutral Killing", "Neutral Apocalypse", "Coven Power", "Coven Killing", "Coven Utility", "Coven Deception", "Coroner", "Investigator", "Lookout", "Psychic", "Seer", "Sheriff", "Spy", "Tracker", "Bodyguard", "Cleric", "Trapper", "Crusader", "Vigilante", "Veteran", "Trickster", "Deputy", "Amnesiac", "Admirer", "Tavern Keeper", "Retributionist", "Jailor", "Mayor", "Monarch", "Prosecutor", "Jester", "Executioner", "Pirate", "Doomsayer", "Serial Killer", "Arsonist", "Werewolf", "Shroud", "Plaguebearer", "Berserker", "Soul Collector", "Baker", "Coven Leader", "Hex Master", "Witch", "Conjurer", "Ritualist", "Jinx", "Potion Master", "Necromancer", "Poisoner", "Voodoo Master", "Wildling", "Medusa", "Illusionist", "Dreamweaver", "Enchanter"};
const std::string roleNames[numRoles] = {"Coroner", "Investigator", "Lookout", "Psychic", "Seer", "Sheriff", "Spy", "Tracker", "Bodyguard", "Cleric", "Trapper", "Crusader", "Vigilante", "Veteran", "Trickster", "Deputy", "Amnesiac", "Admirer", "Tavern Keeper", "Retributionist", "Jailor", "Mayor", "Monarch", "Prosecutor", "Jester", "Executioner", "Pirate", "Doomsayer", "Serial Killer", "Arsonist", "Werewolf", "Shroud", "Plaguebearer", "Berserker", "Soul Collector", "Baker", "Coven Leader", "Hex Master", "Witch", "Conjurer", "Ritualist", "Jinx", "Potion Master", "Necromancer", "Poisoner", "Voodoo Master", "Wildling", "Medusa", "Illusionist", "Dreamweaver", "Enchanter"};
const int necroPriority[numRoles] = {1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 0, 9, 4, 1, 13, 14, 11, 10, 3, 8, 5, 2, 12, 6, 7, };

bool isNumber(std::string s)    {
    return std::all_of(s.begin(), s.end(), ::isdigit);
}

int stringToSlotIndex(std::string s) {
    if (s.empty())  {
        std::cout << "A slot was empty, exiting\n";
        throw 30;
    }

    if (isNumber(s))    {
        return stoi(s);
    }

    // Find the index if the slot's name is used
    auto itr = std::find(slotNames, slotNames+numSlotTypes, s);
    return std::distance(slotNames, itr);
}

int stringToRole(std::string s) {
    if (s.empty())  {
        std::cout << "A role was empty, exiting\n";
        throw 30;
    }

    if (isNumber(s)) {
        return stoi(s);
    }

    // Find the index if the role's name is used
    auto itr = std::find(roleNames, roleNames + numRoles, s);
    return std::distance(roleNames, itr);
}

int generalTestFunction(long long numGenerations, std::vector<int> slotIndices, std::string factionFilename, std::string alignmentFilename, std::string roleFilename, bool isExcluded[], int threadNum=0, bool printing=true)  {
    // Initialise the truck load of data we need to store
    auto start = steady_clock::now();

    int numSlots = slotIndices.size();

    int slots[numSlots][2];

    for (int i=0; i<numSlots; ++i)  {
        slots[i][0] = slotNumbers[slotIndices[i]][0];
        slots[i][1] = slotNumbers[slotIndices[i]][1];
    }

    auto rng = std::mt19937(time(0)+threadNum);

    int factionCounts[numFactions];
    int alignmentCounts[numAlignments];
    int roleCounts[numRoles];
    int roles[numSlots];

    int factionsResult[numFactions][numSlots+1] = {0};
    int alignmentsResult[numAlignments][numSlots+1] = {0};
    int rolesResult[numAlignments][numSlots+1] = {0};

    std::vector<std::uniform_int_distribution<uint64_t>> generators;

    for (int i=0; i<numSlots; ++i)   {
        std::uniform_int_distribution<uint64_t> generator(slots[i][0],slots[i][1]);
        generators.push_back(generator);
    }

    int faction;
    int alignment;
    int generatedRole;
    int n;

    // Perform the generations
    for (long long i=0; i<numGenerations; ++i)  {
        std::fill(factionCounts, factionCounts+numFactions, 0);
        std::fill(alignmentCounts, alignmentCounts+numAlignments, 0);
        std::fill(roleCounts, roleCounts+numRoles, 0);

        for (int j=0; j<numSlots; ++j)  {
            // Loop until a valid role is generated
            // Worst case odds of exiting on a valid slot is (50/51)^10,000 ~ 10^-87
            n = 0;

            do {
                generatedRole = generators[j](rng);
                faction = roleFactions[generatedRole];
                ++n;
            }
            while (n < maxAttempts && (roleLimits[generatedRole] <= roleCounts[generatedRole] || factionLimits[faction] <= factionCounts[faction] || isExcluded[generatedRole]));


            if (n >= maxAttempts)   {
                std::cout << "Role list is impossible to generate!\n";
                throw 20;
            }

            alignment = roleAlignments[generatedRole];

            ++factionCounts[faction];
            ++alignmentCounts[alignment];
            ++roleCounts[generatedRole];
        }

        for (int faction=0; faction<numFactions; ++faction) {
            ++factionsResult[faction][factionCounts[faction]];
        }

        for (int alignment=0; alignment<numAlignments; ++alignment) {
            ++alignmentsResult[alignment][alignmentCounts[alignment]];
        }

        for (int role=0; role<numRoles; ++role) {
            ++rolesResult[role][roleCounts[role]];
        }
    }

    // Save the calculated data to disc
    if (factionFilename != "")  {
        std::ofstream factionOutputFile;
        factionOutputFile.open(factionFilename);

        for (int i=0; i<numSlots+1; ++i)   {
            for (int j=0; j<numFactions; ++j)    {
                factionOutputFile << factionsResult[j][i] << ",";
            }
            factionOutputFile << "\n";
        }

        factionOutputFile.close();
    }

    if (alignmentFilename != "")    {
        std::ofstream alignmentOutputFile;
        alignmentOutputFile.open(alignmentFilename);

        for (int i=0; i<numSlots+1; ++i)   {
            for (int j=0; j<numAlignments; ++j)    {
                alignmentOutputFile << alignmentsResult[j][i] << ",";
            }

            alignmentOutputFile << "\n";
        }

        alignmentOutputFile.close();
    }

    if (roleFilename != "") {
        std::ofstream roleOutputFile;
        roleOutputFile.open(roleFilename);

        for (int i=0; i<numSlots+1; ++i)   {
            for (int j=0; j<numRoles; ++j)    {
                roleOutputFile << rolesResult[j][i] << ",";
            }

            roleOutputFile << "\n";
        }

        roleOutputFile.close();
    }

    auto stop = steady_clock::now();

    if (printing)   {
        std::cout << "Thread " << threadNum << " finished after " << duration_cast<microseconds>(stop - start).count() << "us\n\n";
    }

    return 0;
}

int generalMultithreadedTestFunction(std::string inputFilename, bool printing=true, bool reading=true, long long totalNumGenerations=0, std::vector<int> slotIndices={}, std::string factionFilename="",
                                     std::string alignmentFilename="", std::string roleFilename="", std::string outputPath="", std::string factionSubpath="", std::string alignmentSubpath="",
                                     std::string roleSubpath="", std::vector<int> excludedRoles={}, int filenameOffset=0) {

    auto start = steady_clock::now();

    if (reading)   {
        std::string temp;
        int n = 0;
        std::string lines[11] = {"Number of games to generate", "Slots", "Faction data output filename", "Alignment data output filename", "Role data output filename",
        "Path for data to be written to", "Faction data folder", "Alignment data folder", "Role data folder", "Excluded roles", "Filename index offset"};

        // Get the necessary data from the input file
        std::ifstream inputFile;
        inputFile.open(inputFilename);

        while (getline(inputFile, temp))  {
            switch (n)  {
                case 0:
                    totalNumGenerations = (long long) stod(temp);   // stod is used because it accepts scientific notation
                    break;

                case 1:
                {
                    std::stringstream ss(temp);
                    std::string token;

                    while(std::getline(ss, token, ',')) {
                        slotIndices.push_back(stringToSlotIndex(token));
                    }

                    break;
                }


                case 2:
                    factionFilename = temp;
                    break;

                case 3:
                    alignmentFilename = temp;
                    break;

                case 4:
                    roleFilename = temp;
                    break;

                // These will updated to just accept 3 different paths
                case 5:
                    outputPath = temp;

                    if (outputPath[outputPath.length()-1] != '/')   {
                        outputPath = outputPath + "/";
                    }

                    break;

                case 6:
                    factionSubpath = temp;

                    if (factionSubpath[factionSubpath.length()-1] != '/')   {
                        factionSubpath = factionSubpath + "/";
                    }

                    break;

                case 7:
                    alignmentSubpath = temp;

                    if (alignmentSubpath[alignmentSubpath.length()-1] != '/')   {
                        alignmentSubpath = alignmentSubpath + "/";
                    }

                    break;

                case 8:
                    roleSubpath = temp;

                    if (roleSubpath[roleSubpath.length()-1] != '/')   {
                        roleSubpath = roleSubpath + "/";
                    }

                    break;

                case 9:
                {
                    std::stringstream ss(temp);
                    std::string token;

                    while(std::getline(ss, token, ',')) {
                        excludedRoles.push_back(stringToRole(token));
                    }

                    break;
                }

                case 10:    // This will be removed
                    filenameOffset = stoi(temp);
                    break;
            }

            if (printing)   {
                std::cout << lines[n] << ": " << temp << "\n";
            }

            ++n;
        }
    }

    int numSlots = slotIndices.size();
    factionLimits[0] = numSlots-1;
    factionLimits[1] = numSlots-1;

    // Accessing an array is much faster than searching a vector
    bool isExcluded[numRoles];
    std::fill(isExcluded, isExcluded+numRoles, false);

    for (auto i: excludedRoles) {
        isExcluded[i] = true;
    }

    std::vector<std::thread> threads;
    int numThreads = std::thread::hardware_concurrency();

    // This handles cases when numThreads does or does not divide totalNumGenerations
    // totalNumGenerations % numThreads <= numThreads, so a single thread having too much work will not become a bottleneck
    long long numGenerationsPerThread[numThreads];
    long long initialValue = (long long) totalNumGenerations / numThreads;

    std::fill(numGenerationsPerThread, numGenerationsPerThread+numThreads-1, initialValue);
    numGenerationsPerThread[numThreads-1] = initialValue + (totalNumGenerations % numThreads);

    // Run the computation using multithreading
    for (int i=0; i<numThreads; ++i)    {
        std::string factionPath = "";
        std::string alignmentPath = "";
        std::string rolePath = "";

        if (factionFilename != "")  {
            factionPath = outputPath + factionSubpath + factionFilename + std::to_string(i + filenameOffset) + ".csv";
        }

        if (alignmentFilename != "")    {
            alignmentPath = outputPath + alignmentSubpath + alignmentFilename + std::to_string(i + filenameOffset) + ".csv";
        }

        if (roleFilename != "") {
            rolePath = outputPath + roleSubpath + roleFilename + std::to_string(i + filenameOffset) + ".csv";
        }

        threads.push_back(std::thread(generalTestFunction, numGenerationsPerThread[i], slotIndices, factionPath, alignmentPath, rolePath, isExcluded, i, printing));
    }

    for (auto &th: threads) {
        th.join();
    }

    auto stop = steady_clock::now();
    return duration_cast<microseconds>(stop - start).count();
}

void profile(int numTrials, int step, std::string outputFilename=profilerFilename) {
    int numSlots = 15;
    std::vector<int> excludedRoles = {};
    std::vector<int> slotIndices;

    for (int i=0; i<numSlots; ++i)  {
        slotIndices.push_back(0);
    }

    std::ofstream outputFile;
    outputFile.open(outputFilename);

    for (int i=1; i<=numTrials; ++i) {
        long long N = i * step;
        std::cout << N << "(" << (int) 100 * i / numTrials << "%)\n";
        int time = generalMultithreadedTestFunction("", false, false, N, slotIndices, "", "", "", "", "", "", "", excludedRoles, 0);
        std::cout << time << "us\n\n";
        outputFile <<  N << "," << time << "\n";
    }

    outputFile.close();
}

void generateSingleRoleList(std::vector<int> slotIndices, std::vector<int> excludedRoles, std::string outputFilename) {
    auto rng = std::mt19937(time(0));

    int numSlots = slotIndices.size();
    factionLimits[0] = numSlots-1;
    factionLimits[1] = numSlots-1;

    int roles[numSlots];
    bool isExcluded[numRoles];
    int roleCounts[numRoles] = {};
    int factionCounts[numFactions] = {};
    std::fill_n(isExcluded, numRoles, false);
    int n;
    int role;
    int faction;

    for (auto role: excludedRoles)  {
        isExcluded[role] = true;
    }

    std::ofstream outputFile;
    outputFile.open(outputFilename);

    for (int i=0; i<numSlots; ++i)  {
        std::uniform_int_distribution<uint64_t> generator(slotNumbers[slotIndices[i]][0], slotNumbers[slotIndices[i]][1]);
        n = 0;

        do  {
            role = generator(rng);
            faction = roleFactions[role];
            ++n;
        }

        while (n < maxAttempts && (roleLimits[role] <= roleCounts[role] || factionLimits[faction] <= factionCounts[faction] || isExcluded[role]));

        if (n >= maxAttempts)   {
            outputFile << "Role list is impossible to generate!\n";
            outputFile.close();
            throw 20;
        }

        outputFile << roleNames[role] << "\n";
        ++roleCounts[role];
        int faction = roleFactions[role];
        ++factionCounts[faction];
    }
}

int main()  {
    std::ifstream inputFile;
    inputFile.open(inputFilename);

    std::string temp;
    int i = 0;

    getline(inputFile, temp);
    int mode = stoi(temp);
    ++i;
    std::string lines[11] = {"Number of games to generate", "Slots", "Faction data output filename", "Alignment data output filename", "Role data output filename",
        "Path for data to be written to", "Faction data folder", "Alignment data folder", "Role data folder", "Excluded roles", "Filename index offset"};

    switch (mode)   {
        case 0:
        {
            std::vector<int> slotIndices;
            std::vector<int> excludedRoles;

            while (getline(inputFile, temp)) {
                switch (i)  {
                    case 1:
                    {
                        std::stringstream ss(temp);
                        std::string token;

                        while(std::getline(ss, token, ',')) {
                            slotIndices.push_back(stringToSlotIndex(token));
                        }

                        break;
                    }
                    case 2:
                    {
                        std::stringstream ss(temp);
                        std::string token;

                        while(std::getline(ss, token, ',')) {
                            excludedRoles.push_back(stringToRole(token));
                        }

                        break;
                    }
                }

                ++i;
            }

            for (auto slot: slotIndices)    {
                std::cout << slot << ", ";
            }
            std::cout << "\n";

            generateSingleRoleList(slotIndices, excludedRoles, mainOutputFilename);

            break;
        }

        case 1:
        {
            long long totalNumGenerations = 0;
            std::vector<int> slotIndices;
            std::string factionFilename = "";
            std::string alignmentFilename = "";
            std::string roleFilename = "";
            std::string outputPath = "";
            std::string factionSubpath = "";
            std::string alignmentSubpath = "";
            std::string roleSubpath = "";
            std::vector<int> excludedRoles;
            int filenameOffset;

            while (getline(inputFile, temp))  {
                std::cout << lines[i-1] << ": " << temp << "\n";
                switch (i-1)  {
                    case 0:
                        totalNumGenerations = (long long) stod(temp);   // stod is used because it accepts scientific notation
                        break;

                    case 1:
                    {
                        std::stringstream ss(temp);
                        std::string token;

                        while(std::getline(ss, token, ',')) {
                            slotIndices.push_back(stringToSlotIndex(token));
                        }

                        break;
                    }


                    case 2:
                        factionFilename = temp;
                        break;

                    case 3:
                        alignmentFilename = temp;
                        break;

                    case 4:
                        roleFilename = temp;
                        break;

                    // These will updated to just accept 3 different paths
                    case 5:
                        if (temp[temp.length()-1] != '/')   {
                            temp = temp + "/";
                        }

                        outputPath = temp;
                        break;

                    case 6:
                        if (temp[temp.length()-1] != '/')   {
                            temp = temp + "/";
                        }

                        factionSubpath = temp;

                        break;

                    case 7:
                        if (temp[temp.length()-1] != '/')   {
                            temp = temp + "/";
                        }

                        alignmentSubpath = temp;
                        break;

                    case 8:
                        roleSubpath = temp;

                        if (roleSubpath[roleSubpath.length()-1] != '/')   {
                            roleSubpath = roleSubpath + "/";
                        }

                        break;

                    case 9:
                    {
                        std::stringstream ss(temp);
                        std::string token;

                        while(std::getline(ss, token, ',')) {
                            excludedRoles.push_back(stringToRole(token));
                        }

                        break;
                    }

                    case 10:    // This will be removed
                        filenameOffset = stoi(temp);
                        break;

                }
                ++i;
            }
            generalMultithreadedTestFunction("", true, false, totalNumGenerations, slotIndices, factionFilename, alignmentFilename, roleFilename, outputPath, factionSubpath,
                                                 alignmentSubpath, roleSubpath, excludedRoles, filenameOffset);
            break;
        }

        case 2:
        {
            int numTrials = 500;
            int step = 5000;
            std::string outputFilename = profilerFilename;
            while (getline(inputFile, temp))    {
                switch (i)  {
                    case 1:
                        numTrials = (int) stod(temp);

                    case 2:
                        step = (int) stod(temp);
                }
                ++i;
            }

        profile(numTrials, step);
        }
    }

    inputFile.close();
    return 0;
}
