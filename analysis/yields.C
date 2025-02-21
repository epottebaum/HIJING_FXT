// Dec 3 2024
#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <TTree.h>
#include <TH1F.h>
#include <iostream>
#include <fstream>
#include <string>

TChain hijTree("hijTree");

int include_C = 1;

float rat_err(int N1, int N2) {
    double err1 = sqrt(N1) / N2;
    double err2 = (N1 * sqrt(N2)) / pow(N2, 2);
    return (float)err1 + (float)err2;
}

void yields(){
	// open text files with yield values
	// std::ifstream f31p2("yields_31p2AGeV.txt"); // for some reason K-, K+, pbar yields are all 0
	std::ifstream f70("yields_CM11p5GeV.txt");
	std::ifstream f100("yields_CM13p7GeV.txt");
	std::ifstream f205("yields_LAB_19p6GeV.txt");
	std::ifstream f390("yields_LAB_27GeV.txt");
	std::ifstream f816("yields_LAB_39GeV.txt");	
	
	std::ifstream f70cm("yields_CMframe_11p5GeV.txt");
	std::ifstream f100cm("yields_CMframe_13p7GeV.txt");
	std::ifstream f19p6("yields_C_19p6GeV.txt");
	std::ifstream f27("yields_C_27GeV.txt");
	std::ifstream f39("yields_C_39GeV.txt");

	// skip first 3 lines
	for (int i = 0; i < 3; i++){
		std::string line;
		std::getline(f70, line);
		std::getline(f100, line);
		std::getline(f205, line);
		std::getline(f390, line);
		std::getline(f816, line);
		if (include_C==1){
			std::getline(f70cm, line);
			std::getline(f100cm, line);
			std::getline(f19p6, line);
			std::getline(f27, line);
			std::getline(f39, line);
		}
	}

	int pi_m70[9];
	int pi_m100[9];
	int pi_m205[9];
	int pi_m390[9];
	int pi_m816[9];	

	int pi_p70[9];
	int pi_p100[9];
	int pi_p205[9];
	int pi_p390[9];
	int pi_p816[9];

	int k_m70[9];
	int k_m100[9];
	int k_m205[9];
	int k_m390[9];
	int k_m816[9];

	int k_p70[9];
	int k_p100[9];
	int k_p205[9];
	int k_p390[9];
	int k_p816[9];

	int pbar70[9];
	int pbar100[9];
	int pbar205[9];
	int pbar390[9];
	int pbar816[9];

	int p70[9];
	int p100[9];
	int p205[9];
	int p390[9];
	int p816[9];

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
		std::getline(f70, line1, ' ');
		std::getline(f100, line2, ' ');
		std::getline(f205, line3, ' ');
		std::getline(f390, line4, ' ');
		std::getline(f816, line5, ' ');
		pi_m70[i] = std::stof(line1.c_str());
		pi_m100[i] = std::stof(line2.c_str());	
		pi_m205[i] = std::stof(line3.c_str());
		pi_m390[i] = std::stof(line4.c_str());
		pi_m816[i] = std::stof(line5.c_str());
		if (include_C==1){
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
		}
	} // pi-

	for (int i = 0; i < 9; i++) {
		std::getline(f70, line1, ' ');
		std::getline(f100, line2, ' ');
        std::getline(f205, line3, ' ');
        std::getline(f390, line4, ' ');
        std::getline(f816, line5, ' ');
		pi_p70[i] = std::stof(line1.c_str());
        pi_p100[i] = std::stof(line2.c_str());
		pi_p205[i] = std::stof(line3.c_str());
		pi_p390[i] = std::stof(line4.c_str());
		pi_p816[i] = std::stof(line5.c_str());
		if (include_C==1){
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
		}
	} // pi+

	for (int i = 0; i < 9; i++) {
		std::getline(f70, line1, ' ');
		std::getline(f100, line2, ' '); 
        std::getline(f205, line3, ' ');
        std::getline(f390, line4, ' ');
        std::getline(f816, line5, ' ');
        k_m70[i] = std::stof(line1.c_str());
        k_m100[i] = std::stof(line2.c_str());
		k_m205[i] = std::stof(line3.c_str());
		k_m390[i] = std::stof(line4.c_str());
		k_m816[i] = std::stof(line5.c_str());
		if (include_C==1){
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
		}
	} // K-

	for (int i = 0; i < 9; i++) {
		std::getline(f70, line1, ' ');
		std::getline(f100, line2, ' ');
        std::getline(f205, line3, ' ');
        std::getline(f390, line4, ' ');
        std::getline(f816, line5, ' ');
        k_p70[i] = std::stof(line1.c_str());
        k_p100[i] = std::stof(line2.c_str());
		k_p205[i] = std::stof(line3.c_str());
		k_p390[i] = std::stof(line4.c_str());
		k_p816[i] = std::stof(line5.c_str());
		if (include_C==1) {
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
		}
	} // K+

	for (int i = 0; i < 9; i++) {
		std::getline(f70, line1, ' ');
		std::getline(f100, line2, ' ');
        std::getline(f205, line3, ' ');
        std::getline(f390, line4, ' ');
        std::getline(f816, line5, ' ');
        pbar70[i] = std::stof(line1.c_str());
        pbar100[i] = std::stof(line2.c_str());
		pbar205[i] = std::stof(line3.c_str());
		pbar390[i] = std::stof(line4.c_str());
		pbar816[i] = std::stof(line5.c_str());
		if (include_C==1){
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
		}
	} // Pbar

	for (int i = 0; i < 9; i++) {
		std::getline(f70, line1, ' ');
		std::getline(f100, line2, ' ');
        std::getline(f205, line3, ' ');
        std::getline(f390, line4, ' ');
        std::getline(f816, line5, ' ');
        p70[i] = std::stof(line1.c_str());
        p100[i] = std::stof(line2.c_str());
		p205[i] = std::stof(line3.c_str());
		p390[i] = std::stof(line4.c_str());
		p816[i] = std::stof(line5.c_str());
		if (include_C==1) {
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
		}
	} // P

	f70.close();
	f100.close();
	f205.close();
	f390.close();
	f816.close();
	f70cm.close();
	f100cm.close();
	f19p6.close();
	f27.close();
	f39.close();
	
	float pirats70[] = {0.,0.,0.,0.,0.,0.,0.,0.,0.};
	float piraterr70[] = {0.,0.,0.,0.,0.,0.,0.,0.,0.};
	float krats70[] = {0.,0.,0.,0.,0.,0.,0.,0.,0.};
	float kraterr70[] = {0.,0.,0.,0.,0.,0.,0.,0.,0.};
	float prats70[] = {0.,0.,0.,0.,0.,0.,0.,0.,0.};
	float praterr70[] = {0.,0.,0.,0.,0.,0.,0.,0.,0.};

	float pirats100[] = {0.,0.,0.,0.,0.,0.,0.,0.,0.};
    float piraterr100[] = {0.,0.,0.,0.,0.,0.,0.,0.,0.};
    float krats100[] = {0.,0.,0.,0.,0.,0.,0.,0.,0.};
    float kraterr100[] = {0.,0.,0.,0.,0.,0.,0.,0.,0.};
    float prats100[] = {0.,0.,0.,0.,0.,0.,0.,0.,0.};
    float praterr100[] = {0.,0.,0.,0.,0.,0.,0.,0.,0.};

    float pirats205[] = {0.,0.,0.,0.,0.,0.,0.,0.,0.};
    float piraterr205[] = {0.,0.,0.,0.,0.,0.,0.,0.,0.};
    float krats205[] = {0.,0.,0.,0.,0.,0.,0.,0.,0.};
    float kraterr205[] = {0.,0.,0.,0.,0.,0.,0.,0.,0.};
    float prats205[] = {0.,0.,0.,0.,0.,0.,0.,0.,0.};
    float praterr205[] = {0.,0.,0.,0.,0.,0.,0.,0.,0.};

    float pirats390[] = {0.,0.,0.,0.,0.,0.,0.,0.,0.};
    float piraterr390[] = {0.,0.,0.,0.,0.,0.,0.,0.,0.};
    float krats390[] = {0.,0.,0.,0.,0.,0.,0.,0.,0.};
    float kraterr390[] = {0.,0.,0.,0.,0.,0.,0.,0.,0.};
    float prats390[] = {0.,0.,0.,0.,0.,0.,0.,0.,0.};
    float praterr390[] = {0.,0.,0.,0.,0.,0.,0.,0.,0.};

    float pirats816[] = {0.,0.,0.,0.,0.,0.,0.,0.,0.};
    float piraterr816[] = {0.,0.,0.,0.,0.,0.,0.,0.,0.};
    float krats816[] = {0.,0.,0.,0.,0.,0.,0.,0.,0.};
    float kraterr816[] = {0.,0.,0.,0.,0.,0.,0.,0.,0.};
    float prats816[] = {0.,0.,0.,0.,0.,0.,0.,0.,0.};
    float praterr816[] = {0.,0.,0.,0.,0.,0.,0.,0.,0.};

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
		pirats70[i] = (float)pi_m70[i] / (float)pi_p70[i];
		piraterr70[i] = rat_err(pi_m70[i], pi_p70[i]);
		krats70[i] = (float)k_m70[i] / (float)k_p70[i];
		kraterr70[i] = rat_err(k_m70[i], k_p70[i]);
		prats70[i] = (float)pbar70[i] / (float)p70[i];
		praterr70[i] = rat_err(pbar70[i], p70[i]);

		pirats100[i] = (float)pi_m100[i] / (float)pi_p100[i];
		piraterr100[i] = rat_err(pi_m100[i], pi_p100[i]);
		krats100[i] = (float)k_m100[i] / (float)k_p100[i];
		kraterr100[i] = rat_err(k_m100[i], k_p100[i]);
		prats100[i] = (float)pbar100[i] / (float) p100[i];
		praterr100[i] = rat_err(pbar100[i], p100[i]);

        pirats205[i] = (float)pi_m205[i] / (float)pi_p205[i];
        piraterr205[i] = rat_err(pi_m205[i], pi_p205[i]);
        krats205[i] = (float)k_m205[i] / (float)k_p205[i];
        kraterr205[i] = rat_err(k_m205[i], k_p205[i]);
        prats205[i] = (float)pbar205[i] / (float)p205[i];
        praterr205[i] = rat_err(pbar205[i], p205[i]);

        pirats390[i] = (float)pi_m390[i] / (float)pi_p390[i];
        piraterr390[i] = rat_err(pi_m390[i], pi_p390[i]);
        krats390[i] = (float)k_m390[i] / (float)k_p390[i];
        kraterr390[i] = rat_err(k_m390[i], k_p390[i]);
        prats390[i] = (float)pbar390[i] / (float)p390[i];
        praterr390[i] = rat_err(pbar390[i], p390[i]);

        pirats816[i] = (float)pi_m816[i] / (float)pi_p816[i];
        piraterr816[i] = rat_err(pi_m816[i], pi_p816[i]);
        krats816[i] = (float)k_m816[i] / (float)k_p816[i];
        kraterr816[i] = rat_err(k_m816[i], k_p816[i]);
        prats816[i] = (float)pbar816[i] / (float)p816[i];
        praterr816[i] = rat_err(pbar816[i], p816[i]);

		if (include_C==1){
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
	} 

	TCanvas *c1 = new TCanvas();
	c1->cd();
	//c1->SetGridx();
	float xpts[] = {1,2,3,4,5,6,7,8,9};
	double piylow = 0.9;
	double piyhigh = 1.2;
	TGraphErrors *piratplot70 = new TGraphErrors(9, xpts, pirats70, nullptr, piraterr70);
	TGraphErrors *piratplot100 = new TGraphErrors(9, xpts, pirats100, nullptr, piraterr100);
	TGraphErrors *piratplot205 = new TGraphErrors(9, xpts, pirats205, nullptr, piraterr205);
	TGraphErrors *piratplot390 = new TGraphErrors(9, xpts, pirats390, nullptr, piraterr390);
	TGraphErrors *piratplot816 = new TGraphErrors(9, xpts, pirats816, nullptr, piraterr816);
	piratplot70->GetXaxis()->SetTitle("Centrality [\%]");
    piratplot70->GetYaxis()->SetTitle("#pi_{-}/#pi_{+}");
	
	//TAxis ax1 = piratplot70->GetXaxis();
	const char* const c_labels[] = {"80-100", "60-80", "50-60", "40-50", "30-40", "20-30", "10-20", "5-10", "0-5"};
	for (int i = 0; i < 9; i++){
		piratplot70->GetXaxis()->ChangeLabel(i+1, -1, -1, -1, -1, -1, c_labels[i]);
	}
    piratplot70->SetMarkerStyle(20); // circle
    piratplot100->SetMarkerStyle(22); // triangle
	piratplot205->SetMarkerStyle(21); // square
	piratplot390->SetMarkerStyle(33); // diamond
	piratplot816->SetMarkerStyle(34); // plus
	double marksize = 1.25;
	piratplot70->SetMarkerSize(marksize);
	piratplot100->SetMarkerSize(marksize);
	piratplot205->SetMarkerSize(marksize);
	piratplot390->SetMarkerSize(marksize+0.25);
	piratplot816->SetMarkerSize(marksize);
	piratplot70->SetMarkerColor(kBlue);
    piratplot100->SetMarkerColor(kRed);	
	piratplot205->SetMarkerColor(kViolet);
	piratplot390->SetMarkerColor(kGreen+2);
	piratplot816->SetMarkerColor(kOrange+1);
	piratplot70->GetYaxis()->SetRangeUser(piylow, piyhigh);
    piratplot100->GetYaxis()->SetRangeUser(piylow, piyhigh);
	piratplot205->GetYaxis()->SetRangeUser(piylow, piyhigh);
	piratplot390->GetYaxis()->SetRangeUser(piylow, piyhigh);
	piratplot816->GetYaxis()->SetRangeUser(piylow, piyhigh);
	piratplot70->Draw("AP");
    piratplot100->Draw("Psame");
	piratplot205->Draw("Psame");
	piratplot390->Draw("Psame");
	piratplot816->Draw("Psame");
	TLegend *leg1 = new TLegend(0.45, 0.6, 0.9, 0.9);
    leg1->SetHeader("#sqrt{s_{NN}}: Mode");
	if (include_C==0){
		leg1->SetNColumns(2);
		leg1->AddEntry((TObject*)0, "11.5 GeV: ", "");
		leg1->AddEntry(piratplot70, "FXT", "P");
		leg1->AddEntry((TObject*)0, "13.7 GeV: ", "");
		leg1->AddEntry(piratplot100, "FXT", "P");
		leg1->AddEntry((TObject*)0, "19.6 GeV: ", "");
		leg1->AddEntry(piratplot205, "FXT", "P");
		leg1->AddEntry((TObject*)0, "27 GeV: ", "");
		leg1->AddEntry(piratplot390, "FXT", "P");
		leg1->AddEntry((TObject*)0, "39 GeV: ", "");
		leg1->AddEntry(piratplot816, "FXT", "P");
	}
	else{
		TGraphErrors *piratplot11p5 = new TGraphErrors(9, xpts, pirats11p5, nullptr, piraterr11p5);
		TGraphErrors *piratplot13p7 = new TGraphErrors(9, xpts, pirats13p7, nullptr, piraterr13p7);
		TGraphErrors *piratplot19p6 = new TGraphErrors(9, xpts, pirats19p6, nullptr, piraterr19p6);
		TGraphErrors *piratplot27 = new TGraphErrors(9, xpts, pirats27, nullptr, piraterr27);
		TGraphErrors *piratplot39 = new TGraphErrors(9, xpts, pirats39, nullptr, piraterr39);
		piratplot11p5->SetMarkerStyle(24); // open circle
		piratplot13p7->SetMarkerStyle(26); // open triangle
		piratplot19p6->SetMarkerStyle(25); // open square
		piratplot27->SetMarkerStyle(27); // open diamond
		piratplot39->SetMarkerStyle(28); // open plus
		piratplot11p5->SetMarkerColor(kBlue);
		piratplot13p7->SetMarkerColor(kRed);
		piratplot19p6->SetMarkerColor(kViolet);
		piratplot27->SetMarkerColor(kGreen+2); 
		piratplot39->SetMarkerColor(kOrange+1);
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
		piratplot11p5->Draw("Psame");
		piratplot13p7->Draw("Psame");
		piratplot19p6->Draw("Psame");
		piratplot27->Draw("Psame");
		piratplot39->Draw("Psame");
		leg1->SetNColumns(3);
        leg1->AddEntry((TObject*)0, "11.5 GeV: ", "");
        leg1->AddEntry(piratplot70, "FXT", "P");
		leg1->AddEntry(piratplot11p5, "C", "P");
        leg1->AddEntry((TObject*)0, "13.7 GeV: ", "");
        leg1->AddEntry(piratplot100, "FXT", "P");
		leg1->AddEntry(piratplot13p7, "C", "P");	
		leg1->AddEntry((TObject*)0, "19.6 GeV: ", "");
		leg1->AddEntry(piratplot205, "FXT", "P");		
		leg1->AddEntry(piratplot19p6, "C", "P");	
		leg1->AddEntry((TObject*)0, "27 GeV: ", "");
		leg1->AddEntry(piratplot390, "FXT", "P");
		leg1->AddEntry(piratplot27, "C", "P");
		leg1->AddEntry((TObject*)0, "39 GeV: ", "");	
		leg1->AddEntry(piratplot816, "FXT", "P");
		leg1->AddEntry(piratplot39, "C", "P");
	}
	leg1->Draw();
	c1->Draw();




    TCanvas *c2 = new TCanvas();
    c2->cd();
    double kylow = 0.3;
    double kyhigh = 1.4;
    TGraphErrors *kratplot70 = new TGraphErrors(9, xpts, krats70, nullptr, kraterr70);
    TGraphErrors *kratplot100 = new TGraphErrors(9, xpts, krats100, nullptr, kraterr100);
    TGraphErrors *kratplot205 = new TGraphErrors(9, xpts, krats205, nullptr, kraterr205);
    TGraphErrors *kratplot390 = new TGraphErrors(9, xpts, krats390, nullptr, kraterr390);
    TGraphErrors *kratplot816 = new TGraphErrors(9, xpts, krats816, nullptr, kraterr816);
    kratplot70->GetXaxis()->SetTitle("Centrality [\%]");
    kratplot70->GetYaxis()->SetTitle("K_{-}/K_{+}");
	for (int i = 0; i < 9; i++){
        kratplot70->GetXaxis()->ChangeLabel(i+1, -1, -1, -1, -1, -1, c_labels[i]);
    }
    kratplot70->SetMarkerStyle(20); // circle
    kratplot100->SetMarkerStyle(22); // triangle
    kratplot205->SetMarkerStyle(21); // square
    kratplot390->SetMarkerStyle(33); // diamond
    kratplot816->SetMarkerStyle(34); // plus 
    kratplot70->SetMarkerSize(marksize);
    kratplot100->SetMarkerSize(marksize);
    kratplot205->SetMarkerSize(marksize);
    kratplot390->SetMarkerSize(marksize+0.25);
    kratplot816->SetMarkerSize(marksize);
    kratplot70->SetMarkerColor(kBlue);
    kratplot100->SetMarkerColor(kRed);
    kratplot205->SetMarkerColor(kViolet);
    kratplot390->SetMarkerColor(kGreen+2);
    kratplot816->SetMarkerColor(kOrange+1);
    kratplot70->GetYaxis()->SetRangeUser(kylow, kyhigh);
    kratplot100->GetYaxis()->SetRangeUser(kylow, kyhigh);
    kratplot205->GetYaxis()->SetRangeUser(kylow, kyhigh);
    kratplot390->GetYaxis()->SetRangeUser(kylow, kyhigh);
    kratplot816->GetYaxis()->SetRangeUser(kylow, kyhigh);
    kratplot70->Draw("AP");
    kratplot100->Draw("Psame");
    kratplot205->Draw("Psame");
    kratplot390->Draw("Psame");
    kratplot816->Draw("Psame");
    TLegend *leg2 = new TLegend(0.45, 0.6, 0.9, 0.9);
    leg2->SetHeader("#sqrt{s_{NN}}: Mode");
    if (include_C==0){
        leg2->SetNColumns(2);
        leg2->AddEntry((TObject*)0, "11.5 GeV: ", "");
        leg2->AddEntry(kratplot70, "FXT", "P");
        leg2->AddEntry((TObject*)0, "13.7 GeV: ", "");
        leg2->AddEntry(kratplot100, "FXT", "P");
        leg2->AddEntry((TObject*)0, "19.6 GeV: ", "");
        leg2->AddEntry(kratplot205, "FXT", "P");
        leg2->AddEntry((TObject*)0, "27 GeV: ", "");
        leg2->AddEntry(kratplot390, "FXT", "P");
        leg2->AddEntry((TObject*)0, "39 GeV: ", "");
        leg2->AddEntry(kratplot816, "FXT", "P");
    }
    else{
        TGraphErrors *kratplot11p5 = new TGraphErrors(9, xpts, krats11p5, nullptr, kraterr11p5);
        TGraphErrors *kratplot13p7 = new TGraphErrors(9, xpts, krats13p7, nullptr, kraterr13p7);
        TGraphErrors *kratplot19p6 = new TGraphErrors(9, xpts, krats19p6, nullptr, kraterr19p6);
        TGraphErrors *kratplot27 = new TGraphErrors(9, xpts, krats27, nullptr, kraterr27);
        TGraphErrors *kratplot39 = new TGraphErrors(9, xpts, krats39, nullptr, kraterr39);
        kratplot11p5->SetMarkerStyle(24); // open circle
        kratplot13p7->SetMarkerStyle(26); // open triangle
        kratplot19p6->SetMarkerStyle(25); // open square
        kratplot27->SetMarkerStyle(27); // open diamond
        kratplot39->SetMarkerStyle(28); // open plus
        kratplot11p5->SetMarkerColor(kBlue);
        kratplot13p7->SetMarkerColor(kRed);
        kratplot19p6->SetMarkerColor(kViolet);
        kratplot27->SetMarkerColor(kGreen+2);
        kratplot39->SetMarkerColor(kOrange+1);
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
        kratplot11p5->Draw("Psame");
        kratplot13p7->Draw("Psame");
        kratplot19p6->Draw("Psame");
        kratplot27->Draw("Psame");
        kratplot39->Draw("Psame");
        leg2->SetNColumns(3);
        leg2->AddEntry((TObject*)0, "11.5 GeV: ", "");
        leg2->AddEntry(kratplot70, "FXT", "P");
        leg2->AddEntry(kratplot11p5, "C", "P");
        leg2->AddEntry((TObject*)0, "13.7 GeV: ", "");
        leg2->AddEntry(kratplot100, "FXT", "P");
        leg2->AddEntry(kratplot13p7, "C", "P");
        leg2->AddEntry((TObject*)0, "19.6 GeV: ", "");
        leg2->AddEntry(kratplot205, "FXT", "P");
        leg2->AddEntry(kratplot19p6, "C", "P");
        leg2->AddEntry((TObject*)0, "27 GeV: ", "");
        leg2->AddEntry(kratplot390, "FXT", "P");
        leg2->AddEntry(kratplot27, "C", "P");
        leg2->AddEntry((TObject*)0, "39 GeV: ", "");
        leg2->AddEntry(kratplot816, "FXT", "P");
        leg2->AddEntry(kratplot39, "C", "P");
    }
    leg2->Draw();
    c2->Draw();


	TCanvas *c3 = new TCanvas();
    c3->cd();
	c3->SetLogy(); 
    double pylow = 0.001;
    double pyhigh = 50;
    TGraphErrors *pratplot70 = new TGraphErrors(9, xpts, prats70, nullptr, praterr70);
    TGraphErrors *pratplot100 = new TGraphErrors(9, xpts, prats100, nullptr, praterr100);
    TGraphErrors *pratplot205 = new TGraphErrors(9, xpts, prats205, nullptr, praterr205);
    TGraphErrors *pratplot390 = new TGraphErrors(9, xpts, prats390, nullptr, praterr390);
    TGraphErrors *pratplot816 = new TGraphErrors(9, xpts, prats816, nullptr, praterr816);
    pratplot70->GetXaxis()->SetTitle("Centrality [\%]");
    pratplot70->GetYaxis()->SetTitle("P_{-}/P_{+}");
	for (int i = 0; i < 9; i++){
        pratplot70->GetXaxis()->ChangeLabel(i+1, -1, -1, -1, -1, -1, c_labels[i]);
    }
    pratplot70->SetMarkerStyle(20); // circle
    pratplot100->SetMarkerStyle(22); // triangle
    pratplot205->SetMarkerStyle(21); // square
    pratplot390->SetMarkerStyle(33); // diamond
    pratplot816->SetMarkerStyle(34); // plus 
    pratplot70->SetMarkerSize(marksize);
    pratplot100->SetMarkerSize(marksize);
    pratplot205->SetMarkerSize(marksize);
    pratplot390->SetMarkerSize(marksize+0.25);
    pratplot816->SetMarkerSize(marksize);
    pratplot70->SetMarkerColor(kBlue);
    pratplot100->SetMarkerColor(kRed);
    pratplot205->SetMarkerColor(kViolet);
    pratplot390->SetMarkerColor(kGreen+2);
    pratplot816->SetMarkerColor(kOrange+1);
    pratplot70->GetYaxis()->SetRangeUser(pylow, pyhigh);
    pratplot100->GetYaxis()->SetRangeUser(pylow, pyhigh);
    pratplot205->GetYaxis()->SetRangeUser(pylow, pyhigh);
    pratplot390->GetYaxis()->SetRangeUser(pylow, pyhigh);
    pratplot816->GetYaxis()->SetRangeUser(pylow, pyhigh);
    pratplot70->Draw("AP");
    pratplot100->Draw("Psame");
    pratplot205->Draw("Psame");
    pratplot390->Draw("Psame");
    pratplot816->Draw("Psame");
    TLegend *leg3 = new TLegend(0.45, 0.6, 0.9, 0.9);
    leg3->SetHeader("#sqrt{s_{NN}}: Mode");
    if (include_C==0){
        leg3->SetNColumns(2);
        leg3->AddEntry((TObject*)0, "11.5 GeV: ", "");
        leg3->AddEntry(pratplot70, "FXT", "P");
        leg3->AddEntry((TObject*)0, "13.7 GeV: ", "");
        leg3->AddEntry(pratplot100, "FXT", "P");
        leg3->AddEntry((TObject*)0, "19.6 GeV: ", "");
        leg3->AddEntry(pratplot205, "FXT", "P");
        leg3->AddEntry((TObject*)0, "27 GeV: ", "");
        leg3->AddEntry(pratplot390, "FXT", "P");
        leg3->AddEntry((TObject*)0, "39 GeV: ", "");
        leg3->AddEntry(pratplot816, "FXT", "P");
    }
    else{
        TGraphErrors *pratplot11p5 = new TGraphErrors(9, xpts, prats11p5, nullptr, praterr11p5);
        TGraphErrors *pratplot13p7 = new TGraphErrors(9, xpts, prats13p7, nullptr, praterr13p7);
        TGraphErrors *pratplot19p6 = new TGraphErrors(9, xpts, prats19p6, nullptr, praterr19p6);
        TGraphErrors *pratplot27 = new TGraphErrors(9, xpts, prats27, nullptr, praterr27);
        TGraphErrors *pratplot39 = new TGraphErrors(9, xpts, prats39, nullptr, praterr39);
        pratplot11p5->SetMarkerStyle(24); // open circle
        pratplot13p7->SetMarkerStyle(26); // open triangle
        pratplot19p6->SetMarkerStyle(25); // open square
        pratplot27->SetMarkerStyle(27); // open diamond
        pratplot39->SetMarkerStyle(28); // open plus
        pratplot11p5->SetMarkerColor(kBlue);
        pratplot13p7->SetMarkerColor(kRed);
        pratplot19p6->SetMarkerColor(kViolet);
        pratplot27->SetMarkerColor(kGreen+2);
        pratplot39->SetMarkerColor(kOrange+1);
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
        pratplot11p5->Draw("Psame");
        pratplot13p7->Draw("Psame");
        pratplot19p6->Draw("Psame");
        pratplot27->Draw("Psame");
        pratplot39->Draw("Psame");
        leg3->SetNColumns(3);
        leg3->AddEntry((TObject*)0, "11.5 GeV: ", "");
        leg3->AddEntry(pratplot70, "FXT", "P");
        leg3->AddEntry(pratplot11p5, "C", "P");
        leg3->AddEntry((TObject*)0, "13.7 GeV: ", "");
        leg3->AddEntry(pratplot100, "FXT", "P");
        leg3->AddEntry(pratplot13p7, "C", "P");
        leg3->AddEntry((TObject*)0, "19.6 GeV: ", "");
        leg3->AddEntry(pratplot205, "FXT", "P");
        leg3->AddEntry(pratplot19p6, "C", "P");
        leg3->AddEntry((TObject*)0, "27 GeV: ", "");
        leg3->AddEntry(pratplot390, "FXT", "P");
        leg3->AddEntry(pratplot27, "C", "P");
        leg3->AddEntry((TObject*)0, "39 GeV: ", "");
        leg3->AddEntry(pratplot816, "FXT", "P");
        leg3->AddEntry(pratplot39, "C", "P");
    }
    leg3->Draw();
    c3->Draw();

