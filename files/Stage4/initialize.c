extern FILE *intermediate;

void initialize() {
    intermediate = fopen("machinecode.xsm", "w");
    fprintf(intermediate, "0\n2056\n0\n0\n0\n0\n0\n0\n");
    fprintf(intermediate, "MOV SP, %d\n", totalCount);
    fprintf(intermediate, "CALL MAIN\n");
    fprintf(intermediate, "MOV R0, 10\nPUSH R0\nINT 10\n");
}
