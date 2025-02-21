// Assign HIJING events to centrality classes
// TODO:
//  - input as TChain instead of one file (instead of combining multiple jobs with hadd)
//  - put output in a separate ROOT file
#define hijTree_cxx
#include "hijTree.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <cmath>

int frame = 1; // 0 for CM, 1 for LAB
double Pbeam = 100; // GeV per nucleon
std::string yieldsfilename = "yields_FXT_13p7GeV_100k.txt"; // pi K p yields output to this file
double raplow = -0.5; // relative to midrapidity (0 for CM frame)
double raphigh = 0.5; // relative to midrapidity (0 for CM frame)
void hijTree::Loop()
{
	if (frame==1){
		double Ebeam = sqrt(pow(0.938272, 2) + pow(Pbeam, 2)); // find mid-rapidity for fixed target mode
		double beta = Pbeam / Ebeam;
		double midrap = 0.5 * log((1+beta) / (1-beta)) / 2.0; 
		std::cout << "for Pbeam = " << Pbeam << " GeV, Ycm = " << midrap << std::endl;
		raplow += midrap;
		raphigh += midrap;
	}
//   In a ROOT session, you can do:
//      root> .L hijTree.C
//      root> hijTree t
//      root> t.GetEntry(12); // Fill t data members with entry number 12
//      root> t.Show();       // Show values of entry 12
//      root> t.Show(16);     // Read and show values of entry 16
//      root> t.Loop();       // Loop on all entries

    if (fChain == 0) return;
    Long64_t nentries = fChain->GetEntriesFast();
    Long64_t nbytes = 0, nb = 0;
	std::vector<double> Nch_midRap;
	int nch = 0;
	// Find the number of charged particles at mid-rapidity ("multiplicity")
	TBranch *bNch_midRap = fChain->Branch("bNch_midRap", &nch, "nch/I");
    for (Long64_t jentry=0; jentry<nentries;jentry++) { // loop over events
        Long64_t ientry = LoadTree(jentry);
        if (ientry < 0) break;
		nch = 0;
        nb = fChain->GetEntry(jentry);   nbytes += nb;
		for (Long64_t jp=0; jp<numParticles; jp++) { // loop over particle record for this event
			if ((fFromParticipant[jp]==1) && (fCharge[jp]!=0)){ // if charged and from non-spectator
				if ((fY[jp]<=raphigh) && (fY[jp]>=raplow)) {nch++;} // if mid-rapidity
			}
		}
        Nch_midRap.push_back((double)nch);
		bNch_midRap->Fill();
    }
	// plot multiplicity
	TCanvas *c = new TCanvas();
	c->cd();
	c->SetLogy();
	int maxmult = *max_element(Nch_midRap.begin(), Nch_midRap.end()); // get max multiplicity for histogram bound
	std::vector<double> w(Nch_midRap.size(), 1.0); // trivial weights vector with every element having equal (1.0) weight
	TH1F *hMult = new TH1F("hMult", "Charged particle multiplicity at mid-rapidity", maxmult+1, 0, maxmult+1);
	hMult->FillN(Nch_midRap.size(), Nch_midRap.data(), w.data()); // fill histogram with multiplicity vector
	hMult->GetXaxis()->SetTitle("N_{ch} (y=y_{cm} +/- 0.5)");
	hMult->SetTitle("Multiplicity distribution at mid-rapidity");
	hMult->GetYaxis()->SetTitle("P(N_{ch})");
	double scalefactor = 1.0/hMult->Integral();
	hMult->Scale(scalefactor); // normalize
	hMult->SetLineColor(1);
	hMult->Draw("HIST");

	// Get centrality classes from multiplicity distribution
	// start by creating a vector where each element corresponds to the integral of hMult from the current bin
	// basically just a running sum but taking the sum from the right-most bin
	// NOTE: bin 0 is the underflow bin
	// 		 bin 1 has low edge = xlow (inclusive)
	// 		 second to last bin (bin# nbins) has upper edge xup (exclusive)
	// 		 last bin (bin# nbins+1) is the overflow bin
	std::vector<double> c_upper_bounds = {0.05, 0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.8, 1.0};
	std::vector<double> c_bins_low;
	//std::vector<double> centrality_flag;
	int cur_cIn = c_upper_bounds.size()-1;
	int nbins = hMult->GetNbinsX();
	for (int b = 1; b <= nbins; b++) // skip underflow
	{
		double cur_int = hMult->Integral(b, nbins);
		double cur_bound = c_upper_bounds[cur_cIn];
		if (cur_int < cur_bound) {
			double prev_int = hMult->Integral(b-1, nbins);
			double cur_dist = std::abs(cur_int - cur_bound);
			double prev_dist = std::abs(prev_int - cur_bound);
			if ((cur_dist < prev_dist) || (b==1)) {
				c_bins_low.push_back(b);
			}
			else {
				c_bins_low.push_back(b-1);	
			}
			cur_cIn -= 1;
		}
	}

	std::vector<double>::iterator it;
	int tempcount = 0;
	for (it=c_bins_low.begin(); it != c_bins_low.end(); it++) {
		double val = hMult->GetBinLowEdge(*it);
		std::cout << "Centrality bin: " << tempcount << ", Nch (low bound): " << val << std::endl;
		tempcount += 1;

	}

	// make a histogram showing the centrality distribution
	TH1F *h[9];
	for (int i = 0; i < 9; i++){
		h[i] = (TH1F*)hMult->Clone();
		//TLine *l = new TLine(c_bins_low[i], 0, c_bins_low[i], 0.2);
		//l->SetLineColor(2);
		//l->Draw("same");
		for (int j = 1; j < c_bins_low[i]; j++){
			h[i]->SetBinContent(j, 0);
		}
		if (i < 8){
			for (int j = c_bins_low[i+1]; j <= nbins; j++){
				h[i]->SetBinContent(j, 0);
			} 	
		}
		if (i%2 != 0){
			h[i]->SetFillColor(16);
		}
		else {h[i]->SetFillColor(0); }	
		h[i]->Draw("hist same");
	}
		
    std::vector<std::string> c_labels = {"0-5%", "5-10%", "10-20%", "20-30%", "30-40%", "40-50%", "50-60%", "60-80%", "80-100%"};
	std::reverse(c_labels.begin(), c_labels.end());
	for (int i = 8; i > 0; i--)
	{
		double xcoord = 0.0;
		double cval = hMult->GetBinLowEdge(c_bins_low[i]);	
		if (i==8) {xcoord = cval+15;}
		//else if (i==0) {xcoord = 0.0;}
		else {xcoord = (cval + hMult->GetBinLowEdge(c_bins_low[i+1]))/2.0; }
		TText *t = new TText(xcoord, 0.00005, c_labels[i].c_str());
		t->SetTextAlign(22);
		t->SetTextAngle(90);
		t->Draw();
	}

	// (klunky but gets the job done for now)
	// loop over events and assign each a flag based on corresponding centrality class
	std::vector<int> centrality_flag;
	int cflag;
	TBranch *centrality = fChain->Branch("centrality", &cflag, "cflag/I");
	
	for (Long64_t jentry=0; jentry<nentries; jentry++) {
		LoadTree(jentry);
	//	int curflag = -1;
		double Nch = Nch_midRap[jentry]; // number of charged particles for this event
		for (int i = 8; i >= 0; i--) { // start from most central (c_bins_low is ordered from least to most central)
			double cval = hMult->GetBinLowEdge(c_bins_low[i]); // TODO: make vector of cvals to use instead of continuously redefining cval
			if (Nch >= cval) {
				cflag = 8-i;
				centrality_flag.push_back(cflag);
				goto end; // found centrality class for this event, now fill branch and go to next event
			} // end if Nch>=cval
		} // end loop over centrality classes	
		end:
			centrality->Fill();
	} // end loop over entries

	// get the number of (charged) pions, kaons, and protons in each centrality class
	// output yields to text file
	// because why make a good efficient algorithm when you can use a SLEDGEHAMMER
	int pi_m[] = {0,0,0,0,0,0,0,0,0};
	int pi_p[] = {0,0,0,0,0,0,0,0,0};
	int k_m[] = {0,0,0,0,0,0,0,0,0};
	int k_p[] = {0,0,0,0,0,0,0,0,0};
	int pbar[] = {0,0,0,0,0,0,0,0,0};
	int p[] = {0,0,0,0,0,0,0,0,0};
	int N_per_class[] = {0,0,0,0,0,0,0,0,0};
	int Ev_per_class[] = {0,0,0,0,0,0,0,0,0};
	int nPiM;
	int nPiP;
	int nKM;
	int nKP;
	int nPbar;
	int nP;
	TBranch *bPiM = fChain->Branch("bPiM", &nPiM, "nPiM/I");
	TBranch *bPiP = fChain->Branch("bPiP", &nPiP, "nPiP/I");
	TBranch *bKM = fChain->Branch("bKM", &nKM, "nKM/I");
	TBranch *bKP = fChain->Branch("bKP", &nKP, "nKP/I");
	TBranch *bPbar = fChain->Branch("bPbar", &nPbar, "nPbar/I");
	TBranch *bP = fChain->Branch("bP", &nP, "nP/I");
	for (Long64_t jentry=0; jentry<nentries; jentry++){ //final loop over entries. hopefully
		Long64_t ientry = LoadTree(jentry);
		if (ientry < 0) break;
		int cflag = centrality_flag[jentry];
		Ev_per_class[cflag] += 1;
		nPiM = 0;
		nPiP = 0;
		nKM = 0;
		nKP = 0;
		nPbar = 0;
		nP = 0;
		fChain->GetEntry(jentry);
		for (Long64_t jp=0; jp<numParticles; jp++) {
			if ((fFromParticipant[jp]==1) && (fCharge[jp]!=0)){ // if charged and from non-spectator
				if ((fY[jp]<=raphigh) && (fY[jp]>=raplow)){ // if mid-rapidity
					N_per_class[cflag] += 1;
					if (fFlavCode[jp] == -211){ 
						pi_m[cflag] += 1;
						nPiM += 1;
					}
					else if (fFlavCode[jp] == 211) {
						pi_p[cflag] += 1;
						nPiP += 1;
					}
					else if (fFlavCode[jp] == -321) {
						k_m[cflag] += 1;
						nKM += 1;
					}
					else if (fFlavCode[jp] == 321) {
						k_p[cflag] += 1;
						nKP += 1;
					}
					else if (fFlavCode[jp] == -2212) {
						pbar[cflag] += 1;
						nPbar += 1;
					}
					else if (fFlavCode[jp] == 2212) {
						p[cflag] += 1;
						nP += 1;
					}
				} // end if mid-rapidity
			} // end if charged and non-spectator
		} // end loop over particles	
		bPiM->Fill();
		bPiP->Fill();
		bKM->Fill();
		bKP->Fill();
		bPbar->Fill();
		bP->Fill();
	}// end final loop over entries

	fChain->Write();

	int species_sums[] = {0,0,0,0,0,0,0,0,0};
	double avgN[9];
	for (int i = 0; i < 9; i++){
		species_sums[i] = pi_m[i] + pi_p[i] + k_m[i] + k_p[i] + pbar[i] + p[i];
		if (species_sums[i] > N_per_class[i]){
			std::cout << "pi+K+P > N for centrality class " << i << std::endl;
		}
		std::cout << "Bin " << i << ": pi+K+P= " << species_sums[i] << " / " << N_per_class[i] << " total" << std::endl;
		avgN[i] = (double)N_per_class[i] / (double)Ev_per_class[i];
		//int sum = std::accumulate(nVals[i].begin(), nVals[i].end(), 0);
		//avgN[i] = sum / nVals[i].size();
	//	std::cout << avgN[i] << std::endl;
	}

	std::ofstream outfile;
	outfile.open(yieldsfilename.c_str());
	outfile << "# Yields by centrality class, least to most central.\n";
	outfile << "# 80-100%, 60-80%, 50-60%, 40-50%, 30-40%, 20-30%, 10-20%, 5-10%, 0-5%\n";
	outfile << "# line order: pi-, pi+, K-, K+, Pbar, P\n";
	for (int i = 8; i >= 0; i--){
		outfile << pi_m[i] << " ";	
	}
	outfile << "\n";
	
	//outfile << "pi+ ";
    for (int i = 8; i >= 0; i--){
        outfile << pi_p[i] << " ";
    }
    outfile << "\n";

    //outfile << "k- ";
    for (int i = 8; i >= 0; i--){
        outfile << k_m[i] << " ";
    }
    outfile << "\n";

    //outfile << "k+ ";
    for (int i = 8; i >= 0; i--){
        outfile << k_p[i] << " ";
    }
    outfile << "\n";

    //outfile << "pbar ";
    for (int i = 8; i >= 0; i--){
        outfile << pbar[i] << " ";
    }
    outfile << "\n";

    //outfile << "p ";
    for (int i = 8; i >= 0; i--){
        outfile << p[i] << " ";
    }
    outfile << "\n";
	outfile.close();
	/*for (int i = 0; i < 9; i++){
		std::cout << "Centrality flag " << i << ":" << std::endl;
		std::cout << "pi-: " << pi_m[i] << " | pi+: " << pi_p[i] << std::endl;
		std::cout << "K-: " << k_m[i] << " | K+: " << k_p[i] << std::endl;
		std::cout << "Pbar: " << pbar[i] << " | P: " << p[i] << std::endl;
		std::cout << "========================================" << std::endl;
	}*/
}
