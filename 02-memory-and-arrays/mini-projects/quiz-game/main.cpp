// ============================================================
// Mini-projet : Quiz Interactif C++
// ============================================================
// Compile : g++ -std=c++17 -Wall -Wextra -o quiz main.cpp && ./quiz
// ============================================================

#include <iostream>
#include <string>
#include <cctype>
using namespace std;

const int NUM_QUESTIONS = 10;
const int NUM_CHOICES   = 4;

// Questions sur le C++ et l'informatique
const string questions[NUM_QUESTIONS] = {
    "Quelle est la taille (en bytes) d'un int sur la plupart des systemes 64-bit ?",
    "Quel mot-cle C++ empeche la modification d'une variable ?",
    "Qu'est-ce que le layout 'row-major' ?",
    "Quelle fonction est appelee automatiquement a la destruction d'un objet ?",
    "Que fait 'new' en C++ ?",
    "Quelle est la complexite d'un acces a un element de tableau par index ?",
    "Que signifie RAII ?",
    "Quel operateur permet de recuperer l'adresse d'une variable ?",
    "En C++17, quelle fonctionnalite remplace les includes circulaires en header ?",
    "Que fait std::move() ?"
};

const string choices[NUM_QUESTIONS][NUM_CHOICES] = {
    // Q0 : taille int
    { "A) 2 bytes", "B) 4 bytes", "C) 8 bytes", "D) Depends du compilateur uniquement" },
    // Q1 : const
    { "A) static", "B) volatile", "C) const", "D) final" },
    // Q2 : row-major
    { "A) Les colonnes sont stockees en memoire contiguement",
      "B) Les lignes sont stockees en memoire contiguement",
      "C) Les elements sont stockes en ordre inverse",
      "D) La matrice est transposee automatiquement" },
    // Q3 : destructeur
    { "A) delete()", "B) ~ClassName()", "C) free()", "D) destroy()" },
    // Q4 : new
    { "A) Alloue de la memoire sur la pile",
      "B) Alloue de la memoire sur le tas et retourne un pointeur",
      "C) Copie un objet",
      "D) Cree une reference" },
    // Q5 : complexite acces tableau
    { "A) O(n)", "B) O(log n)", "C) O(1)", "D) O(n^2)" },
    // Q6 : RAII
    { "A) Resource Allocation Is Immediate",
      "B) Resource Acquisition Is Initialization",
      "C) Runtime Array Integrity Invariant",
      "D) Recursive Abstraction Iteration Interface" },
    // Q7 : adresse
    { "A) *", "B) ->", "C) &", "D) @" },
    // Q8 : C++17 feature
    { "A) import", "B) module", "C) namespace inline", "D) using namespace" },
    // Q9 : std::move
    { "A) Copie un objet",
      "B) Supprime un objet",
      "C) Cast un objet en rvalue reference pour activer le move semantics",
      "D) Deplace un fichier sur le disque" }
};

const char correct[NUM_QUESTIONS] = {
    'B',  // Q0 : 4 bytes
    'C',  // Q1 : const
    'B',  // Q2 : row-major
    'B',  // Q3 : destructeur
    'B',  // Q4 : new
    'C',  // Q5 : O(1)
    'B',  // Q6 : RAII
    'C',  // Q7 : &
    'C',  // Q8 : inline namespace (inline variables/constexpr if, closest to reducing circular deps)
    'C'   // Q9 : std::move
};

// Affiche la question et les choix, retourne la reponse de l'utilisateur
char askQuestion(int idx) {
    cout << "\nQuestion " << (idx + 1) << "/" << NUM_QUESTIONS << " :" << endl;
    cout << questions[idx] << endl;
    for (int i = 0; i < NUM_CHOICES; i++) {
        cout << "  " << choices[idx][i] << endl;
    }
    cout << "Votre reponse (A/B/C/D) : ";

    char answer;
    while (true) {
        cin >> answer;
        answer = static_cast<char>(toupper(answer));
        if (answer == 'A' || answer == 'B' || answer == 'C' || answer == 'D') break;
        cout << "Reponse invalide. Entrez A, B, C ou D : ";
    }
    cin.ignore(1000, '\n');
    return answer;
}

// Evalue le score et retourne un message
string evaluate(int score) {
    if (score == NUM_QUESTIONS) return "Parfait ! Tu es un expert C++ !";
    if (score >= 8)             return "Excellent ! Tu maitrises bien le sujet.";
    if (score >= 6)             return "Bien ! Quelques lacunes a combler.";
    if (score >= 4)             return "Moyen... Revise les bases.";
    return                             "Revois tout depuis le debut.";
}

// Affiche une barre de progression du score
void displayScoreBar(int score) {
    cout << "[";
    for (int i = 0; i < NUM_QUESTIONS; i++) {
        cout << (i < score ? "#" : " ");
    }
    cout << "] " << score << "/" << NUM_QUESTIONS << endl;
}

int main() {
    cout << "==========================================" << endl;
    cout << "   Quiz C++ et Informatique" << endl;
    cout << "   10 questions - bonne chance !" << endl;
    cout << "==========================================" << endl;

    int score = 0;
    bool results[NUM_QUESTIONS] = {};

    // Boucle principale du quiz
    for (int i = 0; i < NUM_QUESTIONS; i++) {
        char answer = askQuestion(i);

        if (answer == correct[i]) {
            cout << "Correct ! Bonne reponse." << endl;
            score++;
            results[i] = true;
        } else {
            cout << "Incorrect. La bonne reponse etait : " << correct[i] << endl;
            results[i] = false;
        }
        cout << "Score actuel : " << score << "/" << (i + 1) << endl;
    }

    // Resultat final
    cout << "\n==========================================" << endl;
    cout << "   RESULTAT FINAL" << endl;
    cout << "==========================================" << endl;
    displayScoreBar(score);
    cout << evaluate(score) << endl;

    // Recap question par question
    cout << "\n--- Recapitulatif ---" << endl;
    for (int i = 0; i < NUM_QUESTIONS; i++) {
        cout << "Q" << (i + 1) << " : " << (results[i] ? "[OK]" : "[FAIL]") << endl;
    }

    cout << "\nMerci d'avoir joue !" << endl;
    return 0;
}
