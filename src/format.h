#include <Rcpp.h>
#include <sstream>
using namespace Rcpp;

class currency_format {
  
private:
  
  // Values we need for conversion to work
  std::string symbol;
  bool symbol_first;
  unsigned int grouping;
  std::string decimal;
  std::string group;
  
  template< typename T >
  std::string input_convert(T x){
    std::ostringstream output;
    output << x;
    return output.str();
  }
  
  template< typename T >
  std::string currency_format_single(T x){
    
    // Start by turning it into a string and splitting off any decimal data
    std::string input_str = input_convert(x);
    std::string decimal_fragments;
    size_t was_double = input_str.find(".");
    if(was_double != std::string::npos){
      decimal_fragments = input_str.substr(was_double+1);
      input_str = input_str.substr(0, was_double);
    }
    
    // Create output object and handle format
    std::string output;
    if(symbol_first){
      output = symbol;
    }
    
    // Loop through
    unsigned int input_length = input_str.size();
    for(unsigned int i = 0; i < input_length; i++){
      if((i > 1) && (input_length > grouping) && (grouping % i == 0)){
        output += group;
      }
      output+= input_str[i];
    }
    
    // Handle decimal values
    if(decimal_fragments.size()){
      output += decimal + decimal_fragments;
    }
    // Handle non-symbol-first environments
    if(!symbol_first){
      output += symbol;
    }
    
    return output;
  }
  
  
public:
  
  template< typename T >
  std::vector < std::string > currency_format_vector(std::vector < T > vals){
    
    // Set up
    unsigned int input_size = vals.size();
    std::vector < std::string > output(input_size);
    
    // Run
    for(unsigned int i = 0; i < input_size; i++){
      output[i] = currency_format_single(vals[i]);
    }
    return output;
  }
  
  currency_format(std::string sym_val, bool sym_first, unsigned int group_val, std::string dec_sep,
                  std::string group_sep){
    symbol = sym_val;
    symbol_first = sym_first;
    grouping = group_val;
    decimal = dec_sep;
    group = group_sep;
  }
};
