#include "MyDetector.h"

#include "G4Box.hh"
#include "G4Material.hh"
#include "G4NistManager.hh"
#include "G4LogicalVolume.hh"
#include "G4VPhysicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4SubtractionSolid.hh"

#include "G4OpticalSurface.hh"
#include "G4LogicalBorderSurface.hh"

#include "G4VisAttributes.hh"

#include "MySensorDetector.h"

#include "CLHEP/Units/SystemOfUnits.h"

#include "G4MaterialPropertiesTable.hh"

using namespace CLHEP;

G4VPhysicalVolume* MyDetector::Construct(){

    const int N_DATA = 2;
    double photonEnergies[N_DATA] = { 9*eV, 10*eV };


	// Liquid Argon
	auto lAr = G4NistManager::Instance()->FindOrBuildMaterial("G4_lAr");
    auto lArPropertiesTable = new G4MaterialPropertiesTable();
	lAr->SetMaterialPropertiesTable(lArPropertiesTable);
    
    double lArRIndex[N_DATA] = { 1.32, 1.32 };
    lArPropertiesTable->AddProperty("RINDEX", photonEnergies, lArRIndex, N_DATA);
    double lArAbsLength[N_DATA] = { 2000*cm, 2000*cm };
    lArPropertiesTable->AddProperty("ABSLENGTH", photonEnergies, lArAbsLength, N_DATA);
    
    //const int N_DAT = 141;
    //double lArScintEn[N_DAT] = { 4.130, 4.133, 4.169, 4.200, 4.233, 4.234, 4.236, 4.266, 4.296, 4.331, 4.355, 4.389, 4.422, 4.457, 4.507, 4.543, 4.585, 4.602, 4.638, 4.651, 4.684, 4.695, 4.716, 4.734, 4.772, 4.811, 4.843, 4.866, 4.897, 4.940, 4.981, 5.028, 5.073, 5.094, 5.119, 5.172, 5.227, 5.274, 5.335, 5.384, 5.426, 5.472, 5.535, 5.592, 5.633, 5.685, 5.708, 5.761, 5.829, 5.879, 5.910, 5.944, 6.019, 6.087, 6.147, 6.215, 6.278, 6.348, 6.451, 6.525, 6.595, 6.677, 6.760, 6.835, 6.919, 7.009, 7.093, 7.183, 7.263, 7.349, 7.455, 7.551, 7.616, 7.625, 7.691, 7.798, 7.907, 7.963, 7.968, 7.973, 8.020, 8.125, 8.141, 8.157, 8.195, 8.205, 8.383, 8.389, 8.406, 8.440, 8.498, 8.515, 8.545, 8.568, 8.586, 8.604, 8.640, 8.664, 8.695, 8.713, 8.737, 8.762, 8.793, 8.812, 8.850, 8.869, 8.913, 8.933, 8.958, 8.997, 9.024, 9.063, 9.103, 9.116, 9.164, 9.198, 9.218, 9.259, 9.280, 9.329, 9.350, 9.386, 9.428, 9.479, 9.530, 9.581, 9.671, 9.717, 9.801, 9.903, 9.959, 10.007, 10.064, 10.096, 10.138, 10.204, 10.238, 10.264, 10.332, 10.445, 10.45 };
    //double lArScintilation[N_DAT] = { 0, 0.319, 0.458, 0.461, 0.457, 0.551, 0.643, 0.748, 0.686, 0.682, 1.034, 1.171, 1.148, 1.186, 1.453, 1.515, 1.561, 1.317, 1.266, 1.041, 1.044, 0.922, 0.784, 0.905, 0.825, 0.656, 0.909, 0.810, 0.610, 0.615, 0.594, 0.595, 0.574, 0.504, 0.449, 0.437, 0.412, 0.376, 0.367, 0.352, 0.348, 0.343, 0.364, 0.404, 0.474, 0.551, 0.609, 0.740, 0.823, 0.914, 1.066, 1.227, 1.433, 1.559, 1.767, 1.794, 1.823, 1.831, 1.848, 1.892, 1.788, 1.708, 1.617, 1.560, 1.480, 1.350, 1.223, 1.076, 0.953, 0.848, 0.883, 0.853, 1.004, 1.256, 1.480, 1.723, 1.482, 1.128, 0.953, 1.323, 1.533, 1.749, 1.422, 2.136, 2.941, 3.480, 8.190, 7.121, 9.788, 11.900, 14.320, 17.050, 19.990, 24.530, 29.150, 34.990, 42.570, 54.220, 66.560, 78.760, 93.950, 111.200, 129.400, 154.900, 190.800, 228.500, 272.900, 320.100, 375.600, 445.000, 534.600, 646.400, 765.200, 895.800, 1075.000, 1289.000, 1524.000, 1837.000, 2214.000, 2635.000, 3010.000, 3615.000, 4417.000, 5274.000, 6279.000, 7274.000, 8728.000, 9069.000, 8399.000, 6990.000, 5731.000, 4582.000, 3778.000, 3110.000, 2497.000, 1937.000, 1558.000, 1343.000, 1086.000, 882.800, 0.1
    //for(int i = 0; i < N_DAT; i++) lArScintEn[i] *= eV;

    double lArScintilation[N_DATA] = {534, 4582};
    
    lArPropertiesTable->AddProperty("SCINTILLATION", photonEnergies, lArScintilation, N_DATA);
	
    lArPropertiesTable->AddConstProperty("SCINTILLATIONYIELD", 240 / MeV);
	lArPropertiesTable->AddConstProperty("RESOLUTIONSCALE", 1.0);
	lArPropertiesTable->AddConstProperty("FASTTIMECONSTANT", 6.2 * ns);
    lArPropertiesTable->AddConstProperty("SLOWTIMECONSTANT", 1590 * ns);

	
    auto air = G4NistManager::Instance()->FindOrBuildMaterial("G4_AIR");
    auto airPropertiesTable = new G4MaterialPropertiesTable();
    air->SetMaterialPropertiesTable( airPropertiesTable );

    double airRIndex[N_DATA] = { 1.0, 1.0 };
    airPropertiesTable->AddProperty("RINDEX", photonEnergies, airRIndex, N_DATA);

    auto water = G4NistManager::Instance()->FindOrBuildMaterial("G4_WATER");
    auto waterPropertiesTable = new G4MaterialPropertiesTable();
    water->SetMaterialPropertiesTable( waterPropertiesTable );

    double waterRIndex[N_DATA] = { 1.33, 1.33 };
    waterPropertiesTable->AddProperty("RINDEX", photonEnergies, waterRIndex, N_DATA);

    double waterAbsLength[N_DATA] = { 1.00, 1.00 };
    waterPropertiesTable->AddProperty("ABSLENGTH", photonEnergies, waterAbsLength, N_DATA);

    auto glass = G4NistManager::Instance()->FindOrBuildMaterial("G4_GLASS_PLATE");
    auto glassPropertiesTable = new G4MaterialPropertiesTable();
    glass->SetMaterialPropertiesTable( glassPropertiesTable );

    double glassRIndex[N_DATA] = { 2.50, 2.50 };
    glassPropertiesTable->AddProperty("RINDEX", photonEnergies, glassRIndex, N_DATA);

    double glassAbsLength[N_DATA] = { 50*cm, 50*cm };
    glassPropertiesTable->AddProperty("ABSLENGTH", photonEnergies, glassAbsLength, N_DATA);

    // World volume
    auto worldBox = new G4Box("worldBox", 10*m, 10*m, 10*m); 
    auto logicalWorld = new G4LogicalVolume(worldBox, lAr, "LogicalWorld");
    auto physicalWorld = new G4PVPlacement(0, {0,0,0}, logicalWorld, "World", 0, false, 0);
    logicalWorld->SetVisAttributes( new G4VisAttributes( G4Colour::Green() ) );

    double sideLArBox = 200.0*cm;
    auto LArBox = new G4Box("sideLArBox", sideLArBox/2, sideLArBox/2, sideLArBox/2); 
    auto logLAr = new G4LogicalVolume(LArBox, lAr, "Logical LAr Box");
    auto physLAr = new G4PVPlacement(0, {0,0,0}, logLAr, "World/LArBox", logicalWorld, false, 0);
    logLAr->SetVisAttributes( new G4VisAttributes( G4Colour::Blue() ) );

    // Air Water Optical Properties
    //auto surfaceAirWater = new G4OpticalSurface("Air/Water Surface");
    //surfaceAirWater->SetModel(unified);
    //surfaceAirWater->SetType(dielectric_dielectric);
    //surfaceAirWater->SetFinish(polished);

    //auto surfaceAirWaterProp = new G4MaterialPropertiesTable();
    //surfaceAirWater->SetMaterialPropertiesTable(surfaceAirWaterProp);

    //auto logSurfaceAirWater = new G4LogicalBorderSurface("Air->Water Interface", physicalWorld, physWater, surfaceAirWater);
    //auto logSurfaceWaterAir = new G4LogicalBorderSurface("Water->Air Interface", physWater, physicalWorld, surfaceAirWater);

    //double reflectAirWater[N_DATA] = { 0.7, 0.7 };
    //surfaceAirWaterProp->AddProperty("REFLECTIVITY", photonEnergies, reflectAirWater, N_DATA);

    // Water Glass Optical Properties
    //auto surfaceWaterGlass = new G4OpticalSurface("Water/Glass Surface");
    //surfaceWaterGlass->SetModel(unified);
    //surfaceWaterGlass->SetType(dielectric_dielectric);
    //surfaceWaterGlass->SetFinish(ground);
    //surfaceWaterGlass->SetSigmaAlpha(1*degree);

    //auto surfaceWaterGlassProp = new G4MaterialPropertiesTable();
    //surfaceWaterGlass->SetMaterialPropertiesTable(surfaceWaterGlassProp);

    //auto logsurfaceWaterGlass = new G4LogicalBorderSurface("Water->Glass Interface", physWater, physGlass, surfaceWaterGlass);
    //auto logSurfaceGlassWater = new G4LogicalBorderSurface("Glass->Water Interface", physGlass, physWater, surfaceWaterGlass);

    //double reflectWaterGlass[N_DATA] = { 1, 1 };
    //surfaceWaterGlassProp->AddProperty("REFLECTIVITY", photonEnergies, reflectWaterGlass, N_DATA);

    
    auto silicon = G4NistManager::Instance()->FindOrBuildMaterial("G4_Si");
    auto siliconPropertiesTable = new G4MaterialPropertiesTable();
    silicon->SetMaterialPropertiesTable( siliconPropertiesTable );

    double siliconRIndex[N_DATA] = { 1, 1 };
    siliconPropertiesTable->AddProperty("RINDEX", photonEnergies, siliconRIndex, N_DATA);

    double siliconAbsLength[N_DATA] = { 1*nm, 1*nm };
    siliconPropertiesTable->AddProperty("ABSLENGTH", photonEnergies, siliconAbsLength, N_DATA);

    double sensorDim = 0.5*m;
    double sensorThickness = 1*mm;
    double sensorDistance = sideLArBox/2 - 2*sensorThickness;
    auto boxSensor = new G4Box("SensorBox", sensorDim/2, sensorThickness/2, sensorDim/2); 
    auto logSensor = new G4LogicalVolume(boxSensor, silicon, "LogicalSensor");
    auto phySensor = new G4PVPlacement(0, {0,sensorDistance,0}, logSensor, "World/Sensor", logLAr, false, 0);
    logSensor->SetVisAttributes( new G4VisAttributes( G4Color::Red() ) );

    logSensor->SetSensitiveDetector( new MySensorDetector("PhotonCounter") );

    return physicalWorld;
}