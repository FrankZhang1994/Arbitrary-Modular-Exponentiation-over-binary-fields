# Arbitrary-Modular-Exponentiation-over-binary-fields

This repository is for our paper entitled "Modular Inversion Architecture over GF(2^m) Using Optimal Exponentiation Blocks for ECC Cryptosystems".

This paper is published in "The IEEE International Symposium on Circuits and Systems (ISCAS) 2024, Singapore". ISCAS is the flagship conference of the IEEE Circuits and Systems (CAS) Society.

The Itoh-Tsujii's algorithm (ITA) is an efficient method to calculate modular inversion operations over binary fields. This technique is commonly applied in cryptography applications, such as elliptic curve cryptography.

However, writing Verilog files of arbitrary modular exponentiation, especially high-order exponentiations is rather horrible.

Here, we design two C models to help HDL developers to generate fully combinational modular exponentiation Verilog files automatically.

Besides, a Matlab model will help hardware engineers to evalute the complexity of fully combinational modular exponentiation Verilog designs to improve the timing.

1. sqr_generation.c: generate combinational modular exponentiation Verilog files according to the traditional ITA. The exponentiation values follow the classic addition chain in ITA.

2. Q_Verilog_Generator.c: generate modular exponentiation Verilog files whatever you want. This will help you to exploit other addition chains to optimize the ITA.

3. Matlab_Experiment_Platform.m: a experiment platform written in MATLAB to help developer evaluate the complexity of combinational modular exponentiation architectures. We can treat modular exponentiation operations as m*m matrix and employ the matrix weight to evaluate the hardware complexity.

4. Q_163.m Q_283.m Q_571.m: modular square operation matrix for three binary fields in elliptic curve cryptography.

For academic communication and commercial cooperation, please contact me (zhangjingqi1994@gmail.com).
