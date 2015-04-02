%{
#include <stdio.h>
#include "list.h"
#include <unistd.h>
#define true 1
#define false 0
typedef struct yy_buffer_state * YY_BUFFER_STATE;
Node* global;
Node* list;
Node* local;

Node* funs;

Node* args;

int regs[26];
%}

%union {
  int   nval;
  float fval;
  char *cval;
  void *nodeval;
}

%start Input

%token <nval> INT 
%token <fval> FLOAT
%token <cval> VAR
%token <cval> FUN
%type  <cval> Body
%type  <fval> Expr
%type  <fval> Call
%type  <nodeval> ListVar
%type  <nodeval> Params
%type  <nodeval> Arguments

%left '(' ')'
%left '+' '-'
%left '*' '/' '%'

%%            
Input: 
       | Input Program

Program:  '\n'               { printf(">>"); }
        | Prototype '\n'     { printf(">>"); }
        | Expr      '\n'     { printf("%.10g\n>>", $1);}
        | Call               
        | Assigment '\n'     { printf(">>"); }
        | error     '\n'     { printf(">>"); }

ListVar:                   { $$ =  NULL; } 
        | VAR              { Node *marinheiro; 
                             marinheiro        = malloc(sizeof(Node));
                             marinheiro->value = 4.20;
                             marinheiro->name  = $1;
                             $$ =  marinheiro}
        | ListVar ',' VAR  { 
                             Node* marinheiro;
                             marinheiro        = malloc(sizeof(Node));
                             marinheiro->value = 4.20;
                             marinheiro->name  = $3;
                             insert($1,marinheiro); 
                             $$ = $1; }

Arguments: '(' ListVar ')' { $$ = $2; }

Prototype: FUN VAR Arguments ':' Body { 
         Node *func = malloc(sizeof(Node));
         func->name = $2;
         func->func = malloc(sizeof(Fun));
         func->func->body = $5;
         func->func->arguments = $3;
         insert(funs, func);
        }

Params:                    { $$ =  NULL; } 
        | Expr             { Node *marinheiro; 
                             marinheiro        = malloc(sizeof(Node));
                             marinheiro->value = $1;
                             $$ =  marinheiro }
        | Params  ',' Expr { 
                             Node* marinheiro;
                             marinheiro        = malloc(sizeof(Node));
                             marinheiro->value = $3;
                             insert($1,marinheiro); 
                             $$ = $1; }

Call: VAR '(' Params ')' {
        Node *marinheiros = $3;
        Node *f = get(funs, $1);
        if(f == NULL) {
          printf("Função %s não definida\n", $1);
        } else {
          Node *arguments = f->func->arguments;
          Node *nextM     = marinheiros; 
          Node *nextA     = arguments;
          while(nextM != NULL) {
            nextA->value = nextM->value;
            nextM = nextM->next;
            nextA = nextA->next;
          }
          if(nextA != NULL) {
            printf("Faltou parametros para a função!\n");
          } else {
          char *s = malloc(strlen(f->func->body)+2);
          sprintf(s, "%s\n\0\0", f->func->body);
          global = list;
          list = arguments;
          YY_BUFFER_STATE tmp    = getCurrentBuffer();
          YY_BUFFER_STATE buffer = yy_scan_buffer(s, strlen(s)+3);
          yyparse();
          list = global;
          yy_delete_buffer(buffer);
          yy_switch_to_buffer(tmp);
          yylex();
        }
     }
  }

Body:   Body '+' Body { char *s = malloc(sizeof(char)*strlen($1)
                                         +sizeof(char)*strlen($3)+4);
                         sprintf(s, "%s + %s", $1, $3);
                         free($1);
                         free($3); 
                         $$ = s; }
      |  Body '-' Body { char *s = malloc(sizeof(char)*strlen($1)
                                         +sizeof(char)*strlen($3)+4);
                         sprintf(s, "%s - %s", $1, $3);
                         free($1);
                         free($3); 
                         $$ = s; }
      |  Body '*' Body { char *s = malloc(sizeof(char)*strlen($1)
                                         +sizeof(char)*strlen($3)+4);
                         sprintf(s, "%s * %s", $1, $3);
                         free($1);
                         free($3); 
                         $$ = s; }
      |  Body '/' Body { char *s = malloc(sizeof(char)*strlen($1)
                                         +sizeof(char)*strlen($3)+4);
                         sprintf(s, "%s / %s", $1, $3);
                         free($1);
                         free($3); 
                         $$ = s; }
      |  Body '%' Body { char *s = malloc(sizeof(char)*strlen($1)
                                         +sizeof(char)*strlen($3)+4);
                         sprintf(s, "%s % %s", $1, $3);
                         free($1);
                         free($3); 
                         $$ = s; }
      |  '(' Body ')'  { char *s = malloc(sizeof(char)*strlen($2) + 8);
                         sprintf(s, "(%s)", $2);
                         free($2); 
                         $$ = s }
      |  INT           { char *s = malloc(sizeof(char)*40); 
                         sprintf(s, "%d", $1); 
                         $$ = s; }
      |  '-' INT       { char* s = malloc(sizeof(char)*40); 
                         sprintf(s, "-%d", $1); 
                         $$ = s; }
      |  VAR           { $$ = $1 } 
         
Expr:    Expr '+' Expr { $$ = $1 + $3; }
      |  Expr '-' Expr { $$ = $1 - $3; }
      |  Expr '*' Expr { $$ = $1 * $3; }
      |  Expr '/' Expr { if((int)$3 == 0) printf("Divisão por zero!\n");
                         $$ = $1 / $3; }
      |  Expr '%' Expr { $$ = (int) $1 % (int) $3; }
      |  '(' Expr ')'  { $$ = $2 };
      |  INT           { $$ = $1 };
      |  FLOAT         { $$ = $1 };
      |  '-' FLOAT     { $$ = -$2};
      |  '-' INT       { $$ = -$2};
      |  VAR           { Node* no = get(list, $1);
                         if(no == NULL) {
                          no = get(global, $1);
                          if(no == NULL) {
                            printf("Variável %s não declarada!\n", $1);
                          } else {
                            $$ = no->value;
                          }
                         } else {
                           $$ = no->value;
                         } };

Assigment: VAR '=' Expr { Node* no = get(list, $1);
                          if(no == NULL) {
                            no = malloc(sizeof(Node));
                            no->value = $3;
                            no->name  = $1;
                            insert(list, no);
                          } else {
                            no->value = $3;
                          } };

%%

int main() {
 printf(">>");
 init(&list);
 global = list;
 init(&funs);

 while(1) yyparse();
 return 0;
}

yyerror(char *s) {
  fprintf(stderr, "%s\n",s);
}

int yywrap() {
  return(1);
}
