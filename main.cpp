#include <iostream>
#include <fstream>
#include <string>
#include <chrono>
#include <vector>
#include <iomanip>
#include <functional>
#include "lcs_algos.h"

// Chargement complet du fichier en RAM pour un benchmark de calcul pur
std::string loadFile(const std::string& filename) {
    std::ifstream file(filename, std::ios::in | std::ios::binary);
    if (!file) {
        std::cerr << "[ERREUR] Impossible d'ouvrir le fichier.\n";
        return "";
    }
    return std::string((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
}

int main() {
    int choix;
    std::string text, target;

    std::cout << "--- BENCHMARK : PLUS LONGUE SOUS-CHAINE COMMUNE (LCS) ---\n";
    std::cout << "1. Saisir un texte manuellement\n";
    std::cout << "2. Charger un fichier texte\n";
    std::cout << "Choix (1 ou 2) : ";
    std::cin >> choix;
    std::cin.ignore();

    if (choix == 1) {
        std::cout << "Saisissez votre texte principal : ";
        std::getline(std::cin, text);
    } else {
        std::string filename;
        std::cout << "Chemin du fichier : ";
        std::getline(std::cin, filename);
        text = loadFile(filename);
        if (text.empty()) return 1;
        std::cout << "[INFO] Fichier charge (" << text.length() << " caracteres).\n";
    }

    std::cout << "Phrase ou motif a comparer : ";
    std::getline(std::cin, target);

    std::cout << "\nLancement du Benchmark...\n";
    std::cout << "------------------------------------------------------------------\n";
    std::cout << std::left << std::setw(30) << "Algorithme" 
              << std::setw(20) << "Temps (ms)" 
              << "Taille Max Trouvee\n";
    std::cout << "------------------------------------------------------------------\n";

    // Tableau des fonctions a tester
    std::vector<std::pair<std::string, std::function<int()>>> algos = {
        {"1. Force Brute", [&]() { return lcsBruteForce(text, target); }},
        {"2. DP Matrice 2D", [&]() { return lcsDP2D(text, target); }},
        {"3. DP Vecteur 1D (Optimise)", [&]() { return lcsDPOptimized(text, target); }}
    };

    // Execution
    for (const auto& algo : algos) {
        auto start = std::chrono::high_resolution_clock::now();
        
        int result = algo.second(); 
        
        auto end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

        // Empecher le compilateur d'ignorer le calcul (-O3)
        volatile int dummy = result;

        std::cout << std::left << std::setw(30) << algo.first 
                  << std::setw(20) << duration 
                  << result << " caracteres\n";
    }
    std::cout << "------------------------------------------------------------------\n";

    return 0;
}