import sys, os
import numpy as np
import matplotlib.pyplot as plt

par_lambda = float(sys.argv[1])
print('Lambda:', par_lambda)

n_samples = int(sys.argv[2])
print('Nº de amostras:',n_samples)

#generate exponential distribuited numbers
x = np.random.exponential(1/par_lambda, n_samples) 

#histogram
#set parameters
vmin=0
vmax=5/par_lambda
delta=1/5*1/par_lambda
bin_size = round((vmax-vmin)/delta)

#plot
_ = plt.hist(x, bins=bin_size, range=(vmin,vmax)) 
plt.title("Histogram")
plt.show()