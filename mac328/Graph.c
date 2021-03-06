#ifndef GRAPH
#define GRAPH "graphl.h"
#endif
#include "prompt.h"
#include GRAPH

char *func_names[] = {
    "init", 
    "inputArcs",
    "inputLists",
    "inputArcsFile",
    "inputListsFile",
    "knight",
    "buildComplete",
    "rand1",
    "rand2",
    "randU",
    "insertArc",
    "insertUArc",
    "removeArc",
    "dfs",
    "bfs",
    "topoOrder",
    "path",
    "bridges",
    "indeg",
    "outdeg",
    "rootedForestHeight",
    "dfsForestHeight",
    "cc",
    "ccAdd",
    "scT",
    "scK",
    "isUndirected",
    "isolated",
    "adj",
    "isTopoNumbering",
    "isTopoOrder",
    "reach",
    "hasCycle",
    "isConnected",
    "show",
    "showKnight",
    "minPaths",
    "save",
    "vertices",
    "arcs",
    "ccBfs",
    "grid",
    "gridDiagonals",
    "reverse",
    "sequentialColoring",
    "twoColor",
    "isMatching",
    "bipartiteMatching",
    "quit",
    NULL
};

int main () {
    Graph GR, G = GRAPHinit (1);
    Stack S;
    FILE * in, * out;
    vertex v, w;
    int *arr, *arr2;
    int error = 0, V, A, E, func, i;
    char *file = NULL, *command = NULL;
    bool jump = false;
    prompt_init (func_names);
    
    while (!jump) {
        command = type_prompt (command);

        for (func = 0, i = 0; func_names[i] != NULL; i++) {
            if (strcmp (command, func_names[i]) == 0) {
                func = i + 1;
                break;
            }
        }

        switch (func) {
            
        case 1:
            printf ("Graph GRAPHinit (int V)\n");
            while (scanf (" %d", &V) != EOF) {
                if (V > 0) {
                    GRAPHfree (G);
                    G = GRAPHinit (V);
                    A = 0;
                    break;
                }
                printf ("Please insert an integer V > 0\n");
            }
            break;

        case 2:
            printf ("Graph GRAPHinputArcs (void)\n");
            GRAPHfree (G);
            G = GRAPHinputArcs ();
            V = GRAPHvertices (G);
            A = GRAPHarcs (G);
            break;
            
        case 3:
            printf ("Graph GRAPHinputLists (void)\n");
            GRAPHfree (G);
            G = GRAPHinputLists ();
            V = GRAPHvertices (G);
            A = GRAPHarcs (G);
            break;

        case 4:
            printf ("Graph GRAPHinputArcsFile (FILE *in)\n");
            file = type_file (file);
            if (strlen (file) > 0) {
                in = fopen (file, "r");
                GRAPHfree (G);
                G = GRAPHinputArcsFile (in);
                V = GRAPHvertices (G);
                A = GRAPHarcs (G);
                fclose (in);
            }
            break;

        case 5:
            printf ("Graph GRAPHinputListsFile (FILE *in)\n");
            file = type_file (file);
            if (strlen (file) > 0) {
                in = fopen (file, "r");
                GRAPHfree (G);
                G = GRAPHinputListsFile (in);
                V = GRAPHvertices (G);
                A = GRAPHarcs (G);
                fclose (in);
            }
            break;

        case 6:
            printf ("Graph UGRAPHknight ()\n");
            GRAPHfree (G);
            G = UGRAPHknight ();
            V = GRAPHvertices (G);
            A = GRAPHarcs (G);
            break;

        case 7:
            printf ("Graph GRAPHbuildComplete (int V)\n");
            while (scanf (" %d", &V) != EOF) {
                if (V > 0) {
                    GRAPHfree (G);
                    G = GRAPHbuildComplete (V);
                    V = GRAPHvertices (G);
                    A = GRAPHarcs (G);
                    break;
                }
            }
            break;

        case 8:
            printf ("Graph GRAPHrand1 (int V, int A)\n");
            while (scanf (" %d %d", &V, &A) != EOF) {
                if (V > 0 && A >= 0) {
                    GRAPHfree (G);
                    G = GRAPHrand1 (V, A);
                    break;
                }
            }
            break;

        case 9:
            printf ("Graph GRAPHrand2 (int V, int A)\n");
            while (scanf (" %d %d", &V, &A) != EOF) {
                if (V > 0 && A >= 0) {
                    GRAPHfree (G);
                    G = GRAPHrand1 (V, A);
                    break;
                }
            }
            break;

        case 10:
            printf ("UGraph UGRAPHrandU (int V, int E)\n");
            while (scanf (" %d %d", &V, &E) != EOF) {
                if (V > 0 && E >= 0) {
                    GRAPHfree (G);
                    G = UGRAPHrandU (V, E);
                    break;
                }
            }
            break;
            

        case 11:
            printf ("void GRAPHinsertArc (Graph G, vertex v, vertex w)\n");
            while (scanf (" %d %d", &v, &w) != EOF) {
                if (v >= 0 && w >= 0) {
                    GRAPHinsertArc (G, v, w);
                    A = GRAPHarcs (G);
                    break;
                }
            }
            break;

        case 12:
            printf ("void UGRAPHinsertArc (Graph G, vertex v, vertex w)\n");
            while (scanf (" %d %d", &v, &w) != EOF) {
                if (v >= 0 && w >= 0) {
                    UGRAPHinsertArc (G, v, w);
                    A = GRAPHarcs (G);
                    break;
                }
            }
            break;

        case 13:
            printf ("void GRAPHremoveArc (Graph G, vertex v, vertex w)\n");
            while (scanf (" %d %d", &v, &w) != EOF) {
                if (v >= 0 && w >= 0) {
                    GRAPHremoveArc (G, v, w);
                    A = GRAPHarcs (G);
                    break;
                }
            }
            break;

        case 14:
            printf ("void GRAPHdfs (Graph G)\n");
            GRAPHdfs (G);
            break;

        case 15:
            printf ("void GRAPHbfs (Graph G, vertex s)\n");
            while (scanf (" %d", &v) != EOF) {
                if (v >= 0) {
                    GRAPHbfs (G, v);
                    break;
                }
            }
            break;

        case 16:
            printf ("void GRAPHtopoOrder (Graph G, int *vv)\n");
            arr = malloc (V * sizeof (int));
            GRAPHtopoOrder (G, arr);
            for (v = 0; v < V; ++v)
                printf ("%2d%c", arr[v], ((v == V - 1)) ? '\n' : ' ');
            free (arr);
            break;

        case 17:
            printf ("void GRAPHpath (Graph G, vertex s, vertex t)\n");
            while (scanf (" %d %d", &v, &w) != EOF) {
                if (v >= 0 && w >= 0) {
                    GRAPHpath (G, v, w);
                    break;
                }
            }
            break;

        case 18:
            printf ("void UGRAPHbridges (UGraph G)\n");
            UGRAPHbridges (G);
            break;
            

        case 19:
            printf ("int GRAPHindeg (Graph G, vertex v)\n");
            while (scanf (" %d", &v) != EOF) {
                if (v >= 0) {
                    printf (" %d\n", GRAPHindeg (G, v));
                    break;
                }
            }
            break;

        case 20:
            printf ("int GRAPHoutdeg (Graph G, vertex v)\n");
            while (scanf (" %d", &v) != EOF) {
                if (v >= 0) {
                    printf (" %d\n", GRAPHoutdeg (G, v));
                    break;
                }
            }
            break;

        case 21:
            printf ("int GRAPHrootedForestHeight (Graph G, vertex *p)\n");
            arr = malloc (V * sizeof (int));
            for (i = 0; i < V; ++i) error |= scanf (" %d", &arr[i]);
            printf (" %d\n", GRAPHrootedForestHeight (G, arr));
            free (arr);
            break;

        case 22:
            printf ("int GRAPHdfsForestHeight (Graph G)\n");
            printf (" %d\n", GRAPHdfsForestHeight (G));
            break;

        case 23:
            printf ("int UGRAPHcc (UGraph G, int *cc)\n");
            arr = malloc (V * sizeof (int));
            printf ("components: %2d\n", UGRAPHcc (G, arr));
            printf ("v           ");
            for (i = 0; i < V; ++i) printf ("%2d%c", i, (i == V - 1) ? '\n' : ' ');
            printf ("cc          ");
            for (i = 0; i < V; ++i) printf ("%2d%c", arr[i], (i == V - 1) ? '\n' : ' ');
            free (arr);
            break;

        case 24:
            printf ("int UGRAPHccAdd (UGraph G, int *cc, vertex v, vertex w)\n");
            while (scanf (" %d %d", &v, &w) != EOF && v < 0 && w < 0) {}
            arr = malloc (V * sizeof (int));
            printf ("components: %2d\n", UGRAPHcc (G, arr));
            printf ("v           ");
            for (i = 0; i < V; ++i) printf ("%2d%c", i, (i == V - 1) ? '\n' : ' ');
            printf ("cc          ");
            for (i = 0; i < V; ++i) printf ("%2d%c", arr[i], (i == V - 1) ? '\n' : ' ');
            printf ("components: %2d", UGRAPHccAdd (G, arr, v, w));
            printf ("v           ");
            for (i = 0; i < V; ++i) printf ("%2d%c", i, (i == V - 1) ? '\n' : ' ');
            printf ("cc          ");
            for (i = 0; i < V; ++i) printf ("%2d%c", arr[i], (i == V - 1) ? '\n' : ' ');
            free (arr);
            break;

        case 25:
            printf ("int GRAPHscT (Graph G, int *sc)\n");
            arr = malloc (V * sizeof (int));
            printf ("components: %2d\n", GRAPHscT (G, arr));
            printf ("v           ");
            for (i = 0; i < V; ++i) printf ("%2d%c", i, (i == V - 1) ? '\n' : ' ');
            printf ("sc          ");
            for (i = 0; i < V; ++i) printf ("%2d%c", arr[i], (i == V - 1) ? '\n' : ' ');
            free (arr);
            break;

        case 26:
            printf ("int GRAPHscK (Graph G, int *sc)\n");
            arr = malloc (V * sizeof (int));
            printf ("components: %2d\n", GRAPHscK (G, arr));
            printf ("v           ");
            for (i = 0; i < V; ++i) printf ("%2d%c", i, (i == V - 1) ? '\n' : ' ');
            printf ("sc          ");
            for (i = 0; i < V; ++i) printf ("%2d%c", arr[i], (i == V - 1) ? '\n' : ' ');
            free (arr);
            break;

        case 27:
            printf ("bool GRAPHisUndirected (Graph G)\n");
            printf (GRAPHisUndirected (G) ? "Yes\n" : "No\n");
            break;

        case 28:
            printf ("bool GRAPHisolated (Graph G, vertex v)\n");
            error |= scanf (" %d", &v);
            printf (GRAPHisolated (G, v) ? "Yes\n" : "No\n");
            break;

        case 29:
            printf ("bool GRAPHadj (Graph G, vertex v, vertex w)\n");
            error |= scanf (" %d %d", &v, &w);
            printf (GRAPHadj (G, v, w) ? "Yes\n" : "No\n");
            break;

        case 30:
            printf ("bool GRAPHisTopoNumbering (Graph G, int *topo)\n");
            arr = malloc (V * sizeof (int));
            for (i = 0; i < V; ++i) error |= scanf (" %d", &arr[i]);
            printf (GRAPHisTopoNumbering (G, arr) ? "Yes\n" : "No\n");
            free (arr);
            break;

        case 31:
            printf ("bool GRAPHisTopoOrder (Graph G, vertex *vv)\n");
            arr = malloc (V * sizeof (int));
            for (i = 0; i < V; ++i) error |= scanf (" %d", &arr[i]);
            printf (GRAPHisTopoOrder (G, arr) ? "Yes\n" : "No\n");
            free (arr);
            break;

        case 32:
            printf ("bool GRAPHreach (Graph G, vertex s, vertex t)\n");
            error |= scanf (" %d %d", &v, &w);
            printf (GRAPHreach (G, v, w) ? "Yes\n" : "No\n");
            break;

        case 33:
            printf ("bool GRAPHhasCycle (Graph G)\n");
            printf (GRAPHhasCycle (G) ? "Yes\n" : "No\n");
            break;

        case 34:
            printf ("bool UGRAPHisConnected (UGraph G)\n");
            printf (UGRAPHisConnected (G) ? "Yes\n" : "No\n");
            break;

        case 35:
            printf ("void GRAPHshow (Graph G)\n");
            GRAPHshow (G);
            break;

        case 36:
            printf ("void UGRAPHshowKnight (Graph G, int i, int j)\n");
            error |= scanf (" %d %d", &v, &w);
            UGRAPHshowKnight (G, v, w);
            break;

        case 37:
            printf ("void GRAPHminPaths (Graph G, vertex s, int *pred, int *dist)\n");
            error |= scanf (" %d", &v);
            arr = malloc (V * sizeof (int));
            arr2 = malloc (V * sizeof (int));
            GRAPHminPaths (G, v, arr, arr2);
            S = STACKinit (V);
            for (v = 0; v < V; ++v) {
                if (arr[v] >= 0) {
                    printf (" dist[%d] = %d: ", v, arr2[v]);
                    for (w = v; w != arr[w]; STACKput (S, w), w = arr[w]);
                    for (printf ("%2d", w); !STACKempty (S); printf (" %2d", STACKget (S)));
                    printf ("\n");
                }
            }
            STACKfree (S);
            free (arr);
            free (arr2);
            break;

        case 38:
            printf ("void GRAPHsave (Graph G, FILE * out)\n");
            file = type_file (file);
            if (strlen (file) > 0) {
                out = fopen (file, "w");
                GRAPHsave (G, out);
                fclose (out);
            }
            break;

        case 39:
            printf ("int GRAPHvertices (Graph G)\n");
            printf (" %d\n", GRAPHvertices (G));
            break;

        case 40:
            printf ("int GRAPHarcs (Graph G)\n");
            printf (" %d\n", GRAPHarcs (G));
            break;

        case 41:
            printf ("int UGRAPHccBfs (UGraph G, int *cc)\n");
            arr = malloc (V * sizeof (int));
            printf ("components: %2d\n", UGRAPHccBfs (G, arr));
            printf ("v           ");
            for (i = 0; i < V; ++i) printf ("%2d%c", i, (i == V - 1) ? '\n' : ' ');
            printf ("cc          ");
            for (i = 0; i < V; ++i) printf ("%2d%c", arr[i], (i == V - 1) ? '\n' : ' ');
            free (arr);
            break;

        case 42:
            printf ("UGraph UGRAPHgrid (int N)\n");
            GRAPHfree (G);
            scanf (" %d", &V);
            G = UGRAPHgrid (V);
            V = GRAPHvertices (G);
            A = GRAPHarcs (G);
            break;

        case 43:
            printf ("UGraph UGRAPHgridDiagonals (int N)\n");
            GRAPHfree (G);
            scanf (" %d", &V);
            G = UGRAPHgridDiagonals (V);
            V = GRAPHvertices (G);
            A = GRAPHarcs (G);
            break;

        case 44:
            printf ("Graph GRAPHreverse (Graph G)\n");
            GR = GRAPHreverse (G);
            GRAPHfree (G);
            G = GR;
            V = GRAPHvertices (G);
            A = GRAPHarcs (G);
            break;

        case 45:
            printf ("int UGRAPHsequentialColoring (UGraph G, int *color)\n");
            arr = malloc (V * sizeof (int));
            printf ("colors: %2d\n", UGRAPHsequentialColoring (G, arr));
            printf ("v           ");
            for (i = 0; i < V; ++i) printf ("%2d%c", i, (i == V - 1) ? '\n' : ' ');
            printf ("color       ");
            for (i = 0; i < V; ++i) printf ("%2d%c", arr[i], (i == V - 1) ? '\n' : ' ');
            free (arr);
            break;

        case 46:
            printf ("bool UGRAPHtwoColor (UGraph G, int *color)\n");
            arr = malloc (V * sizeof (int));
            if (UGRAPHtwoColor (G, arr)) {
                printf ("v           ");
                for (i = 0; i < V; ++i) printf ("%2d%c", i, (i == V - 1) ? '\n' : ' ');
                printf ("color       ");
                for (i = 0; i < V; ++i) printf ("%2d%c", arr[i], (i == V - 1) ? '\n' : ' ');
            }
            else printf ("No\n");
            free (arr);
            break;

        case 47:
            printf ("bool UGRAPHisMatching (UGraph G, vertex *match)\n");
            arr = malloc (V * sizeof (int));
            for (v = 0; v < V; ++v) scanf (" %d", &arr[v]);
            printf (UGRAPHisMatching (G, arr) ? "Yes\n" : "No\n");
            free (arr);
            break;

        case 48:
            printf ("int UGRAPHbipartiteMatching (UGraph G, int *color, vertex *match, bool bfs)\n");
            arr = malloc (V * sizeof (int));
            if (UGRAPHtwoColor (G, arr)) {
                arr2 = malloc (V * sizeof (int));
                printf ("matching size: %2d\n", UGRAPHbipartiteMatching (G, arr, arr2, true));
                printf ("v           ");
                for (i = 0; i < V; ++i) printf ("%2d%c", i, (i == V - 1) ? '\n' : ' ');
                printf ("match       ");
                for (i = 0; i < V; ++i) printf ("%2d%c", arr2[i], (i == V - 1) ? '\n' : ' ');
                free (arr2);
            }
            else printf ("Graph is not bipartite\n");
            free (arr);
            break;

        case 49:
            jump = true;
        }
    }

    GRAPHfree (G);
    if (file) free (file);
    if (command) free (command);
    return 0;
}
