
    /*
    printf("-----------------------------------\n");
    printf("Example 1\n");
    printf("-----------------------------------\n");

    double **arr = malloc(sizeof(double)*3);
    for (int j = 0; j < 3; j++) arr[j] = malloc(sizeof(double)*3); 
    arr[0][0] = 1.0;
    arr[0][1] = 4.0;
    arr[0][2] = 5.0;
    arr[1][0] = 5.0;
    arr[1][1] = 7.0;
    arr[1][2] = 6.0;
    arr[2][0] = 5.0;
    arr[2][1] = 8.0;
    arr[2][2] = 8.0;
    double **copy1 = copyMatrix(arr, 3);
    
    reduceByMin(arr, 3);
    int mat[3];
    int c = maxMatching(arr, 3, mat);
    printf("Max matching = %d\n", c);

    int *urlst = malloc(sizeof(int)*3);
    int *positionst = malloc(sizeof(int)*3);
    labelling(urlst, positionst, arr, 3);

    modifyByMin(arr, 3, urlst, positionst);
    int matc[3];
    int cw = maxMatching(arr, 3, matc);
    printf("Max matching = %d\n", cw);
    printArray(matc, 3, "matches");
    printf("%lf\n", computeWCP(copy1, matc, 3));

    printf("-----------------------------------\n");
    printf("Example 2\n");
    printf("-----------------------------------\n");

    double **arr2 = malloc(sizeof(double)*4);
    for (int j = 0; j < 4; j++) arr2[j] = malloc(sizeof(double)*4); 
    arr2[0][0] = 6.0;
    arr2[0][1] = 12.0;
    arr2[0][2] = 15.0;
    arr2[0][3] = 15.0;
    arr2[1][0] = 4.0;
    arr2[1][1] = 8.0;
    arr2[1][2] = 9.0;
    arr2[1][3] = 11.0;
    arr2[2][0] = 10.0;
    arr2[2][1] = 5.0;
    arr2[2][2] = 7.0;
    arr2[2][3] = 8.0;
    arr2[3][0] = 12.0;
    arr2[3][1] = 10.0;
    arr2[3][2] = 6.0;
    arr2[3][3] = 9.0;
    double **copy2 = copyMatrix(arr2, 4);
    
    reduceByMin(arr2, 4);
    int mat2[4];
    int c2 = maxMatching(arr2, 4, mat2);
    printf("Max matching = %d\n", c2);

    int *urlst2 = malloc(sizeof(int)*4);
    int *positionst2 = malloc(sizeof(int)*4);
    labelling(urlst2, positionst2, arr2, 4);

    modifyByMin(arr2, 4, urlst2, positionst2);
    int matc2[4];
    int cw2 = maxMatching(arr2, 4, matc2);
    printf("Max matching = %d\n", cw2);
    printArray(matc2, 4, "matches");
    printf("%lf\n", computeWCP(copy2, matc2, 4));
    */
