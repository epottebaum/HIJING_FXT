// attempt to generate hijing events from a c++ program
// Sep 16, 2024 (v1)
// Oct 15, 2024 (v2) - removed some unnecessary branches
// Dec 13, 2024, v3 (current):
// 	isParticipant/fIsParticipant changed to fromParticipant/fFromParticipant
// 	numChargedParticipants branch removed
// 	deleted some commented out lines from previous versions
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <cmath>
#include <string>
#include <map>
#include <random>
#include <chrono>
#include <csignal>

#include "TROOT.h"
#include "TFile.h"
#include "TTree.h"
#include "TMath.h"
#include "TLorentzVector.h"

#include "HepMC3/GenEvent.h"


#define f2cFortran
#define gFortran
#include <cfortran.h>

// I believe here we are essentially initializing instances of the Fortran
// subroutines that will be used
extern "C" {
	void hijset_(float* efrm, char* frame, char* proj, char* targ, int* iap, int* izp, int* iat, int* izt);
}
#define HIJSET hijset_

extern "C" {
	void hijing_(char* FRAME, float* BMIN, float* BMAX);
}
#define HIJING hijing_

extern "C" {
	int luchge_(int*);
}
#define luchge luchge_

extern "C" {
	extern struct{
		int natt;
		int eatt;
		int jatt;
		int nt;
		int np;
		int n0;
		int n01;
		int n10;
		int n11;
	}himain1_;
}
#define himain1 himain1_

extern "C" {
	extern struct{
		int katt[4][130000];
		float patt[4][130000];
		float vatt[4][130000];
	}himain2_;
}
#define himain2 himain2_

extern "C" {
	extern struct{
		float vatt[4][130000];
	}himain3_;
}
#define himain3 himain3_

extern "C" {
	extern struct{
		float hipr1[100];
		int ihpr2[50];
		float hint1[100];
		int ihnt2[50];
	}hiparnt_;
}
#define hiparnt hiparnt_

extern "C" {
	extern struct{
		int nfp[15][300];
		float pp[15][300];
		int nft[15][300];
		float pt[15][300];
	}histrng_;
}
#define histrng histrng_

extern "C" {
	extern struct{
		float yp[300][3];
		float yt[300][3];
	}hijcrdn_;
}
#define hijcrdn hijcrdn_

extern "C" {
	extern struct{
		int nseed;
	}ranseed_;
}
#define ranseed ranseed_


