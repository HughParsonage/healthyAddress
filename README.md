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

```
