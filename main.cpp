#include <iostream>
#include <vector>
#include <cassert>

#include "nutrition.h"

int main(int argc, char* argv[])
{
    Nutrition Nutr;
    assert(Nutr.test() && "test failed");

    std::string path = "./data/";
    std::string pdd_filemane = "nutrition_pdd.txt";
    if(argc > 1)
        path = argv[1];  
        
    auto total_data = Nutr.load_files(path);
    auto aver = Nutr.averaged(total_data);
    std::cout << "Total averaged: \n";
    Nutr.print_macronutrients(aver);
    if(total_data.size() > 6)
    {
        std::vector<macronutrients> last_week(total_data.end() - 7, total_data.end()); 
        macronutrients aver7 = Nutr.averaged(last_week);
        std::cout << "Last week: \n";
        Nutr.print_macronutrients(aver7);
    }
    Nutr.save2pdd(total_data, path + pdd_filemane);

}