std::string config_file = "../hijing_config.txt";
int main(int argc, char **argv)
{
	if (argc < 2) {	
		std::cout << "Usage: " << argv[0] << " output_file_name.root" << std::endl;
		std::cout << "To specify config file: " << argv[0] << " output_file_name.root config_file_name" << std::endl; 
		return 1;
	}

	std::string output_file = argv[1];
	if (argc == 3) {
		std::string config_file = argv[2];
	}

	std::ifstream infile(config_file);
	
	// load parameters from config file
	// make this more efficient?
	std::string line;
	std::getline(infile, line); // get the first line
	std::string outdir = line.c_str(); // first line is output directory

	int intpar[8];
	float flopar[3];

	for (int i = 0; i < 8; i++) {
		std::getline(infile, line, ' ');	
		intpar[i] = std::stoi(line.c_str());
		std::getline(infile, line); // skip to end of line
	}

	for (int i = 0; i < 3; i++) {
		std::getline(infile, line, ' ');
		flopar[i] = std::stof(line.c_str());
		std::getline(infile, line);
	}

	// structured bindings my beloved
	auto [N_EVENT, FRAMEID, PROJID, TARGID, IAP, IZP, IAT, IZT] = intpar;
	auto [EFRM, BMIN, BMAX] = flopar;

	infile.close();

	char FRAME[2][9];
	std::strcpy(FRAME[0], "CMS     ");
	std::strcpy(FRAME[1], "LAB     ");

	char PROJ[7][9];
	std::strcpy(PROJ[0], "P       ");
	std::strcpy(PROJ[1], "PBAR    ");
	std::strcpy(PROJ[2], "N       ");
	std::strcpy(PROJ[3], "NBAR    ");
	std::strcpy(PROJ[4], "PI+     ");
	std::strcpy(PROJ[5], "PI-     ");
	std::strcpy(PROJ[6], "A       ");
	
	char TARG[7][9];
	std::strcpy(TARG[0], "P       ");
	std::strcpy(TARG[1], "PBAR    ");
	std::strcpy(TARG[2], "N       ");
	std::strcpy(TARG[3], "NBAR    ");
	std::strcpy(TARG[4], "PI+     ");
	std::strcpy(TARG[5], "PI-     ");
	std::strcpy(TARG[6], "A       ");


	// Initialize ROOT stuff
	std::string outfile = outdir + output_file;
	TFile f(outfile.c_str(), "recreate"); // output file
	TTree *hijTree = new TTree("hijTree","hijTree");
		
	// initialize variables to be placed in branches
	int eventNum = 0;
	int numParticles = 0;
	float b = 0.;
	int fPartNum[80000] = {0};
	int fFlavCode[80000] = {0}; // better way to handle initializing the size?
	int fSource[80000] = {0};
	int fStatus[80000] = {0};
	int fCharge[80000] = {0};
	int fFromParticipant[80000] = {0};
	float fEn[80000] = {0};
	float fP[80000] = {0};
	float fPt[80000] = {0}; 
	float fY[80000] = {0};
	float fEta[80000] = {0}; 
	float fTheta[80000] = {0};
	float fPhi[80000] = {0};	

	// Initialize TTree branches
	hijTree->Branch("eventNum", &eventNum, "eventNum/I");
	hijTree->Branch("numParticles", &numParticles, "numParticles/I");
	hijTree->Branch("b", &b, "b/F");
	hijTree->Branch("fPartNum", fPartNum, "fPartNum[numParticles]/I");
	hijTree->Branch("fFlavCode", fFlavCode, "fFlavCode[numParticles]/I");
	hijTree->Branch("fSource", fSource, "fSource[numParticles]/I");
	hijTree->Branch("fStatus", fStatus, "fStatus[numParticles]/I");
	hijTree->Branch("fCharge", fCharge, "fCharge[numParticles]/I");
	hijTree->Branch("fFromParticipant", fFromParticipant, "fFromParticipant[numParticles]/I");
	hijTree->Branch("fEn", fEn, "fEn[numParticles]/F");
	hijTree->Branch("fP", fP, "fP[numParticles]/F");
	hijTree->Branch("fPt", fPt, "fPt[numParticles]/F");
	hijTree->Branch("fY", fY, "fY[numParticles]/F"); // rapidity
	hijTree->Branch("fEta", fEta, "fEta[numParticles]/F");
	hijTree->Branch("fTheta", fTheta, "fTheta[numParticles]/F");
	hijTree->Branch("fPhi", fPhi, "fPhi[numParticles]/F");

	// now get a random number to set the seed
	auto currentTime = std::chrono::system_clock::now().time_since_epoch(); // current time as duration since epoch
	auto currentTimeMs = std::chrono::duration_cast<std::chrono::milliseconds>(currentTime).count();
	std::mt19937_64 generator(currentTimeMs); // seed RNG with current time
	std::uniform_int_distribution<int> distribution(1, 20000);
	int randomNumber = distribution(generator);
	if (randomNumber %2 == 0) randomNumber++; // make sure random number is odd (why odd?)
	ranseed.nseed = randomNumber; 

	hiparnt.ihpr2[20] = 1;

	// Initialize HIJING
	hijset_(&EFRM, FRAME[FRAMEID], PROJ[PROJID], TARG[TARGID], &IAP, &IZP, &IAT, &IZT);
	
	if (BMAX == -1) { // minimum bias (let b range from 0 to R_A + R_B)	
		BMIN = 0.0;
		BMAX = hiparnt.hipr1[33] + hiparnt.hipr1[34];		
	}

	// HIJING event simulation
	int nEv_tot = 0;
	for (int IE = 0; IE < N_EVENT; IE++) { // for each event
		nEv_tot++;
		if (nEv_tot%100 == 0) {
			std::cout << "Event " << nEv_tot << std::endl;
		}
		eventNum = nEv_tot;
		hijing_(FRAME[FRAMEID], &BMIN, &BMAX);	
		numParticles = himain1.natt;
		b = hiparnt.hint1[18];
		
		// loop over particles
		int nPart = 0;
		int nChParticipants = 0;
		for (int part=0; part < numParticles; part++){
			nPart++;
			int fromParticipant = 0;
			int id = himain2.katt[0][part];
			int src = himain2.katt[1][part];
			int stat = himain2.katt[3][part];
			int charge = luchge(&id);
		    double px = himain2.patt[0][part];
			double py = himain2.patt[1][part];
			double pz = himain2.patt[2][part];
			double en = himain2.patt[3][part];
			TLorentzVector vec; // initialized as (0,0,0,0)
			vec.SetPxPyPzE(px, py, pz, en);
			double mom = vec.P();
			double eta = vec.Eta();
			double pt = vec.Pt();
			double theta = vec.Theta();
			double phi = vec.Phi();
			double rap = vec.Rapidity();
			if ( (src != 0) && (src != 10) ) { // if participant (if not spectator)
				fromParticipant = 1;
			}
			if ((fromParticipant==1) && (charge != 0) ){
				nChParticipants++;
			}
			fPartNum[part] = nPart;
			fFlavCode[part] = id;
			fSource[part] = src;
			fStatus[part] = stat;
			fCharge[part] = charge/3;
			fFromParticipant[part] = fromParticipant;
			fEn[part] = en;
			fP[part] = mom;
			fPt[part] = pt;	
			fEta[part] = eta;
			fY[part] = rap;
			fTheta[part] = theta;
			fPhi[part] = phi;


		} // end loop over particles	
		hijTree->Fill(); // add info from current event to tree

	} // end event generation loop

	hijTree->Write();
	f.Close();
	std::cout << "done!" << std::endl;
	return 0;
} // end main

