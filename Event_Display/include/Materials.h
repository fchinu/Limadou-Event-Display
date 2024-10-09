#pragma once

class Material {
public:
  virtual ~Material() = default;
  virtual const char *GetName() const = 0;
  virtual int GetZ() const = 0;
  virtual int GetA() const = 0;
  virtual double GetDensity() const = 0;
};

/**
 * @brief Silicon material properties
 * @param Z Atomic number
 * @param A Atomic mass
 * @param Density Material density in g/cm^3
 */
class Silicon : public Material {
public:
  const char *GetName() const override { return fName; }
  int GetZ() const override { return fZ; }
  int GetA() const override { return fA; }
  double GetDensity() const override { return fDensity; }

private:
  const char *fName = "Si";
  const int fZ = 14;
  const int fA = 28;
  const double fDensity = 2.329085; // g/cm^3
};

/**
 * @brief Carbon material properties
 * @param Z Atomic number
 * @param A Atomic mass
 * @param Density Material density in g/cm^3
 */
class Carbon : public Material {
public:
  const char *GetName() const override { return fName; }
  int GetZ() const override { return fZ; }
  int GetA() const override { return fA; }
  double GetDensity() const override { return fDensity; }

private:
  const char *fName = "C";
  const int fZ = 6;
  const int fA = 12;
  const double fDensity = 2.267; // g/cm^3
};