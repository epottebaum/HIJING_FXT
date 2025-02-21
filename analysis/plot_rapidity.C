// Jan 8, 2025
#include <TROOT.h>
#include <TFile.h>
#include <TTree.h>
#include <iostream>



void draw_plots(int mode, int species){
	// mode: 0 for C, 1 for FXT
	// species: 1 for pions, 2 for kaons, 3 for protons
	TFile *f70 = nullptr;
	TFile *f100 = nullptr;
	TFile *f205 = nullptr;
	TFile *f390 = nullptr;
	TFile *f816 = nullptr;
	int xlow = 0;
	int xhigh = 0;
	TCut cut = "";
	std::string title = "";
	std::string cname = "rapDist_";
	if (mode==0){
    	f70 = new TFile("/gpfs/gibbs/project/havener/egp28/HIJING-out/hijout_1m_minbias_CMframe_11p5GeV.root");
	    f100 = new TFile("/gpfs/gibbs/project/havener/egp28/HIJING-out/hijout_1m_minbias_CMframe_13p7GeV.root");
    	f205 = new TFile("/gpfs/gibbs/project/havener/egp28/HIJING-out/hijout_1m_minbias_C_19p6GeV.root");
	    f390 = new TFile("/gpfs/gibbs/project/havener/egp28/HIJING-out/hijout_1m_minbias_C_27GeV.root");
    	f816 = new TFile("/gpfs/gibbs/project/havener/egp28/HIJING-out/hijout_1m_minbias_C_39GeV.root");
		xlow = -3;
		xhigh = 3;
		title = "Collider Mode: ";
		cname += "C_";
	}
	if (mode==1){
		f70 = new TFile("/gpfs/gibbs/project/havener/egp28/HIJING-out/hijout_1m_minbias_FXT_11p5GeV.root");
		f100 = new TFile("/gpfs/gibbs/project/havener/egp28/HIJING-out/hijout_1m_minbias_FXT_13p7GeV.root");
		f205 = new TFile("/gpfs/gibbs/project/havener/egp28/HIJING-out/hijout_1m_minbias_FXT_19p6GeV.root");
		f390 = new TFile("/gpfs/gibbs/project/havener/egp28/HIJING-out/hijout_1m_minbias_FXT_27GeV.root");
		f816 = new TFile("/gpfs/gibbs/project/havener/egp28/HIJING-out/hijout_1m_minbias_FXT_39GeV.root");
		xlow = -2;
		xhigh = 10;
		title = "Fixed Target: ";
		cname += "FXT_";
	}
	if (species==0){
		cut = "fFlavCode==211 || fFlavCode==-211";
		title += "#pi^{+-}";
		cname += "pions.pdf";
	}
	if (species==1){
		cut = "fFlavCode==321 || fFlavCode==-321";
		title += "K^{+-}";
		cname += "kaons.pdf";
	}
	if (species==2){
		cut = "fFlavCode==2212 || fFlavCode==-2212";
		title += "P^{+-}";
		cname += "protons.pdf";
	}

	int nbins = 50;
	TTree *t70 = (TTree*)f70->Get("hijTree");
	TTree *t100 = (TTree*)f100->Get("hijTree");
	TTree *t205 = (TTree*)f205->Get("hijTree");
	TTree *t390 = (TTree*)f390->Get("hijTree");
	TTree *t816 = (TTree*)f816->Get("hijTree");

	// pions
	TCanvas *c1 = new TCanvas();
	gPad->SetLogy();
	TH1F *h70 = new TH1F("h70", "", nbins, xlow, xhigh);
	TH1F *h100 = new TH1F("h100", "", nbins, xlow, xhigh);
	TH1F *h205 = new TH1F("h205", "", nbins, xlow, xhigh);
	TH1F *h390 = new TH1F("h390", "", nbins, xlow, xhigh);
	TH1F *h816 = new TH1F("h816", "", nbins, xlow, xhigh);
	t70->Draw("fY >> h70", cut);
	t100->Draw("fY >> h100", cut);
	t205->Draw("fY >> h205", cut);
	t390->Draw("fY >> h390", cut);
	t816->Draw("fY >> h816", cut);
	h70->SetLineColor(kRed);
	h100->SetLineColor(kViolet);
	h205->SetLineColor(kBlue);
	h390->SetLineColor(kGreen);
	h816->SetLineColor(kBlack);
	h70->GetXaxis()->SetTitle("y");
	h70->SetTitle(title.c_str());
	h70->SetStats(0);
	h70->Draw("hist");
	h100->Draw("hist same");
	h205->Draw("hist same");
	h390->Draw("hist same");
	h816->Draw("hist same");

	// Draw y_beam and y_CM
/*	TLine *yb = new TLine(7.46, 0, 7.46, 5e6);
	TLine *ycm = new TLine(3.73, 0, 3.73, 5e6);
	yb->SetLineColor(kBlack);
	ycm->SetLineColor(kBlack);
	yb->SetLineStyle(9);
	yb->Draw("same");
	ycm->Draw("same");*/

	//TLegend *leg1 = new TLegend(0.3, 0.1, 0.7, 0.4);
	TLegend *leg1 = new TLegend(0.3, 0.25);
	leg1->SetNColumns(2);
	leg1->SetHeader("#sqrt{s_{NN}}");
	leg1->AddEntry(h70, "11.5 GeV", "l");
	leg1->AddEntry(h390, "27 GeV", "l");
	leg1->AddEntry(h100, "13.7 GeV", "l");
	leg1->AddEntry(h816, "39 GeV", "l");
	leg1->AddEntry(h205, "19.6 GeV", "l");
	leg1->SetBorderSize(0);
	leg1->Draw();
	//c1->SaveAs(cname.c_str());

}


void plot_rapidity(int mode, int species){
    // mode: 0 for C, 1 for FXT
    // species: 1 for pions, 2 for kaons, 3 for protons
	draw_plots(mode, species);

} // plot_rapidity()
