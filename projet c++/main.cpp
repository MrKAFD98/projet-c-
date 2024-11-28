#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>

struct Contact {
    std::string nom;
    std::string telephone;
    std::string email;
    std::string adresse;
};

// Afficher les informations d'un contact
void afficherContact(const Contact& contact) {
    std::cout << "Nom: " << contact.nom << "\n"
              << "Telephone: " << contact.telephone << "\n"
              << "Email: " << contact.email << "\n"
              << "Adresse: " << contact.adresse << "\n\n";
}

// Ajouter un contact
void ajouterContact(std::vector<Contact>& contacts) {
    Contact contact;
    std::cout << "Entrez le nom : ";
    std::getline(std::cin, contact.nom);
    std::cout << "Entrez le telephone : ";
    std::getline(std::cin, contact.telephone);
    std::cout << "Entrez l'email : ";
    std::getline(std::cin, contact.email);
    std::cout << "Entrez l'adresse : ";
    std::getline(std::cin, contact.adresse);
    contacts.push_back(contact);
    std::cout << "ajout du contact reussi.\n";
}

// Modifier un contact
void modifierContact(std::vector<Contact>& contacts) {
    std::string nom;
    std::cout << "Entrez le nom du contact pour la modification : ";
    std::getline(std::cin, nom);

    for (auto& contact : contacts) {
        if (contact.nom == nom) {
            std::cout << "Modifier le téléphone (actuel : " << contact.telephone << "): ";
            std::getline(std::cin, contact.telephone);
            std::cout << "Modifier l'email (actuel : " << contact.email << "): ";
            std::getline(std::cin, contact.email);
            std::cout << "Modifier l'adresse (actuel : " << contact.adresse << "): ";
            std::getline(std::cin, contact.adresse);
            std::cout << "modifier avec succes.\n";
            return;
        }
    }
    std::cout << "pas de resultat similaire pour ce contact.\n";
}

// Supprimer un contact
void supprimerContact(std::vector<Contact>& contacts) {
    std::string nom;
    std::cout << "Entrez le nom du contact pour la suppression: ";
    std::getline(std::cin, nom);

    auto it = std::remove_if(contacts.begin(), contacts.end(), [&](const Contact& contact) {
        return contact.nom == nom;
    });

    if (it != contacts.end()) {
        contacts.erase(it, contacts.end());
        std::cout << "suppression reussi.\n";
    } else {
        std::cout << "pas de resultat similaire pour ce contact.\n";
    }
}

// Rechercher un contact par nom
void rechercherContact(const std::vector<Contact>& contacts) {
    std::string nom;
    std::cout << "Entrez le nom pour la recherche : ";
    std::getline(std::cin, nom);

    for (const auto& contact : contacts) {
        if (contact.nom.find(nom) != std::string::npos) {
            afficherContact(contact);
        }
    }
}

// Trier les contacts par nom
void trierContacts(std::vector<Contact>& contacts) {
    std::sort(contacts.begin(), contacts.end(), [](const Contact& a, const Contact& b) {
        return a.nom < b.nom;
    });
    std::cout << "Trie (par nom)des contacts reussi .\n";
}

// Sauvegarder les contacts dans un fichier
void sauvegarderContacts(const std::vector<Contact>& contacts, const std::string& nomFichier) {
    std::ofstream fichier(nomFichier);
    if (!fichier) {
        std::cerr << "Erreur lors de l'ouverture du fichier.\n";
        return;
    }

    for (const auto& contact : contacts) {
        fichier << contact.nom << '\n'
                << contact.telephone << '\n'
                << contact.email << '\n'
                << contact.adresse << '\n';
    }

    std::cout << "Sauvegarde des contacts dans le fichier reussi  " << nomFichier << ".\n";
}

// Charger les contacts depuis un fichier
void chargerContacts(std::vector<Contact>& contacts, const std::string& nomFichier) {
    std::ifstream fichier(nomFichier);
    if (!fichier) {
        std::cerr << "Erreur lors de l'ouverture du fichier.\n";
        return;
    }

    contacts.clear();
    Contact contact;
    while (std::getline(fichier, contact.nom) &&
           std::getline(fichier, contact.telephone) &&
           std::getline(fichier, contact.email) &&
           std::getline(fichier, contact.adresse)) {
        contacts.push_back(contact);
    }

    std::cout << "chargement des contacts depuis le fichier reussi " << nomFichier << ".\n";
}

int main() {
    std::vector<Contact> contacts;
    std::string nomFichier = "contacts.txt";
    int choix;

    do {
        std::cout << "\n---------------------------------------- GESTIONNAIRE DE CONTACTS ----------------------------------------\n"
                  << "1. Ajouter un contact\n"
                  << "2. Modifier un contact\n"
                  << "3. Supprimer un contact\n"
                  << "4. Rechercher un contact\n"
                  << "5. Trier les contacts\n"
                  << "6. Sauvegarder les contacts\n"
                  << "7. Charger les contacts\n"
                  << "8. Afficher tous les contacts\n"
                  << "0. Quitter\n"
                  << "Votre choix : ";
        std::cin >> choix;
        std::cin.ignore(); // Pour ignorer le caractère '\n' laissé dans le buffer

        switch (choix) {
            case 1:
                ajouterContact(contacts);
                break;
            case 2:
                modifierContact(contacts);
                break;
            case 3:
                supprimerContact(contacts);
                break;
            case 4:
                rechercherContact(contacts);
                break;
            case 5:
                trierContacts(contacts);
                break;
            case 6:
                sauvegarderContacts(contacts, nomFichier);
                break;
            case 7:
                chargerContacts(contacts, nomFichier);
                break;
            case 8:
                for (const auto& contact : contacts) {
                    afficherContact(contact);
                }
                break;
            case 0:
                std::cout << "Au revoir !\n";
                break;
            default:
                std::cout << "Choix invalide.\n";
        }
    } while (choix != 0);

    return 0;
}
