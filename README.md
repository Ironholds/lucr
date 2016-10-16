
# Currency conversion, handling and manipulation in R

[![](http://www.r-pkg.org/badges/version/lucr)](http://www.r-pkg.org/pkg/lucr)
[![CRAN RStudio mirror downloads](http://cranlogs.r-pkg.org/badges/lucr)](http://www.r-pkg.org/pkg/lucr)

`lucr` provides currency data reformatting and retrieval. In particular, it lets you:

1. Easily refactor numeric values as currency values, controlling for the separators, the group sizes, the positioning of the
currency sign, and the currency sign itself;
2. Take currency-formatted data and refactor it into numeric values;
3. Retrieve currency conversion rates from the [Open Exchange Rates](https://openexchangerates.org) API.

## Installation

To get the release version:

```r
install.packages("lucr")
```

For the development version:
```r
devtools::install_github("ironholds/lucr")
```

## License

MIT + file LICENSE © [Oliver Keyes](https://github.com/).
