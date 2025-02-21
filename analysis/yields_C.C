// Jan 7 2025 -- recreate Fig. 19 in BES bulk properties paper (Physical Review C 96, 044904 (2017))
#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <TTree.h>
#include <TH1F.h>
#include <iostream>
#include <fstream>
#include <string>

TChain hijTree("hijTree");

//int include_C = 1;

float rat_err(int N1, int N2) {
    double err1 = sqrt(N1) / N2;
    double err2 = (N1 * sqrt(N2)) / pow(N2, 2);
    return (float)err1 + (float)err2;
}

void yields_C(){
	// open text files with yield values	
	std::ifstream f70cm("yields_C_11p5GeV.txt");
	std::ifstream f100cm("yields_C_13p7GeV.txt");
	std::ifstream f19p6("yields_C_19p6GeV.txt");
	std::ifstream f27("yields_C_27GeV.txt");
	std::ifstream f39("yields_C_39GeV.txt");

	// skip first 3 lines
	for (int i = 0; i < 3; i++){
		std::string line;
		std::getline(f70cm, line);
		std::getline(f100cm, line);
		std::getline(f19p6, line);
		std::getline(f27, line);
		std::getline(f39, line);

	}

	int pi_m11p5[9];
	int pi_m13p7[9];
	int pi_m19p6[9];
	int pi_m27[9];
	int pi_m39[9];

   	int pi_p11p5[9];
   	int pi_p13p7[9];
	int pi_p19p6[9];
	int pi_p27[9];
	int pi_p39[9];

    int k_m11p5[9];
   	int k_m13p7[9];
	int k_m19p6[9];
	int k_m27[9];
	int k_m39[9];

    int k_p11p5[9];
   	int k_p13p7[9];
	int k_p19p6[9];
	int k_p27[9];
	int k_p39[9];

	int pbar11p5[9];
   	int pbar13p7[9];
	int pbar19p6[9];
	int pbar27[9];
	int pbar39[9];

    int p11p5[9];
   	int p13p7[9];
	int p19p6[9];
	int p27[9];
	int p39[9];

	std::string line1;
	std::string line2;
	std::string line3;
	std::string line4;
	std::string line5;

	std::string line1cm;
	std::string line2cm;
	std::string line3cm;
	std::string line4cm;
	std::string line5cm;

	// sure yeah let's do 6 of the same loops that's an efficient plan
	for (int i = 0; i < 9; i++) { // loop over each centrality class
		std::getline(f70cm, line1cm, ' ');
       	std::getline(f100cm, line2cm, ' ');
		std::getline(f19p6, line3cm, ' ');
		std::getline(f27, line4cm, ' ');
		std::getline(f39, line5cm, ' ');		
		pi_m11p5[i] = std::stof(line1cm.c_str());
		pi_m13p7[i] = std::stof(line2cm.c_str());
		pi_m19p6[i] = std::stof(line3cm.c_str());
		pi_m27[i] = std::stof(line4cm.c_str());
		pi_m39[i] = std::stof(line5cm.c_str());

	} // pi-

	for (int i = 0; i < 9; i++) {
		std::getline(f70cm, line1cm, ' ');
		std::getline(f100cm, line2cm, ' ');
        std::getline(f19p6, line3cm, ' ');
        std::getline(f27, line4cm, ' ');
        std::getline(f39, line5cm, ' ');
		pi_p11p5[i] = std::stof(line1cm.c_str());
		pi_p13p7[i] = std::stof(line2cm.c_str());
		pi_p19p6[i] = std::stof(line3cm.c_str());
		pi_p27[i] = std::stof(line4cm.c_str());
		pi_p39[i] = std::stof(line5cm.c_str());
	} // pi+

	for (int i = 0; i < 9; i++) {
		std::getline(f70cm, line1cm, ' ');
		std::getline(f100cm, line2cm, ' ');
        std::getline(f19p6, line3cm, ' ');
        std::getline(f27, line4cm, ' ');
        std::getline(f39, line5cm, ' ');
		k_m11p5[i] = std::stof(line1cm.c_str());
		k_m13p7[i] = std::stof(line2cm.c_str());
		k_m19p6[i] = std::stof(line3cm.c_str());
		k_m27[i] = std::stof(line4cm.c_str());
		k_m39[i] = std::stof(line5cm.c_str());

	} // K-

	for (int i = 0; i < 9; i++) {	
		std::getline(f70cm, line1cm, ' ');
		std::getline(f100cm, line2cm, ' ');
        std::getline(f19p6, line3cm, ' ');
        std::getline(f27, line4cm, ' ');
        std::getline(f39, line5cm, ' ');
		k_p11p5[i] = std::stof(line1cm.c_str());
		k_p13p7[i] = std::stof(line2cm.c_str());
		k_p19p6[i] = std::stof(line3cm.c_str());
		k_p27[i] = std::stof(line4cm.c_str());
		k_p39[i] = std::stof(line5cm.c_str());

	} // K+

	for (int i = 0; i < 9; i++) {
		std::getline(f70cm, line1cm, ' ');
		std::getline(f100cm, line2cm, ' ');
        std::getline(f19p6, line3cm, ' ');
        std::getline(f27, line4cm, ' ');
        std::getline(f39, line5cm, ' ');
		pbar11p5[i] = std::stof(line1cm.c_str());
		pbar13p7[i] = std::stof(line2cm.c_str());
		pbar19p6[i] = std::stof(line3cm.c_str());
		pbar27[i] = std::stof(line4cm.c_str());
		pbar39[i] = std::stof(line5cm.c_str());
	} // Pbar

	for (int i = 0; i < 9; i++) {
		std::getline(f70cm, line1cm, ' ');
		std::getline(f100cm, line2cm, ' ');
        std::getline(f19p6, line3cm, ' ');
        std::getline(f27, line4cm, ' ');
        std::getline(f39, line5cm, ' ');
		p11p5[i] = std::stof(line1cm.c_str());
		p13p7[i] = std::stof(line2cm.c_str());
		p19p6[i] = std::stof(line3cm.c_str());
		p27[i] = std::stof(line4cm.c_str());
		p39[i] = std::stof(line5cm.c_str());
	} // P

	f70cm.close();
	f100cm.close();
	f19p6.close();
	f27.close();
	f39.close();
	
	float pirats11p5[] = {0.,0.,0.,0.,0.,0.,0.,0.,0.};
   	float piraterr11p5[] = {0.,0.,0.,0.,0.,0.,0.,0.,0.};
	float krats11p5[] = {0.,0.,0.,0.,0.,0.,0.,0.,0.};
   	float kraterr11p5[] = {0.,0.,0.,0.,0.,0.,0.,0.,0.};
   	float prats11p5[] = {0.,0.,0.,0.,0.,0.,0.,0.,0.};
   	float praterr11p5[] = {0.,0.,0.,0.,0.,0.,0.,0.,0.};

   	float pirats13p7[] = {0.,0.,0.,0.,0.,0.,0.,0.,0.};
   	float piraterr13p7[] = {0.,0.,0.,0.,0.,0.,0.,0.,0.};
   	float krats13p7[] = {0.,0.,0.,0.,0.,0.,0.,0.,0.};
   	float kraterr13p7[] = {0.,0.,0.,0.,0.,0.,0.,0.,0.};
   	float prats13p7[] = {0.,0.,0.,0.,0.,0.,0.,0.,0.};
   	float praterr13p7[] = {0.,0.,0.,0.,0.,0.,0.,0.,0.};
	
    float pirats19p6[] = {0.,0.,0.,0.,0.,0.,0.,0.,0.};
    float piraterr19p6[] = {0.,0.,0.,0.,0.,0.,0.,0.,0.};
    float krats19p6[] = {0.,0.,0.,0.,0.,0.,0.,0.,0.};
    float kraterr19p6[] = {0.,0.,0.,0.,0.,0.,0.,0.,0.};
    float prats19p6[] = {0.,0.,0.,0.,0.,0.,0.,0.,0.};
    float praterr19p6[] = {0.,0.,0.,0.,0.,0.,0.,0.,0.};

    float pirats27[] = {0.,0.,0.,0.,0.,0.,0.,0.,0.};
    float piraterr27[] = {0.,0.,0.,0.,0.,0.,0.,0.,0.};
    float krats27[] = {0.,0.,0.,0.,0.,0.,0.,0.,0.};
    float kraterr27[] = {0.,0.,0.,0.,0.,0.,0.,0.,0.};
    float prats27[] = {0.,0.,0.,0.,0.,0.,0.,0.,0.};
    float praterr27[] = {0.,0.,0.,0.,0.,0.,0.,0.,0.};
	
    float pirats39[] = {0.,0.,0.,0.,0.,0.,0.,0.,0.};
    float piraterr39[] = {0.,0.,0.,0.,0.,0.,0.,0.,0.};
    float krats39[] = {0.,0.,0.,0.,0.,0.,0.,0.,0.};
    float kraterr39[] = {0.,0.,0.,0.,0.,0.,0.,0.,0.};
    float prats39[] = {0.,0.,0.,0.,0.,0.,0.,0.,0.};
    float praterr39[] = {0.,0.,0.,0.,0.,0.,0.,0.,0.};

	for (int i = 0; i < 9; i++){
       	pirats11p5[i] = (float)pi_m11p5[i] / (float)pi_p11p5[i];
       	piraterr11p5[i] = rat_err(pi_m11p5[i], pi_p11p5[i]);
       	krats11p5[i] = (float)k_m11p5[i] / (float)k_p11p5[i];
       	kraterr11p5[i] = rat_err(k_m11p5[i], k_p11p5[i]);
       	prats11p5[i] = (float)pbar11p5[i] / (float)p11p5[i];
       	praterr11p5[i] = rat_err(pbar11p5[i], p11p5[i]);

       	pirats13p7[i] = (float)pi_m13p7[i] / (float)pi_p13p7[i];
       	piraterr13p7[i] = rat_err(pi_m13p7[i], pi_p13p7[i]);
      	krats13p7[i] = (float)k_m13p7[i] / (float)k_p13p7[i];
       	kraterr13p7[i] = rat_err(k_m13p7[i], k_p13p7[i]);
       	prats13p7[i] = (float)pbar13p7[i] / (float) p13p7[i];
       	praterr13p7[i] = rat_err(pbar13p7[i], p13p7[i]);

        pirats19p6[i] = (float)pi_m19p6[i] / (float)pi_p19p6[i];
        piraterr19p6[i] = rat_err(pi_m19p6[i], pi_p19p6[i]);
        krats19p6[i] = (float)k_m19p6[i] / (float)k_p19p6[i];
        kraterr19p6[i] = rat_err(k_m19p6[i], k_p19p6[i]);
        prats19p6[i] = (float)pbar19p6[i] / (float) p19p6[i];
        praterr19p6[i] = rat_err(pbar19p6[i], p19p6[i]);

       	pirats27[i] = (float)pi_m27[i] / (float)pi_p27[i];
       	piraterr27[i] = rat_err(pi_m27[i], pi_p27[i]);
       	krats27[i] = (float)k_m27[i] / (float)k_p27[i];
       	kraterr27[i] = rat_err(k_m27[i], k_p27[i]);
   	    prats27[i] = (float)pbar27[i] / (float)p27[i];
        praterr27[i] = rat_err(pbar27[i], p27[i]);

        pirats39[i] = (float)pi_m39[i] / (float)pi_p39[i];
        piraterr39[i] = rat_err(pi_m39[i], pi_p39[i]);
        krats39[i] = (float)k_m39[i] / (float)k_p39[i];
        kraterr39[i] = rat_err(k_m39[i], k_p39[i]);
        prats39[i] = (float)pbar39[i] / (float)p39[i];
        praterr39[i] = rat_err(pbar39[i], p39[i]);
	} 

	TCanvas *c1 = new TCanvas("c1", "c1", 900, 500);
	c1->Divide(3,0,0.001,0.001);
	double marksize = 1.25;
	gPad->SetBottomMargin(0.001);
	// pions
	c1->cd(1);
	float xpts[] = {1,2,3,4,5,6,7,8,9};
	double piylow = 0.95;
	double piyhigh = 1.1;

	TGraphErrors *piratplot11p5 = new TGraphErrors(9, xpts, pirats11p5, nullptr, piraterr11p5);
    TGraphErrors *piratplot13p7 = new TGraphErrors(9, xpts, pirats13p7, nullptr, piraterr13p7);
    TGraphErrors *piratplot19p6 = new TGraphErrors(9, xpts, pirats19p6, nullptr, piraterr19p6);
    TGraphErrors *piratplot27 = new TGraphErrors(9, xpts, pirats27, nullptr, piraterr27);
    TGraphErrors *piratplot39 = new TGraphErrors(9, xpts, pirats39, nullptr, piraterr39);
    piratplot11p5->SetMarkerStyle(20); // filled circle
    piratplot13p7->SetMarkerStyle(28); // open plus
    piratplot19p6->SetMarkerStyle(25); // open square
    piratplot27->SetMarkerStyle(22); // filled triangle
    piratplot39->SetMarkerStyle(24); // open circle
    piratplot11p5->SetMarkerColor(kRed);
    piratplot13p7->SetMarkerColor(kViolet);
    piratplot19p6->SetMarkerColor(kBlue);
    piratplot27->SetMarkerColor(kGreen);
    piratplot39->SetMarkerColor(kRed);
    piratplot11p5->SetMarkerSize(marksize);
    piratplot13p7->SetMarkerSize(marksize);
    piratplot19p6->SetMarkerSize(marksize);
    piratplot27->SetMarkerSize(marksize+0.25);
    piratplot39->SetMarkerSize(marksize);
    piratplot11p5->GetYaxis()->SetRangeUser(piylow, piyhigh);
    piratplot13p7->GetYaxis()->SetRangeUser(piylow, piyhigh);
    piratplot19p6->GetYaxis()->SetRangeUser(piylow, piyhigh);
    piratplot27->GetYaxis()->SetRangeUser(piylow, piyhigh);
    piratplot39->GetYaxis()->SetRangeUser(piylow, piyhigh);
    piratplot11p5->SetTitle("");
    //piratplot11p5->GetYaxis()->SetTitle("#pi_{-}/#pi_{+}");
	//piratplot11p5->GetYaxis()->SetTitleOffset(-0.15);
	//piratplot11p5->GetYaxis()->SetTitleSize(0.07);
	//piratplot11p5->GetYaxis()->CenterTitle(true);
	const char* const c_labels[] = {"80-100", "60-80", "50-60", "40-50", "30-40", "20-30", "10-20", "5-10", "0-5"};
	for (int i = 0; i < 9; i++){
		piratplot11p5->GetXaxis()->ChangeLabel(i+1, 30, 0.045, -1, -1, -1, c_labels[i]);
	}
 	piratplot11p5->GetYaxis()->SetLabelSize(0.045); 
	piratplot11p5->Draw("AP");
    piratplot13p7->Draw("Psame");
    piratplot19p6->Draw("Psame");
    piratplot27->Draw("Psame");
    piratplot39->Draw("Psame");

	TLegend *leg1 = new TLegend(0.15, 0.15, 0.9, 0.35);
	leg1->SetNColumns(2);
	leg1->SetBorderSize(0);
	leg1->SetFillStyle(0);
	leg1->SetTextSize(0.06);
	leg1->AddEntry(piratplot11p5, "11.5 GeV", "P");
	leg1->AddEntry(piratplot27, "27 GeV", "P");
	leg1->AddEntry(piratplot13p7, "13.7 GeV", "P");
	leg1->AddEntry(piratplot39, "39 GeV", "P");
	leg1->AddEntry(piratplot19p6, "19.6 GeV", "P");
	leg1->Draw();
    TPaveText *pit = new TPaveText(0.17, 0.7, 0.32, 0.99, "NDC");
    pit->AddText("#pi^{-} / #pi^{+}");
    pit->SetBorderSize(0);
    pit->SetFillStyle(0);
    pit->Draw();


	// kaons
    c1->cd(2);
	//c1->SetBottomMargin(0.2);   
    double kylow = 0.5;
    double kyhigh = 0.9;
    TGraphErrors *kratplot11p5 = new TGraphErrors(9, xpts, krats11p5, nullptr, kraterr11p5);
    TGraphErrors *kratplot13p7 = new TGraphErrors(9, xpts, krats13p7, nullptr, kraterr13p7);
    TGraphErrors *kratplot19p6 = new TGraphErrors(9, xpts, krats19p6, nullptr, kraterr19p6);
    TGraphErrors *kratplot27 = new TGraphErrors(9, xpts, krats27, nullptr, kraterr27);
    TGraphErrors *kratplot39 = new TGraphErrors(9, xpts, krats39, nullptr, kraterr39);
    kratplot11p5->SetMarkerStyle(20); // filled circle
    kratplot13p7->SetMarkerStyle(28); // open plus
    kratplot19p6->SetMarkerStyle(25); // open square
    kratplot27->SetMarkerStyle(22); // filled triangle
    kratplot39->SetMarkerStyle(24); // open circle
    kratplot11p5->SetMarkerColor(kRed);
    kratplot13p7->SetMarkerColor(kViolet);
    kratplot19p6->SetMarkerColor(kBlue);
    kratplot27->SetMarkerColor(kGreen);
    kratplot39->SetMarkerColor(kRed);
    kratplot11p5->SetMarkerSize(marksize);
    kratplot13p7->SetMarkerSize(marksize);
    kratplot19p6->SetMarkerSize(marksize);
    kratplot27->SetMarkerSize(marksize+0.25);
    kratplot39->SetMarkerSize(marksize);
    kratplot11p5->GetYaxis()->SetRangeUser(kylow, kyhigh);
    kratplot13p7->GetYaxis()->SetRangeUser(kylow, kyhigh);
    kratplot19p6->GetYaxis()->SetRangeUser(kylow, kyhigh);
    kratplot27->GetYaxis()->SetRangeUser(kylow, kyhigh);
    kratplot39->GetYaxis()->SetRangeUser(kylow, kyhigh);


    
	kratplot11p5->GetXaxis()->SetTitle("Centrality [\%]");
	kratplot11p5->GetXaxis()->CenterTitle(true);
	kratplot11p5->GetXaxis()->SetTitleSize(0.05);
	kratplot11p5->GetYaxis()->SetLabelSize(0.045);
	kratplot11p5->SetTitle("Collider Mode");
	gStyle->SetTitleFontSize(0.08);
    for (int i = 0; i < 9; i++){
		kratplot11p5->GetXaxis()->ChangeLabel(i+1, 30, 0.045, -1, -1, -1, c_labels[i]);
/*		if ( (i<2) || (i>6) ){
        	kratplot11p5->GetXaxis()->ChangeLabel(i+1, 30, 0.045, -1, -1, -1, c_labels[i]);
    	}
		else {
			kratplot11p5->GetXaxis()->ChangeLabel(i+1, -1, 0, -1, -1, -1, "");
		}*/
	}

    kratplot11p5->Draw("AP");
    kratplot13p7->Draw("Psame");
    kratplot19p6->Draw("Psame");
    kratplot27->Draw("Psame");
    kratplot39->Draw("Psame");
	TPaveText *kt = new TPaveText(0.17, 0.7, 0.32, 0.99, "NDC");
    kt->AddText("K^{-} / K^{+}");
    kt->SetBorderSize(0);
    kt->SetFillStyle(0);
    kt->Draw();


	// protons
    c1->cd(3);
	gPad->SetLogy();
    double pylow = 0.08;
    double pyhigh = 1.2;
    TGraphErrors *pratplot11p5 = new TGraphErrors(9, xpts, prats11p5, nullptr, praterr11p5);
    TGraphErrors *pratplot13p7 = new TGraphErrors(9, xpts, prats13p7, nullptr, praterr13p7);
    TGraphErrors *pratplot19p6 = new TGraphErrors(9, xpts, prats19p6, nullptr, praterr19p6);
    TGraphErrors *pratplot27 = new TGraphErrors(9, xpts, prats27, nullptr, praterr27);
    TGraphErrors *pratplot39 = new TGraphErrors(9, xpts, prats39, nullptr, praterr39);
    pratplot11p5->SetMarkerStyle(20); // filled circle
    pratplot13p7->SetMarkerStyle(28); // open plus
    pratplot19p6->SetMarkerStyle(25); // open square
    pratplot27->SetMarkerStyle(22); // filled triangle
    pratplot39->SetMarkerStyle(24); // open circle
    pratplot11p5->SetMarkerColor(kRed);
    pratplot13p7->SetMarkerColor(kViolet);
    pratplot19p6->SetMarkerColor(kBlue);
    pratplot27->SetMarkerColor(kGreen);
    pratplot39->SetMarkerColor(kRed);
    pratplot11p5->SetMarkerSize(marksize);
    pratplot13p7->SetMarkerSize(marksize);
    pratplot19p6->SetMarkerSize(marksize);
    pratplot27->SetMarkerSize(marksize+0.25);
    pratplot39->SetMarkerSize(marksize);
    pratplot11p5->GetYaxis()->SetRangeUser(pylow, pyhigh);
    pratplot13p7->GetYaxis()->SetRangeUser(pylow, pyhigh);
    pratplot19p6->GetYaxis()->SetRangeUser(pylow, pyhigh);
    pratplot27->GetYaxis()->SetRangeUser(pylow, pyhigh);
    pratplot39->GetYaxis()->SetRangeUser(pylow, pyhigh);
	pratplot11p5->SetTitle("");
 

	pratplot11p5->GetYaxis()->SetLabelSize(0.045);
    for (int i = 0; i < 9; i++){
        pratplot11p5->GetXaxis()->ChangeLabel(i+1, 30, 0.045, -1, -1, -1, c_labels[i]);
    }

    pratplot11p5->Draw("AP");
    pratplot13p7->Draw("Psame");
    pratplot19p6->Draw("Psame");
    pratplot27->Draw("Psame");
    pratplot39->Draw("Psame");
	TPaveText *pt = new TPaveText(0.15, 0.75, 0.26, 0.96, "NDC");

    pt->AddText("#bar{P} / P");
    pt->SetBorderSize(0);
    pt->SetFillStyle(0);
    pt->Draw();

	//TPaveText *pit = new TPaveText(0.2, 0.8, 0.3, 0.8, "brNDC");
    //pit->AddText("#pi_{0}/#pi_{+}");
   // pit->SetBorderSize(0);
   // pit->SetFillStyle(0);
    //pit->Draw();
	//c1->Draw();


}
