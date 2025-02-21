Largely taken from https://github.com/niseem-magdy/Niseem_Hij_HepMC3/tree/main
modified to not use HepMC and go directly from HIJING to ROOT
(HepMC is inevitable. -EP Feb 2025)

hijingcpp.cxx outputs HIJING events as a ROOT TTree
hijingHep.cxx outputs HIJING events as a HepMC3 (ascii) file
hijingHepROOT.cxx outputs HIJING events as both a TTree and HepMC3 file


Initial compile and to compile after changing CMakeLists:
$ cd build
$ cmake ..
$ cmake --build .

To compile after editing .cxx file, do
$ cd build
$ cmake --build .

This should create an executable in the build directory that you can run. The config_file_name parameter is optional (default is hijing_config.txt)
hijingcpp.cxx: ./Hij output_file_name.root config_file_name
hijingHep.cxx: ./HijHep output_file_name.hepmc config_file_name
hijingHepROOT.cxx: ./HijHepRoot hepmc_outfile.hepmc root_outfile.root config_file_name

hijingcpp.cxx and hijingHep.cxx currently put the output file in /gpfs/gibbs/project/havener/egp28/HIJING-out, might add an option to more easily change the output path later
hijingHepROOT.cxx sends output to /vast/palmer/scratch/havener/egp28/HIJING-out

hijing_config.txt contains the HIJING parameters that will be used if no config file is specified when running the executable. 

VERSIONS
current: hijingcpp.cxx, hijingHep.cxx, hijingHepROOT.cxx
Oct 15 2024: hijingcpp_v1.cxx






