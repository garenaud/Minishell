#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

#define MAX_COMMANDES 100
#define MAX_LONGUEUR_COMMANDE 256

void lire_ligne_commande(char *commande) 
{
	fgets(commande, MAX_LONGUEUR_COMMANDE, stdin);
	// Supprimer le retour à la ligne final
	commande[strlen(commande) - 1] = '\0';
}

int main(int argc, char *argv[]) 
{
	char commande[MAX_LONGUEUR_COMMANDE];
	char *commandes[MAX_COMMANDES];
	int nb_commandes = 0;
	int i;

	printf("Entrez une ligne de commande : ");
	lire_ligne_commande(commande);

	// Séparer la ligne de commande en plusieurs commandes séparées par des pipes
	char *token = strtok(commande, "|");
	while (token != NULL) 
	{
		commandes[nb_commandes] = token;
		nb_commandes++;
		token = strtok(NULL, "|");
	}
	// Créer les pipes pour chaque commande
	int pipes[nb_commandes][2];
	for (i = 0; i < nb_commandes; i++) 
	{
		if (pipe(pipes[i]) < 0) {
		perror("Erreur lors de la création des pipes");
		return 1;
	}
}

// Exécuter les commandes en utilisant les pipes pour la communication entre les processus
pid_t pid;
for (i = 0; i < nb_commandes; i++) {
pid = fork();
if (pid < 0) {
perror("Erreur lors de la création du processus");
return 1;
}
if (pid == 0) {
// Processus fils : exécuter la commande
if (i > 0) {
// Si c'est pas la première commande, utiliser le pipe précédent en tant qu'entrée
dup2(pipes[i-1][0], STDIN_FILENO);
close(pipes[i-1][0]);
close(pipes[i-1][1]);
}
if (i < nb_commandes - 1) 
{
// Si c'est pas la dernière commande, utiliser le pipe suivant en tant que sortie
dup2(pipes[i][1], STDOUT_FILENO);
close(pipes[i][0]);
close(pipes[i][1]);
}