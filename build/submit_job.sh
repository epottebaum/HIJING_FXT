#!/bin/bash

#SBATCH --job-name=genHijingEvents
#SBATCH --mail-type=FAIL

./Hij hijout.root
