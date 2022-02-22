# Molecule-Visualizer
A C++-based program for molecular visualization and building using OpenGL. 

This is the first project I made with OpenGL, and among the first of my large C++ projects. It has a few different ways of rendering molecules in 3D space. Given an arbitrary collection of atoms and bonds, it can use VSEPR to calculate the 3D shape of the resultant molecule, as well as an approximate repulsion calculation to derive torsional angles. 
It is also capable of loading PDB files, positioning atoms and bonding them according to the implied bonds of the amino acids.
This project has been a wonderful opportunity to combine my passions for chemistry and molecular biology with my computer science abilities.

### Lysine calculated from only atoms and bonds
![Lysine](resources/images/lysine.png?raw=true)

### Benzene ring showing ring structure calculation capabilities
![Benzene Ring](resources/images/benzenering.png?raw=true)

### Human insulin loaded from a PDB
![Insulin](resources/images/insulin.png?raw=true)
PDB from [here](https://www.rcsb.org/structure/3I40)

### Botulinum neurotoxin loaded from a PDB
![Botulinum Neurotoxin](resources/images/botulinumneurotoxin.png?raw=true)
PDB from [here](https://www.rcsb.org/structure/3BTA)