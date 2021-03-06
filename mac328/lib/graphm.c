#include "graphm.h"

/* REPRESENTAÇÃO POR MATRIZ DE ADJACÊNCIAS: A estrutura graph representa
   um grafo. O campo adj é um ponteiro para a matriz de adjacências do 
   grafo. O campo V contém o número de vértices e o campo A contém o 
   número de arcos do grafo. */
struct graph {
    int V; 
    int A; 
    int **adj;
    int cnt1;
    int cnt2;
    int *pre;
    int *post;
    int *pred;
    int *low;
};


/* REPRESENTAÇÃO POR MATRIZ DE ADJACÊNCIAS: A função MATRIXint() aloca uma matriz
   com linhas 0..r-1 e colunas 0..c-1. Cada elemento da matriz recebe valor val. */
static int **MATRIXint (int r, int c, int val) {
    vertex i, j;
    int **m = malloc (r * sizeof (int *));
    for (i = 0; i < r; ++i)
        m[i] = malloc (c * sizeof (int));
    for (i = 0; i < r; ++i)
        for (j = 0; j < c; ++j)
            m[i][j] = val;
    return m;
}

/* REPRESENTAÇÃO POR MATRIZ DE ADJACÊNCIAS: A função GRAPHinit() constrói um
   grafo com vértices 0 1 .. V-1 e nenhum arco. */
Graph GRAPHinit (int V) {
    Graph G = malloc (sizeof *G);
    G->V = V;
    G->A = 0;
    G->adj = MATRIXint (V, V, 0);
    return G;
}

