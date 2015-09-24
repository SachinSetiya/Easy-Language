/* 
 * File:   main.c
 * Author: sachin
 *
 * Created on 26 April, 2015, 5:01 AM
 */

#include <stdio.h>
#include <stdlib.h>
#include"lex.yy.c"
#include"y.tab.c"

/*
 * 
 * 
 */
int main(int argc, char** argv) {
    assignment_ht();
   yyparse();
    //checking class making is working or not
//    add_class("sachin");
//    add_class("sdsd");
//    struct class * as = lookup_c("sachin");
//   //  printf("%s",as->name);
//    add_c_var(as,"a1",1,2);
//    add_c_var(as,"s2",1,3);
//    add_c_var(as,"s3",1,4);
//  //  add_c_func(as,NULL);
//    // actually i cant believe that it worked its awesome
//   // add_c_func(as,"ss",1,NULL,NULL);
//    _make_object(as,"object");
//    printf("%f",(lookup_u(lookup_c("object"),NULL,"s3"))->value);
    
    
//    void *ptr;
//    int a=34;
//    ptr =&a;
   // printf("%d",*ptr);
    
   // struct class a;
    return (EXIT_SUCCESS);
}

