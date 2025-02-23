#ifndef NUTRITION
#define NUTRITION

#include <iostream>
#include <fstream>
#include <vector>
#include <cassert>
#include <array>
#include <sstream>
#include <algorithm>
#include <filesystem>
#include <stdexcept>

#define NUTR    4

using macronutrients = std::array<int, NUTR>;

class Nutrition
{

    //const int NUTR = 4;
    const std::array<std::string, NUTR> nutr_names = {"Energy", "Protein", "Fat", "Carb"};

    macronutrients load_file(const std::filesystem::path &filename);
    std::vector<std::filesystem::path> filenames;


  public:
    macronutrients averaged(const std::vector<macronutrients> &data);
    void print_macronutrients(const macronutrients &mac);
    bool test();
    std::vector<macronutrients> load_files(const std::string &folder);

    void save2pdd(const std::vector<macronutrients> &data, const std::filesystem::path &filename = "./nutrition_pdd.txt");

};

#endif