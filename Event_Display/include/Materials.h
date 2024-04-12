#pragma once

/**
 * @brief Silicon material properties
 * @param Z Atomic number
 * @param A Atomic mass
 * @param Density Material density in g/cm^3
 */
typedef struct Silicon {
  const char *fMaterial = "Si";
  const int fZ = 14;
  const int fA = 28;
  const double fDensity = 2.329085; // g/cm^3
} Silicon;

/**
 * @brief Carbon material properties
 * @param Z Atomic number
 * @param A Atomic mass
 * @param Density Material density in g/cm^3
 */
typedef struct Carbon {
  const char *fMaterial = "C";
  const int fZ = 6;
  const int fA = 12;
  const double fDensity = 2.267; // g/cm^3
} Carbon;