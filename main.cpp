/* to do:
 * - sort files
 * -print all data into text (like a pandas) with filenames (in load_files)
 * - check output to find problems with averaged data - the one is overvaluated...
 * - error is somewhere in summ of data from files, averaging is correct and even tested...
 * - so check transform and std::plus<float>()... clean the temp array....
 */


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
/*
    std::vector<macronutrients> first_week(total_data.begin(), total_data.begin() + 7);
    aver7 = averaged(first_week);
    print_macronutrients(aver7);    
    std::vector<macronutrients> first_day(total_data.begin(), total_data.begin() + 1);
    aver7 = averaged(first_day);
    print_macronutrients(aver7); 
    std::vector<macronutrients> last_day(total_data.end() - 1 , total_data.end());
    aver7 = averaged(last_day);
    print_macronutrients(aver7); 
*/
}
