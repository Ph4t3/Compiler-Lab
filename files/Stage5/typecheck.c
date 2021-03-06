int checkAvailability(char *name, int global) {
    if(global) {
        Gtemp = GLookup(name);
        if(Gtemp != NULL) {
            yyerror("Re-initialization of variable/function '%s'\n", name);
            exit(1);
        }
    } else {
        Ltemp = LLookup(name);
        Ptemp = PLookup(name);
        if(Ptemp != NULL || Ltemp != NULL) {
            yyerror("Re-initialization of variable '%s'\n", name);
            exit(1);
        }
    }

    return 1;
}

void assignType(struct ASTNode* node, int code) {
    // Code 0 - Local or Global Variable
    // Code 1 - Function
    // Code 2 - Array
    
    Ltemp = LLookup(node->name);
    if(Ltemp != NULL && code == 0) {
        node->Lentry = Ltemp;
        node->type = Ltemp->type;
    } else {
        Gtemp = GLookup(node->name);
        if(Gtemp != NULL) {
            node->Gentry = Gtemp;
            node->type = Gtemp->type;

            if(code == 1 && Gtemp->size != -1) {
                yyerror("conflict in ID NodeType : Expected Function \n");
                printf("%s\n", node->name);
                exit(1);
            }
        } else {
            if(code == 1)
                yyerror("Function '%s' not declared!", node->name);
            else
                yyerror("Variable '%s' not declared!", node->name);
            exit(1);
        }
    }

    return;
}

void typecheck(int t1, int t2, char c) {
    switch(c) {
        case 'w': if(t1 != t2) {
                      yyerror("Expected Boolean in WHILE check\n", NULL);
                      exit(1);
                  }
                  break;
        case 'e': if(t1 != t2) {
                      yyerror("Expected Boolean in IF ELSE check\n", NULL);
                      exit(1);
                  }
                  break;
        case 'i': if(t1 != t2) {
                      yyerror("Expected Boolean in IF check\n", NULL);
                      exit(1);
                  }
                  break;
        case 'a': if(t1 != TYPE_INT || t2 != TYPE_INT) {
                      yyerror("Invalid type for arithmetic operation\n", NULL);
                      exit(1);
                  }
                  break;
        case 'b': if(t1 != TYPE_INT || t2 != TYPE_INT) {
                      yyerror("Invalid type for comparing (<, >, <=..) operation\n", NULL);
                      exit(1);
                  }
                  break;
        case '=': if(t1 != t2) {
                      yyerror("Invalid type for assignment operation\n", NULL);
                      exit(1);
                  }
                  break;
    }
}
