#include "graphl.h"

static int cnt1, cnt2;
static vertex *stack;
static int k, N;

/* A função NEWnode() recebe um vértice w e o endereço next de um nó e devolve o
   endereço a de um novo nó tal que a->w == w e a->next == next. */
static linkL NEWnode (vertex w, linkL next) { 
    linkL a = malloc (sizeof (struct node));
    a->w = w; 
    a->next = next;     
    return a;                         
}

/* REPRESENTAÇÃO POR LISTAS DE ADJACÊNCIA: A função GRAPHinit() constrói um 
   grafo com vértices 0 1 .. V-1 e nenhum arco. */
Graph GRAPHinit (int V) { 
    vertex v;
    Graph G = malloc (sizeof *G);
    G->V = V; 
    G->A = 0;
    G->adj = malloc (V * sizeof (linkL));
    for (v = 0; v < V; ++v) 
        G->adj[v] = NULL;
    G->pre = malloc (V * sizeof v);
    G->post = malloc (V * sizeof v);
    G->parent = malloc (V * sizeof v);
    G->low = malloc (V * sizeof v);
    return G;
}

Graph GRAPHinputArcs (void) {
    int V, A, i, v, w, error;
    Graph G;
    error = scanf (" %d %d", &V, &A);
    G = GRAPHinit(V);
    for (i = 0; i < A; ++i) {
        error |= scanf (" %d %d", &v, &w);
        GRAPHinsertArc(G, v, w);
    }
    if (error == 1) fprintf (stderr, "error\n");
    return G;
}

Graph GRAPHinputLists (void) {
    int V, i, v, w, error = 0, insert;
    char c;
    Graph G;
    error |= scanf (" %d", &V);
    G = GRAPHinit (V);
    for (i = 0; i < V; ++i) {
        error |= scanf (" %d", &v);
        w = c = insert = 0;
        while (c != '\n') {
            error |= scanf ("%c", &c);
            while (isdigit(c)) {
                insert = 1;
                w *= 10;
                w += c - '0';
                error |= scanf ("%c", &c);
            }
            if (insert) GRAPHinsertArc (G, v, w);
            w = insert = 0;
        }
    }
    return G;
}

Graph GRAPHinputArcsFile (FILE *in) {
    int V, A, i, v, w, error;
    Graph G;
    error = fscanf (in, " %d %d", &V, &A);
    G = GRAPHinit(V);
    for (i = 0; i < A; ++i) {
        error |= fscanf (in, " %d %d", &v, &w);
        GRAPHinsertArc(G, v, w);
    }
    if (error == 1) fprintf (stderr, "error\n");
    return G;
}

Graph GRAPHinputListsFile (FILE *in) {
    int V, i, v, w, error = 0, insert;
    char c;
    Graph G;
    error |= fscanf (in, " %d", &V);
    G = GRAPHinit (V);
    for (i = 0; i < V; ++i) {
        error |= fscanf (in, " %d", &v);
        w = c = insert = 0;
        while (c != '\n') {
            error |= fscanf (in, "%c", &c);
            while (isdigit(c)) {
                insert = 1;
                w *= 10;
                w += c - '0';
                error |= fscanf (in, "%c", &c);
            }
            if (insert) GRAPHinsertArc (G, v, w);
            w = insert = 0;
        }
    }
    return G;
}

