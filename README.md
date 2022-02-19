# Molecule-Visualizer
A C++-based program for molecular visualization and building using OpenGL. 

This is the first project I made with OpenGL, and among the first of my large C++ projects. It has a few different ways of rendering molecules in 3D space. Given an arbitrary collection of atoms and bonds, it can use VSEPR to calculate the 3D shape of the resultant molecule (unfortunately, torsional angles are somewhat innacurate, as I have not yet developed a system to calculate those). 
It is also capable of loading PDB files, positioning atoms and bonding them according to the implied bonds of the amino acids.
