/* Implantation du module ListeNoms.
 *
 * Auteur : E. Chaput
 * Date   : 08/10/2000
 */
#include <liste-noms-mt.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
#include <pthread.h>

#include <assert.h>

#define TRUE	1
#define FALSE	0

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

ListeNoms * creerListeNoms()
{
  ListeNoms * result = (ListeNoms *) malloc(sizeof(ListeNoms));
  initialiserListeNoms(result);
  return result;
}

void initialiserListeNoms(ListeNoms * f)
{
   f->premier = NULL;
   f->dernier = NULL;
	f->writing = 1;
	pthread_mutex_init(&(f->mutexListe), NULL);
	pthread_mutex_lock(&(f->mutexListe));
}

void insererNom(ListeNoms * f, Nom nom)
{
   CelluleNom * nc = (CelluleNom *)malloc(sizeof(CelluleNom));

   nc->nom = strdup(nom);

   /* Mise dans la chaine */
   nc->suivant = NULL;

   if (f->dernier != NULL) {
      f->dernier->suivant = nc;
   }
   f->dernier = nc;

   /* Si c'est le seul, c'est aussi le premier */
   if (f->premier == NULL) {
      f->premier = nc;
   }
   pthread_mutex_unlock(&(f->mutexListe));
}

void extraireNom(ListeNoms * f, Nom * nom)
{
	pthread_mutex_lock(&(f->mutexListe));
   CelluleNom * cv = f->premier; // Cellule vid�e � d�truire

   if (f->premier) {
     /* Son suivant devient le premier */
     *nom = f->premier->nom;
     f->premier = f->premier->suivant;

     /* Si c'�tait le dernier */
     if (f->dernier == cv) {
        f->dernier = NULL;
     } else if (writing){
	pthread_mutex_lock(&(f->mutexListe);
	}                                                                                      
 
     free(cv);
   } else {
     *nom = NULL;
   }
}

void afficherListeNoms(ListeNoms f)
{
   CelluleNom * cc = f.premier;

   while (cc != NULL) {
      printf("%s\n", cc->nom);
      cc = cc->suivant;
   }
}

int listeNomsVide(ListeNoms f)
{
   return (f.premier == NULL);
}