Graph UGRAPHknight() {
    int i, j;
    Graph G = GRAPHinit (64);
    for (i = 0; i < 64; ++i) {
        j = i - 16 + 1;
        if (j > 0 && j % 8 > i % 8) {
            GRAPHinsertArc (G, i, j);
            GRAPHinsertArc (G, j, i);
        }
        j = i - 8 + 2;
        if (j > 0 && j % 8 > i % 8) {
            GRAPHinsertArc (G, i, j);
            GRAPHinsertArc (G, j, i);
        }
        j = i + 8 + 2;
        if (j < 64 && j % 8 > i % 8) {
            GRAPHinsertArc (G, i, j);
            GRAPHinsertArc (G, j, i);            
        }
        j = i + 16 + 1;
        if (j < 64 && j % 8 > i % 8) {
            GRAPHinsertArc (G, i, j);
            GRAPHinsertArc (G, j, i);            
        }
        j = i + 16 - 1;
        if (j < 64 && j % 8 < i % 8) {
            GRAPHinsertArc (G, i, j);
            GRAPHinsertArc (G, j, i);            
        }
        j = i + 8 - 2;
        if (j < 64 && j % 8 < i % 8) {
            GRAPHinsertArc (G, i, j);
            GRAPHinsertArc (G, j, i);            
        }
        j = i - 8 - 2;
        if (j > 0 && j % 8 < i % 8) {
            GRAPHinsertArc (G, i, j);
            GRAPHinsertArc (G, j, i);
        }
        j = i - 16 - 1;
        if (j > 0 && j % 8 < i % 8) {
            GRAPHinsertArc (G, i, j);
            GRAPHinsertArc (G, j, i);
        }
    }
    return G;
}

Graph GRAPHbuildComplete (int V) {
    Graph G;
    vertex v, w;
    G = GRAPHinit (V);
    for (v = 0; v < G->V; ++v)
        for (w = v + 1; w < G->V; ++w) {
            GRAPHinsertArc (G, v, w);
            GRAPHinsertArc (G, w, v);
        }
    return G;
}

/* A função randV() devolve um vértice aleatório do grafo G. */
static vertex randV (Graph G) { 
    double r;
    r = rand () / (RAND_MAX + 1.0);
    return r * G->V;
}

/* Essa função constrói um grafo aleatório com vértices 0..V-1 e exatamente A
   arcos. A função supõe que A <= V*(V-1). Se A for próximo de V*(V-1), a função
   pode consumir muito tempo. (Código inspirado no Programa 17.7 de Sedgewick.) */
Graph GRAPHrand1 (int V, int A) { 
    Graph G = GRAPHinit (V);
    while (G->A < A) {
        vertex v = randV (G);
        vertex w = randV (G);
        if (v != w) 
            GRAPHinsertArc (G, v, w);
    }
    return G;
}

/* Constrói um grafo aleatório com vértices 0..V-1 e número esperado de arcos
   igual a A. A função supõe que V >= 2 e A <= V*(V-1). (Código inspirado no
   Program 17.8 de Sedgewick.) */
Graph GRAPHrand2 (int V, int A) { 
    double prob = (double) A / V / (V-1);
    Graph G = GRAPHinit (V);
    vertex v, w;
    for (v = 0; v < V; ++v)
        for (w = 0; w < V; ++w)
            if (v != w)
                if (rand () < prob*(RAND_MAX+1.0))
                    GRAPHinsertArc (G, v, w);
    return G;
}

Graph GRAPHbuildRandRootedTree (int V) {
    Graph G;
    G = GRAPHinit (V);
    return G;
}

/* Constrói o inverso do grafo G. */
Graph GRAPHreverse (Graph G) {
    vertex v, w; linkL a;
    Graph GR = GRAPHinit (G->V);
    for (v = 0; v < G->V; ++v) 
        for (a = G->adj[v]; a != NULL; a = a->next) {
            w = a->w;
            GRAPHinsertArc (GR, w, v);
        }
    return GR;
}

UGraph UGRAPHrandU (int V, int E) {
    double prob = (double) E / V / (V-1);
    UGraph G = GRAPHinit (V);
    vertex v, w;
    for (v = 0; v < V; ++v)
        for (w = 0; w < V; ++w)
            if (v != w)
                if (rand () < prob*(RAND_MAX+1.0))
                    UGRAPHinsertArc (G, v, w);
    return G;
}

