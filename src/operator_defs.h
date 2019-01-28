#pragma once

#include "netlist.h"

namespace netlistDB {

// bitwise
extern FunctionDef OpNot;
extern FunctionDef OpAnd;
extern FunctionDef OpOr;
extern FunctionDef OpXor;
// nand, reverse

// cmp
extern FunctionDef OpLE;
extern FunctionDef OpGE;
extern FunctionDef OpGt;
extern FunctionDef OpLt;
extern FunctionDef OpEq;
extern FunctionDef OpNeq;


// arithmetic
extern FunctionDef OpUnMinus;
extern FunctionDef OpNeg;
extern FunctionDef OpAdd;
extern FunctionDef OpSub;
extern FunctionDef OpDiv;
extern FunctionDef OpMul;
// modulo, rem?

extern FunctionDef OpConcat;

extern FunctionDef OpRising;
extern FunctionDef OpFalling;
// [todo] rising and falling ?= event

}