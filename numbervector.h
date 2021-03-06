#ifndef NUMBERVECTOR_H
#define NUMBERVECTOR_H

class NumberVector
{
public:
    double x,y,z;

    NumberVector();
    NumberVector(double, double, double);
    NumberVector normalize();
    NumberVector cross_product(NumberVector other);
    double dot_product(NumberVector other);
    NumberVector multiply(double amount);
    NumberVector add(NumberVector other);
    NumberVector sub(NumberVector other);
    NumberVector negative();
    NumberVector k_multiply_by_I_lighting(NumberVector other);

};


#endif // NUMBERVECTOR_H
