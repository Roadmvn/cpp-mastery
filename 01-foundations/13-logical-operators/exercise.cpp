// ============================================================
// Exercice : Operateurs Logiques
// Compile : g++ -std=c++17 -o exercise exercise.cpp
// ============================================================

#include <iostream>
#include <string>

int main() {
    // ========================================================
    // PARTIE 1 : && et ||
    // Combine les conditions pour determiner l'acces.
    // ========================================================

    int age = 25;
    bool a_permis = true;
    bool est_assure = false;

    // TODO: Un conducteur peut conduire si :
    //   age >= 18 ET a_permis ET est_assure
    // Stocke le resultat dans 'peut_conduire'
    // bool peut_conduire = ...;

    // TODO: Affiche si la personne peut conduire ou non
    // std::cout << "Peut conduire : " << (peut_conduire ? "OUI" : "NON") << std::endl;
    // Attendu : "NON" (pas assure)

    // TODO: La personne peut au moins s'inscrire au permis si :
    //   age >= 16 OU (age >= 15 ET accompagnement)
    bool accompagnement = true;
    // bool peut_inscrire = ...;
    // std::cout << "Peut s'inscrire : " << (peut_inscrire ? "OUI" : "NON") << std::endl;

    // ========================================================
    // PARTIE 2 : ! (negation) et combinaisons
    // ========================================================

    bool alarme_active = true;
    bool porte_fermee = false;
    bool fenetre_fermee = true;

    // TODO: La maison est securisee si :
    //   alarme_active ET porte_fermee ET fenetre_fermee
    // bool securisee = ...;

    // TODO: Il y a une alerte si la maison n'est PAS securisee
    // mais que l'alarme EST active (= quelque chose est ouvert)
    // bool alerte = ...;

    // std::cout << "Securisee : " << (securisee ? "OUI" : "NON") << std::endl;
    // std::cout << "Alerte    : " << (alerte ? "OUI" : "NON") << std::endl;
    // Attendu : Securisee = NON, Alerte = OUI

    // ========================================================
    // PARTIE 3 : Court-circuit
    // Utilise le court-circuit pour eviter une division par zero.
    // ========================================================

    int dividende = 100;
    int diviseur = 0;

    // TODO: Affiche le resultat de la division SEULEMENT si
    // le diviseur n'est pas zero. Utilise && avec court-circuit.
    // (la deuxieme condition ne doit pas etre evaluee si diviseur == 0)
    // if (...) {
    //     std::cout << "Resultat : " << (dividende / diviseur) << std::endl;
    // } else {
    //     std::cout << "Division par zero evitee" << std::endl;
    // }

    return 0;
}
