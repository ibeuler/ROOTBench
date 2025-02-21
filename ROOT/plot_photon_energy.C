void plot_photon_energy() {
    // Open ROOT file
    TFile *file = TFile::Open("../DATA/data_A.GamGam.root");
    if (!file || file->IsZombie()) {
        std::cerr << "Error: Cannot open file!" << std::endl;
        return;
    }

    // Get the TTree
    TTree *tree = (TTree*)file->Get("mini");
    if (!tree) {
        std::cerr << "Error: TTree 'mini' not found!" << std::endl;
        file->Close();
        return;
    }

    // Check if branch exists
    if (!tree->GetBranch("photon_E")) {
        std::cerr << "Error: Branch 'photon_E' not found!" << std::endl;
        file->Close();
        return;
    }

    TH1F *hPhotonE = new TH1F("hPhotonE", "Photon Energy Distribution;Energy (MeV);Events", 50, 0, 400000);

    // Set up branch for reading
    std::vector<Double_t> *photon_E = nullptr;
tree->SetBranchAddress("photon_E", &photon_E);

    // Loop over entries
    Long64_t nentries = tree->GetEntries();
    for (Long64_t i = 0; i < nentries; i++) {
        tree->GetEntry(i);
        if (!photon_E) continue;  // Avoid null pointer access
        for (float energy : *photon_E) {
            hPhotonE->Fill(energy);
        }
    }

    // Draw histogram
    TCanvas *c1 = new TCanvas("c1", "Photon Energy", 800, 600);
    hPhotonE->SetLineColor(kBlue);
    hPhotonE->Draw();

    // Save the plot
    c1->SaveAs("photon_energy.png");

    // Clean up
    delete c1;
    delete hPhotonE;
    file->Close();
}
