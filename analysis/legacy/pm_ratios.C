// plot some pions
// author: Emily Pottebaum
// date: September 25, 2024

TChain chain("hijTree");

float rat_err(int N1, int N2) {
	double err1 = sqrt(N1) / N2;
	double err2 = (N1 * sqrt(N2)) / pow(N2, 2);
	return (float)err1 + (float)err2;
}
void pm_ratios(){
    //gSystem->Setenv("dir", "/gpfs/gibbs/project/havener/egp28/HIJING-out/hijout_1k_100x");
    gSystem->Setenv("dir", "/gpfs/gibbs/project/havener/egp28/HIJING-out/hijout_pp_1k_50x");
	for (int i = 0; i < 51; i++){
        std::string file = "$dir/hijout_pp_1k_" + std::to_string(i) + ".root";
        //std::cout << file << std::endl;
        char const* f = file.c_str();
        chain.Add(f);
    }

	TBranch *fPt = chain.GetBranch("fPt");
	//TBranch *fFlavCode = chain.GetBranch("fFlavCode");
	TCut pi_m = "fFlavCode==-211";
	TCut pi_p = "fFlavCode==211";	
	TCut k_m = "fFlavCode==-321";
	TCut k_p = "fFlavCode==321";
	TCut p = "fFlavCode==2212";
	TCut pbar = "fFlavCode==-2212";

	// pT bins
	TCut pt025 = "fPt < 0.25";
	TCut pt05 = "(fPt >= 0.25) && (fPt < 0.5)";
	TCut pt075 = "(fPt >= 0.5) && (fPt < 0.75)";
	TCut pt1 = "(fPt >= 0.75) && (fPt < 1.0)";
	TCut pt125 = "(fPt >= 1.0) && (fPt < 1.25)";
	TCut pt15 = "(fPt >= 1.25) && (fPt < 1.5)";
	TCut pt175 = "(fPt >= 1.5) && (fPt < 1.75)";
	TCut pt2 = "(fPt >= 1.75) && (fPt < 2.0)";
	TCut cuts[] = {pt025, pt05, pt075, pt1, pt125, pt15, pt175, pt2};
	float pirats[] = {0.0, 0.0, 0.0,0.0,0.0,0.0,0.0,0.0};
	float piraterr[] = {0.0, 0.0, 0.0,0.0,0.0,0.0,0.0,0.0};
	float krats[] = {0.0, 0.0, 0.0,0.0,0.0,0.0,0.0,0.0};
	float kraterr[] = {0.0, 0.0, 0.0,0.0,0.0,0.0,0.0,0.0};
	float prats[] = {0.0, 0.0, 0.0,0.0,0.0,0.0,0.0,0.0};
	float praterr[] = {0.0, 0.0, 0.0,0.0,0.0,0.0,0.0,0.0};
	for (int i = 0; i < 8; i++) {	
		TH1F *piP = new TH1F("piP", "", 100, 0, 4);
		TH1F *piM = new TH1F("piM", "", 100, 0, 4);
		TH1F *kP = new TH1F("kP", "", 100, 0, 4);
		TH1F *kM = new TH1F("kM", "", 100, 0, 4);
		TH1F *protons = new TH1F("protons", "", 100, 0, 4);
		TH1F *antip = new TH1F("antip", "", 100, 0, 4);
		chain.Draw("fPt >> piP", pi_p&&cuts[i]);
		chain.Draw("fPt >> piM", pi_m&&cuts[i]);
		chain.Draw("fPt >> kP", k_p&&cuts[i]);
		chain.Draw("fPt >> kM", k_m&&cuts[i]);
		chain.Draw("fPt >> protons", p&&cuts[i]);
		chain.Draw("fPt >> antip", pbar&&cuts[i]);
		int nPiP = piP->GetEntries();
		int nPiM = piM->GetEntries();
		int nKp = kP->GetEntries();
		int nKm = kM->GetEntries();
		int nP = protons->GetEntries();
		int nPbar = antip->GetEntries();
		float piRat = 0.0;
		float kRat = 0.0;
		float pRat = 0.0;
		if ( (nPiP != 0) && (nPiM != 0) ) {
			piRat = (float)nPiP/(float)nPiM;
			pirats[i] = piRat;
			piraterr[i] = rat_err(nPiP, nPiM);
		}

        if ( (nKp != 0) && (nKm != 0) ) {
            kRat = (float)nKp/(float)nKm;
            krats[i] = kRat;
            kraterr[i] = rat_err(nKp, nKm);
        }

        if ( (nP != 0) && (nPbar != 0) ) {
            pRat = (float)nP/(float)nPbar;
            prats[i] = pRat;
            praterr[i] = rat_err(nP, nPbar);
        }
		/*
		float piRat = (float)nPiP/(float)nPiM;
		float kRat = (float)nKp/(float)nKm;
		float pRat = (float)nP/(float)nPbar;
		pirats[i] = piRat;
		krats[i] = kRat;
		prats[i] = pRat;
		piraterr[i] = rat_err(nPiP, nPiM);
		kraterr[i] = rat_err(nKp, nKm);
		praterr[i] = rat_err(nP, nPbar);*/
		std::cout << cuts[i]  << std::endl;
		std::cout << "pi+: " << nPiP << ", pi-: " << nPiM << ", err: " << rat_err(nPiP, nPiM) << std::endl;
		std::cout << "pi+/pi-: " << piRat << ", K+/K-: " << kRat << ", p/pbar: " << pRat << std::endl;
		std::cout << "-------------" << std::endl;
		delete piP;
		delete piM;
		delete kP;
		delete kM;
		delete protons;
		delete antip;
	}
	TCanvas *c1 = new TCanvas();
	c1->cd();
	float xpts[] = {0.25, 0.5, 0.75, 1.0, 1.25, 1.5, 1.75, 2.0};
	TGraphErrors *ratPlot = new TGraphErrors(8,xpts,pirats,nullptr,piraterr);
	ratPlot->GetXaxis()->SetTitle("p_{T} [GeV]");
	ratPlot->GetYaxis()->SetTitle("#pi_{+}/#pi_{-}");
	//ratPlot->GetHistogram()->SetMinimum(0.8);
	//ratPlot->GetHistogram()->SetMaximum(1.1);
	ratPlot->SetMarkerStyle(8);
	ratPlot->SetMarkerSize(1);
	ratPlot->SetMarkerColor(kBlack);
	ratPlot->Draw("AP");
	c1->Draw();


    TCanvas *c2 = new TCanvas();
    c2->cd();
    TGraph *ratPlot2 = new TGraph(8,xpts,krats);
    ratPlot2->GetXaxis()->SetTitle("p_{T} [GeV]");
    ratPlot2->GetYaxis()->SetTitle("K_{+}/K_{-}");
    //ratPlot2->GetHistogram()->SetMinimum(0.8);
    //ratPlot2->GetHistogram()->SetMaximum(1.1);
    ratPlot2->SetMarkerStyle(8);
    ratPlot2->SetMarkerSize(1);
    ratPlot2->SetMarkerColor(kBlack);
    ratPlot2->Draw("AP");
    c2->Draw();

    TCanvas *c3 = new TCanvas();
    c3->cd();
	c3->SetLogy(); 
    TGraph *ratPlot3 = new TGraph(8,xpts,prats);
    ratPlot3->GetXaxis()->SetTitle("p_{T} [GeV]");
    ratPlot3->GetYaxis()->SetTitle("p/pBar");
    //ratPlot3->GetHistogram()->SetMinimum(0.8);
    //ratPlot3->GetHistogram()->SetMaximum(1.1);
    ratPlot3->SetMarkerStyle(8);
    ratPlot3->SetMarkerSize(1);
    ratPlot3->SetMarkerColor(kBlack);
    ratPlot3->Draw("AP");
    c3->Draw();

}
