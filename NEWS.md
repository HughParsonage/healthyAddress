# 0.5.1

Uses the qs2 format

# 0.4.4

* Internal
  - Use `{{NULL}}` as advised by clang19
  - RM unused variable k in internal function

# 0.4.3

* Internal
   - `STRING_PTR` to `STRING_PTR_RO` due to new CRAN C API enforcement
   - New repo "https://github.com/HughParsonage/PSMA-202405" supported

# 0.4.0

* New latlon support (#1):
   - `download_latlon_data` downloades the latest geocoded addresses (in compressed form)
   - `compress_latlon` provides compression to 32-bit integers of lat-lon coordinates while
      retaining reasonably high precision.
   - `mutate_latlon` takes a standardized address data.table and adds the lat-lon coordinates
* Bug fix:
   - UNPROTECT correctly positioned

# 0.3.0

* Updated to Nov 2023 data
* `unique_Postcodes` gains a `strict` argument, to include only real postcodes

# healthyAddress 0.0.4

* Added a `NEWS.md` file to track changes to the package.

Enhancements:
  - Supports addresses 'U 105'.
