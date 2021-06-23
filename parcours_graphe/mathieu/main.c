#include "const.h"

int main()
{

    //srand(time(NULL));
    srand(48);
    /*
    for (int i = 0; i < 10; ++i)
        printf("%d\n", rand() % N);
*/
    SDL_DisplayMode screen;
    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;

    SDL_Rect window_dimensions = {0};

    /* Initialisation de la SDL  + gestion de l'échec possible */
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        SDL_Log("Error : SDL initialisation - %s\n", SDL_GetError()); // l'initialisation de la SDL a échoué
        exit(EXIT_FAILURE);
    }

    SDL_GetCurrentDisplayMode(0, &screen);
    printf("Résolution écran\n\tw : %d\n\th : %d\n", screen.w, screen.h);

    /************** creation window ****************/
    window = SDL_CreateWindow(
        "Labyrinthe",
        (screen.w - LARGEUR_FENETRE) / 2, (screen.h - HAUTEUR_FENETRE) / 2,
        LARGEUR_FENETRE, HAUTEUR_FENETRE,
        0);
    if (window == NULL)
        end_sdl(0, "ERROR WINDOW CREATION", window, renderer);
    SDL_GetWindowSize(window, &window_dimensions.w, &window_dimensions.h);

    /************** creation renderer ****************/
    renderer = SDL_CreateRenderer(window, -1, 0);
    if (renderer == NULL)
        end_sdl(0, "ERROR RENDERER CREATION", window, renderer);

    //generation graph arete
    graph_l_arete_t *graph = NULL;
    graph = init_graph_arete_en_grille();
    graphviz_affiche_graph_arete(graph);

    melange_fisher_yates_arete(graph);

    float p = 0.01;

    graph_l_arete_t *quasi_arbre = NULL;
    quasi_arbre = calcul_quasi_foret_couvrant(graph, p);
    graphviz_affiche_graph_arete(quasi_arbre);
    
    liberer_graph_arete(graph);

    int map[NB_LIGNE_LABY][NB_COLONNE_LABY];
    construire_map(map, quasi_arbre);

/*
    int parent[N];
    int distance[N];

    dijkstra(map, 0, distance, parent);
    printf("parent : "); affficher_tab(parent,N);
    printf("distance : "); affficher_tab(distance,N);
*/
    //main_labyrinthe(map);
    //dessiner(window, renderer, map);
    int sourc = 0;
    int dest = 0;

    int chemin_list[N];
    int taille_chemin;
    int compt = 0;
    int alea;
    while (compt < 10)
    {
        sourc = dest;
        alea = rand() % quasi_arbre->nb_noeud;
        printf("alea=%d\n", alea);
        dest = alea;
        taille_chemin = chemin(map, sourc, dest, chemin_list);

        //printf("sourc=%d, dest=%d\n", sourc, dest);
        //affficher_tab(chemin_list, taille_chemin);

        dessiner_dijkstra(window, renderer, map, chemin_list, taille_chemin);
        ++compt;
    }

    //play_texture_mur(window, renderer, map);

    dessiner(window, renderer, map);
    SDL_Delay(2000);
    SDL_RenderPresent(renderer);

    liberer_graph_arete(quasi_arbre);

    end_sdl(1, "fin normal", window, renderer);
    return 0;
}