//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Thu Oct 17 15:05:33 2024 by ROOT version 6.26/06
// from TTree hijTree/hijTree
// found on file: hijout_100k.root
//////////////////////////////////////////////////////////

#ifndef hijTree_h
#define hijTree_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

// Header file for the classes stored in the TTree if any.

class hijTree {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

// Fixed size dimensions of array or collections stored in the TTree if any.

   // Declaration of leaf types
   Int_t           eventNum;
   Int_t           numParticles; 
   Float_t         b;
   Int_t           fPartNum[5000];   //[numParticles]
   Int_t           fFlavCode[5000];   //[numParticles]
   Int_t           fSource[5000];   //[numParticles]
   Int_t           fStatus[5000];   //[numParticles]
   Int_t           fCharge[5000];   //[numParticles]
   Int_t           fFromParticipant[5000];   //[numParticles]
   Float_t         fEn[5000];   //[numParticles]
   Float_t         fP[5000];
   Float_t         fPt[5000];   //[numParticles]
   Float_t         fEta[5000];   //[numParticles]
   Float_t         fY[5000];
   Float_t         fTheta[5000];   //[numParticles]
   Float_t         fPhi[5000];   //[numParticles]

   // List of branches
   TBranch        *b_eventNum;   //!
   TBranch        *b_numParticles;   //! 
   TBranch        *b_b;   //!
   TBranch        *b_fPartNum;   //!
   TBranch        *b_fFlavCode;   //!
   TBranch        *b_fSource;   //!
   TBranch        *b_fStatus;   //!
   TBranch        *b_fCharge;   //!
   TBranch        *b_fFromParticipant;   //!
   TBranch        *b_fEn;   //!
   TBranch        *b_fP;
   TBranch        *b_fPt;   //!
   TBranch        *b_fEta;   //!
   TBranch        *b_fY;
   TBranch        *b_fTheta;   //!
   TBranch        *b_fPhi;   //!

   hijTree(TTree *tree=0);
   virtual ~hijTree();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
};

#endif

#ifdef hijTree_cxx
hijTree::hijTree(TTree *tree) : fChain(0) 
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("/gpfs/gibbs/project/havener/egp28/HIJING-out/hijout_100k_minbias_FXT_13p7GeV.root");
      if (!f || !f->IsOpen()) {
         f = new TFile("/gpfs/gibbs/project/havener/egp28/HIJING-out/hijout_100k_minbias_FXT_13p7GeV.root", "update");
      }
      f->GetObject("hijTree",tree);

   }
   Init(tree);
}

hijTree::~hijTree()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t hijTree::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t hijTree::LoadTree(Long64_t entry)
{
// Set the environment to read one entry
   if (!fChain) return -5;
   Long64_t centry = fChain->LoadTree(entry);
   if (centry < 0) return centry;
   if (fChain->GetTreeNumber() != fCurrent) {
      fCurrent = fChain->GetTreeNumber();
      Notify();
   }
   return centry;
}

void hijTree::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("eventNum", &eventNum, &b_eventNum);
   fChain->SetBranchAddress("numParticles", &numParticles, &b_numParticles); 
   fChain->SetBranchAddress("b", &b, &b_b);
   fChain->SetBranchAddress("fPartNum", fPartNum, &b_fPartNum);
   fChain->SetBranchAddress("fFlavCode", fFlavCode, &b_fFlavCode);
   fChain->SetBranchAddress("fSource", fSource, &b_fSource);
   fChain->SetBranchAddress("fStatus", fStatus, &b_fStatus);
   fChain->SetBranchAddress("fCharge", fCharge, &b_fCharge);
   fChain->SetBranchAddress("fFromParticipant", fFromParticipant, &b_fFromParticipant);
   fChain->SetBranchAddress("fEn", fEn, &b_fEn);
   fChain->SetBranchAddress("fPt", fPt, &b_fPt);
   fChain->SetBranchAddress("fEta", fEta, &b_fEta);
   fChain->SetBranchAddress("fY", fY, &b_fY);
   fChain->SetBranchAddress("fTheta", fTheta, &b_fTheta);
   fChain->SetBranchAddress("fPhi", fPhi, &b_fPhi);
   Notify();
}

Bool_t hijTree::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void hijTree::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t hijTree::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef hijTree_cxx
