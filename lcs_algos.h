#ifndef LCS_ALGOS_H
#define LCS_ALGOS_H

#include <string>
#include <vector>
#include <algorithm>

// Algo 1 : Force Brute (Naif) - Complexite O(N * M^2)
// Compare chaque caractere du texte avec la cible
int lcsBruteForce(const std::string& text, const std::string& target) {
    if (text.empty() || target.empty()) return 0;
    int maxLen = 0;
    
    for (size_t i = 0; i < text.length(); ++i) {
        for (size_t j = 0; j < target.length(); ++j) {
            int len = 0;
            while (i + len < text.length() && j + len < target.length() 
                   && text[i + len] == target[j + len]) {
                len++;
            }
            if (len > maxLen) maxLen = len;
        }
    }
    return maxLen;
}

// Algo 2 : Programmation Dynamique avec Matrice 2D - Complexite O(N * M) Temps et Espace
// Methode classique enseignee dans les universites
int lcsDP2D(const std::string& text, const std::string& target) {
    if (text.empty() || target.empty()) return 0;
    int n = text.length();
    int m = target.length();
    
    // Allocation d'une grosse matrice (peut crasher sur des fichiers de plusieurs Mo)
    std::vector<std::vector<int>> dp(n + 1, std::vector<int>(m + 1, 0));
    int maxLen = 0;

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (text[i - 1] == target[j - 1]) {
                dp[i][j] = dp[i - 1][j - 1] + 1;
                if (dp[i][j] > maxLen) maxLen = dp[i][j];
            }
        }
    }
    return maxLen;
}

// Algo 3 : Programmation Dynamique Optimisee (1D) - Complexite O(N * M) Temps, O(M) Espace
// Ne garde en memoire que la ligne precedente. Ideal pour les tres gros fichiers.
int lcsDPOptimized(const std::string& text, const std::string& target) {
    if (text.empty() || target.empty()) return 0;
    int n = text.length();
    int m = target.length();
    
    // Allocation minimale : juste 2 tableaux de la taille de la chaine cible
    std::vector<int> prev(m + 1, 0);
    std::vector<int> curr(m + 1, 0);
    int maxLen = 0;

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (text[i - 1] == target[j - 1]) {
                curr[j] = prev[j - 1] + 1;
                if (curr[j] > maxLen) maxLen = curr[j];
            } else {
                curr[j] = 0; // Reinitialisation car sous-chaine contigue
            }
        }
        prev = curr; // La ligne actuelle devient la ligne precedente
    }
    return maxLen;
}

#endif