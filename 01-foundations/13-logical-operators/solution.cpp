// ============================================================
// Solution : Operateurs Logiques
// Compile : g++ -std=c++17 -o solution solution.cpp
// ============================================================

#include <iostream>
#include <string>

int main() {
    // ========================================================
    // PARTIE 1 : && et ||
    // ========================================================

    int age = 25;
    bool a_permis = true;
    bool est_assure = false;

    // Les 3 conditions doivent etre vraies (ET logique)
    bool peut_conduire = (age >= 18) && a_permis && est_assure;
    std::cout << "Peut conduire : " << (peut_conduire ? "OUI" : "NON") << std::endl;
    // NON car est_assure = false

    // OU logique : age >= 16 suffit, OU (age >= 15 ET accompagnement)
    bool accompagnement = true;
    bool peut_inscrire = (age >= 16) || (age >= 15 && accompagnement);
    std::cout << "Peut s'inscrire : " << (peut_inscrire ? "OUI" : "NON") << std::endl;
    // OUI car age >= 16

    // ========================================================
    // PARTIE 2 : ! (negation) et combinaisons
    // ========================================================

    bool alarme_active = true;
    bool porte_fermee = false;
    bool fenetre_fermee = true;

    // Tout doit etre vrai pour que la maison soit securisee
    bool securisee = alarme_active && porte_fermee && fenetre_fermee;

    // Alerte : alarme active MAIS maison pas securisee
    // -> quelque chose est ouvert alors que l'alarme tourne
    bool alerte = alarme_active && !securisee;

    std::cout << "Securisee : " << (securisee ? "OUI" : "NON") << std::endl;
    std::cout << "Alerte    : " << (alerte ? "OUI" : "NON") << std::endl;

    // ========================================================
    // PARTIE 3 : Court-circuit
    // ========================================================

    int dividende = 100;
    int diviseur = 0;

    // Grace au court-circuit, si diviseur == 0 (false pour != 0),
    // la deuxieme partie (dividende / diviseur > 5) n'est JAMAIS evaluee.
    // Pas de division par zero !
    if (diviseur != 0 && (dividende / diviseur) > 5) {
        std::cout << "Resultat : " << (dividende / diviseur) << std::endl;
    } else {
        std::cout << "Division par zero evitee" << std::endl;
    }

    return 0;
}
