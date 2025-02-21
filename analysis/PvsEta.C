// Jan 21, 2025
#include <iostream>
#include <TROOT.h>
#include <TFile.h>
#include <TTree.h>

void PvsEta(){
  //gROOT->LoadMacro("epic_acceptances.C");
	TFile *f10p5 = new TFile("/gpfs/gibbs/project/havener/egp28/HIJING-out/hijout_100k_minbias_FXT_13p7GeV.root");
	TTree *t10p5 = (TTree*)f10p5->Get("hijTree");
	TCut pions = "(fFlavCode==211) || (fFlavCode==-211)"; // ignore pi0, just looking at charged hadrons
	TCut kaons = "(fFlavCode==321) || (fFlavCode==-321)";
	TCut protons = "(fFlavCode==2212) || (fFlavCode==-2212)";

	TCanvas *c0 = new TCanvas();
	//c0->Divide(2);
	c0->cd();
	gPad->SetLogz();
	gPad->SetLogy();
	gStyle->SetOptStat(0);
	int nbinsEta = 200;
	int nbinsP = 200;
	float etalow = -5.0;
	float etahigh = 8.0;
	float plow = 0.08;
	float phigh = 200; 
 
	TH2F *h10p5_pi = new TH2F("h10p5_pi", "#sqrt{s}=13.7 GeV, charged #pi yield", nbinsEta, etalow, etahigh, nbinsP, plow, phigh);
	//TH2F *h10p5_k = new TH2F("h10p5_k", " ", nbinsEta, etalow, etahigh, nbinsP, plow, phigh);
	//TH2F *h10p5_piK = new TH2F("h10p5_piK", " ", nbinsEta, etalow, etahigh, nbinsP, plow, phigh);
	//c0->cd(1);
	t10p5->Draw("fP:fEta >> h10p5_pi", pions);
	//h10p5_piK = (TH2F*)h10p5_pi->Clone();
	//h10p5_pi->Draw("COLZ");
	//c0->cd(2);
	//t10p5->Draw("fP:fEta >> h10p5_k", kaons);
	//h10p5_k->Draw("COLZ");
	//c0->Draw();
	h10p5_pi->GetXaxis()->SetTitle("#eta");
	h10p5_pi->GetYaxis()->SetTitle("Momentum (GeV/c)");
	h10p5_pi->Draw("COLZ");
	//TCanvas *c1 = new TCanvas();
	//c1->cd();
	//gPad->SetLogz();
	//gPad->SetLogy();
	//h10p5_piK = (TH2F*)h10p5_pi->Clone();
	//h10p5_piK->Divide(h10p5_k);
	//h10p5_piK->GetXaxis()->SetTitle("#eta");
	//h10p5_piK->GetYaxis()->SetTitle("Momentum (GeV/c)");
	//h10p5_piK->Draw("COLZ");
	//epic_acceptances(0, h10p5_piK);
	c0->Draw();

	//TH2F *h10p5_k = new TH2F("h10p5_k", "h10p5_k", nbinsEta, etalow, etahigh, nbinsP, plow, phigh);
	//t10p5->Draw("fP:fEta >> h10p5_pi", pions);
	//t10p5->Draw("fP:fEta >> h10p5_k", kaons);
	//h10p5_pi->GetXaxis()->SetTitle("#eta");
	//h10p5_pi->GetYaxis()->SetTitle("Momentum (GeV/c)");
	//
	//c0->cd(1);
//	h10p5_pi->Draw("COLZ");

//	c0->Draw();
	//c0->cd(2);
	//h10p5_k->Draw("COLZ");

} // end PvsEta
