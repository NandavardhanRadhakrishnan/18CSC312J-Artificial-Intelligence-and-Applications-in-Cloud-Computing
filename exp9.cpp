// waste water treatment

#include <iostream>
#include <random>
using namespace std;

double simulateTreatmentProcess(double incomingPollutionConcentration, double treatmentEfficiency) {
    random_device rd;
    mt19937 gen(rd());
    normal_distribution<> incomingDist(incomingPollutionConcentration, 0.1); 
    normal_distribution<> efficiencyDist(treatmentEfficiency, 0.05); 
    double treatedPollutionConcentration = incomingDist(gen) * (1 - efficiencyDist(gen));
    return treatedPollutionConcentration;
}

int main() {

    double incomingPollutionConcentration = 100; 
    double treatmentEfficiency = 0.8; 
    double treatedPollutionConcentration = simulateTreatmentProcess(incomingPollutionConcentration, treatmentEfficiency);
    
    cout << "Incoming Pollution Concentration: " << incomingPollutionConcentration << " mg/L\n";
    cout << "Treatment Efficiency: " << treatmentEfficiency * 100 << "%\n";
    cout << "Treated Pollution Concentration: " << treatedPollutionConcentration << " mg/L\n";
   
    return 0;
}