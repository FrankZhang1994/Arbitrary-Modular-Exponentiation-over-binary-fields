# Arbitrary-Modular-Exponentiation-over-binary-fields

The Itoh-Tsujii's algorithm (ITA) is an efficient method to calculate modular inversion operations over binary fields.
However, writing Verilog files of arbitrary modular exponentiation, especially high-order exponentiations is rather horrible.
Here, we design two C models to help HDL developers to generate fully combinational modular exponentiation Verilog files automatically.

sqr_generation.c: generate combinational modular exponentiation Verilog files according to the traditional ITA. The exponentiation values follow the classic addition chain in ITA.

sqr_arbitrary.c: generate modular exponentiation Verilog files whatever you want. This will help you to exploit other addition chains to optimize the ITA.
