// March 10, 2025
// Emily Pottebaum
// Read in HepMC3 output and save as ROOT file

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
#include "HepMC3/ReaderAscii.h"
#include "HepMC3/WriterAscii.h"
#include "HepMC3/Print.h"
#include "HepMC3/Selector.h"

using namespace HepMC3;

int main(int argc, char *argv[]){
	ReaderAscii infile("/gpfs/gibbs/project/havener/egp28/HIJING-out/test_1ev_FXT_13p7GeV.hepmc");
	
	// make TTree that looks like hijTree, read in event and particle info
	// Initialize ROOT stuff
	TFile outfile("hepmc2root_out.root", "recreate");
	TTree *hepTree = new TTree("hepTree", "hepTree");
	int eventID = 0;
	int numVert = 0;
	int numParticles = 0;
	int vOID[80000] = {0}; // vertex internal ID
	int vStatus[80000] = {0}; // vertex status
	float vX[80000] = {0}; 
	float vY[80000] = {0};
	float vZ[80000] = {0};
	float vT[80000] = {0};
	int pOID[80000] = {0}; // particle internal ID
	int pVID[80000] = {0}; // originating vertex ID
	int pID[80000] = {0}; // PDG ID
	float pPx[80000] = {0};
	float pPy[80000] = {0};
	float pPz[80000] = {0};
	float pEn[80000] = {0};
	//float pMass[80000] = {0};
	//int pIntCode[80000] = {0}; // interaction code

	hepTree->Branch("eventID", &eventID, "eventID/I");
	hepTree->Branch("numVert", &numVert, "numVert/I");
	hepTree->Branch("numParticles", &numParticles, "numParticles/I");
	hepTree->Branch("vOID", vOID, "vOID[numVert]/I");
	hepTree->Branch("vStatus", vStatus, "vStatus[numVert]/I");
	hepTree->Branch("vX", vX, "vX[numVert]/F");
	hepTree->Branch("vY", vY, "vY[numVert]/F");
	hepTree->Branch("vZ", vZ, "vZ[numVert]/F");
	hepTree->Branch("vT", vT, "vT[numVert]/F");
	hepTree->Branch("pOID", pOID, "pOID[numParticles]/I");
	hepTree->Branch("pVID", pVID, "pVID[numParticles]/I");
	hepTree->Branch("pID", pID, "pID[numParticles]/I");
	hepTree->Branch("pPx", pPx, "pPx[numParticles]/F");
	hepTree->Branch("pPy", pPy, "pPy[numParticles]/F");
	hepTree->Branch("pPz", pPz, "pPz[numParticles]/F");
	hepTree->Branch("pEn", pEn, "pEn[numParticles]/F");
	//hepTree->Branch("pMass", pMass, "pMass[numParticles]/F");
	//hepTree->Branch("pIntCode", pIntCode, "pIntCode[numParticles]/I");

	// read in hepmc
	int events_parsed = 0;
	while (!infile.failed()){ // read ascii file
		GenEvent evt(Units::GEV, Units::MM);
		infile.read_event(evt);
		if (infile.failed()) break;
		if (events_parsed % 100 == 0)
		{
			std::cout << "Parsing event " << events_parsed << std::endl;
		}
		
		// Fill event-level branches
		eventID = evt.event_number();
		numParticles = evt.particles_size();
		numVert = evt.vertices_size();
		const vector<GenParticlePtr> p_vec = evt.particles();
		const vector<GenVertexPtr> v_vec = evt.vertices();
		// Loop over vertices in this event
		int vi = 0;
		//for (int vi = 0; vi < numVert; vi++){
		vector<GenVertexPtr>::const_iterator v;
		for (v = v_vec.begin(); v != v_vec.end(); ++v){
			//GenVertex v = *it;
			int vid = (*v)->id();
			int vstat = (*v)->status();
			const FourVector v4 = (*v)->position();
			float vx = v4.x();
			float vy = v4.y();
			float vz = v4.z();
			float vt = v4.t();
			
			vOID[vi] = vid;
			vStatus[vi] = vstat;
			vX[vi] = vx;
			vY[vi] = vy;
			vZ[vi] = vz;
			vT[vi] = vt;
			vi++;
		} // end loop over vertices
		
		// Loop over particles in this event
		vector<GenParticlePtr>::const_iterator p;
		int pi = 0;
		for (p = p_vec.begin(); p != p_vec.end(); ++p){
			//GenParticle p = p_vec[pi];
			int poid = (*p)->id();
			int pvid = (*p)->production_vertex()->id();
			int pid = (*p)->pid();
			const FourVector p4 = (*p)->momentum();
			float px = p4.px();
			float py = p4.py();
			float pz = p4.pz();
			float pen = p4.e();

			pOID[pi] = poid;
			pVID[pi] = pvid;
			pID[pi] = pid;
			pPx[pi] = px;
			pPy[pi] = py;
			pPz[pi] = pz;
			pEn[pi] = pen;
			pi++;
		} // end loop over particles

		hepTree->Fill();
		events_parsed++;

	} // end read ascii file loop

	hepTree->Write();
	infile.close();
	outfile.Close();
	return 0;
} // end hepmc2root()
