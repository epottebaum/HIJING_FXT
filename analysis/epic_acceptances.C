// Jan 22, 2025
// Draw P-eta detector acceptance regions for ePIC
#include <TROOT.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <iterator>

// Momenta (p) for each detector's (eta, p) acceptance region
double pfRICH_P[5] = {8.6, 8.6, 2.0, 2.0, 8.6};
double ToF_HRPPD_P[5] = {2.7, 2.8, 0.11, 0.8, 2.7}; // same eta as pfRICH
double hpDIRC_P[5] = {5.98, 5.98, 0.48, 0.48, 5.98};
double ToF_barrel_P[5] = {1.75, 1.76, 0.17, 0.17, 1.75};
double dRICH_gas_P[5] = {51.9, 51.9, 4.02, 4.02, 51.9};
double dRICH_gel_P[5] = {16.4, 14.9, 1.4, 1.4, 16.4};
double ToF_HD_P[5] = {2.47, 2.42, 0.57, 0.11, 2.47};
double SVT_P[5] = {200, 200, 0.5, 0.5, 200}; // 200 is a placeholder, PDR says anything >= 0.5 GeV

// Detector geometry. Everything in centimeters
// IR = inner radius
// OR = outer radius
// physStart, physEnd = physical start/end as measured from z=0
double pfRICH_IR = 9.5;
double pfRICH_OR = 65.0;
double pfRICH_physStart = -172.7;
double pfRICH_physEnd = -123.6;

double hpDIRC_IR = 75.5;
double hpDIRC_OR = 78.6; // not used in eta calculation
double hpDIRC_physStart = -273.0;
double hpDIRC_physEnd = 185.0;

double ToF_barrel_IR = 62.0;
double ToF_barrel_OR = 69.5; // not used in eta calculation
double ToF_barrel_physStart = -117.5;
double ToF_barrel_physEnd = 171.5;

double dRICH_gas_IR = 22.0;
double dRICH_gas_OR = 180.0;
double dRICH_gas_physStart = 231.0;
double dRICH_gas_physEnd = 325.0;

double dRICH_gel_IR = 22.0;
double dRICH_gel_OR = 109.4;
double dRICH_gel_physStart = 198.0;
double dRICH_gel_physEnd = 231.0;

double ToF_HD_IR = 10.5;
double ToF_HD_OR = 60.0;
double ToF_HD_physStart = 185.0;
double ToF_HD_physEnd = 193.0;

// Tracking
double SiL1_IR = 3.6;
double SiL1_OR = 4.1;
double SiL1_physStart = -13.5;
double SiL1_physEnd = 13.5;

double SiL2_IR = 4.8;
double SiL2_OR = 5.3;
double SiL2_physStart = -13.5;
double SiL2_physEnd = 13.5;

double SiL3_IR = 12;
double SiL3_OR = 12.5;
double SiL3_physStart = -13.5;
double SiL3_physEnd = 13.5;

double SiL4_IR = 27;
double SiL4_OR = 27.5;
double SiL4_physStart = -27;
double SiL4_physEnd = 27;

double SiL5_IR = 42;
double SiL5_OR = 42.5;
double SiL5_physStart = -40;
double SiL5_physEnd = 40;

double SiHD1_IR = 3.676;
double SiHD1_OR = 23;
double SiHD1_physStart = 23.75;
double SiHD1_physEnd = 26.25;

double SiHD2_IR = 3.676;
double SiHD2_OR = 43;
double SiHD2_physStart = 43.75;
double SiHD2_physEnd = 46.25;

double SiHD3_IR = 3.842;
double SiHD3_OR = 43;
double SiHD3_physStart = 68.75;
double SiHD3_physEnd = 71.25;

double SiHD4_IR = 5.443;
double SiHD4_OR = 43;
double SiHD4_physStart = 98.75;
double SiHD4_physEnd = 101.25;

double SiHD5_IR = 7.014;
double SiHD5_OR = 43;
double SiHD5_physStart = 133.75;
double SiHD5_physEnd = 136.25;

