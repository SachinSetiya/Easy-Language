/* 
 * File:   HelpAst.h
 * Author: sachin
 *
 * Created on 6 April, 2015, 1:16 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include<stdarg.h>
#include<math.h>
#include<string.h>
#include "y.tab.h"

int _count_arg; //counting the argument of function 
//struct symlist {
  //  struct c_member *sym; // argument 
   // struct symlist * next;
//}symlist ;
struct c_member{
    char name[31]; //name
    int access_modifier ;   //public or private
    double value;    // value 
    struct c_member *next;  // point to next class member 
} c_member;

struct c_memberref {
    int nodetype; //ref '=' means equating the c_member with exp l
    struct c_member *s;
    struct ast * l;
}c_memberref; 

 struct ast {
    int nodetype;
    struct ast * l;
    struct ast * r;
};


struct numval{
    int nodetype; //type K
    double number;
        
};
struct varvalue{
    int nodetype; //type 'V' means giving value of variable 
    struct c_member *s;
}varvalue;
struct num{
    int nodetype; //type 'K
    double value;
};

// assigning the value eval(ast v) to c_member s
 struct  symasgn{
    int nodetype;  //type '='
    struct c_member *s;
    struct ast *v;
};
//implementation of hash table 
// generation hash it depend  on first character of c_member 
// i know the worst hash function
int hash(char   s[]){
    if(isupper(s[0])){
        return s[0] - 'A';
    }
    else
        return s[0] - 'a';
}
struct hash_v {
    struct c_member *sym;
};
struct hash_v ht_v[26];
// whta is does is that is 
void add_c_member(struct c_member *s){
//struct     c_member *   temp  =   (struct c_member *)malloc(sizeof(struct c_member));

 //  temp->curr =     ht[hash(s->name)].curr;
//temp->next=ht_v[hash()]
//   temp->next =     ht[hash(s->name)].next;
//// there is an error i should make allocation of memory than 
////copy it 
//     ht[hash(s->name)].curr = s;
//     ht[hash(s->name)].next = temp;
   // temp = lookup_s;
//temp->curr = ht[1].curr;
s->next=ht_v[hash(s->name)].sym;
ht_v[hash(s->name)].sym=s;
}
//lookup for normal global variables 
struct c_member * lookup(char  s[]){
struct     c_member * temp =  ht_v[hash(s)].sym;
   
    while(temp){
        if(strcmp(temp->name,s)==0){
      //     printf("found value = %f ",temp->curr->value);
            return temp;
        }
        temp = temp->next;
    }
   struct c_member * sym = ( struct c_member * )malloc(sizeof(struct c_member));
        strcpy(sym->name , s);

        sym->value = 0;

        add_c_member(sym);
    //    printf("Data stored %s",s);
    return sym;
    
}
// now implementatin the newast function 
struct ast * newast(int nodetype , struct ast * l,struct ast * r){
//printf("reached over ast ");    
struct ast * tmp = (struct ast *)malloc(sizeof(struct ast ));
    tmp->l = l;
    tmp->nodetype =  nodetype;
    tmp->r = r;
//printf("all good");
    return tmp;
}
//take value from variable

struct ast * var(struct c_member * a ){
    struct varvalue * tmp = (struct varvalue *)malloc(sizeof(struct varvalue ));
    tmp->nodetype = 'V';
    tmp->s = a;
    return (struct ast * )tmp;
}
// new assignment assign value to variable 
struct ast * newasgn(struct c_member * a,struct ast * ex){
    struct c_memberref * tmp = (struct c_memberref *)malloc(sizeof(struct c_memberref));
    tmp->nodetype = '=';
    tmp->s =a;
    tmp->l = ex;
    return (struct ast * )tmp;
}
struct ast * newnum(double t){
  //  printf("reached over newnum ");
    struct num *  tmp =(struct num *)malloc(sizeof(struct num));
    tmp->nodetype = 'K';
    tmp->value=t;
//printf("all good newnum");
     return (struct ast * )tmp;
}

///////////////////////////////let us implement if else i know it is some what harder but let us do it !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!1
struct flow{
    int nodetype ;  //type 'I' or an while loop 
    struct ast * cond;
    struct ast * tl;
    struct ast * el;
} flow;
struct ast *  newflow(int nodetype ,struct ast  *c,struct ast * t,struct ast *e){
    struct flow * tmp =(struct flow * )malloc(sizeof(struct flow));
    tmp->nodetype=nodetype;
    tmp->cond = c;
    tmp->tl=t;
    tmp->el=e;
    return(struct ast *)tmp;
}

double eval(struct ast * a){
   
    double ans;
   // double c;
    // double d,e,f;
   // struct ast *dd;
    struct c_member * x ;
    switch(a->nodetype){
        case 'V' : 
            ans =((struct varvalue *)a)->s->value;break;
        case '=': //d=((struct c_memberref * )a)->s->value;
       
       
   //   printf("%f \n",  eval(((struct c_memberref * )a)->l));
     //  printf("%f \n", ((struct c_memberref * )a)->s->value); 
     //  sleep(1);
     //   printf("value = %f",eval(((struct c_memberref * )a)->l));
      // ((struct c_memberref * )a)->s->value=eval(((struct c_memberref * )a)->l);
      // printf("value of eval(((struct c_memberref * )a)->l) = %f  \n",eval(((struct c_memberref * )a)->l));
      // printf("noww the value of left variable = ((struct c_memberref * )a)->s->value = %f \n ",((struct c_memberref * )a)->s->value);
            //   ((struct c_memberref * )a)->s->value=eval(((struct c_memberref * )a)->l);
       ///        printf("now one more turn \n");
         //       printf("noww the value of left variable = ((struct c_memberref * )a)->s->value = %f  \n ",((struct c_memberref * )a)->s->value);
         //       printf("value of eval(((struct c_memberref * )a)->l) = %f  \n",eval(((struct c_memberref * )a)->l));
      
         x     =((struct c_memberref * )a)->s;
           
            
       ans =
               ((struct c_memberref * )a)->s->value=eval(((struct c_memberref * )a)->l);
        break;
        case 'K':ans=((struct num *)a)->value;break;
        case '+':ans=eval(a->l)+eval(a->r);break;
        case '-':ans=eval(a->l)-eval(a->r);break;
        case '*':ans=eval(a->l)*eval(a->r);break;
        case '/':ans=eval(a->l)/eval(a->r);break;
        case 1 : ans = eval(a->l)<eval(a->r)?  1:0;break;
        case 2 : ans = eval(a->l)>eval(a->r)?  1:0;break;
        case 3 : ans = eval(a->l)!=eval(a->r)? 1:0;break;
        case 4 : ans = eval(a->l)==eval(a->r)? 1:0;break;
        case 5 : ans = eval(a->l)<=eval(a->r)? 1:0;break;
        case 6 : ans = eval(a->l)>=eval(a->r)? 1:0;break;
        //now the if else qqqq
        case 'I' :ans = eval(((struct flow * )a)->cond)!=0?eval(((struct flow * )a)->tl):eval(((struct flow * )a)->el);break;
        case 'L':eval(a->l);ans=eval(a->r);break;
        case 'W' : 
            while(eval(((struct flow * )a)->cond)){
           //  c = eval(((struct flow * )a)->cond);
            ans = eval(((struct flow * )a)->tl);
        }
         break;
            //arguments of function 
       // case'A':  break;
        case 'F'://ans = eval(((struct ufc *)a)->fun->body);
       //     dd= ((struct ufc * )a)->fun->arg;
          break;
        default:printf("bad happened");
        
    }
    return ans;
}

//now the hard stuff i am thinking of implementing function which may be much more harder than what we think 
//whatever
//// let us do oops i know diffucult but i wanna try it
//

struct class {
    char name[31];
    struct c_member *var;
    struct c_function *fun;
}class ;
// definition for class  member variable 



struct c_function{
    char name[31];
    int access_modifier;
    struct c_member * arg;
    struct ast * body;
    struct c_member *data;
    struct c_function * next;
}c_function;


//now the hash table for classes 
struct hash_c{
   struct  class *  curr;
    struct hash_c  * next;
} ;
struct hash_c ht_c[26];
int assignment_ht(){
    _count_arg=0;
    for(int i =0;i<25;i++){
        ht_v[i].sym = NULL;
      //  ht_v[i]. = NULL;
        ht_c[i].curr=NULL;
        ht_c[i].next=NULL;
       }
    return 1;
}
void add_class(char nme[]){
    struct class * s = (struct class *)malloc(sizeof(struct class));
    s->fun=NULL;
    strcpy(s->name,nme);
    s->var=NULL;
struct     hash_c *   temp  =   (struct hash_c *)malloc(sizeof(struct hash_c));

   temp->curr =     ht_c[hash(s->name)].curr;
   temp->next =     ht_c[hash(s->name)].next;
// there is an error i should make allocation of memory than 
//copy it 
     ht_c[hash(s->name)].curr = s;
     ht_c[hash(s->name)].next = temp;
   // temp = lookup_s;
}
//lookup for classes
struct class * lookup_c(char  s[]){
struct     hash_c * temp = & ht_c[hash(s)];
   
    while(temp->curr){
        if(strcmp(temp->curr->name,s)==0){
      //     printf("found value = %f ",temp->curr->value);
            return temp->curr;
        }
        temp = temp->next;
    }
return NULL;

}
// now the difficult task is to make class
//class if two d linked list one list for arguments 
// second fo fun asd(),g,g,g,fg) = dfdfdf endfun
void add_c_var(struct class * _c,char  c_name[],int acces_mod,int value){
    struct c_member * temp = (struct c_member * )malloc(sizeof(struct c_member));
    strcpy(temp->name,c_name);
    temp->access_modifier=acces_mod;
    temp->value=value;
    temp->next=_c->var;
    _c->var=temp;
    
}
// actually first we need make function with null and then add arguments 
void add_c_func(struct class * _c, char name[]){
    struct c_function * temp = (struct c_function *)malloc(sizeof(struct c_function));
    temp->access_modifier=1;
    temp->arg=NULL;
    temp->body=NULL;
    temp->data=NULL;
    strcpy(temp->name,name);
    
    temp->next=_c->fun;
    _c->fun=temp;
    
}
// then adding all args and list so 
void make_c_f(struct c_function * _f,struct c_member *arg1,struct ast *  body ){
   _f->arg = arg1;
   _f->body = body;
}
void _make_object(struct class *_c,char obj[]){
    add_class(obj);
   struct class * s = lookup_c(obj);
  // strcpy(s->name,obj);
 //
   s->fun=_c->fun;
   struct c_member *t1;
   // now copy variables from  class _c to s 
   t1=_c->var;
   struct c_member * t2;
   struct c_member * t;
   struct c_member * pt;
   int a=0;
   while(t1){
       
        t = (struct c_member * )malloc(sizeof(struct c_member));
        if(a){
            pt->next= t;
       }
        else{
            t2=t;
        }
       t->access_modifier=t1->access_modifier;
       strcpy(t->name,t1->name);
       t->value=t1->value;
       t->next=NULL;
       
      t1= t1->next;
      pt=t;
      
      t=t->next;
      a++;
     //  s->var = temp;
      s->var=t2;
   }
    
}
// lookup the function of class _c
struct c_function *  lookup_c_f(struct class * _c ,char name[]){
    if(_c){
    struct c_function *temp;
    temp= _c->fun;
    while(temp){
        if(strcmp(temp->name,name)==0){
            return temp;
        }
        temp=temp->next;
    }
     return NULL;
    }
    return NULL;
}
// lookup the variable of class _c
struct c_member *  lookup_c_v(struct class * _c ,char name[]){
    struct c_member *temp;
    temp= _c->var;
    while(temp){
        if(strcmp(temp->name,name)==0){
            return temp;
        }
        temp=temp->next;
    }
    return NULL;
}
// now is some what harder stuff actually i have to implement function symlist and ast 
//basically ast can be built simply but we have to make linked list 
//of arguments and then attach then to function
struct c_member *_c_f_start_arg=NULL,*_c_f_end_arg=NULL;
struct c_member * addsymlist(char name[]){
    struct c_member *tem = (struct c_member *)malloc(sizeof(struct c_member) );
    struct c_member *list = (struct c_member *)malloc(sizeof(struct c_member));
    strcpy(tem->name,name);
    tem->value=0;
    
    if(_c_f_start_arg==NULL){
        list=tem;
        list->next=NULL;
        _c_f_end_arg=_c_f_start_arg=list;
        return  _c_f_start_arg ;
    }
    list=tem;
    list->next=NULL;
    _c_f_end_arg->next = list;
    _c_f_end_arg=_c_f_end_arg->next;
    return _c_f_start_arg;
    
}
//lookup for data of function f
struct c_member *  lookup_c_f_d(struct class * _c ,struct c_function * _f ,char name[]){
    struct c_member *temp;
    temp= _c->fun->data;
    while(temp){
        if(strcmp(temp->name,name)==0){
            return temp;
        }
        temp=temp->next;
    }
    return NULL;
}
//lookup for symbol list  of function f 
struct c_member *  lookup_c_f_s(struct class * _c ,struct c_function * _f ,char name[]){
    struct c_member *temp;
    temp= _c->fun->arg;
    while(temp){
        if(strcmp(temp->name,name)==0){
            return temp;
        }
        temp=temp->next;
    }
    return NULL;
}
//now the special look up function for function arguments 
//number 1 arguments of
//
struct c_member * lookup_u(struct class * _c,struct c_function *_f,char _n[]){
    if(_c){
    // suppose if this is for internal function  datatype 
         if(lookup_c_v(_c,_n)){
           return lookup_c_v(_c,_n);
       }
        if(_f){
             if(lookup_c_f_d( _c,  _f, _n)){
                 return lookup_c_f_d( _c,  _f, _n);
             }
             if(lookup_c_f_s(_c,_f,_n)){
                 return lookup_c_f_s( _c,  _f, _n);
             }
            
             
        }
          return  lookup(_n);
       
      
        return NULL;
    }
    else{
       return  lookup(_n);
//        loo
       
     //  loo
    }
    
}
//now the special look up function for function arguments 
//number 1 arguments of
// RESTRICTED VERSION.
struct c_member * lookup_r(struct class * _c,struct c_function *_f,char _n[]){
    if(_c){
    // suppose if this is for internal function  datatype 
         if(lookup_c_v(_c,_n)){
           return lookup_c_v(_c,_n);
       }
        if(_f){
             if(lookup_c_f_d( _c,  _f, _n)){
                 return lookup_c_f_d( _c,  _f, _n);
             }
             if(lookup_c_f_s(_c,_f,_n)){
                 return lookup_c_f_s( _c,  _f, _n);
             }
            
             
        }
        //  return  lookup(_n);
       
      
        return NULL;
    }
    else{
       return  lookup(_n);
//        loo
       
     //  loo
    }
    
}
void setvalue(struct c_function * f, double value){
    _count_arg++;
    int temp =_count_arg;
    struct c_member *m;
    m= f->arg;
    while(temp-1){
        
        m=m->next;
        temp--;
    }
    m->value=value;
    
}
// now the inheritance its like object making and thats all
void inherits(struct class *_c,char name[]){
    _make_object( _c, name);
}
