This is the root macro to calculate W(t)

There are multiple macros:

* AW_draw():
   Draw the 2D histogram relation between Voltage and Time
* AW_draw_slice(int bin, int num_of_bin_slices = 10)
   Draw a 1D histogram of Time based on for a given `bin` of Voltage, with `num_of_bin_slices` total number of slices
* AW_constat_slices(int num_of_bin_slices = 10)
   Prints best fit with `num_of_bin_slices` total number of slices
* AW_dynamic(int minimum_chi = 10)
   Prints best fits with dynamic slicing, with each slice having `chi < 10`
* AW_dynamic_slices(int min_num_of_bin_slices = 5, int max_num_of_bin_slices = 20)
   Prints best fits result for a range of `num_of_bin_slices`.


