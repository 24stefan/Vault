#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>

struct Entry {
    std::string service;
    std::string password;
};

// Caesar cipher helpers -------------------------
std::string encrypt(const std::string& text, int key)     {
        std::string result = text;
        for (char& c : result)
            c = (isprint(c)) ? char(((c - 32 + key) % 95) + 32) : c;
        return result;
}

std::string decrypt(const std::string& text, int key)     {
        std::string result = text;
        for (char& c : result)
            c = (isprint(c)) ? char(((c - 32 - key + 95) % 95) + 32) : c;
         return result;
}
//---------------------------------------------------------------------------

// File I/O
void saveVault(const std::vector<Entry>& vault, int key, const std::string& filename)     {
        std::ofstream out(filename);
        for (auto& e : vault)
            out << encrypt(e.service, key) << "," << encrypt(e.password, key) << "\n";
       out.close();
}

std::vector<Entry> loadVault(int key, const std::string& filename) {
    std::vector<Entry> vault;
    std::ifstream in(filename);
    if (!in.is_open()) return vault;

    std::string line;
    while (std::getline(in, line)) {
        size_t pos = line.find(',');
        if (pos == std::string::npos) continue;
        std::string encService = line.substr(0, pos);
        std::string encPass = line.substr(pos + 1);
        vault.push_back({decrypt(encService, key), decrypt(encPass, key)});
    }
    in.close();
    return vault;
}
//--------------------------------------------------------------------------------------


// ======== UI HELPERS ========

void clearScreen() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}


std::string color(const std::string& text, const std::string& code) {
    return "\033[" + code + "m" + text + "\033[0m";
}

void showBanner() {
    clearScreen();
    std::cout << color("\n╔═══════════════════════════════════════╗\n", "36"); // cyan
    std::cout << color("║              PASSWORD VAULT          ║\n", "36;1");
    std::cout << color("╚═══════════════════════════════════════╝\n", "36");
    std::cout << color("  primitive storage system\n", "90");
    std::cout << "-----------------------------------------\n";
}

void showMenu() {
    std::cout << "\n" << color("┌─── MENU ─────────────────────────────┐", "33") << "\n";
    std::cout << color("│ [1] Add new entry                    │\n", "33");
    std::cout << color("│ [2] View vault                       │\n", "33");
    std::cout << color("│ [3] Save vault                       │\n", "33");
    std::cout << color("│ [4] Load vault                       │\n", "33");
    std::cout << color("│ [5] Exit                             │\n", "33");
    std::cout << color("└───────────────────────────────────────┘", "33") << "\n";
    std::cout << color(">> ", "32");
}
