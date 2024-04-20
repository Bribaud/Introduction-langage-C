#include <stdio.h>
#include <stdlib.h> //On a besoin de cette librairie pour faire de l'allocation dynamique de mémoire

/* Question 2.1:
Le premier code affiche 012342 car i est une variable locale, sa valeure dans le main n'est donc pas modifié par un appel à la fonction affiche
Le deuxième code renvoie une erreur car i étant locale, elle n'est pas déclaré avant la boucle for de la fonction affiche.
Le 3e code affiche 012345 car i est une variable globale. L'appel à la fonction affiche modifie donc bien sa valeure.

Question 2.2:
Le premier code affiche 6 car la ligne i=1 est une affectation et non un test d'égalité.
Le second code affiche 3 car b est un pointeur vers la case mémoire où a est stocké. Donc modifier la valeur de a modifie également celle de b.
Le troisième code affiche 2 car b n'est pas un pointeur donc est just égale à la valeur de a lors de son initialisation.

Question 3.1:
Bien que le code ne renvoie pas d'erreur, il y a une surcharge mémoire à la ligne 6 car le scanf va prendre en compte toute la chaine de caractère entrée par l 'utilisateur.
Une solution est de transformer le %s en %6s pour ne prendre en compte que les 6 premiers caractères.
*/


//Question 3.2
int jour(float nombre)
{
    float bissextile = nombre/4;
    int res = (int) 365* nombre + bissextile; //Le (int) sert à forcer le type de lors de l'affectation.
    if ((int) nombre %4 ==3) res++; //Si on ne le met pas, en général, il y a un warning (mais pas d'erreur). Cela dépend du compilateur utilisé.
    return res;
 }


//Question 4.1
int fibo(int n){
    if(n==0)return 0;
    if(n==1)return 1;
    return fibo(n-1) + fibo(n-2); //On peut faire des appels reccursifs facilement.
}

//Question 4.2
int parmi(int k, int n){
    if(k==0)return 1;
    if(k>n)return 0;
    return (parmi(k-1,n-1) + parmi(k,n-1));
}

//Question 5
long* fibo_tab; // Le type long permet de stocker des entiers plus grand que le type int.
//On définit fibo_tab comme un pointeur vers des entiers.

long fibo2(int n){
    fibo_tab = malloc((n+1)*sizeof(long)); //On allour à fibo_tab la mémoire requise pour stocker n+1 long.
    fibo_tab[0] = 0;
    fibo_tab[1] = 1;
    for(int i =2;i<n+1;i++) //C'est la structure d'une boucle for en C. Remarquez qu'on peut déclarer i directement dans la boucle.
    {
        fibo_tab[i] = fibo_tab[i-1] + fibo_tab[i-2]; //On stock en case i la somme des 2 précédentes
    }
    return fibo_tab[n];
}
 
long** parmi_tab; //parmi_tab est un tableau vers des pointeurs. C'est l'équivalent d'une matrice.
long parmi2(int k, int n){ //On définit sépare par une virgule les différents arguments d'un tableau
    parmi_tab = malloc((n+1)*sizeof(long*)); //On alloue la bonne taille à pour parmi_tab
    for(int i = 0; i <n+1; i++) parmi_tab[i] = malloc((n+1)*sizeof(long)); //Puis pour chaque pointeur de parmi tab, on allour également la taille mémoire requise
//Notez que la ligne précédente permet de faire une boucle for en 1 ligne. C'est possible uniquement si l'ont ne met qu'une instruction après la boucle for.
    //Maintenant que la mémoire est allouée, on peut calculer les termes.
    for(int i =0;i<n+1;i++) 
    {
        parmi_tab[0][i] = 1; //0 parmi i vaut 1
        for(int j =1; j<n+1;j++){
            parmi_tab[j][i] = (j<=i)? parmi_tab[j-1][i-1] + parmi_tab[j][i-1] : 0; //Cette ligne un peu compliquée est un if ternaire:
	//Si la condition avant le ? est validée, on effectue ce qu'il y a avant les :, sinon on effectue ce qu'il y a après.
        }
    }
    long res = parmi_tab[k][n]; //On stock le résultat que l'on veut garder
    for(int i = 0; i <n+1; i++) free(parmi_tab[i]); //on libère la mémoire occupée
    return res;
}

int main()
{	printf("%ld \n",parmi2(2,5)); // Pour afficher un long on utilise %ld.
	free(fibo_tab); //On pense à free fibo_tab
	free(parmi_tab); //Les différentes lignes de parmi_tab ont été free directement dans la fonction.
	return 0;
}
