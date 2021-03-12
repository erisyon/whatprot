# -*- coding: utf-8 -*-
"""
@author: Matthew Beauregard Smith (UT Austin)
"""

from numpy import concatenate
from numpy import load
from numpy import transpose
from numpy import zeros

NUM_CHANNELS_IN = 1
NUM_CHANNELS_OUT = 3
NUM_MOCKS = 3
NUM_CYCLES = 9
CUTOFF = 1000
RADMAT_FILE = 'C:/Users/Matthew/ICES/MarcotteLab/data/classification/abbe16_1e/abbe16_1e_radmat.npy'
OUTPUT_FILE = 'C:/Users/Matthew/ICES/MarcotteLab/data/classification/abbe16_1e/radiometries.tsv'

radmat = load(RADMAT_FILE)

radmat = transpose(radmat, (1, 3, 2, 0))
radmat = radmat.reshape(radmat.shape[0],
                        radmat.shape[1] * radmat.shape[2],
                        radmat.shape[3])

fixedrads = zeros(0).reshape(0, radmat.shape[1])
nondark_sum = 0.0
nondark_count = 0
for rad in radmat:
    # This is necessary because for some reason reshaping radmat doesn't
    # reshape the contained ndarrays.
    rad = rad.reshape(radmat.shape[1], radmat.shape[2])
    fixedrad = zeros(rad.shape[0])
    isok = True
    isdark = False
    for i in range(len(rad)):
        # See if this is a dark cycle. If it is we don't have to do anything,
        # fixedrad at i is already 0. If not we need to copy it over.
        if rad[i][0] > CUTOFF:
            # Here we check the aspect ratio of the peak on the slide. If this
            # value is too high it indicates there is probably two peptides
            # there and we should throw out this result.
            if rad[i][1] > 1.5 or rad[i][1] == 0:
                isok = False
                break
            # Here we check that we haven't already seen a dark cycle. If we
            # have, something is wrong. THIS WILL NOT WORK WITH MORE CHANNELS
            # need to fix....
            if isdark:
                isok = False
                break
            fixedrad[i] = rad[i][0]
            nondark_sum += rad[i][0]
            nondark_count += 1
        else:
            # Throw out if all results are dark, or if first result is dark
            # and laters aren't (see above)
            if i == NUM_MOCKS:
                isok = False
                break
            isdark = True
    if isok:
        fixedrads = concatenate((fixedrads, fixedrad.reshape(1, rad.shape[0])), 0)
fixedrads = fixedrads.reshape(fixedrads.shape[0], NUM_CYCLES, NUM_CHANNELS_IN)
# Cut off mock edmans.
fixedrads = fixedrads[:,NUM_MOCKS:,:]
fixed_num_cycles = NUM_CYCLES - NUM_MOCKS
# Normalize intensities (this will break if the dye count is higher than 1)
mu = nondark_sum / nondark_count
fixedrads = fixedrads / mu

f = open(OUTPUT_FILE, 'w')
f.write(str(fixed_num_cycles) + "\n")
f.write(str(NUM_CHANNELS_OUT) + "\n")
f.write(str(fixedrads.shape[0]) + "\n")
for fixedrad in fixedrads:
    for i in range(fixed_num_cycles):
        for j in range(NUM_CHANNELS_IN):
            if i > 0 or j > 0:
                f.write("\t")
            f.write(str(fixedrad[i, j]))
        # Write data for fake extra channels.
        for j in range(NUM_CHANNELS_IN, NUM_CHANNELS_OUT):
            f.write("\t0.0")
    f.write("\n")
f.close()
