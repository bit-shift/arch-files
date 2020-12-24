
    int inserts = 0;
    for (int i = 0; i < g->nV; i++) {
        if (dist[i] <= d) inserts++;
    }
    int *within = malloc(sizeof(int)*inserts);
    int index = 0;
    for (int i = 0; i < g-nV; i++) {
        if (dist[i] <= d) within[index++] = i
