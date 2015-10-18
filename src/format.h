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
  
  std::string currency_format_single(std::string x){
    
    // Start by turning it into a string and splitting off any decimal data
    std::string decimal_fragments;
    size_t was_double = x.find(".");
    if(was_double != std::string::npos){
      decimal_fragments = x.substr(was_double+1);
      x = x.substr(0, was_double);
    }
    
    // Loop through adding group delimiters
    signed int position = (x.size() - grouping);
    while (position > 0) {
      x.insert(position, group);
      position -= grouping;
    }
    
    // Create output object and handle format
    std::string output;
    if(symbol_first){
      output = symbol;
    }
    output += x;
    
    // Handle decimal values
    if(decimal_fragments.size() > 0 ){
      output += decimal + decimal_fragments;
    }
    
    // Handle non-symbol-first environments
    if(!symbol_first){
      output += symbol;
    }
    
    return output;
  }
  
  double currency_unformat_single(std::string x){
    
    size_t decimal_place = x.find_last_of(decimal);
    std::string holding;
    for(unsigned int i = 0; i < x.size(); i++){
      if(isdigit(x[i]) || i == decimal_place){
        holding += x[i];
      }
    }
    
    double output;
    std::istringstream(holding) >> output;
    return output;
  }
  
public:
  
  std::vector < std::string > currency_format_vector(std::vector < std::string > vals){
    
    // Set up
    unsigned int input_size = vals.size();
    std::vector < std::string > output(input_size);
    
    // Run
    for(unsigned int i = 0; i < input_size; i++){
      output[i] = currency_format_single(vals[i]);
    }
    return output;
  }
  
  std::vector < double > currency_unformat_vector(std::vector < std::string > vals){
    
    // Set up
    unsigned int input_size = vals.size();
    std::vector < double > output(input_size);
    
    // Run
    for(unsigned int i = 0; i < input_size; i++){
      output[i] = currency_unformat_single(vals[i]);
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
  
  currency_format(std::string dec_sep){
    decimal = dec_sep;
  }
};
