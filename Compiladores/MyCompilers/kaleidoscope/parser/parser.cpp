#include <parser.hpp>

int Parser::getNextToken() {
  return CurTok = scanner.gettok();
}

ExprAST *Parser::Error(const char *Str) {
  fprintf(stdout, "Error: %s\n", Str);
  return 0;
}

PrototypeAST *Parser::ErrorP(const char *Str) {
  Error(Str); 
  return 0;
}

FunctionAST *Parser::ErrorF(const char *Str) {
  Error(Str); 
  return 0;
}

ExprAST *Parser::ParseNumberExpr() {
  ExprAST *Result = new NumberExprAST(scanner.NumVal);
  getNextToken();
  return Result;
}

ExprAST *Parser::ParseParenExpr() {
  getNextToken();  // eat (.
  ExprAST *V = ParseExpression();
  if (!V) return 0;

  if (CurTok != ')')
    return Error("expected ')'");
  getNextToken();  // eat ).
  return V;
}

ExprAST *Parser::ParseIdentifierExpr() {
  std::string IdName = scanner.IdentifierStr;

  getNextToken();  // eat identifier.

  if (CurTok != '(') // Simple variable ref.
    return new VariableExprAST(IdName);

  getNextToken();  // eat (
  std::vector<ExprAST*> Args;
  if (CurTok != ')') {
    while (1) {
      ExprAST *Arg = ParseExpression();
      if (!Arg) return 0;
      Args.push_back(Arg);

      if (CurTok == ')') break;

      if (CurTok != ',')
        return Error("Expected ')' or ',' in argument list");
      getNextToken();
    }
  }

  getNextToken();

  return new CallExprAST(IdName, Args);
}

ExprAST *Parser::ParsePrimary() {
  switch (CurTok) {
    default: return Error("unknown token when expecting an expression");
    case tok_identifier: return ParseIdentifierExpr();
    case tok_number:     return ParseNumberExpr();
    case '(':            return ParseParenExpr();
  }
}

int Parser::GetTokPrecedence() {
  if (!isascii(CurTok))
    return -1;

  int TokPrec = BinopPrecedence[CurTok];
  if (TokPrec <= 0) return -1;
  return TokPrec;
}

ExprAST *Parser::ParseBinOpRHS(int ExprPrec, ExprAST *LHS) {
  while (1) {
    int TokPrec = GetTokPrecedence();

    if (TokPrec < ExprPrec)
      return LHS;

    int BinOp = CurTok;
    getNextToken();  // eat binop

    ExprAST *RHS = ParsePrimary();
    if (!RHS) return 0;

    int NextPrec = GetTokPrecedence();
    if (TokPrec < NextPrec) {
      RHS = ParseBinOpRHS(TokPrec+1, RHS);
      if (RHS == 0) return 0;
    }

    LHS = new BinaryExprAST(BinOp, LHS, RHS);
  }
}

ExprAST *Parser::ParseExpression() {
  ExprAST *LHS = ParsePrimary();
  if (!LHS) return 0;

  return ParseBinOpRHS(0, LHS);
}

PrototypeAST *Parser::ParsePrototype() {
  if (CurTok != tok_identifier)
    return ErrorP("Expected function name in prototype");

  std::string FnName = scanner.IdentifierStr;
  getNextToken();

  if (CurTok != '(')
    return ErrorP("Expected '(' in prototype");

  std::vector<std::string> ArgNames;
  while (getNextToken() == tok_identifier)
    ArgNames.push_back(scanner.IdentifierStr);
  if (CurTok != ')')
    return ErrorP("Expected ')' in prototype");

  getNextToken();  // eat ')'.

  return new PrototypeAST(FnName, ArgNames);
}

FunctionAST *Parser::ParseDefinition() {
  getNextToken();  // eat def.
  PrototypeAST *Proto = ParsePrototype();
  if (Proto == 0) return 0;

  if (ExprAST *E = ParseExpression())
    return new FunctionAST(Proto, E);
  return 0;
}

FunctionAST *Parser::ParseTopLevelExpr() {
  if (ExprAST *E = ParseExpression()) {
    PrototypeAST *Proto = new PrototypeAST("", std::vector<std::string>());
    return new FunctionAST(Proto, E);
  }
  return 0;
}

PrototypeAST *Parser::ParseExtern() {
  getNextToken();  // eat extern.
  return ParsePrototype();
}

void Parser::HandleDefinition() {
  if (FunctionAST *F = ParseDefinition()) {
    if (llvm::Function *LF = F->Codegen()) {
      fprintf(stdout, "Read function definition:");
      LF->dump();
    }
  } else {
    getNextToken();
  }
}

void Parser::HandleExtern() {
  if (PrototypeAST *P = ParseExtern()) {
    if (llvm::Function *F = P->Codegen()) {
      fprintf(stdout, "Read extern: ");
      F->dump();
    }
  } else {
    // Skip token for error recovery.
    getNextToken();
  }
}

void Parser::HandleTopLevelExpression() {
  if (FunctionAST *F = ParseTopLevelExpr()) {
    if (llvm::Function *LF = F->Codegen()) {
      fprintf(stdout, "Read top-level expression:");
      LF->dump();
    }
  } else {
    // Skip token for error recovery.
    getNextToken();
  }
}

void Parser::MainLoop() {
  getNextToken();
  while (1) {
    switch (CurTok) {
      case tok_eof:    return;
      case ';':        getNextToken(); break;  // ignore top-level semicolons.
      case tok_def:    HandleDefinition(); break;
      case tok_extern: HandleExtern(); break;
      default:         HandleTopLevelExpression(); break;
    }
  }
}

