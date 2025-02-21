#!/bin/bash

#SBATCH --job-name=hijingcpp_array # name of job
#SBATCH --mail-type=FAIL # send email if job fails
#SBATCH --requeue # allow job to be restarted if eg a node fails or something
#SBATCH --time=1:00:00 # set time limit for a job (default is 1 hour, 1:00:00)
#SBATCH --array=0-9 # 0-500%20 -> submit the same job 500 times, with 20 jobs running at a time
#SBATCH --output=/vast/palmer/scratch/havener/egp28/slurm-out/hijingcpp_C_10p5GeV_%A-%a.out

./Hij hijout_100k_minbias_FXT_13p7GeV/hijout_10k_"$SLURM_ARRAY_TASK_ID".root
