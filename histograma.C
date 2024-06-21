#include <iostream>
#include <fstream>
#include <TFile.h>
#include <TH1F.h>
#include <TCanvas.h>

void histograma() {
    // Open the file
    std::ifstream inputFile("output.dat");
    if (!inputFile.is_open()) {
        std::cerr << "Error opening file: " << endl;
        return;
    }

    // Read values from the file and determine the range
    float minValue = std::numeric_limits<float>::max();
    float maxValue = std::numeric_limits<float>::min();

    float value;
    while (inputFile >> value) {
        if (value < minValue) minValue = value;
        if (value > maxValue) maxValue = value;
    }

    // Close the file
    inputFile.close();

    // Determine the number of bins based on the range and data distribution
    int numBins = static_cast<int>((maxValue - minValue) / 1); // Adjust the bin width as needed

    // Create a ROOT histogram
    //TH1F *histogram = new TH1F("histogram", "Number of photons arriving at the detector;Time (ns);", numBins, minValue-0.01, maxValue);
    TH1F *histogram = new TH1F("histogram", "Number of photons/ns;Time (ns);", 251, 3, 250);

    // Reopen the file and fill the histogram
    inputFile.open("output.dat");
    while (inputFile >> value) {
        histogram->Fill(value);
    }

    // Close the file
    inputFile.close();

    // Create a ROOT canvas and draw the histogram
    TCanvas *canvas = new TCanvas("canvas", "Canvas Title", 800, 600);
    canvas->SetLogy();
    histogram->Draw();
    canvas->Update();

    // Keep the ROOT application alive
    //canvas->WaitPrimitive();

    canvas->SaveAs("photonstime.png");
}