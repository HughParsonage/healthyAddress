# healthyAddress

*Intelligent and fast parsing of Australian addresses*

A common problem when dealing with Australian addresses is that they are often
recorded as strings as they appear on an envelope. For example, 

> 1408/170 The Esplanade St Kilda VIC 3182

In order to match with data, such as the PSMA, we often want to extract the
components of this address. For example, we want to extract the flat number
(1408) and the postcode (3182). Problems arise in both performance and 
intelligently parsing this address. In the above, we want to recognize that 
'St' refers to 'Saint Kilda' not 'Street'. The package `healthyAddress` attempts
to provide fast and intelligent parsing of Australian addresses.

The main function is `standardize_address`:

```r
library(healthyAddress)
standardize_address("1408/170 The Esplanade St Kilda VIC 3182")
#>    FLAT_NUMBER NUMBER_FIRST NUMBER_LAST NUMBER_SUFFIX   STREET_NAME
#>          <int>        <int>       <int>         <raw>        <char>
#> 1:        1408          170           0            00 THE ESPLANADE
#>    STREET_TYPE_CODE POSTCODE STREET_TYPE
#>               <int>    <int>      <char>
#> 1:                0     3182        <NA>
```

<sup>Created on 2024-01-31 by the [reprex package](https://reprex.tidyverse.org) (v2.0.1)</sup>

There are two arguments to the function that affect performance, 

* `hash_StreetName`: instead of returning the street name as a string, return an integer. This
  can be useful when performing merges (which are faster on integer vectors), by applying
  `HashStreetName` to the foreign table's street name.
* `integer_StreetType`: instead of returning the street type as a string, return an integer. 
* `check` performs a check on the input. Setting to zero can improve performance on
  input that has already checked.
