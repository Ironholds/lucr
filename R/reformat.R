#'@title Format numeric or integer values as currency values
#'
#'@description a formatter that lets you take numeric or integer values (12000) and convert them
#'to strings that are currency-formatted ($12,000). Full control is available over the currency symbol,
#'the size of delimited groups, the sign used \emph{to} delimit groups, and decimal placement.
#'
#'@param x a numeric or integer vector containing values you want to currency-ify
#'
#'@param currency_symbol the symbol that identifies the currency. "£" by default.
#'
#'@param symbol_first whether the symbol goes at the beginning (TRUE) or end (FALSE) of the generated
#'value. TRUE by default.
#'
#'@param group_size the size of delimited groups (2, 3, or 4 digits, say). Set to 3 by default.
#'
#'@param decimal_delim the delimiter to use for sub-unit, decimal values. A period by default.
#'
#'@param group_delim the delimiter for each group.
#'
#'@examples
#'to_currency(120000.03)
#'
#'@export
to_currency <- function(x, currency_symbol = "£", symbol_first = TRUE, group_size = 3,
                        decimal_delim = ".", group_delim = ","){
  
  if(is.integer(x)){
    return(currency_format_int(x, currency_symbol, symbol_first, group_size, decimal_delim, group_delim))
  } else if(is.numeric(x)){
    return(currency_format_double(x, currency_symbol, symbol_first, group_size, decimal_delim, group_delim))
  }
  stop("x must be a numeric or integer vector")
}
