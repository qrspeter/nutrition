#include "nutrition.h"


void Nutrition::print_macronutrients(const macronutrients &mac)
{
    /*
    for(size_t i = 0; i < mac.size(); i++)
    {
       std:: cout << nutr_names[i] << ": " << mac[i];
        if(i < mac.size() - 1)
            std::cout << ", ";
    } 
    */
    for(auto & m : mac) 
    std::cout << m << ' ';
    std::cout << '\n';
}

macronutrients Nutrition::load_file(const std::filesystem::path &filename)
{
    std::array<float, NUTR> total_f{}, temp{};
    macronutrients total{};
    std::ifstream infile(filename);
    std::string line;
    //std::cerr << filename << '\n';
    while(std::getline(infile, line))
    {
        if(line.empty() ||line[0] == '#' || line[0] == '\r' || line[0] == '\n') //  
        continue;

        //std::array<float, NUTR> temp{};
        //std::cerr << line << '\n';        
        auto pos = line.find(',') + 1;
        std::string nutr = line.substr(pos);
        std::istringstream iss {nutr}; // std::string_view is better
        std::string s;
        std::getline(iss, s, ',');
        float weigth = std::stof(s);
        //std::string nutr = line.substr(line.find(',', pos) + 1);
        //std::istringstream iss {nutr}; // std::string_view is better
        //std::string s;
        for(auto i = 0; i < NUTR; ++i)
        {
            std::getline(iss, s, ',');
            //std::cerr << i << ':' << s << ' ';
            temp[i] = weigth * std::stof(s) / 100;
        }
        std::transform(total_f.begin(), total_f.end(), temp.begin(), total_f.begin(), std::plus<float>()); // [](int a_, int b_) {return a_+ b_;}
        std::fill(std::begin(temp), std::end(temp), 0);
    }
    std::transform(total_f.begin(), total_f.end(), total.begin(), [](float a){return static_cast<int>(a);});

    return total;
}

std::vector<macronutrients> Nutrition::load_files(const std::string &folder)
{
    std::vector<macronutrients> data;
    
    for(const auto& entry : std::filesystem::directory_iterator(folder))
    {
        std::filesystem::path filepath = entry.path();
        if(filepath.extension() == ".csv")
        filenames.push_back(filepath);
        
        // print here filename + nutr into a file, line by line
        
    }


    std::sort(filenames.begin(), filenames.end());

    for(const auto& f : filenames)
    {
        //data.push_back(load_file(p));
        auto filename = std::filesystem::path(f).stem();
        
        macronutrients day_nutr;

        try
        {
            day_nutr = load_file(f);
        }
        catch(std::invalid_argument const& ex)
        {
            std::cout << "Error while processing " << filename << ": " << ex.what() << '\n';
            continue;
        }
        
        std::cerr << filename << ' ';
        print_macronutrients(day_nutr);
        data.push_back(day_nutr);

    }


    return data;
}

void Nutrition::save2pdd(const std::vector<macronutrients> &data, const std::filesystem::path &filename)
{

    std::string foutput{filename.generic_string()}; // {"./nutrition_pdd.txt"}; //filename};
    
    std::ofstream fsave;
    fsave.open(foutput, std::ios::out); 
    if (fsave.is_open())
    {
        /*
        for(const auto & d : data)
        {
            for(auto i = 0; i < NUTR; i++)
            {
                fsave << d[i];
                if(i != NUTR-1) fsave << ',';
            }
            fsave << '\n';
        }
        */
        for(size_t j = 0; j < data.size(); j++)
        {
            auto filename = std::filesystem::path(filenames[j]).stem();
            fsave << filename.generic_string();
            for(auto i = 0; i < NUTR; i++)
            {
                fsave << ',';
                fsave << data[j][i];
            }
            fsave << '\n';            
        }
        
        
        fsave << "# Averaged: \n";
        auto aver = averaged(data);
        for(auto i = 0; i < NUTR; i++)
        {
            fsave << "# " << nutr_names[i] << ": " << aver[i] << '\n';
            if(i != NUTR - 1) fsave << ',';
        }
            
    }
    fsave.close();


}


macronutrients Nutrition::averaged(const std::vector<macronutrients> &data)
{
    macronutrients aver{};
    for(auto const & d : data)
    {
        for(auto i = 0; i < NUTR; i++) // 
        aver[i] += d[i];
    }
    
    //print_macronutrients(aver);
    std::transform(aver.begin(), aver.end(), aver.begin(), [&data](auto &i){return i/data.size();});
    //for(auto i = 0; i < NUTR; i++)
    //aver[i] = aver[i]/data.size();
    return aver;
}

bool Nutrition::test()
{
    bool result = true;
    macronutrients m1 {10,1,100,1000};
    
    macronutrients m2 {30,3,300,3000};
    //macronutrients m3 {};
    macronutrients m1m2 {20,2,200,2000};
    macronutrients av = averaged(std::vector{m1, m2, m1, m2});
    //if(!std::equal(std::begin(av), std::end(av), std::begin(m1m2)))
    if(!(av == m1m2)) // std::mismatch
    {
        print_macronutrients(av); print_macronutrients (m1m2);
        result = false;
    }
    
    return result;
}
