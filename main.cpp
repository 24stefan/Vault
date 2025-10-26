#include "include.hpp"

int main() {
    std::vector<Entry> vault;
    // here will be stored your  encrypted passwords ----------------

    std::string filename = "vault.dat";
   // --------------------------------------
    
   showBanner();
    std::cout << "Enter master password: ";
    std::string masterPassword;
    std::getline(std::cin, masterPassword);

    std::cout << "Enter Caesar cipher key (1-50): ";
    int key;
    std::cin >> key;
    std::cin.ignore();

    bool running = true;
    while (running) {
        showMenu();
        int choice;
        std::cin >> choice;
        std::cin.ignore();

        switch (choice) {
            case 1: {
                Entry e;
                std::cout << "Service name: ";
                std::getline(std::cin, e.service);
                std::cout << "Password/token: ";
                std::getline(std::cin, e.password);
                vault.push_back(e);
                std::cout << "Entry added.\n";
                break;
            }
            case 2: {
                std::cout << "\n--- VAULT CONTENT ---\n";
                for (size_t i = 0; i < vault.size(); ++i) {
                    std::cout << std::setw(2) << i + 1 << ". "
                              << vault[i].service << " : " << vault[i].password << "\n";
                }
                if (vault.empty()) std::cout << "(empty)\n";
                break;
            }
            case 3: {
                saveVault(vault, key, filename);
                std::cout << " Vault saved to '" << filename << "'.\n";
                break;
            }
            case 4: {
                vault = loadVault(key, filename);
                std::cout << "Vault loaded (" << vault.size() << " entries).\n";
                break;
            }
            case 5:
                running = false;
                std::cout << "Exiting vault...\n";
                break;
            default:
                std::cout << "Invalid option.\n";
                break;
        }
    }

    return 0;
}

