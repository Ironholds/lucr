#include <Rcpp.h>
#include "format.h"
using namespace Rcpp;

//[[Rcpp::export]]
std::vector < std::string > currency_format_(std::vector < std::string > x, std::string symbol, bool symbol_first,
                                                unsigned int grouping, std::string decimal, std::string group){
  currency_format currency_inst(symbol, symbol_first, grouping, decimal, group);
  return currency_inst.currency_format_vector(x);
}

//[[Rcpp::export]]
std::vector < double > currency_unformat_(std::vector < std::string > x, std::string decimal){
  currency_format currency_inst(decimal);
  return currency_inst.currency_unformat_vector(x);
}
