import numpy as np

def calculate(list1):
    if len(list1) != 9:
        raise ValueError("List must contain nine numbers.")
    
    acc_array = np.array(list1).reshape(3,3)

    mean = [list(np.mean(acc_array, axis = 0)), list(np.mean(acc_array, axis = 1)), np.mean(acc_array)]
    variance = [list(np.var(acc_array, axis = 0)), list(np.var(acc_array, axis = 1)), np.var(acc_array)]
    std_dev = [list(np.std(acc_array, axis = 0)), list(np.std(acc_array, axis = 1)), np.std(acc_array)]
    max_value = [list(np.max(acc_array, axis = 0)), list(np.max(acc_array, axis = 1)), np.max(acc_array)]
    min_value = [list(np.min(acc_array, axis = 0)), list(np.min(acc_array, axis = 1)), np.min(acc_array)]
    sum_value = [list(np.sum(acc_array, axis = 0)), list(np.sum(acc_array, axis = 1)), np.sum(acc_array)]

    calculations = {
        'mean': mean,
        'variance': variance,
        'standard deviation': std_dev,
        'max': max_value,
        'min': min_value,
        'sum': sum_value
    }

    return calculations
