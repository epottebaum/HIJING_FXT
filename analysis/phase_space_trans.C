/*****************************************************************************************************/
// ROOT macro to transform momentum-pseudorapidity diagrams when interaction point (IP) is shifted   //
// author: Zoltan Varga			last updated: Jan 22, 2025                                   //
// email: zoltan.varga@yale.edu                                                                      //
/*****************************************************************************************************/

void phase_space_trans(double delta_z)
{

	double R = 100; // vertical distance between between IP and detector in EPIC (unit = centimeter)
	//double delta_z = 0; // shift in IP (unit = cm), negative if shifted to left
	

	TText *text_pfRICH = new TText(-3.0,2.0,"pfRICH");
	text_pfRICH->SetTextSize(0.04);

	Double_t x_pfRICH[5] = {-3.5, -1.5, -1.5, -3.5, -3.5};
   	Double_t y_pfRICH[5] = {0.5, 0.5, 3.0, 3.0, 0.5};
   	TPolyLine *pl_pfRICH = new TPolyLine(5, x_pfRICH, y_pfRICH);
   	pl_pfRICH->SetFillColor(38);
   	pl_pfRICH->SetLineColor(2);
   	pl_pfRICH->SetLineWidth(4);
   	
   	TText *text_hpDIRC = new TText(-0.75, 0.9,"hpDIRC");
	text_hpDIRC->SetTextSize(0.04);
   	
   	Double_t x_hpDIRC[12] = {-1.7, -1.5, -1.4, -0.8, -0.7, 0.7, 0.8, 1.1, 1.5, 1.5, -1.7, -1.7};
   	Double_t y_hpDIRC[12] = {0.35, 0.35, 0.3, 0.3, 0.25, 0.25, 0.35, 0.35, 0.55, 1.5, 1.5, 0.35};
   	TPolyLine *pl_hpDIRC = new TPolyLine(12, x_hpDIRC, y_hpDIRC);
   	pl_hpDIRC->SetFillColor(38);
   	pl_hpDIRC->SetLineColor(2);
   	pl_hpDIRC->SetLineWidth(4);
   	
   	TText *text_ToF = new TText(2.5, 0.5,"ToF");
	text_ToF->SetTextSize(0.04);
   	
   	Double_t x_ToF[5] = {2.05, 3.8, 3.8, 2.05, 2.05};
   	Double_t y_ToF[5] = {0.15, 0.55, 0.8, 0.8, 0.15};
   	TPolyLine *pl_ToF = new TPolyLine(5, x_ToF, y_ToF);
   	pl_ToF->SetFillColor(38);
   	pl_ToF->SetLineColor(2);
   	pl_ToF->SetLineWidth(4);

	TH2* h2_yield = new TH2F("h2_yield", "Relative yield of charged hadrons", 5000, -5.0, 5.0, 5000, 0.1, 100.0);
	h2_yield->GetXaxis()->SetTitle("#eta");
	h2_yield->GetYaxis()->SetTitle("Momentum (GeV/c)");
	h2_yield->SetStats(0);
	for (Int_t j=0;j<10000000;j++) h2_yield->Fill( gRandom->Gaus(0,0.5), gRandom->Exp(4) );

	//TFile *f = TFile::Open("test.root");
	
	TH2* h2_yield_shifted = new TH2F("h2_yield_shifted", "Relative yield of charged hadrons with shifted IP", 5000, -5.0, 5.0, 5000, 0.1, 100.0);
	h2_yield_shifted->GetXaxis()->SetTitle("#eta");
	h2_yield_shifted->GetYaxis()->SetTitle("Momentum (GeV/c)");
	h2_yield_shifted->SetStats(0);
	
	//----------------------------
	// Reading the 2D histogram (p,eta) content and transform pseudorapidity, then fill new histogram with new (p,eta') pair
	auto ax = h2_yield->GetXaxis();
   	auto ay = h2_yield->GetYaxis();
  	int n = 0;
  	double eta, eta_new, theta, p, pt, pz, pz_shifted;
   	for (int ix=0; ix<=h2_yield->GetNbinsX()+1; ix++){
      		for (int iy=0; iy<=h2_yield->GetNbinsY()+1; iy++){
        	 	if (h2_yield->GetBinContent(ix, iy) != 0){
        	    		//cout << ax->GetBinCenter(ix) << " " << ay->GetBinCenter(iy) << " " <<h2_yield->GetBinContent(ix, iy) << endl;
        	    		eta = ax->GetBinCenter(ix);
        	    		p = ay->GetBinCenter(iy);
        	    		if(p<0) p *= (-1); // can happen only during test
        	    		pt = p / TMath::CosH(eta);
        	    		pz = pt * TMath::SinH(eta);
        	    		pz_shifted = ((delta_z * pt) / R) + pz;
        	    		if(pz_shifted == 0) pz_shifted = 0.0001; // it can be zero with specific IP shifts
        	    		theta = atan2(pt, pz_shifted);
        	    		eta_new = -1 * TMath::Log(tan(theta/2));
        	    		
        	    		//cout << "eta: " << eta << "  p: " << p << "  pt: " << pt << "  pz: " << pz << "  eta_new: " << eta_new << "\n";
        	    		
        	    		for(int j = 0; j < h2_yield->GetBinContent(ix, iy); j++){
        	    			h2_yield_shifted->Fill(eta_new, p);
        	    		}
        	    		
        	    		n++;
        	 	}
     		}
   	}
   	//----------------------------
	
	TCanvas *c_yield = new TCanvas("c_yield", "Relative yield of charged hadrons", 900, 600);
	c_yield->SetLogy();
	
	//h2_yield->Draw();
	h2_yield_shifted->Draw();
	
	text_pfRICH->Draw();
	pl_pfRICH->Draw();
	
	text_hpDIRC->Draw();
	pl_hpDIRC->Draw();
	
	text_ToF->Draw();
	pl_ToF->Draw();
	
	c_yield -> SaveAs("yield.png");
}