double SiLD1_IR = 3.676;
double SiLD1_OR = 23;
double SiLD1_physStart = -26.25;
double SiLD1_physEnd = -23.75;

double SiLD2_IR = 3.676;
double SiLD2_OR = 43;
double SiLD2_physStart = -46.25;
double SiLD2_physEnd = -43.75;

double SiLD3_IR = 3.676;
double SiLD3_OR = 43;
double SiLD3_physStart = -66.25;
double SiLD3_physEnd = -63.75;

double SiLD4_IR = 4.006;
double SiLD4_OR = 43;
double SiLD4_physStart = -86.25;
double SiLD4_physEnd = -83.75;

double SiLD5_IR = 4.635;
double SiLD5_OR = 43;
double SiLD5_physStart = -106.25;
double SiLD5_physEnd = -103.75;


double calc_eta(double theta){
  // -1 * ln[ tan(theta/2) ]
  return -1 * TMath::Log( TMath::Tan(TMath::Abs(theta) / 2.0) );
}

// TODO
// for all get_eta functions, add check to make sure physStart, physEnd match detector type (backward, forward, barrel)


// Calculate effective pseudorapidity for detectors entirely in backward region
// dz = z location of target
void get_eta_backward(double etaArr[], double IR, double OR, double physStart, double physEnd, double dz){
  //double thetaLow = TMath::ATan(IR / TMath::Abs(physStart - dz));
  double thetaLow = TMath::ATan(IR / TMath::Abs(physEnd - dz)); // from inner face
  double thetaHigh = TMath::ATan(OR / TMath::Abs(physEnd - dz));
  double etaLow = -1 * calc_eta(thetaLow);
  double etaHigh = -1 * calc_eta(thetaHigh);
  etaArr[0] = etaLow;
  etaArr[1] = etaHigh;
  etaArr[2] = etaHigh;
  etaArr[3] = etaLow;
  etaArr[4] = etaLow;
}

// Calculate effective pseudorapidity for detectors entirely in forward region
void get_eta_forward(double etaArr[], double IR, double OR, double physStart, double physEnd, double dz){
  double thetaLow = TMath::ATan(OR / TMath::Abs(physStart - dz));
  //double thetaHigh = TMath::ATan(IR / TMath::Abs(physEnd - dz));
  double thetaHigh = TMath::ATan(IR / TMath::Abs(physStart - dz)); // from inner face
  double etaLow = calc_eta(thetaLow);
  double etaHigh = calc_eta(thetaHigh);
  etaArr[0] = etaLow;
  etaArr[1] = etaHigh;
  etaArr[2] = etaHigh;
  etaArr[3] = etaLow;
  etaArr[4] = etaLow;
}

// Calculate effective pseudorapidity for barrel detectors that start in backward region, end in forward region
// Going from inner radius is probably not realistic but IR vs OR doesn't change things much so fine to first order
void get_eta_barrel(double etaArr[], double IR, double physStart, double physEnd, double dz){
  double thetaLow = TMath::ATan(IR / TMath::Abs(physStart - dz));
  double thetaHigh = TMath::ATan(IR / TMath::Abs(physEnd - dz));
  double etaLow = -1 * calc_eta(thetaLow);
  double etaHigh = calc_eta(thetaHigh);
  etaArr[0] = etaLow;
  etaArr[1] = etaHigh;
  etaArr[2] = etaHigh;
  etaArr[3] = etaLow;
  etaArr[4] = etaLow;
}

void get_eta(double etaArr[], double IR, double OR, double physStart, double physEnd, double dz){
  if (dz < physStart){
    get_eta_forward(etaArr, IR, OR, physStart, physEnd, dz);
  }
  else if (dz > physEnd){
    get_eta_backward(etaArr, IR, OR, physStart, physEnd, dz);
  }
  else {
    get_eta_barrel(etaArr, IR, physStart, physEnd, dz);
  }
}

void set_pl(TPolyLine *pl){
  pl->SetFillColor(38);
  pl->SetLineColor(1);
  pl->SetLineWidth(3);
}

