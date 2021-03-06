/*
 * Interface d'une liste �l�mentaire de cha�nes de caract�res.
 *
 * Note : les cha�nes de caract�res sont copi�es dans des zones m�moire
 * allou�es lors de l'insertion dans la liste. L'utilisateur peut donc
 * d�truire ou r�utiliser les cha�nes pass�es en param�tres et re�ues des
 * sous-programmes de ce module.
 *
 * Auteur : E. Chaput
 * Date   : 08/10/2000
 */
#ifndef FILE_NOMS
#define FILE_NOMS

#include <pthread.h>

#include <nom.h>

/*
 * Type d'une cellule de la liste
 */
typedef struct _CelluleNom {
   Nom                  nom;
   struct _CelluleNom * suivant;
} CelluleNom;

/*
 * Une liste de noms est caract�ris�e simplement par son premier
 * et son dernier �l�ments.
 */
struct ListeNoms {
   CelluleNom * premier;
   CelluleNom * dernier;
   pthread_mutex_t mutexListe;
        int writing;
};

typedef struct ListeNoms ListeNoms;

ListeNoms * creerListeNoms();
/*
 * Cr�ation d'une liste de noms
 * 
 * Assure
 *    listeNomsVide(*f)
 */

void initialiserListeNoms(ListeNoms * f);
/*
 * Initialisation de la liste de noms
 * 
 * Assure
 *    listeNomsVide(*f)
 */

void insererNom(ListeNoms * f, Nom nom);
/*
 * Insertion d'un nom en fin de liste
 */

void extraireNom(ListeNoms * f, Nom * nom);
/*
 * Extraction du premier �l�ment de la liste.
 *
 * Retourne le premier �l�ment ou NULL si la liste est vide
 */

void afficherListeNoms(ListeNoms f);
/*
 * Affichage de la liste, du premier au dernier �l�ment
 * un �l�ment par ligne.
 */

int listeNomsVide(ListeNoms f);

void ouvrirListeNoms(ListeNoms * f);
/*
 * Ce sous-programme doit �tre utilis� par tout producteur avant
 * toute autre manipulation de la liste afin de s'identifier.
 */

void fermerListeNoms(ListeNoms * f);
/*
 * Ce sous-programme doit �tre utilis� par tout producteur lorsqu'il
 * a fini d'utiliser la liste.
 */

#endif
