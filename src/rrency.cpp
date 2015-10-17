#include <Rcpp.h>
#include "format.h"
using namespace Rcpp;

//[[Rcpp::export]]
std::vector < std::string > currency_format_int(std::vector < int > x, std::string symbol, bool symbol_first,
                                                unsigned int grouping, std::string decimal, std::string group){
  currency_format currency_inst(symbol, symbol_first, grouping, decimal, group);
  return currency_inst.currency_format_vector(x);
}

//[[Rcpp::export]]
std::vector < std::string > currency_format_double(std::vector < double > x, std::string symbol, bool symbol_first,
                                                unsigned int grouping, std::string decimal, std::string group){
  currency_format currency_inst(symbol, symbol_first, grouping, decimal, group);
  return currency_inst.currency_format_vector(x);
}
