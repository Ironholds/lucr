#'@importFrom httr GET user_agent stop_for_status content
oer_query <- function(path, key, ...){
  
  # Construct URL
  url <- paste0("https://openexchangerates.org/api/", path, "?app_id=", key)
  
  # Make request
  result <- httr::GET(url, httr::user_agent("rrency - https://github.com/Ironholds/rrency"))
  httr::stop_for_status(result)
  
  # Format result and return it
  result <- httr::content(result)
  if("timestamp" %in% names(result)){
    result$timestamp <- as.POSIXct(result$timestamp, origin="1970-01-01")
  }
  return(result)
}

#'@title Convert between currencies using the Open Exchange Rates API
#'
#'@description Uses the Open Exchange Rates API to convert a series of amounts between
#'two currencies.
#'
#'@param x a vector of amounts, formatted as integer or numeric values.
#'
#'@param from the currency \code{x} is currently in.
#'
#'@param to the currency you \emph{want} \code{x} to be in.
#'
#'@param key your Open Exchange Rates API key. See their \href{https://openexchangerates.org/signup}{access plans}
#'(particularly the 'forever free' plan linked at the bottom).
#'
#'@param ... further arguments to pass to httr's \code{GET} function.
#'
#'@export
currency_convert <- function(x, from, to, key, ...){
  
  # Check the data is integer/numeric
  if(!any(is.numeric(x), is.integer(x))){
    stop("You must provide integer or numeric values. If you have currency strings to convert, see ?from_currency")
  }
  
  # Request the current conversion rates
  rates <- oer_query("latest.json", key, ...)
  
  # Check we have the currency
  conversion_rate <- rates$rates[[to]]
  if(is.null(conversion_rate)){
    stop("Conversion to that currency is not supported. See ?list_currencies for what is.")
  }
  
  # These are going to be coming back in USD. Boo.
  # If the user actually has USD that's fine.
  if(from == "USD"){
    return(x * conversion_rate)
  }
  
  # Otherwise we need to convert TO USD and then to the currency
  # we want. Ugh.
  intermediary_rate <- rates$rates[[from]]
  if(is.null(intermediary_rate)){
    stop("Conversion from that currency is not supported. See ?list_currencies for what is.")
  }
  return( (x / intermediary_rate) * conversion_rate)
}

#'@title Find Supported Currencies
#'@description Generates a list of the currencies supported by \code{\link{currency_convert}}.
#'
#'@param key Your Open Exchange Rates API key. See their \href{https://openexchangerates.org/signup}{access plans}
#'(particularly the 'forever free' plan linked at the bottom).
#'
#'@param as_df Whether to return the results as a data.frame. If not, it will be a named list. Set to FALSE
#'by default.
#'
#'@param ... Further arguments to pass to httr's \code{GET} function.
#'
#'@export
list_currencies <- function(key, as_df = FALSE, ...){
  results <- oer_query("currencies.json", key, ...)
  if(as_df){
    return(data.frame(code = names(results),
                      name = unlist(results),
                      stringsAsFactors = FALSE))
  }
  return(results)
}