/* REPRESENTAÇÃO POR LISTAS DE ADJACÊNCIA: A função GRAPHinsertArc() insere um
   arco v-w no grafo G. A função supõe que v e w são distintos, positivos e 
   menores que G->V. Se o grafo já tem um arco v-w, a função não faz nada. */
void GRAPHinsertArc (Graph G, vertex v, vertex w) { 
    linkL a;
    for (a = G->adj[v]; a != NULL; a = a->next) 
        if (a->w == w) return;
    G->adj[v] = NEWnode (w, G->adj[v]);
    G->A++;
}

void UGRAPHinsertArc (Graph G, vertex v, vertex w) {
    GRAPHinsertArc (G, v, w);
    GRAPHinsertArc (G, w, v);
}

void GRAPHremoveArc (Graph G, vertex v, vertex w) { 
    linkL a, *ant;
    for (ant = &G->adj[v], a = G->adj[v]; a != NULL; ant = &a, a = a->next)
        if (a->w == w) {
            *ant = a->next;
            free (a);
            G->A--;
            return;
        }
}

/* Seja X o conjunto dos vértices x que estão ao alcance de v e têm pre[x] == -1.
   Para cada vértice x em X, a função dfsR() atribui um valor positivo a pre[x] 
   de modo que o k-ésimo vértice descoberto receba valor cnt+k.  O código supõe 
   que G é representado por uma matriz de adjacências. (Código inspirado no 
   programa 18.1 de Sedgewick.) */
static void dfsR (Graph G, vertex v) { 
    linkL a;
    G->pre[v] = cnt1++; 
    for (a = G->adj[v]; a != NULL; a = a->next)
        if (G->pre[a->w] == -1) {
            G->parent[a->w] = v;
            dfsR (G, a->w);
        }
    G->post[v] = cnt2++;
}

/* A função GRAPHdfs() visita todos os vértices e todos os arcos do grafo G. 
   A função atribui um número de ordem pre[x] a cada vértice x: o k-ésimo 
   vértice descoberto recebe número de ordem k.  (Código inspirado no 
   programa 18.3 de Sedgewick.) */
void GRAPHdfs (Graph G) { 
    vertex v;
    cnt1 = cnt2 = 0;
    for (v = 0; v < G->V; ++v) 
        G->pre[v] = -1;
    for (v = 0; v < G->V; ++v)
        if (G->pre[v] == -1) {
            G->parent[v] = v;
            dfsR (G, v);
        }
}

void GRAPHtopoOrder (Graph G, int *vv) {
    vertex v;
    GRAPHdfs (G);
    for (v = 0; v < G->V; ++v)
        vv[G->V - 1 - G->post[v]] = v;
}

void GRAPHpath (Graph G, vertex s, vertex t) {
    vertex v;
    cnt1 = cnt2 = 0;
    for (v = 0; v < G->V; ++v) G->pre[v] = -1;
    G->parent[s] = s;
    dfsR (G, s);

    if (G->pre[t] == -1) {
        for (v = 0; v < G->V; ++v)
            if (G->pre[v] != -1)
                printf (" %2d", v);
        printf ("\n");
    }
    else {
        stack = malloc (G->V * sizeof v);
        for (N = 0, v = t; v != G->parent[v]; v = G->parent[v])
            stack[N++] = v;
        printf ("%2d", s);
        for (v = N - 1; v >= 0; --v)
            printf ("%2d%c", stack[v], v == 0 ? '\n' : ' ');
    }
}

static void bridgesR (Graph G, vertex v) { 
    vertex w; linkL a; int min;
    G->pre[v] = cnt1++;
    min = G->pre[v];
    for (a = G->adj[v]; a != NULL; a = a->next) {
        w = a->w;
        if (w == G->parent[v]) continue;
        if (G->pre[w] == -1) {
            G->parent[w] = v;
            bridgesR (G, w);
            if (G->low[w] < min) min = G->low[w];
        }
        else if (G->pre[w] < G->pre[v]) {
            if (G->pre[w] < min) min = G->pre[w];
        }
    }
    G->low[v] = min;
    if (G->parent[v] != v && G->low[v] > G->pre[G->parent[v]])
        printf ("%d-%d\n", G->parent[v], v);
}

