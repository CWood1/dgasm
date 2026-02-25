#include "ast.h"
#include "symbol_tbl.h"

#include <stdio.h>
#include <stdlib.h>

uint16_t eval(expression_t* expr, symboltbl_t* symbols) {
  if (!expr) {
    fprintf(stderr, "Internal error: NULL expression\n");
    exit(1);
  }

  uint32_t left, right;
  uint32_t result;

  switch (expr->kind) {
  case EXPR_INTEGER:
    return (uint16_t)(expr->u.number & 0xFFFF);

  case EXPR_IDENTIFIER: {
    uint32_t value = find_symbol(symbols, expr->u.identifier);

    if (value == 0xFFFFFFFF) {
      fprintf(stderr, "Undefined symbol: %s\n",
	      expr->u.identifier);
      exit(1);
    }

    return (uint16_t)(value & 0xFFFF);
  }

  case EXPR_BINARY:
    left  = eval(expr->u.binary.left, symbols);
    right = eval(expr->u.binary.right, symbols);

    switch (expr->u.binary.op) {

    case OP_PLUS:
      result = left + right;
      break;

    case OP_MINUS:
      result = left - right;
      break;

    case OP_MULTIPLY:
      result = left * right;
      break;

    case OP_DIVIDE:
      if (right == 0) {
	fprintf(stderr, "Division by zero\n");
	exit(1);
      }
      result = left / right;
      break;

    case OP_AND:
      result = left & right;
      break;

    case OP_OR:
      result = left | right;
      break;

    case OP_XOR:
      result = left ^ right;
      break;

    default:
      fprintf(stderr, "Unknown binary operator\n");
      exit(1);
    }

    return (uint16_t)(result & 0xFFFF);

  case EXPR_UNARY:
    left = eval(expr->u.unary.child, symbols);

    switch (expr->u.unary.op) {

    case OP_NOT:
      result = ~left;
      break;

    case OP_MINUS:
      result = (uint32_t)(-((int32_t)left));
      break;

    case OP_PLUS:
      result = left;
      break;

    default:
      fprintf(stderr, "Unknown unary operator\n");
      exit(1);
    }

    return (uint16_t)(result & 0xFFFF);

  default:
    fprintf(stderr, "Unknown expression kind\n");
    exit(1);
  }
}
