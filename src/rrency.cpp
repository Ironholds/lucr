#include <Rcpp.h>
#include "format.h"
using namespace Rcpp;

//[[Rcpp::export]]
CharacterVector currency_format_(CharacterVector x, String symbol, bool symbol_first,
                                 int grouping, String decimal, String group){
  currency_format currency_inst(symbol, symbol_first, grouping, decimal, group);
  return currency_inst.currency_format_vector(x);
}

//[[Rcpp::export]]
NumericVector currency_unformat_(CharacterVector x, String decimal){
  currency_format currency_inst(decimal);
  return currency_inst.currency_unformat_vector(x);
}