void UGRAPHbridges (UGraph G) {
    vertex v;
    for (v = 0; v < G->V; ++v)
        G->pre[v] = -1;

    cnt1 = 0;
    for (v = 0; v < G->V; ++v)
        if (G->pre[v] == -1) {
            G->parent[v] = v;
            bridgesR (G, v);
        }
}

int GRAPHindeg (Graph G, vertex v) {
    int i, ans = 0;
    linkL a;
    for (i = 0; i < G->V; i++)
        for (a = G->adj[i]; a != NULL; a = a->next)
            if (a->w == v) ans++;
    return ans;
}

int GRAPHoutdeg (Graph G, vertex v) {
    int ans = 0;
    linkL a;
    for (a = G->adj[v]; a != NULL; a = a->next)
        ans++;
    return ans;
}

int GRAPHrootedForestHeight (Graph G, vertex *p) {
    int *h, *stack, top = 0, i, max = 0;
    h = malloc (G->V * sizeof (int));
    stack = malloc (G->V * sizeof (int));
    for (i = 0; i < G->V; ++i) h[i] = (i == p[i] ? 0:-1);
    for (i = 0; i < G->V; ++i) {
        while (h[i] == -1) {
            stack[top++] = i;
            i = p[i];
        }
        while (top > 0) {
            i = stack[--top];
            h[i] = h[p[i]] + 1;
        }
        max = (h[i] > max ? h[i] : max);
    }
    free (h); free (stack);
    return max;
}

/* A função dfsRcc() atribui o número id a todos os vértices que estão na mesma 
   componente conexa que v. A função supõe que o grafo é representado por listas 
   de adjacência. */
static void dfsRcc (UGraph G, int *cc, vertex v, int id) { 
    linkL a; 
    cc[v] = id;
    for (a = G->adj[v]; a != NULL; a = a->next)
        if (cc[a->w] == -1) 
            dfsRcc (G, cc, a->w, id); 
}

/* A função UGRAPHcc() devolve o número de componentes conexas do grafo 
   não-dirigido G. Além disso, armazena no vetor cc[] uma numeração dos 
   vértices tal que dois vértices v e w pertencem à mesma componente se 
   e somente se cc[v] == cc[w]. (O código foi copiado do programa 18.4 
   de Sedgewick.) */
int UGRAPHcc (UGraph G, int *cc) { 
    vertex v; int id = 0;
    for (v = 0; v < G->V; ++v) 
        cc[v] = -1;
    for (v = 0; v < G->V; ++v)
        if (cc[v] == -1) 
            dfsRcc (G, cc, v, id++);
    return id;
}

int UGRAPHccAdd (UGraph G, int *cc, vertex v, vertex w) {
    vertex s; int id = 0, idv = cc[v], idw = cc[w];
    for (s = 0; s < G->V; ++s)
        id = id < cc[s] ? cc[s] : id;
    if (cc[v] != cc[w]) {
        for (s = 0; s < G->V; ++s)
            if (cc[s] == idv || cc[s] == idw)
                cc[s] = cc[v] < cc[w] ? cc[v] : cc[w];
        return id;
    }
    return id + 1;
}

/* O código de strongR() foi adaptado da figura 5.15 do livro de Aho,
   Hopcroft e Ullman. */