Graph GRAPHinputArcs (void) {
    int V, A, i, v, w, error;
    Graph G;
    error = scanf (" %d %d", &V, &A);
    G = GRAPHinit (V);
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

Graph UGRAPHknight () {
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
    vertex v, w;
    srand (time (NULL));
    while (G->A < A) {
        v = randV (G);
        w = randV (G);
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
    srand (time (NULL));
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
    vertex v, w;
    Graph GR = GRAPHinit (G->V);
    for (v = 0; v < G->V; ++v)
        for (w = 0; w < G->V; ++w)
            if (G->adj[v][w]) GRAPHinsertArc (GR, w, v);
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

/* REPRESENTAÇÃO POR MATRIZ DE ADJACÊNCIAS: A função GRAPHinsertArc() insere um
   arco v-w no grafo G. A função supõe que v e w são distintos, positivos e
   menores que G->V. Se o grafo já tem um arco v-w, a função não faz nada. */
void GRAPHinsertArc (Graph G, vertex v, vertex w) {
    G->A += 1 - G->adj[v][w];
    G->adj[v][w] = 1;
}

void UGRAPHinsertArc (Graph G, vertex v, vertex w) {
    G->A += ((v == w) ? 1 - G->adj[v][w] : 2 - G->adj[v][w] - G->adj[w][v]);
    G->adj[v][w] = G->adj[w][v] = 1;
}

/* REPRESENTAÇÃO POR MATRIZ DE ADJACÊNCIAS: A função GRAPHremoveArc() remove do
   grafo G o arco v-w. A função supõe que v e w são distintos, positivos e
   menores que G->V. Se não existe arco v-w, a função não faz nada. */
void GRAPHremoveArc (Graph G, vertex v, vertex w) {
    if (G->adj[v][w] == 1) {
        G->adj[v][w] = 0;
        G->A--;
    }
}

/* Seja X o conjunto dos vértices x que estão ao alcance de v e têm pre[x] == -1.
   Para cada vértice x em X, a função dfsR() atribui um valor positivo a pre[x]
   de modo que o k-ésimo vértice descoberto receba valor cnt+k.  O código supõe
   que G é representado por uma matriz de adjacências. (Código inspirado no
   programa 18.1 de Sedgewick.) */
static void dfsR (Graph G, vertex v) {
    vertex w;
    G->pre[v] = G->cnt1++;
    for (w = 0; w < G->V; ++w)
        if (G->adj[v][w] != 0 && G->pre[w] == -1) {
            G->pred[w] = v;
            dfsR (G, w);
        }
    G->post[v] = G->cnt2++;
}

static void initDfs (Graph G) {
    vertex v;
    G->pre = malloc (G->V * sizeof v);
    G->post = malloc (G->V * sizeof v);
    G->pred = malloc (G->V * sizeof v);
    G->cnt1 = G->cnt2 = 0;
    for (v = 0; v < G->V; ++v)
        G->pre[v] = G->post[v] = -1;
}

static void freeDfs (Graph G) {
    if (G->pre) free (G->pre);
    if (G->post) free (G->post);
    if (G->pred) free (G->pred);
}

/* A função GRAPHdfs() visita todos os vértices e todos os arcos do grafo G.
   A função atribui um número de ordem pre[x] a cada vértice x: o k-ésimo
   vértice descoberto recebe número de ordem k.  (Código inspirado no
   programa 18.3 de Sedgewick.) */
void GRAPHdfs (Graph G) {
    vertex v;
    initDfs (G);
    
    for (v = 0; v < G->V; ++v)
        if (G->pre[v] == -1) {
            G->pred[v] = v;
            dfsR (G, v);
        }

    for (printf ("v     "), v = 0; v < G->V; ++v)
        printf ("%2d%c", v, (v == G->V - 1) ? '\n' : ' ');
    
    for (printf ("pre   "), v = 0; v < G->V; ++v)
        printf ("%2d%c", G->pre[v], (v == G->V - 1) ? '\n' : ' ');
    
    for (printf ("post  "), v = 0; v < G->V; ++v)
        printf ("%2d%c", G->post[v], (v == G->V - 1) ? '\n' : ' ');
    
    for (printf ("pred  "), v = 0; v < G->V; ++v)
        printf ("%2d%c", G->pred[v], (v == G->V - 1) ? '\n' : ' ');

    freeDfs (G);
}

/* A função GRAPHbfs() implementa o algoritmo de busca em largura. Ela visita
   todos os vértices do grafo G que estão ao alcance do vértice s.  A ordem em
   que os vértices são descobertos é registrada no vetor num[]. Esta versão da
   função supõe que o grafo G é representado por listas de adjacência.  (Código
   inspirado no programa 18.9 de Sedgewick.) */
void GRAPHbfs (Graph G, vertex s) {
    vertex v, w; Queue Q;
    int cnt = 0;
    int *num = malloc (G->V * sizeof v);
    for (v = 0; v < G->V; ++v) num[v] = -1;
    Q = QUEUEinit (G->V);
    num[s] = cnt++;
    QUEUEput(Q, s);

    while (!QUEUEempty (Q)) {
        v = QUEUEget (Q);
        for (w = 0; w < G->V; ++w)
            if (G->adj[v][w] && num[w] == -1) {
                num[w] = cnt++;
                QUEUEput (Q, w);
            }
    }

    for (printf ("v     "), v = 0; v < G->V; ++v)
        printf ("%2d%c", v, (v == G->V - 1) ? '\n' : ' ');
    
    for (printf ("num   "), v = 0; v < G->V; ++v)
        printf ("%2d%c", num[v], (v == G->V - 1) ? '\n' : ' ');

    free (num);
    QUEUEfree (Q);
}

/* Para cada vértice v do grafo G, esta função armazena em dist[v] a distância
   de s a v.  Também armazena em parent[] o vetor de pais da árvore de caminhos
   mínimos. Esta versão da função supõe que o grafo G é representado por listas
   de adjacência.  (Código inspirado no programa 18.9 de Sedgewick.) */
void GRAPHminPaths (Graph G, vertex s, int *pred, int *dist) {
   const int INFINITY = G->V;
   vertex v, w; Queue Q;
   for (v = 0; v < G->V; ++v)
      pred[v] = -1, dist[v] = INFINITY;
   Q = QUEUEinit (G->V);
   dist[s] = 0;
   pred[s] = s;
   QUEUEput (Q, s);

   while (!QUEUEempty (Q)) {
      v = QUEUEget (Q);
      for (w = 0; w < G->V; ++w)
         if (G->adj[v][w] && pred[w] == -1) {
            pred[w] = v;
            dist[w] = dist[v] + 1;
            QUEUEput (Q, w);
         }
   }
   QUEUEfree (Q);
}

void GRAPHtopoOrder (Graph G, int *vv) {
    vertex v;
    initDfs (G);

    for (v = 0; v < G->V; ++v)
        if (G->pre[v] == -1) {
            G->pred[v] = v;
            dfsR (G, v);
        }

    for (v = 0; v < G->V; ++v)
        vv[G->V - 1 - G->post[v]] = v;

    freeDfs (G);
}

void GRAPHpath (Graph G, vertex s, vertex t) {
    vertex v; Stack S = STACKinit (G->V);
    initDfs (G);
    G->pred[s] = s;
    dfsR (G, s);

    if (G->pre[t] == -1) {
        for (v = 0; v < G->V; ++v)
            if (G->pre[v] != -1)
                printf (" %2d", v);
        printf ("\n");
    }
    else {
        for (v = t; v != G->pred[v]; STACKput (S, v), v = G->pred[v]);
        for (printf ("%2d", s); !STACKempty (S); printf (" %2d", STACKget (S)));
        printf ("\n");
    }

    STACKfree (S);
    freeDfs (G);
}

static void bridgesR (Graph G, vertex v) {
    vertex w; int min;
    G->pre[v] = G->cnt1++;
    min = G->pre[v];
    for (w = 0; w < G->V; ++w) {
        if (!G->adj[v][w] || w == G->pred[v]) continue;
        if (G->pre[w] == -1) {
            G->pred[w] = v;
            bridgesR (G, w);
            if (G->low[w] < min) min = G->low[w];
        }
        else if (G->pre[w] < G->pre[v]) {
            if (G->pre[w] < min) min = G->pre[w];
        }
    }
    G->low[v] = min;
    if (G->pred[v] != v && G->low[v] > G->pre[G->pred[v]])
        printf ("%d-%d\n", G->pred[v], v);
}

void UGRAPHbridges (UGraph G) {
    vertex v;
    G->low = malloc (G->V * sizeof v);
    initDfs (G);
    
    for (v = 0; v < G->V; ++v)
        if (G->pre[v] == -1) {
            G->pred[v] = v;
            bridgesR (G, v);
        }
    
    freeDfs (G);
    free (G->low);
}

int GRAPHvertices (Graph G) {
    return G->V;
}

int GRAPHarcs (Graph G) {
    return G->A;
}

int GRAPHindeg (Graph G, vertex v) {
    int i, ans = 0;
    for (i = 0; i < G->V; ++i)
        if (G->adj[i][v]) ans++;
    return ans;
}

int GRAPHoutdeg (Graph G, vertex v) {
    int i, ans = 0;
    for (i = 0; i < G->V; ++i)
        if (G->adj[v][i]) ans++;
    return ans;
}

int GRAPHrootedForestHeight (Graph G, vertex *p) {
    int *h, i, max = 0;
    Stack S = STACKinit (G->V);
    h = malloc (G->V * sizeof (int));

    for (i = 0; i < G->V; ++i) h[i] = (i == p[i] ? 0:-1);
    for (i = 0; i < G->V; ++i) {
        while (h[i] == -1) {
            STACKput (S, i);
            i = p[i];
        }
        while (!STACKempty (S)) {
            i = STACKget (S);
            h[i] = h[p[i]] + 1;
        }
        max = (h[i] > max ? h[i] : max);
    }

    free (h); STACKfree (S);
    return max;
}

int GRAPHdfsForestHeight (Graph G) {
    vertex v; int ans;
    initDfs (G);

    for (v = 0; v < G->V; ++v)
        if (G->pre[v] == -1) {
            G->pred[v] = v;
            dfsR (G, v);
        }
    ans = GRAPHrootedForestHeight (G, G->pred);

    freeDfs (G);
    return ans;
}

/* A função dfsRcc() atribui o número id a todos os vértices que estão na mesma
   componente conexa que v. A função supõe que o grafo é representado por
   listas de adjacência. */
static void dfsRcc (UGraph G, int *cc, vertex v, int id) {
    vertex w;
    cc[v] = id;
    for (w = 0; w < G->V; ++w)
        if (G->adj[v][w] && cc[w] == -1)
            dfsRcc (G, cc, w, id);
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

int UGRAPHccBfs (UGraph G, int *cc) {
    vertex v, w, y; int id = -1;
    Queue Q;
    for (v = 0; v < G->V; ++v)
        cc[v] = -1;
    Q = QUEUEinit (G->V);

    for (v = 0; v < G->V; ++v)
        if (cc[v] == -1)
            for (QUEUEput (Q, v), cc[v] = ++id; !QUEUEempty (Q); ) {
                y = QUEUEget (Q);
                for (w = 0; w < G->V; ++w)
                    if (G->adj[v][w] && cc[w] == -1) {
                        cc[w] = id;
                        QUEUEput (Q, w);
                    }
            }

    QUEUEfree (Q);
    return id + 1;
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
static void strongR (Graph G, vertex v, int *sc, Stack S, int *k) {
    vertex w, u; int min;
    G->pre[v] = G->cnt1++;
    min = G->pre[v];
    STACKput (S, v);

    for (w = 0; w < G->V; ++w) {
        if (G->adj[v][w] && G->pre[w] == -1) {
            strongR (G, w, sc, S, k);
            if (G->low[w] < min) min = G->low[w]; /*A*/
        }
        else if (G->adj[v][w] && G->pre[w] < G->pre[v] && sc[w] == -1) {
            if (G->pre[w] < min) min = G->pre[w]; /*B*/
        }
    }
    G->low[v] = min;
    if (G->low[v] == G->pre[v]) {               /*C*/
        do {
            u = STACKget (S);
            sc[u] = *k;
        } while (u != v);
        *k = *k + 1;
    }
}

/* A função GRAPHscT() devolve o número de componentes fortes do grafo G e
   armazena no vetor sc[], indexado pelo vértices de G, os nomes das componentes
   fortes de G: para cada vértice u, sc[u] será o nome da componente forte que
   contém u. Os nomes das componentes fortes são 0, 1, 2, etc. (A função
   implementa o algoritmo de Tarjan.) */
int GRAPHscT (Graph G, int *sc) {
    vertex v; int *k = malloc (sizeof (int));
    Stack S = STACKinit (G->V);
    G->low = malloc (G->V * sizeof v);
    for (v = 0; v < G->V; ++v) sc[v] = -1;
    initDfs (G);
    
    *k = 0;
    for (v = 0; v < G->V; ++v)
        if (G->pre[v] == -1)
            strongR (G, v, sc, S, k);
    v = *k;

    free (k);
    STACKfree (S);
    free (G->low);
    freeDfs (G);
    return v;
}

/* Atribui o rótulo k a todo vértice w ao alcance de v que ainda não foi
   rotulado. Os rótulos são armazenados no vetor sc[]. */
static void dfsRsc( Graph G, vertex v, int *sc, int k) {
    vertex w;;
    sc[v] = k;
    for (w = 0; w < G->V; ++w)
        if (G->adj[v][w] && sc[w] == -1)
            dfsRsc( G, w, sc, k);
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
    initDfs (GR);
    
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

    freeDfs (GR);
    GRAPHfree (GR);
    free (vv);
    return k;
}

bool GRAPHisUndirected (Graph G) {
    int i, j;
    for (i = 0; i < G->V; ++i)
        for (j = i; j < G->V; ++j)
            if (G->adj[i][j] != G->adj[j][i]) return false;
    return true;
}

bool GRAPHisolated (Graph G, vertex v) {
    if (GRAPHindeg (G, v) > 0) return false;
    if (GRAPHoutdeg (G, v) > 0) return false;
    return true;
}

bool GRAPHadj (Graph G, vertex v, vertex w) {
    if (G->adj[v][w]) return true;
    if (G->adj[w][v]) return false;
    return false;
}

bool GRAPHisTopoNumbering (Graph G, int *topo) {
    vertex v, w;
    for (v = 0; v < G->V; ++v)
        for (w = 0; w < G->V; ++w)
            if (G->adj[v][w] && topo[v] >= topo[w])
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
    vertex v, w;
    bool *visit;
    Stack S = STACKinit (G->V);
    Stack N = STACKinit (G->V);
    visit = malloc (G->V * sizeof (bool));

    N = 0;
    for (v = 0; v < G->V; ++v) visit[v] = false;
    STACKput (S, s);
    STACKput (N, 0);

    while (!STACKempty (S)) {
        v = STACKget (S);
        w = STACKget (N);
        visit[v] = true;
        if (v == t) break;

        while (w < G->V) {
            if (G->adj[v][w] && !visit[w]) {
                STACKput (S, s);
                STACKput (N, w);
                STACKput (S, w);
                STACKput (N, 0);
                break;
            }
            w++;
        }
    }
    free (visit);
    STACKfree (S);
    STACKfree (N);
    return v == t;
}

/* A função cycleR() devolve TRUE se encontra um ciclo ao percorrer G a partir
   do vértice v e devolve FALSE em caso contrário. */
static bool cycleR (Graph G, vertex v) {
    vertex w;
    G->pre[v] = G->cnt1++;
    for (w = 0; w < G->V; ++w) {
        if (G->adj[v][w] && G->pre[w] == -1) {
            if (cycleR (G, w))
                return true;
        } else {
            if (G->post[w] == -1) /* A */
                return true;   /* v-w é de retorno */
            /* B */
        }
    }
    G->post[v] = G->cnt2++;
    return false;
}

bool GRAPHhasCycle (Graph G) {
    vertex v; bool ans = false;
    initDfs (G);

    for (v = 0; v < G->V; ++v)
        if (G->pre[v] == -1)
            if (cycleR (G, v))
                ans = true;
    
    freeDfs (G);
    return ans;
}

bool UGRAPHisConnected (UGraph G) {
    vertex v; bool ans = true;
    initDfs (G);
    
    dfsR (G, 0);
    for (v = 0; v < G->V; ++v)
        if (G->pre[v] == -1) ans = false;

    freeDfs (G);
    return ans;
}

/* REPRESENTAÇÃO POR MATRIZ DE ADJACÊNCIAS: A função GRAPHshow() imprime, para
   cada vértice v do grafo G, em uma linha, todos os vértices adjacentes a v. */
void GRAPHshow (Graph G) {
    vertex v, w;
    for (v = 0; v < G->V; ++v) {
        printf ("%2d:", v);
        for (w = 0; w < G->V; ++w)
            if (G->adj[v][w] == 1)
                printf (" %2d", w);
        printf ("\n");
    }
}

void UGRAPHshowKnight (Graph G, int i, int j) {
    vertex v, w;
    for (v = i * 8 + j, w = 0; w < G->V; ++w) {
        if (G->adj[v][w])
            printf ("X ");
        else if (w == v)
            printf ("K ");
        else
            printf (". ");
        if (w % 8 == 7)
            printf ("\n");
    }
}

void GRAPHsave (Graph G, FILE * out) {
    vertex v, w;

    fprintf (out, "%d\n", G->V);
    for (v = 0; v < G->V; ++v) {
        fprintf (out, "%d:", v);
        for (w = 0; w < G->V; ++w)
            if (G->adj[v][w])
                fprintf (out, " %d", w);
        fprintf (out, "\n");
    }
}

void GRAPHfree (Graph G) {
    vertex i;
    for (i = 0; i < G->V; i++)
        free (G->adj[i]);
    free (G->adj);
    free (G);
}
