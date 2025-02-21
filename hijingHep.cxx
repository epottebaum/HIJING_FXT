// Generate HIJING events, output to HepMC
// essentially just re-writing Niseem's code (Niseem_Hij_HepMC3 on Github)
// February 5, 2025
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
#include "HepMC3/GenVertex.h"
#include "HepMC3/GenParticle.h"
#include "HepMC3/WriterAscii.h"
#include "HepMC3/Print.h"
#include "HepMC3/Selector.h"

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

using namespace HepMC3;
const double FMtoMM = 1.0e-12;
const double Pi = 3.141592653589793;
const double mass_au_gev = 1.834732e+02;

std::string config_file = "../hijing_config.txt";
int main(int argc, char **argv)
{
	if (argc < 2) {	
		std::cout << "Usage: " << argv[0] << " output_file_name.hepmc" << std::endl;
		std::cout << "To specify config file: " << argv[0] << " output_file_name.hepmc config_file_name" << std::endl; 
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
	std::string outdir = line.c_str(); // first line is the output directory

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


	// Nuclear radius (formula from liquid drop model)
	float RIonP = 1.2*pow(IAP,0.3333333333);
	float RIonT = 1.2*pow(IAT,0.3333333333);
	float RPT   = (RIonP + RIonT)/2.0; // average radius

	// Get a random number to set the seed
    auto currentTime = std::chrono::system_clock::now().time_since_epoch(); // current time as duration since epoch
    auto currentTimeMs = std::chrono::duration_cast<std::chrono::milliseconds>(currentTime).count();
    std::mt19937_64 generator(currentTimeMs); // seed RNG with current time
    std::uniform_int_distribution<int> distribution(1, 20000);
    int randomNumber = distribution(generator);
    if (randomNumber %2 == 0) randomNumber++; // make sure random number is odd (why odd?)
    ranseed.nseed = randomNumber;

	hiparnt.ihpr2[9] = 0; // option to print warning messages about errors that might happen
	hiparnt.ihpr2[20] = 1; // option to keep information of all particles including those which have decayed
	hiparnt.ihpr2[11] = 0; // option to turn off automatic decay of: pi0, K0_S, D+-, Lambda, Sigma+-

    // Initialize HIJING
    hijset_(&EFRM, FRAME[FRAMEID], PROJ[PROJID], TARG[TARGID], &IAP, &IZP, &IAT, &IZT);

	// Initialize ROOT stuff
	std::string outfile = outdir + output_file;
	std::ofstream outputStream(outfile);
	WriterAscii outputWriter(outputStream);

	// TODO: structured binding to get mass based on projectile and target... for now assume if TARG=6 (A), running Au+Au
	// TODO: safeguard beam pdg_id re: L and I in case eg try to make a beam of excited sigmas or some shit
	// get PDG code for beams (projectile and target)
	// Nuclear codes given as +-10LZZZAAAI (L=number of strange quarks, I=isomer (excited state) )	

	// Projectile beam
    std::stringstream IonP;
    IonP << std::setw(3) << std::setfill('0') << IZP; // ZZZ
    IonP << std::setw(3) << std::setfill('0') << IAP; // AAA
    std::string IonPP = IonP.str();
    IonPP = "100" + IonPP + "0"; // 10L + ZZZAAA + I
	int IonBeamP = std::stoi(IonPP); // turn into int
	
	// Target beam
	std::stringstream IonT;
	IonT << std::setw(3) << std::setfill('0') << IZT; // ZZZ
	IonT << std::setw(3) << std::setfill('0') << IAT; // AAA
	std::string IonPT = IonT.str();
	IonPT = "100" + IonPT + "0"; // 10L + ZZZAAA + I
	int IonBeamT = std::stoi(IonPT); // turn into int

	if (FRAMEID==0) { // collider mode
		std::cout << "HIJING running in collider mode" << std::endl;		
	} // end if collider mode

	else if (FRAMEID==1) { // fixed target mode
		std::cout << "HIJING running in fixed target mode" << std::endl;
	} // end if fixed target mode
		
	if (BMAX == -1) { // minimum bias (let b range from 0 to R_A + R_B)
		BMIN = 0.0;
		BMAX = hiparnt.hipr1[33] + hiparnt.hipr1[34];
	}

	// Generate HIJING events
	int Nev_tot = 0;
	for (int IE = 0; IE < N_EVENT; IE++) { // loop over events
		Nev_tot++; // HIJING events start at 1, not 0 (++IE was not incrementing correctly so doing this)
		if (Nev_tot%100 == 0){
			std::cout << "Event " << Nev_tot << std::endl;
		}
		hijing_(FRAME[FRAMEID], &BMIN, &BMAX);
		if (himain1.natt <= 1) continue; // if number of events <=1
		GenEvent Hep_event; // initialize hepmc event
		Hep_event.set_units(Units::GEV,Units::MM);
		float ImpactP = hiparnt.hint1[18]*FMtoMM; // put impact parameter into mm
		
		//----------------------------------------------------------------------------------
		// Set up beams
		// ---------------------------------------------------------------------------------
		HepMC3::GenParticlePtr BeamPP;
		HepMC3::GenParticlePtr BeamPT;
		if (FRAMEID==0){ // collider mode
			// FourVector(Px, Py, Pz, E/c), IonBeam, HEPEVT decay status (4: incoming particle)
			BeamPP = std::make_shared<GenParticle>(FourVector(0.0, 0.0, EFRM/2., EFRM/2.), IonBeamP, 4);
			BeamPT = std::make_shared<GenParticle>(FourVector(0.0, 0.0, -EFRM/2., EFRM/2.), IonBeamT, 4);
		}
		else if (FRAMEID==1) { // fixed target mode
			BeamPP = std::make_shared<GenParticle>(FourVector(0.0, 0.0, EFRM, EFRM), IonBeamP, 4);
			BeamPT = std::make_shared<GenParticle>(FourVector(0.0, 0.0, 0.0, mass_au_gev), IonBeamT, 4); // TODO: check this is correct
		}
		BeamPP->set_generated_mass(mass_au_gev);
		BeamPT->set_generated_mass(mass_au_gev);
		Hep_event.set_beam_particles(BeamPP, BeamPT);

		// ---------------------------------------------------------------------------------
		// Set up initial (projectile and target) vertices 
		// ---------------------------------------------------------------------------------
		int npart0 = 0; // counter for number of nucleons that underwent inelastic collisions in this event
		float vxpart[600] = {0}; // x-coordinate of nucleon wrt center of parent nucleus
		float vypart[600] = {0}; // y-coordinate of nucleon wrt center of parent nucleus

		HepMC3::GenVertexPtr BeamP_vertex;
		HepMC3::GenVertexPtr BeamT_vertex;
		if (FRAMEID==0) { // collider mode
			BeamP_vertex = std::make_shared<GenVertex>(FourVector(0.5*ImpactP, 0.0, 0.0, 0.0));
			BeamT_vertex = std::make_shared<GenVertex>(FourVector(-0.5*ImpactP, 0.0, 0.0, 0.0));
		}
		else if (FRAMEID==1) { // fixed target mode
			BeamP_vertex = std::make_shared<GenVertex>(FourVector(ImpactP, 0.0, 0.0, 0.0)); // TODO: check this is correct
			BeamT_vertex = std::make_shared<GenVertex>(FourVector(0.0, 0.0, 0.0, 0.0)); // TODO: only valid for target at origin? !!!!!!!!!!!!!
		}
		BeamP_vertex->add_particle_in(BeamPP); // add projectile beam as ingoing particle to projectile vertex
		BeamT_vertex->add_particle_in(BeamPT); // add target beam as ingoing particle to target vertex

		for(int ip=0; ip<IAP; ip++){ // loop over projectile nucleons
			int idp = 0; // nucleon PDG ID
			if(ip < IZP) idp = 2212; // proton
			else	     idp = 2112; // neutron
			// add nucleon as outgoing particle from projectile vertex
			// histrng.pp(1-5) (here [0-4]) = projectile nucleon (px, py, pz, E, M)
			BeamP_vertex->add_particle_out(std::make_shared<GenParticle>(FourVector( histrng.pp[0][ip],
																					 histrng.pp[1][ip],
																					 histrng.pp[2][ip],
																					 histrng.pp[3][ip]),
																		  idp, 0) );
			if(histrng.nfp[4][ip] > 1) { // if nucleon underwent inelastic collision (not spectator or elastic collision)
				vxpart[npart0] = hijcrdn.yp[ip][0]; // x-coordinate of nucleon
				vypart[npart0] = hijcrdn.yp[ip][1]; // y-coordinate of nucleon
				npart0++;
			} // TODO: check that my understanding of this is correct
		} // end loop over projectile nucleons
		Hep_event.add_vertex(BeamP_vertex);

		// Now do the same thing for the target nucleons
		for(int it=0; it<IAT; it++){ // loop over target nucleons
			int idt = 0;
			if(it < IZT) idt = 2212;
			else	     idt = 2112;
			BeamT_vertex->add_particle_out(std::make_shared<GenParticle>(FourVector( histrng.pt[0][it],
																					 histrng.pt[1][it],
																					 histrng.pt[2][it],
																					 histrng.pt[3][it]),
																		  idt, 0) );
			if(histrng.nft[4][it] > 1){
				vxpart[npart0] = hijcrdn.yt[it][0];
				vypart[npart0] = hijcrdn.yt[it][1];
				npart0++;
			}
		} // end loop over target nucleons
		Hep_event.add_vertex(BeamT_vertex);

		// ---------------------------------------------------------------------------------
		//  For our next act we shall calculate the eccentricity (I think)
		// ---------------------------------------------------------------------------------
		int Npart = 0; // TODO: I think Npart == npart0, check to make sure before replacing
		float Mx = 0.0; // average x-coord of nucleons that underwent inelastic collisions
		float My = 0.0; // average y-coord of nucleons that underwent inelastic collisions
		for (int i = 0; i < (int) npart0; i++){
			Mx += vxpart[i];
			My += vypart[i];
			Npart++;
		}
		if (Npart == 0) continue;
		Mx /= ((float)Npart);
		My /= ((float)Npart);
		
		float Rn[10];
		float Xn[10];
		float Yn[10];
		for (int i=0; i < 10; i++){ // idk why we're initializing like this but keeping it for now as it's what Niseem does
			Rn[i] = 0.;
			Xn[i] = 0.;
			Yn[i] = 0.;
		}

		for (int i = 0; i < (int)npart0; i++){ // loop over (inelastic participant) nucleons
			float Vxd = vxpart[i] - Mx; // x_i - <x>
			float Vyd = vypart[i] - My; // y_i - <y>
			float r = sqrt( pow(Vxd, 2.) + pow(Vyd, 2.) ); // magnitude of (x,y) residuals
			float p = atan2(Vyd, Vxd); // arctan^2( (yi-<y>)/(xi-<x>) )
			for (int ni=0; ni<10; ni++){ // calculate first 10 modes of eccentricity (think like Fourier expansion)
				float h = (float)1.0*ni + 1.0; // order (mode)
				float w;
				if (ni==0) w = 3.0;
				else       w = h;
				Rn[ni] += pow(r,w); // idk why we aren't just using = since each element initialized to 0 but oh well
				Xn[ni] += pow(r,w)*cos(h*p);
				Yn[ni] += pow(r,w)*sin(h*p);
			} // end count to 10
		} // end loop over (inelastic participant) nucleons

		// the prestige
		double Psi[10] = {0};
		double Ecc[10] = {0};
		for (int ni=0; ni < 10; ni++){ // count to 10 again
			float h = (float)1.0*ni + 1.0;
			Xn[ni] /= ((float) Npart);
			Yn[ni] /= ((float) Npart);
			Rn[ni] /= ((float) Npart);
			Psi[ni] = (atan2(Yn[ni],Xn[ni]) + Pi)/h; // event (participant) plane angle
			Ecc[ni] = sqrt(pow(Xn[ni],2.) + pow(Yn[ni],2.))/Rn[ni]; // calculate nth order eccentricity
		} // end count to 10 again


		// ---------------------------------------------------------------------------------
		// Add particles generated by HIJING to the HepMC event record
		// ---------------------------------------------------------------------------------
		vector<HepMC3::GenParticlePtr> Hep_particles; // particles
		vector<int>					   Hep_mother_ids; // particle mother IDs
		vector<HepMC3::GenVertexPtr>   Hep_prods; // production vertices
		Hep_particles.clear();
		Hep_mother_ids.clear();
		Hep_prods.clear();

		for (int part=0; part < himain1.natt; part++){ // Loop over hijing particles
			int mid = himain2.katt[2][part]-1; // line number of parent particle???	
			int id = himain2.katt[0][part]; // particle flavor code
			double px = himain2.patt[0][part];
			double py = himain2.patt[1][part];
			double pz = himain2.patt[2][part];
			double en = himain2.patt[3][part];
			// I guess HIMAIN3 stores formation time and position of each... particle? brief comment in the code says each hadron...
			double vx = himain3.vatt[0][part]*FMtoMM; // x
			double vy = himain3.vatt[1][part]*FMtoMM; // y
			double vz = himain3.vatt[2][part]*FMtoMM; // z
			double tt = himain3.vatt[3][part]*FMtoMM; // t/c
			int status = himain2.katt[3][part];
			if (status <= 10 && status > 0 ) status = 1; // final state particle
			if (status <= 20 && status > 10) status = 2; // decayed particle

			Hep_particles.push_back(std::make_shared<GenParticle>(FourVector(px, py, pz, en), id, status));
			Hep_prods.push_back(std::make_shared<GenVertex>(FourVector(vx, vy, vz, tt)));
			Hep_mother_ids.push_back(mid);
		} // end loop over hijing particles
		for (unsigned int ipart=0; ipart<Hep_particles.size(); ipart++){ // loop over hepmc particles
			int mid = Hep_mother_ids[ipart];
			double pT = sqrt(Hep_particles[ipart]->momentum().px()*Hep_particles[ipart]->momentum().px() +
						 	 Hep_particles[ipart]->momentum().py()*Hep_particles[ipart]->momentum().py());
			if (Hep_particles[ipart]->status()==1 && pT==0.0) continue; // I guess these are spectators? maybe??? seems like a wide net for that
			if (mid < 0){ // idk how line number of parent particle could be < 0... maybe these are nucleons that underwent elastic scattering?
				Hep_event.add_particle(Hep_particles[ipart]);
			}
			else{
				GenVertexPtr Prod_vertex = std::make_shared<GenVertex>();
				Prod_vertex = Hep_prods[mid]; // get mother particle vertex... TODO: okay to use mid as index??? thought it was a value
				Prod_vertex->add_particle_in(Hep_particles[mid]);
				Prod_vertex->add_particle_out(Hep_particles[ipart]);
				Hep_event.add_vertex(Prod_vertex);
			}
		} // end loop over hepmc particles
	
        // ---------------------------------------------------------------------------------
        // Additional event information is stored in attributes:
		// GenHeavyIon holds info on the heavy ions in the incoming beams
		// GenCrossSection: you'll never guess (holds info on cross sections of processes in the event)
        // ---------------------------------------------------------------------------------
		double Sigma_NN = hiparnt.hint1[11]*pow(10,9); // In units of Pb
		Hep_event.weights().push_back(1.0);
		float cent = 0.0;
		cent = 100*pow((hiparnt.hint1[18]/(2*RPT)),2.0); // centrality

		std::shared_ptr<GenHeavyIon> heavy_ion = std::make_shared<GenHeavyIon>();
		Hep_event.add_attribute("GenHeavyIon", heavy_ion);
		// setting number spectator neutrons and spectator protons to 0, so they did get weeded out above as I thought
		// also setting event plane angle and eccentricity to 0, why??? we calculate those things?????????
		// oh those get added in literally the next line
		heavy_ion->set(himain1.jatt, himain1.np, himain1.nt, himain1.n0+himain1.n01+himain1.n10+himain1.n11,
					   0, 0, himain1.n01, himain1.n10, himain1.n11, hiparnt.hint1[18], 0.0, 0.0, Sigma_NN, cent);
		for (int i = 0; i < 10; i++){
			heavy_ion->participant_plane_angles[i] = Psi[i];
			heavy_ion->eccentricities[i] = Ecc[i];
		}
		Hep_event.set_heavy_ion(heavy_ion);

		std::shared_ptr<GenCrossSection> cross_section = std::make_shared<GenCrossSection>();
		Hep_event.add_attribute("GenCrossSection", cross_section);
		cross_section->set_cross_section(Sigma_NN, 0.000000001*Sigma_NN); // is the second param supposed to be uncertainties??????? fake news
		
		// ---------------------------------------------------------------------------------
		// Finish up with this event
		// ---------------------------------------------------------------------------------
		outputWriter.write_event(Hep_event);
		Hep_event.clear();
		Nev_tot++;
	} // end loop over events
	outputWriter.close();
	std::cout << "done!" << std::endl;
	return 0;
} // end main

