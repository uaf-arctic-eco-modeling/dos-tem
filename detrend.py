#!/usr/bin/env python

# Tobey Carman
# Feb 2018
# Script to remove the trend from some older style climate inputs from Helene.


# THIS SCRIPT WILL MODIFY THE FILES IN PLACE!
# 
# So if you aren't sure what you are doing, you might want to make a copy
# of the files first to work on, like this:
#
#     $ mkdir /workspace/Shared/Tech_Projects/dvmdostem/feb6-detrend-for-helene
#     $ cd /workspace/Shared/Tech_Projects/dvmdostem/feb6-detrend-for-helene/
#     $ cp /atlas_scratch/hgenet/cru_* .
# 
# I never actually ran the file as a script, but was pasting pieces of this
# into an IPython shell. Especially handy to control the plotting.


import os
import netCDF4 as nc
import numpy as np
import scipy.signal
import matplotlib.pyplot as plt
import matplotlib.gridspec as gridspec

files = '''
cru_cccma_a1b_BP_gf.nc  cru_cccma_b1_BP_gf.nc    cru_echam5_a2_BP_gf.nc
cru_cccma_a2_BP_gf.nc   cru_echam5_a1b_BP_gf.nc  cru_echam5_b1_BP_gf.nc
'''.strip().split()

variables='''NIRR PREC TAIR VAPO'''.split()


for file in files[:]:
  ds = nc.Dataset(file, 'a')
  for var in variables[:]:
    print "Working on variable: {}".format(var)
    data = ds.variables[var]
    dtd = scipy.signal.detrend(data, axis=1)
    offset = data[:,0,:] - dtd[:,0,:]
    exp_offset = np.expand_dims(offset, axis=1)
    # Demo of np.expand_dims(...)
    # a = np.ones((7,4,3))
    # b = np.expand_dims(a[:,0,:],axis=1)
    # print a+b
    dtd_ofst = dtd + exp_offset

    ########## PLOTTING ##########
    ROWS=4
    COLS=3

    # Total hack to provide 1D index 
    d1idx = np.arange(ROWS*COLS).reshape((ROWS,COLS))

    gs = gridspec.GridSpec(ROWS, COLS)
    fig = plt.figure(file, figsize=(12,12)) # <- width, height, in inches

    for r in range(0, ROWS):
      for c in range(0, COLS):
    
        CHTID=0
        MONTH=d1idx[r,c]
    
        ax = plt.subplot(gs[r,c])
        ax.set_title('var: {} chtid: {} month: {}'.format(var, CHTID, MONTH))
        ax.plot(data[CHTID,:,MONTH], label='orig', color='black')
        ax.plot(dtd[CHTID,:,MONTH], label='dtd', color='blue')
        ax.plot(dtd_ofst[CHTID,:,MONTH], label='dtd-ofst', color='red')

    plt.tight_layout()
    #plt.show() # <- Enable if you want to stop and inspect each file/variable!!
      
    # THIS PART HERE DOES THE OVERWRITING!!!
    print "OVERWRITING data!"
    data[:] = dtd_ofst[:]

  print "Closing file! {}".format(file)
  ds.close()    
  
###############################################

#!/usr/bin/env python

# Tobey Carman
# Feb 2018
# Script to compare files before and after applying detrending (above)

# I never actually ran the file as a script, but was pasting pieces of this
# into an IPython shell. Especially handy to control the plotting.

import os
import netCDF4 as nc
import numpy as np
import matplotlib.pyplot as plt
import matplotlib.gridspec as gridspec

oldpath = '/atlas_scratch/hgenet/'
newpath = '/workspace/Shared/Tech_Projects/dvmdostem/feb6-detrend-for-helene/'
files = '''
cru_cccma_a1b_BP_gf.nc  cru_cccma_b1_BP_gf.nc    cru_echam5_a2_BP_gf.nc
cru_cccma_a2_BP_gf.nc   cru_echam5_a1b_BP_gf.nc  cru_echam5_b1_BP_gf.nc
'''.strip().split()

for file in files[:]:
  old = os.path.join(oldpath, file)
  new = os.path.join(newpath, file)

  oldds = nc.Dataset(old)
  newds = nc.Dataset(new)

  for var in 'TAIR PREC NIRR VAPO'.split():
  
    olddata = oldds.variables[var]
    newdata = newds.variables[var]

    ROWS=4
    COLS=3

    # Total hack to provide 1D index 
    d1idx = np.arange(ROWS*COLS).reshape((ROWS,COLS))

    gs = gridspec.GridSpec(ROWS, COLS)
    fig = plt.figure(file, figsize=(12,12)) # <- width, height, in inches

    for r in range(0, ROWS):
      for c in range(0, COLS):

        CHTID=997
        MONTH=d1idx[r,c]

        ax = plt.subplot(gs[r,c])
        ax.set_title('var: {} chtid: {} month: {}'.format(var, CHTID, MONTH))
        ax.plot(olddata[CHTID,:,MONTH], label='orig', color='black')
        ax.plot(newdata[CHTID,:,MONTH], label='dtd-ofst', color='red')

    plt.tight_layout()
    if not os.path.exists('before-after-plots/chtid-{:04d}'.format(CHTID)):
      os.makedirs('before-after-plots/chtid-{:04d}'.format(CHTID))
    plt.savefig('before-after-plots/chtid-{:04d}/{}__{}.pdf'.format(CHTID, file, var))
    #plt.show()
  
 
