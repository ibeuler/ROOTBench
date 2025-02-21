void read_root() {
    TFile *file = new TFile("../DATA/data_A.GamGam.root", "READ");
    if (!file || file->IsZombie()) {
        std::cout << "Error opening file!" << std::endl;
        return;
    }

    file->ls();  // List file contents

    TTree *tree = (TTree*) file->Get("mini");
    if (tree) {
        std::cout << "Entries: " << tree->GetEntries() << std::endl;
    }

    file->Close();
}