static void strongR (Graph G, vertex v, int *sc) { 
    vertex w, u; linkL a; int min;
    G->pre[v] = cnt1++;
    min = G->pre[v]; 
    stack[N++] = v;
    for (a = G->adj[v]; a != NULL; a = a->next) {
        w = a->w;
        if (G->pre[w] == -1) {
            strongR (G, w, sc);
            if (G->low[w] < min) min = G->low[w]; /*A*/
        }
        else if (G->pre[w] < G->pre[v] && sc[w] == -1) {
            if (G->pre[w] < min) min = G->pre[w]; /*B*/
        }
    }
    G->low[v] = min;
    if (G->low[v] == G->pre[v]) {               /*C*/
        do {
            u = stack[--N];
            sc[u] = k;
        } while (u != v);
        k++;
    }
}

/* A função GRAPHscT() devolve o número de componentes fortes do grafo G e 
   armazena no vetor sc[], indexado pelo vértices de G, os nomes das componentes
   fortes de G: para cada vértice u, sc[u] será o nome da componente forte que 
   contém u. Os nomes das componentes fortes são 0, 1, 2, etc. (A função 
   implementa o algoritmo de Tarjan.) */
int GRAPHscT (Graph G, int *sc) {
    vertex v; 
    stack = malloc (G->V * sizeof (vertex));
    for (v = 0; v < G->V; ++v) 
        G->pre[v] = sc[v] = -1;

    k = N = cnt1 = 0;
    for (v = 0; v < G->V; ++v) 
        if (G->pre[v] == -1)
            strongR (G, v, sc);
   
    free (stack);
    return k;
}

/* Atribui o rótulo k a todo vértice w ao alcance de v que ainda não foi 
   rotulado. Os rótulos são armazenados no vetor sc[]. */
static void dfsRsc( Graph G, vertex v, int *sc, int k) { 
    linkL a;
    sc[v] = k;
    for (a = G->adj[v]; a != NULL; a = a->next)
        if (sc[a->w] == -1) 
            dfsRsc( G, a->w, sc, k);
}

/* Esta função atribui um rótulo sc[v] (os rótulos são 0,1,2,...) a cada vértice
   v do grafo G de modo que dois vértices tenham o mesmo rótulo se e somente se 
   os dois pertencem à mesma componente forte. A função devolve o número 
   (quantidade) de componentes fortes de G. (A função implementa o algoritmo de 
   Kosaraju. O código é adaptado do Programa 19.10 de Sedgewick.) */
int GRAPHscK (Graph G, int *sc) {
    int k, i, *vv;
    vertex v; 
    
    /* fase 1 */
    Graph GR = GRAPHreverse (G);
    vv = malloc (G->V * sizeof (int));
   
    cnt1 = cnt2 = 0;
    for (v = 0; v < GR->V; ++v) 
        GR->pre[v] = -1;
    for (v = 0; v < GR->V; ++v) 
        if (GR->pre[v] == -1)
            dfsR (GR, v);
    for (v = 0; v < GR->V; ++v) 
        vv[GR->post[v]] = v;

    /* fase 2 */
    for (v = 0; v < G->V; ++v) 
        sc[v] = -1;
    for (k = 0, i = G->V-1; i >= 0; --i) {
        v = vv[i];
        if (sc[v] == -1) { /* nova etapa */
            dfsRsc (G, v, sc, k);
            k++;
        }
    }
    GRAPHfree (GR);
    free (vv);
    return k;
}

bool GRAPHisUndirected (Graph G) {
    int i, w;
    linkL a, b;
    for (i = 0; i < G->V; ++i)
        for (a = G->adj[i]; a != NULL; a = a->next) {
            w = a->w;
            for (b = G->adj[w]; b != NULL; b = b->next)
                if (b->w == i) break;
            if (b == NULL) return false;
        }
    return true;
}

bool GRAPHisolated (Graph G, vertex v) {
    if (GRAPHindeg (G, v) > 0) return false;
    if (GRAPHoutdeg (G, v) > 0) return false;
    return true;
}

