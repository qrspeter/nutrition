# Nutrition calculator


Calculate daily macronutrients from files with daily diet (one day - one file).

Daily diet files are csv, the fields are separated by comma: 

  FoodName, amount (g), energy (kkal/100g), protein (g/100g), fat (g/100g), carbs (g/100g).
 
Examples are in ./data/.

Result is shown in terminal and saved into *.txt file (nutrition_pd.txt for Python and nutrition_pdd.txt for c++), and into nutrition_pd.pkl is a Pandas dataframe (for Python version).

Python and c++ versions do almost the same and used the same data.

Created in Python 3.10.11 and GCC 13.2.0 (and MinGW-W64 13.2.0 in Windows).


### Usage:

- Run "python main.py"
- Run main.exe in Windows (or mingw32-make -f Makefile_win to compile)
- Run ./main in Linux (or make to compile)