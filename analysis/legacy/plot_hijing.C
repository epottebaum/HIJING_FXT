// Make some histograms from the generated HIJING events
// This is mostly for me to remember how to do that
// author: Emily Pottebaum
// date: September 23, 2024

TChain chain("hijTree");

void plot_hijing(){

	//gSystem->Setenv("dir", "/gpfs/gibbs/project/havener/egp28/HIJING-out/hijout_1k_100x");
	gSystem->Setenv("dir", "/gpfs/gibbs/project/havener/egp28/HIJING-out/hijout_pp_1k_50x");
	for (int i = 0; i < 51; i++){
		std::string file = "$dir/hijout_pp_1k_" + std::to_string(i) + ".root";
		//std::cout << file << std::endl;
		char const* f = file.c_str();
		chain.Add(f);
	}
	TCut pions = "(fFlavCode==111) || (fFlavCode==211) || (fFlavCode==-211)";
	TCut kaons = "(fFlavCode==311) || (fFlavCode==321) || (fFlavCode==-321)";
	TCanvas *c = new TCanvas();
	c->cd();
	gPad->SetLogz();
	TH2F *etavpt = new TH2F("etavpt", "All final state particles", 50, 0, 5, 120, -8, 4);
	TBranch *fPt = chain.GetBranch("fPt");
	TBranch *fEta = chain.GetBranch("fEta");
	etavpt->GetXaxis()->SetTitle("p_{T} [GeV]");
	etavpt->GetYaxis()->SetTitle("#eta");
	chain.Draw("fEta:fPt >> etavpt");
	etavpt->Draw("COLZ");
	c->Draw();

	TCanvas *c1 = new TCanvas();
	c1->cd();
	gPad->SetLogz();
	TH2F *etavpt_pions = new TH2F("etavpt_pions", "All Pions", 50, 0, 5, 120, -8, 4);
	etavpt_pions->GetXaxis()->SetTitle("p_{T} [GeV]");
	etavpt_pions->GetYaxis()->SetTitle("#eta");
	chain.Draw("fEta:fPt >> etavpt_pions", pions);
	etavpt_pions->Draw("COLZ");
	c1->Draw(); 

	TCanvas *c0 = new TCanvas();
	c0->cd();
	gPad->SetLogz();
	TH2F *etavpt_kaons = new TH2F("etavpt_kaons", "All Kaons", 50, 0, 5, 120, -8, 4);
	etavpt_kaons->GetXaxis()->SetTitle("p_{T} [GeV]");	
	etavpt_kaons->GetYaxis()->SetTitle("#eta");
	chain.Draw("fEta:fPt >> etavpt_kaons", kaons);
	etavpt_kaons->Draw("COLZ");
	c0->Draw();

	TCanvas *c2 = new TCanvas();
	c2->cd();
	gPad->SetLogy();
	TH1F *pt = new TH1F("pt", " ", 100, 0, 5);
	TH1F *pt_pions = new TH1F("pt_pions", " ", 100, 0, 5);
	TH1F *pt_kaons = new TH1F("pt_kaons", " ", 100, 0, 5);
	pt->GetXaxis()->SetTitle("p_{T} [GeV]");
	pt->SetLineColor(kBlack);
	pt->SetLineWidth(2);
	pt_pions->SetLineColor(kRed);
	pt_pions->SetLineWidth(2);
	pt_kaons->SetLineColor(kAzure+7);
	pt_kaons->SetLineWidth(2);
	chain.Draw("fPt >> pt");
	chain.Draw("fPt >> pt_pions", pions);
	chain.Draw("fPt >> pt_kaons", kaons);
	pt->Draw();
	pt_pions->Draw("same");
	pt_kaons->Draw("same");
	TLegend *leg = new TLegend(0.55, 0.5, 0.85, 0.7);
	leg->SetHeader("Final State Particles");
	leg->AddEntry(pt, "all", "l");
	leg->AddEntry(pt_pions, "pions", "l");
	leg->AddEntry(pt_kaons, "kaons", "l");
	leg->Draw();
	c2->Draw();

	TCanvas *c3 = new TCanvas();
    c3->cd();
	gPad->SetLogy();
    TH1F *eta = new TH1F("eta", " ", 200, -8, 4);
    TH1F *eta_pions = new TH1F("eta_pions", " ", 200, -8, 4);
	TH1F *eta_kaons = new TH1F("eta_kaons", " ", 200, -8, 4);	
	eta->GetXaxis()->SetTitle("#eta");
    eta->SetLineColor(kBlack);
	eta->SetLineWidth(2);
    eta_pions->SetLineColor(kRed);
	eta_pions->SetLineWidth(2);
	eta_kaons->SetLineColor(kAzure+7);
	eta_kaons->SetLineWidth(2);
    chain.Draw("fEta >> eta");
    chain.Draw("fEta >> eta_pions", pions);
	chain.Draw("fEta >> eta_kaons", kaons);
    eta->Draw();
    eta_pions->Draw("same");
	eta_kaons->Draw("same");
    TLegend *leg2 = new TLegend(0.15, 0.6, 0.45, 0.8);
    leg2->SetHeader("Final State Particles");
    leg2->AddEntry(eta, "all", "l");
    leg2->AddEntry(eta_pions, "pions", "l");
	leg2->AddEntry(eta_kaons, "kaons", "l");
    leg2->Draw();
    c3->Draw();
}
