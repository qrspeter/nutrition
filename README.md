# nutrition
Nutrition calculator


Calculate daily macronutrients from files with daily diet (one day - one file).

Daily diet file stricture is csv: FoodName, amount (g), energy (kkal), protein (g), fat (g), carbs (g).
The fields are separated by comma.

Result is shown on a screen and saved into *.txt file (nutrition_pd.txt for Python and nutrition_pdd.txt for c++).
nutrition_pd.pkl is a Pandas dataframe with output data.

Python and c++ versions do almost the same and used the same data.

Created in Python 3.10.11 and MinGW-W64 13.2.0.