bool GRAPHadj (Graph G, vertex v, vertex w) {
    linkL a;
    for (a = G->adj[v]; a != NULL; a = a->next)
        if (a->w == w) return true;
    for (a = G->adj[w]; a != NULL; a = a->next)
        if (a->w == v) return true;
    return false;
}

bool GRAPHisTopoNumbering (Graph G, int *topo) {
    vertex v;
    linkL a;
    for (v = 0; v < G->V; ++v) 
        for (a = G->adj[v]; a != NULL; a = a->next) 
            if (topo[v] >= topo[a->w]) 
                return false;
    return true;
}

bool GRAPHisTopoOrder (Graph G, vertex *vv) {
    int *topo, i;
    topo = malloc (G->V * sizeof (int));
    for (i = 0; i < G->V; ++i)
        topo[vv[i]] = i;
    i = GRAPHisTopoNumbering (G, topo);
    free (topo);
    return i;
}

bool GRAPHreach (Graph G, vertex s, vertex t) {
    vertex v; linkL a, *next;
    bool *visit;
    visit = malloc (G->V * sizeof (bool));
    stack = malloc (G->V * sizeof v);
    next = malloc (G->V * sizeof a);

    N = 0;
    for (v = 0; v < G->V; ++v) visit[v] = false;
    stack[N] = s;
    next[N] = G->adj[s];

    while (N >= 0) {
        v = stack[N];
        a = next[N];
        visit[v] = true;
        if (v == t) break;

        while (a != NULL) {
            if (!visit[a->w]) {
                stack[N + 1] = a->w;
                next[N + 1] = G->adj[a->w];
                break;
            }
            a = a->next;
        }
        next[N] = a;
        if (a == NULL) N--;
        else N++;
    }
    free (visit); free (stack); free (next);
    return v == t;
}

/* A função cycleR() devolve TRUE se encontra um ciclo ao percorrer G a partir 
   do vértice v e devolve FALSE em caso contrário. */
static bool cycleR (Graph G, vertex v) { 
    linkL a;
    G->pre[v] = cnt1++;
    for (a = G->adj[v]; a != NULL; a = a->next) {
        vertex w = a->w;
        if (G->pre[w] == -1) {
            if (cycleR (G, w)) 
                return true;
        } else {
            if (G->post[w] == -1) /* A */
                return true;   /* v-w é de retorno */
            /* B */
        }
    }
    G->post[v] = cnt2++;
    return false;
}

bool GRAPHhasCycle (Graph G) {
    vertex v;
    cnt1 = cnt2 = 0;
    for (v = 0; v < G->V; ++v)
        G->pre[v] = G->post[v] = -1;
    for (v = 0; v < G->V; ++v)
        if (G->pre[v] == -1)
            if (cycleR (G, v)) return true;
    return false;
}

bool UGRAPHisConnected (UGraph G) {
    vertex v;
    dfsR (G, 0);
    for (v = 0; v < G->V; ++v)
        if (G->pre[v] == -1) return false;
    return true;
}

void GRAPHshow (Graph G) { 
    vertex v;
    linkL a;
    for (v = 0; v < G->V; ++v) {
        printf  ("%2d:", v);
        for (a = G->adj[v]; a != NULL; a = a->next) {
            printf  (" %2d", a->w);
        }
        printf  ("\n");
    }
}

void UGRAPHshowKnight (Graph G, int i, int j) {
    vertex v, w;
    for (v = i * 8 + j, w = 0; w < G->V; ++w) {
        if (GRAPHadj (G, v, w))
            printf ("X ");
        else if (w == v)
            printf ("K ");
        else
            printf (". ");
        if (w % 8 == 7)
            printf ("\n");
    }
}

void GRAPHfree (Graph G) {
    vertex v;
    linkL a, b;
    for (v = 0; v < G->V; ++v) {
        a = G->adj[v];
        while (a != NULL) {
            b = a->next;
            free (a);
            a = b;
        }
    }
    free (G->adj);
    free (G->pre);
    free (G);
}
