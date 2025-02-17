import numpy as np
import matplotlib.pyplot as plt
import os  

import pandas as pd


def load_file(filename) -> list:
    try:
        data = np.loadtxt(filename, usecols=(1,2,3,4,5), delimiter=',')
    except ValueError:
        print('Loading error in', filename)
        return None
    for d in data:
        for n, i in enumerate(d[1:]):
            d[n+1] = d[1+n] * d[0]/100
    #print(data)
    total = np.sum(data[:,1:], axis=0)
    if check_daily(total) == False:
        print(f'{filename.split(".")[-2:]} daily warning')
    return total.astype('int').tolist()


def load_files(path) -> dict:
    filelist = [f for f in os.listdir(path) if os.path.isfile(path + f)]
    assert len(filelist) > 0, "No files in folders"
    filelist.sort()
    data = {}
    for filename in filelist:
        name = filename.split('.')
        if name[-1] == 'csv' and name[0].startswith('2025'):
            data[name[0]] = load_file(path + filename)
            
    # data = []
    # for name in filelist:
        # if name.split('.')[1] == 'csv':
            # data.append(load_file(name))
            
    return data

def averaged(data: dict) -> list:
    list_of_data = list(data.values())
    total = []
    for n,_ in enumerate(list_of_data[0]):
        summ = 0
        for i in list_of_data:
            summ += i[n]
        aver = summ // len(list_of_data)
        total.append(aver)
    return(total)
    
    
def check_daily(daily: list) -> bool:
    check = True
    norm = {'Energy': 2500, 'Protein': 100, 'Fat':80, 'Carbs':400}
    for d, n in zip(daily, norm):
        if d < 0.3*norm[n] or d > 1.5*norm[n]:
            #print(f'{n} error')
            check = False
    return check
    
assert check_daily([2500, 100, 80, 400]), "Daily check error"
assert check_daily([100, 100, 800, 40]) == False, "Daily check error"

'''
def print_data(data: dict) -> None:
    for d in data:
        lst = [str(i) for i in data[d]]
        line = '\t'.join(lst)
        print(f'{d}: \t{line}')
'''        

'''
test = load_file(path + '20250117.csv')
assert (test[0] > 1000 and test[0] < 4000), 'Energy error' 
assert (test[1] > 30 and test[1] < 150), 'Protein error' 
assert (test[2] > 20 and test[2] < 150), 'Fat error' 
assert (test[3] > 200 and test[3] < 500), 'Carbs error' 
'''
'''
for n,i in enumerate(macronutrients):
    assert (test[n] > 10 and test[n] < 5000), i + ' error'
'''


if __name__ == "__main__":
    
    path = './data/' 
    macronutrients = ['Energy', 'Protein', 'Fat', 'Carbs']
    data = load_files(path)
    #pprint.pprint(data)
    #print_data(data)
    #aver = averaged(data)
    #print(aver)
    #print_data({'Avraged is': aver})
    
    
    df = pd.DataFrame.from_dict(data, orient='index', columns=macronutrients)
    print(df)

    
    mean = df.mean().apply(lambda x: int(x))
    print('Averaged:\n', mean)
    df_filename = 'nutrition_pd'
    df.to_pickle(path + df_filename + '.pkl')
    df.to_csv(path + df_filename + '.txt')

    if df.shape[0] > 6:
        days_average = 7
        mean_week = df[-days_average:].mean().apply(lambda x: int(x))
        mean_week.to_csv(path + df_filename + '.txt', mode='a')
        print(f'{days_average} days averaged:\n', mean_week)
    #mean.to_csv(path + df_filename + '.txt', mode='a')

'''
replacement lists to pandas:
df = pd.DataFrame(columns=macronutrients)
for n,filename in enumerate(filelist):
    df.loc[n] = [filename] + load_file(path + filename)
'''
