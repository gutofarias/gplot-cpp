//
//  gplot-test.cpp
//
//  Test file for the library 'gplot'.
//
//  Created by João Gutemberg Barbosa de Farias Filho
//  See https://github.com/gutofarias/gplot
//

#include <math.h>
#include "gplot.h"

int main(int argc, const char * argv[]) {

    const char file1[] = "./output/exported_vectors_1.txt";
    const char file2[] = "./output/exported_vectors_2.txt";

    const int n = 100;
    double x[n];
    double y[n];
    double z[n];

    for(int i=0; i<n; i++) {
        x[i] = 0.1 * i;
	y[i] = sin(x[i]);
	z[i] = cos(x[i]);
    }

    Gnuplot2D plot1 (2);
    plot1.curve[0].set_plot(file1, x, y, n);
    plot1.curve[1].set_plot(file2, x, z, n, 3);
    plot1.bundle_files("./output");
    plot1.set_term_pdflatex_eps();

    return 0;
 
}
