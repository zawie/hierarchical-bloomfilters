# 🌸 Hierarchical Bloomfilters
This was a research project for a graduate level course at Rice University: COMP 580, probabilistic data structures and algorithms.

## 🔎 Code
The experiment code is written in bash and can be found in the `./experiments` directory. The code to generate the plots can be found in `./plots`. The experiment scripts automatically call these scripts to generate the plots.

The actual bloom filters are implemented in C and can be found in the `./code/src` directory.

When compiled, the main, standard bloom filter, and hierarchical bloom filter are compiled seperately and linked to gather afterwords. Optimization is disable as well, so this should minimize any performance increases due to different compilations.

## 🚀 How to run
Simply run `make run_fast` for a quick execution of all the tests. These are not the settings used in the final report, but are used to validate the functionaltiy of the scripts.
To generate data used in the reportm run `make run_full`. Both of these commands will generate .dat files in `./experiments/dats` and plots in `./plots`.
Note, only one of each plot will be preserved, while the `.dats` will be preserved until deleted.

## 📝 Writeup
The PDF of the writeup as well sa the source tex files for can be found in the `./writeup` directory.
