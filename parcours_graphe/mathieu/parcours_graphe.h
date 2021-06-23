#ifndef __PARCOURS_GRAPHE_H__
#define __PARCOURS_GRAPHE_H__

#include "const.h"

int main_parcours_graphe();

void dijkstra_init(int r, int distance[N], int parent[N]);
void relachement(int u, int v, int p_u_v, int distance[N], int parent[N], tas_binaire_t *tas);
void dijkstra(int map[NB_LIGNE_LABY][NB_COLONNE_LABY], int r, int distance[N], int parent[N]);

graph_l_arete_t *copie_graph(graph_l_arete_t *graph);
void dessiner_dijkstra(SDL_Window *window, SDL_Renderer *renderer, int map[NB_LIGNE_LABY][NB_COLONNE_LABY], int chemin_list[N], int taille_chemin);
int chemin(int map[NB_LIGNE_LABY][NB_COLONNE_LABY], int sour, int dest, int chemin_list[N]);
#endif