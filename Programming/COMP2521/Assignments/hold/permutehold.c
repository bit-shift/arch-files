
    /*
    UrlNode ite;
    for (int a = 0; a < argc-1; a++) {
        ite = rankings[a]->head;
        while (ite != NULL) {
            printf("%s - (%d)\n", ite->url, ite->id);
            ite = ite->next;
        }
        printf("--------------------\n");
    }
    UrlNode curr1 = unionR->head;
    while (curr1 != NULL) {
        printf("%s\n", curr1->url);
        curr1 = curr1->next;
    }
    printf("--------------------\n");
    int maxUrls = rankings[0]->nurls;
    int indexOfMaxUrls = 0;
    for (int j = 0; j < argc-1; j++) {
        if (rankings[j]->nurls > maxUrls) {
            maxUrls = rankings[j]->nurls;
            indexOfMaxUrls = j;
        }
    }
    int *perms = malloc(maxUrls*sizeof(int));
    for (int k = 0; k < maxUrls; k++) perms[k] = k+1;
    int *gloperm = malloc(maxUrls*sizeof(int));
    double minWCP = DBL_MAX;
    permute(perms, 0, maxUrls-1, unionR, rankings, argc, &minWCP, gloperm);
    printf("%lf\n", minWCP);
    UrlNode curr;
    int index;
    for (int z = 0; z < maxUrls; z++) {
        curr = unionR->head;
        index = 1;
        while (curr != NULL) {
            if (index == gloperm[z]) printf("%s\n", curr->url);
            index++;
            curr = curr->next;
        }
    }
	free(perms);
	free(gloperm);
	freeUrlList(unionR);
	for (int x = 0; x < argc-1; x++) {
		freeUrlList(rankings[x]);
	}
    */

/*
void computeTotalWCP(UrlList unionRanking, UrlList *lists, int argc, int *perm, int n, double *minWCP, int *gloperm) {
    double WCP = 0;
    for (int i = 0; i < argc-1; i++) {
        WCP += computeListWcp(unionRanking, lists[i], perm, n);
    }
    if (WCP < *minWCP) {
        *minWCP = WCP;
        for (int j = 0; j < n; j++) gloperm[j] = perm[j];
    }
}

double computeListWcp(UrlList unionRanking, UrlList list, int *perm, int n) {
    double wcp = 0;
    double listDiv, permDiv, diff;
    int id;
    UrlNode curr = unionRanking->head;
    for (int i = 0; i < list->nurls; i++) {
        if (isInUrlList(list, curr->url)) {
            id = getID(list, curr->url);
            listDiv = (double) (id)/(list->nurls);
            permDiv = (double) (perm[i])/(n);
            diff = fabs(listDiv - permDiv);
            wcp += diff;
        }
        curr = curr->next;
    }
    return wcp;
}*/