// PID and track: set to 1 to draw associated detector acceptances
// set drawHist to 1 to draw acceptances on their own (run macro by itself)
void epic_acceptances(double dz=0, int track = 0, int PID = 1, int drawHist=0){
  double textsize = 0.04;
  int lw = 3; // line width

  if (drawHist == 1){
  	TCanvas *c = new TCanvas();
  	c->cd();
  	gPad->SetLogy();
  	TH2F *h = new TH2F("h", "h", 10, -5, 5, 10, 0.08, 300);
  	h->Draw();
  }


  if (track == 1){
    double SiL1_eta[5];
    double SiL2_eta[5];
    double SiL3_eta[5];
    double SiL4_eta[5];
    double SiL5_eta[5];
    double SiHD1_eta[5];
    double SiHD2_eta[5];
    double SiHD3_eta[5];
    double SiHD4_eta[5];
    double SiHD5_eta[5];
    double SiLD1_eta[5];
    double SiLD2_eta[5];
    double SiLD3_eta[5];
    double SiLD4_eta[5];
    double SiLD5_eta[5];
    
    get_eta(SiL1_eta, SiL1_IR, SiL1_OR, SiL1_physStart, SiL1_physEnd, dz);
    get_eta(SiL2_eta, SiL2_IR, SiL2_OR, SiL2_physStart, SiL2_physEnd, dz);
    get_eta(SiL3_eta, SiL3_IR, SiL3_OR, SiL3_physStart, SiL3_physEnd, dz);
    get_eta(SiL4_eta, SiL4_IR, SiL4_OR, SiL4_physStart, SiL4_physEnd, dz);
    get_eta(SiL5_eta, SiL5_IR, SiL5_OR, SiL5_physStart, SiL5_physEnd, dz);
    get_eta(SiHD1_eta, SiHD1_IR, SiHD1_OR, SiHD1_physStart, SiHD1_physEnd, dz);
    get_eta(SiHD2_eta, SiHD2_IR, SiHD2_OR, SiHD2_physStart, SiHD2_physEnd, dz);
    get_eta(SiHD3_eta, SiHD3_IR, SiHD3_OR, SiHD3_physStart, SiHD3_physEnd, dz);
    get_eta(SiHD4_eta, SiHD4_IR, SiHD4_OR, SiHD4_physStart, SiHD4_physEnd, dz);
    get_eta(SiHD5_eta, SiHD5_IR, SiHD5_OR, SiHD5_physStart, SiHD5_physEnd, dz);
    get_eta(SiLD1_eta, SiLD1_IR, SiLD1_OR, SiLD1_physStart, SiLD1_physEnd, dz);
    get_eta(SiLD2_eta, SiLD2_IR, SiLD2_OR, SiLD2_physStart, SiLD2_physEnd, dz);
    get_eta(SiLD3_eta, SiLD3_IR, SiLD3_OR, SiLD3_physStart, SiLD3_physEnd, dz);
    get_eta(SiLD4_eta, SiLD4_IR, SiLD4_OR, SiLD4_physStart, SiLD4_physEnd, dz);
    get_eta(SiLD5_eta, SiLD5_IR, SiLD5_OR, SiLD5_physStart, SiLD5_physEnd, dz);
    
    TPolyLine *pl_SiL1 = new TPolyLine(5, SiL1_eta, SVT_P);
    TPolyLine *pl_SiL2 = new TPolyLine(5, SiL2_eta, SVT_P);
    TPolyLine *pl_SiL3 = new TPolyLine(5, SiL3_eta, SVT_P);
    TPolyLine *pl_SiL4 = new TPolyLine(5, SiL4_eta, SVT_P);
    TPolyLine *pl_SiL5 = new TPolyLine(5, SiL5_eta, SVT_P);
    TPolyLine *pl_SiHD1 = new TPolyLine(5, SiHD1_eta, SVT_P);
    TPolyLine *pl_SiHD2 = new TPolyLine(5, SiHD2_eta, SVT_P);
    TPolyLine *pl_SiHD3 = new TPolyLine(5, SiHD3_eta, SVT_P);
    TPolyLine *pl_SiHD4 = new TPolyLine(5, SiHD4_eta, SVT_P);
    TPolyLine *pl_SiHD5 = new TPolyLine(5, SiHD5_eta, SVT_P);
    TPolyLine *pl_SiLD1 = new TPolyLine(5, SiLD1_eta, SVT_P);
    TPolyLine *pl_SiLD2 = new TPolyLine(5, SiLD2_eta, SVT_P);
    TPolyLine *pl_SiLD3 = new TPolyLine(5, SiLD3_eta, SVT_P);
    TPolyLine *pl_SiLD4 = new TPolyLine(5, SiLD4_eta, SVT_P);
    TPolyLine *pl_SiLD5 = new TPolyLine(5, SiLD5_eta, SVT_P);
    
    set_pl(pl_SiL1);
    set_pl(pl_SiL2);
    set_pl(pl_SiL3);
    set_pl(pl_SiL4);
    set_pl(pl_SiL5);
    set_pl(pl_SiHD1);
    set_pl(pl_SiHD2);
    set_pl(pl_SiHD3);
    set_pl(pl_SiHD4);
    set_pl(pl_SiHD5);
    set_pl(pl_SiLD1);
    set_pl(pl_SiLD2);
    set_pl(pl_SiLD3);
    set_pl(pl_SiLD4);
    set_pl(pl_SiLD5);
    
    pl_SiL1->Draw();
    pl_SiL2->Draw();
    pl_SiL3->Draw();
    pl_SiL4->Draw();
    pl_SiL5->Draw();
    pl_SiHD1->Draw();
    pl_SiHD2->Draw();
    pl_SiHD3->Draw();
    pl_SiHD4->Draw();
    pl_SiHD5->Draw();
    pl_SiLD1->Draw();
    pl_SiLD2->Draw();
    pl_SiLD3->Draw();
    pl_SiLD4->Draw();
    pl_SiLD5->Draw();

    //double SiL2_eta[5];
    //get_eta(SiL2_eta, SiL2_IR, SiL2_OR, SiL2_physStart, SiL2_physEnd, dz);
    
  } // end if(track)
  
  if (PID == 1){
    double pfRICH_eta[5];
    get_eta(pfRICH_eta, pfRICH_IR, pfRICH_OR, pfRICH_physStart, pfRICH_physEnd, dz);
    TPolyLine *pl_pfRICH = new TPolyLine(5, pfRICH_eta, pfRICH_P);
    pl_pfRICH->SetFillColor(38);
    pl_pfRICH->SetLineColor(1);
    pl_pfRICH->SetLineWidth(lw);
    TText *text_pfRICH = new TText(-3.2, 5, "pfRICH");
    text_pfRICH->SetTextSize(textsize);
    //text_pfRICH->Draw();
    pl_pfRICH->Draw();
    //std::cout << pfRICH_eta[0] << ", " << pfRICH_eta[1] << ", " << pfRICH_eta[2] << ", " << pfRICH_eta[3] << ", " << pfRICH_eta[4] << std::endl;

    TPolyLine *pl_ToF_HRPPD = new TPolyLine(5, pfRICH_eta, ToF_HRPPD_P);
    pl_ToF_HRPPD->SetFillColor(38);
    pl_ToF_HRPPD->SetLineColor(1);
    pl_ToF_HRPPD->SetLineWidth(lw);
    pl_ToF_HRPPD->SetLineStyle(9);
    TText *text_ToF_HRPPD = new TText(-3, 1.3, "ToF");
    TText *text_ToF_HRPPD2 = new TText(-3.2, 0.8, "(HRPPD)");
    text_ToF_HRPPD->SetTextSize(textsize);
    text_ToF_HRPPD2->SetTextSize(textsize);
    //text_ToF_HRPPD->Draw();
    //text_ToF_HRPPD2->Draw();
    pl_ToF_HRPPD->Draw();

    double hpDIRC_eta[5];
    get_eta(hpDIRC_eta, hpDIRC_IR, pfRICH_OR, hpDIRC_physStart, hpDIRC_physEnd, dz);
    TPolyLine *pl_hpDIRC = new TPolyLine(5, hpDIRC_eta, hpDIRC_P);
    pl_hpDIRC->SetFillColor(38);
    pl_hpDIRC->SetLineColor(1);
    pl_hpDIRC->SetLineWidth(lw);
    TText *text_hpDIRC = new TText(-0.5, 3.8, "hpDIRC");
    text_hpDIRC->SetTextSize(textsize);
    //text_hpDIRC->Draw();
    pl_hpDIRC->Draw();

    double ToF_barrel_eta[5];
    get_eta(ToF_barrel_eta, ToF_barrel_IR, ToF_barrel_OR, ToF_barrel_physStart, ToF_barrel_physEnd, dz);
    TPolyLine *pl_ToF_barrel = new TPolyLine(5, ToF_barrel_eta, ToF_barrel_P);
    pl_ToF_barrel->SetFillColor(38);
    pl_ToF_barrel->SetLineColor(1);
    pl_ToF_barrel->SetLineWidth(lw);
    pl_ToF_barrel->SetLineStyle(2);
    TText *text_ToF_barrel = new TText(-0.6, 0.3, "Barrel ToF");
    text_ToF_barrel->SetTextSize(textsize);
    //text_ToF_barrel->Draw();
    pl_ToF_barrel->Draw();

    double dRICH_gas_eta[5];
    get_eta(dRICH_gas_eta, dRICH_gas_IR, dRICH_gas_OR, dRICH_gas_physStart, dRICH_gas_physEnd, dz);
    TPolyLine *pl_dRICH_gas = new TPolyLine(5, dRICH_gas_eta, dRICH_gas_P);
    pl_dRICH_gas->SetFillColor(38);
    pl_dRICH_gas->SetLineColor(1);
    pl_dRICH_gas->SetLineWidth(lw);
    TText *text_dRICH_gas = new TText(1.15, 30, "dRICH (gas)");
    text_dRICH_gas->SetTextSize(textsize);
    //text_dRICH_gas->Draw();
    pl_dRICH_gas->Draw();

    double dRICH_gel_eta[5];
    get_eta(dRICH_gel_eta, dRICH_gel_IR, dRICH_gel_OR, dRICH_gel_physStart, dRICH_gel_physEnd, dz);
    TPolyLine *pl_dRICH_gel = new TPolyLine(5, dRICH_gel_eta, dRICH_gel_P);
    pl_dRICH_gel->SetFillColor(38);
    pl_dRICH_gel->SetLineColor(1);
    pl_dRICH_gel->SetLineWidth(lw);
    pl_dRICH_gel->SetLineStyle(9);
    TText *text_dRICH_gel = new TText(1.5, 9.5, "dRICH");
    TText *text_dRICH_gel2 = new TText(1.5, 6.8, "(aerogel)");
    text_dRICH_gel->SetTextSize(textsize);
    text_dRICH_gel2->SetTextSize(textsize);
    //text_dRICH_gel->Draw();
    //text_dRICH_gel2->Draw();
    pl_dRICH_gel->Draw();

    double ToF_HD_eta[5];
    get_eta(ToF_HD_eta, ToF_HD_IR, ToF_HD_OR, ToF_HD_physStart, ToF_HD_physEnd, dz);
    TPolyLine *pl_ToF_HD = new TPolyLine(5, ToF_HD_eta, ToF_HD_P);
    pl_ToF_HD->SetFillColor(38);
    pl_ToF_HD->SetLineColor(1);
    pl_ToF_HD->SetLineWidth(lw);
    TText *text_ToF_HD = new TText(2, 0.7, "HD ToF");
    text_ToF_HD->SetTextSize(textsize);
    //text_ToF_HD->Draw();
    pl_ToF_HD->Draw();
  } // end if (PID)
}