/*

	TCanvas *c3 = new TCanvas();
	c3->cd();
	c3->SetLogy();
    TGraphErrors *pratplot70 = new TGraphErrors(9, xpts, prats70, nullptr, praterr70);
    TGraphErrors *pratplot100 = new TGraphErrors(9, xpts, prats100, nullptr, praterr100);
	TGraphErrors *pratplot11p5 = new TGraphErrors(9, xpts, prats11p5, nullptr, praterr11p5);
	TGraphErrors *pratplot13p7 = new TGraphErrors(9, xpts, prats13p7, nullptr, praterr13p7);
    pratplot70->GetXaxis()->SetTitle("Centrality Class [least to most, put in labels!]");
    pratplot70->GetYaxis()->SetTitle("Pbar/P");
    pratplot70->SetMarkerStyle(20); // circle
    pratplot100->SetMarkerStyle(22); // triangle
	pratplot11p5->SetMarkerStyle(24);
	pratplot13p7->SetMarkerStyle(26);
    pratplot70->SetMarkerColor(kBlue);
    pratplot100->SetMarkerColor(kRed);
	pratplot11p5->SetMarkerColor(38);
	pratplot13p7->SetMarkerColor(46);
	pratplot70->GetYaxis()->SetRangeUser(0.001, 10);
	pratplot100->GetYaxis()->SetRangeUser(0.001, 10);
	pratplot11p5->GetYaxis()->SetRangeUser(0.001, 10);
	pratplot13p7->GetYaxis()->SetRangeUser(0.001, 10);
    pratplot70->Draw("AP");
    pratplot100->Draw("Psame");
	pratplot11p5->Draw("Psame");
	pratplot13p7->Draw("Psame");
    TLegend *leg3 = new TLegend(0.55, 0.6, 0.9, 0.9);
    leg3->SetHeader("#sqrt{s_{NN}} | Mode");
    leg3->AddEntry(pratplot70, "11.5 GeV | FXT", "P");
	leg3->AddEntry(pratplot11p5, "11.5 GeV | C", "P");
    leg3->AddEntry(pratplot100, "13.7 GeV | FXT", "P");
	leg3->AddEntry(pratplot13p7, "13.7 GeV | C", "P");
    leg3->Draw();
    c3->Draw();
*/
}
