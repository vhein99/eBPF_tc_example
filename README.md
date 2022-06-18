# eBPF_tc_example
A minimalistic example of a traffic control eBPF program that prints out the type and code fields of received ICMP messages.

## Requirements
In order to compile the example you need **clang** and **llvm >= 3.7**. \
The **make** program is required as well.

## Constraints
The run script requires a Linux kernel and the Bourne Again SHell (BASH).  \
The script has to be run as a superuser as it makes use of priveleged commands to create namespaces for the virtual network devices.

## Setup
To build and execute the example simply issue following commands.
```
make
run
```
The first command builds an object file __minimal.o__ from the __minimal.c__ source.  \
The second line creates a pair of virtual network devices:
```
------            ------
| H1 |------------| H2 |
------            ------
```
The compiled eBPF program in __minimal.o__ is attached to a traffic control hook on __H2__,
which allows the program to handle ingress traffic.  \
On __H1__ a ping is issued towards __H2__.  \
The debug output of the eBPF program is printed alongside the output of the ping command.
