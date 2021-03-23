//
//  gnuplot.h
//  gnuplot_cpp
//
//  Created by João Gutemberg Farias Filho on 20/03/15.
//  Copyright (c) 2015 Joao Gutemberg. All rights reserved.
//

#ifndef gnuplot_cpp_gnuplot_h
#define gnuplot_cpp_gnuplot_h

#include <iostream>
#include <math.h>
#include <string.h>
#include <sstream>
#include <fstream>
#include <unistd.h>
#include <list>


using namespace std;


/* -----------------------------------------------------------------------------------------*/

/* -----------------------------------------------------------------------------------------*/

/* -----------------------------------------------------------------------------------------*/


const int TERM_EPS = 1;
const int TERM_X11 = 2;
const int TERM_AQUA = 3;
const int TERM_WXT = 4;
const int TERM_QT = 5;
const int TERM_WINDOWS = 6;
const int TERM_PDFLATEX_EPS = 7;
const int TERM_PDFLATEX_CAIRO = 8;


//BEGIN USER CONFIGURATION



//CHOOSE THE DEFAULT TERMINAL TO RUN THE SCRIPTS
const int TERM_DEFAULT = TERM_EPS;

//CHOOSE THE DEFAULT FONT AND FONT SIZE
const string FONT_DEFAULT = "Verdana";//"Helvetica";
const int FONT_SIZE_DEFAULT = 10;

//CHOOSE THE DEFAULT FONT SIZE AND GRAPH SIZE WHEN USING THE PDFLATEX TERMINALS
const int FONT_SIZE_DEFAULT_PDFLATEX = 10;
const double GRAPH_SIZE_DEFAULT_PDFLATEX[2] = {16.0, 11.0}; //{width_in_cm, height_in_cm}

//ENTER NAME (COMMAND TO RUN) OF THE PROGRAM TO RUN THE LATEX OUTPUT AND GENERATE A PDF FILE WHEN USING PDFLATEX TERMINAL
const string LATEX2PDFCOMPILER = "pdflatex";
//IF THE NAME DOES NOT WORK, SET THE BOOLEAN TO TRUE AND TRY THE ABSOLUTE PATH OF OF PDFLATEX, EPSTOPDF AND GHOSTSCRIPT(GS) (GS IS NOT NEEDED ON WINDOWS)
const bool PDFLATEX_MANUAL_PATH_BOOL = true;
const string LATEX2PDFCOMPILER_PATH = "/Library/TeX/texbin/pdflatex"; //terminal: "type -a pdflatex", cmd: "where pdflatex"
//const string LATEX2PDFCOMPILER_PATH = "C:\\Program Files\\MiKTeX 2.9\\miktex\\bin\\pdflatex.exe"; //example on windows
const string EPSTOPDF_PATH = "/Library/TeX/texbin/epstopdf"; //terminal: "type -a epstopdf", cmd: "where epstopdf"
//const string EPSTOPDF_PATH = "C:\\Program Files\\MiKTeX 2.9\\miktex\\bin\\epstopdf.exe"; //example on windows
const string GHOSTSCRIPT_PATH = "/opt/local/bin/gs"; //terminal: "type -a gs", will not be used in Windows
const bool DEBUG_MANUAL_PATH = false; //Use this if the program says "OK" but do not generate the pdf file. If true it is going to show all the shell outputs
//OBS.: REMEMBER TO USE '\\' and '\"' WHEN SETTING AN ABSOLUTE PATH FOR WINDOWS


//ADD A CUSTOM GNUPLOT ABSOLUTE PATH IF THE LIBRARY IS NOT ABLE TO FIND IT AUTOMATICALLY
//SET THE VARIABLE CUSTOM_GNUPLOT_PATH_BOOL TO TRUE TO USE THE CUSTOM PATH
const bool CUSTOM_GNUPLOT_PATH_BOOL = false;
const string CUSTOM_GNUPLOT_PATH = "/opt/local/bin/gnuplot";//"/opt/local/bin/gnuplot";
//const string CUSTOM_GNUPLOT_PATH = "C:\\Program Files\\gnuplot\\bin\\gnuplot.exe";
//OBS.: REMEMBER TO USE '\\' and '\"' WHEN SETTING AN ABSOLUTE PATH FOR WINDOWS, EX.:
//const string CUSTOM_GNUPLOT_PATH = "\"C:\\Program Files\\gnuplot\\bin\\gnuplot.exe\"";


//CONFIGURING XCODE (MAC) TO WORK WITH THE LIBRARY

//SETTING THE WORKING DIRECTORY
/*
 FIRST WE RECOMMEND YOU TO CHANGE THE WORKING DIRECTORY FOR ONE THAT YOU DESIRE, E.G. THE SAME FOLDER THAT CONTAINS THE main.cpp

 TO DO THIS GO IN:
 PRODUCT > SCHEME > EDIT SCHEME > RUN > OPTIONS
 THEN ACTIVATE AND CHOOSE A CUSTOM WORKING DIRECTORY
*/

//END USER CONFIGURATION



//CODE TO TEST IF THE LIBRARY CAN FIND THE GNUPLOT EXECUTABLE

/*
 #include <iostream>
 #include <math.h>
 #include "gnuplot.h"

 using namespace std;

 int main(int argc, const char * argv[]) {

 const int n = 100;
 double x[n];
 double y[n];
 for(int i=0; i<n; i++)
 {
 x[i] = 0.1 * i;
 y[i] = sin(x[i]);
 }
 Gnuplot2D plot1 (2) ;
 plot1.curve[0].set_plot("exported_vectors.txt", x, y, n);
 plot1.curve[1].set_plot("exported_vectors.txt", x, y, n, 3);
 plot1.set_term_eps();

 return 0;
 }
 */

//IF YOU CAN FIND AN IMAGE NAMED gnuplot2d_1.eps WHICH HAS A SINE WAVE PLOTTED, THE LIBRARY WAS ABLE TO FIND THE GNUPLOT EXECUTABLE.

/* -----------------------------------------------------------------------------------------*/

/* -----------------------------------------------------------------------------------------*/

/* -----------------------------------------------------------------------------------------*/



//DO NOT CHANGE ANYTHING FROM NOW ON
//DO NOT CHANGE ANYTHING FROM NOW ON
//DO NOT CHANGE ANYTHING FROM NOW ON


//CONSTANTS
const string PLOT_FILENAME_DEFAULT = "You need to set the plot!";


//OPERATIONAL SYSTEM DEFINITION AND GNUPLOT PATH

#if defined(_WIN32)||defined(WIN32)||defined(_WIN64)
#define WINDOWS_OS
#endif

#if defined(__APPLE__)||defined(__unix)||defined(__linux)||defined(__posix)
#define UNIX_OS
#endif
	
// #define WINDOWS_OS defined(_WIN32)||defined(WIN32)||defined(_WIN64)
// #define UNIX_OS defined(__APPLE__)||defined(__unix)||defined(__linux)||defined(__posix)

#if WINDOWS_OS
#include <process.h>
#include <Windows.h>
//#define popen _popen
//#define pclose _pclose
const bool WINDOWS = true;
#else
#include <sys/mman.h>
#include <sys/wait.h>
const bool WINDOWS = false;
#endif

#ifdef UNIX_OS

const bool UNIX = true;
#else
const bool UNIX = false;
#endif


//CLASS PLOTBASE

class plotbase
{
protected:
    string _filename;
    int _columns[6];
    bool _title_bool;
    string _title;
    bool _lines;
    bool _points;
    int _color_gnuplot;
    bool _color_rgb_bool;
    string _color_rgb;
    string end_of_plot (void);
    bool _parametric;
    int _type_or_style;
    double _size_width;
    bool _palette;
    int _palette_column;
    bool _pm3d;
    bool _dashtype_string_bool;
    int _dashtype_int;
    string _dashtype_string;
    bool _vectors;
    double _vector_headsize[2];
    bool _vector_headfilled;

    void set_parametric (void);
    plotbase(int color_gnu = 0); //protected constructor
    void set_color_rgb_or_option (string opt);
    
    bool _plotstring_custom_bool;
    string _plotstring_custom;

public:

    void set_filename (string filename);
    void set_columns (int col1, int col2, int col3=0, int col4=0, int col5=0, int col6=0);
    //void set_one_column (int column_index, int column_value);
    void set_color_gnuplot(int color_gnuplot);
    void set_color_rgb (string color_rgb);
    void set_title (string title);
    void set_with_points (double point_size=1.0, int point_type=1);
    void set_with_lines (double line_width=1.0, int line_style=1);
    void set_with_vectors(double line_width=1.0, int line_style=1);
    void set_vector_headsize(double length, double angle = 20.0);
    void set_vector_headfilled(bool filled);
    //void set_with_lines (double line_width, string dash_pattern);
    //void set_with_lines_dashed (double line_width = 1.0, int dash_pattern = 1);
    //void set_with_lines_dashed (double line_width, string dash_pattern);
    void set_dashtype (int dash_pattern);
    void set_dashtype (string custom_dash_pattern);
    void set_type_or_style (int point_type_or_line_style);
    void set_size_or_width (double point_size_or_line_width);
    void set_palette (int function_column);
    void set_pm3d (int function_column);
    void set_plot_custom(string plotstring_custom);
    bool get_parametric (void);
    string get_filename (void);
};




/* -----------------------------------------------------------------------------------------*/

/* -----------------------------------------------------------------------------------------*/

/* -----------------------------------------------------------------------------------------*/

//CLASS PLOTSTRING2D_SINGLE

class plotstring2d_single : public plotbase {
private:
    bool _straight_line_bool;
    string _straight_line;
    plotstring2d_single(void);  //private constructor
    string plotstring (void);
    
    bool _x2y2bool;
    int _xyaxes[2];

public:

    friend class gnup2D; //allows gnup2D to access this class private data (access its constructor)

    void set_plot(string filename, int col1, int col2, int color_gnuplot=0);
    void set_plot(string filename, int col1, int col2, int col3, int col4, int color_gnuplot=0); //for ploting vectors
    void set_plot(string filename, int col1, int col2, string color_rgb);
    void set_plot(string filename, int col1, int col2, int col3, int col4, string color_rgb); //for ploting vectors
    void set_plot(string filename, double* x, double* y, long long number_of_points, int color_gnuplot=0);
    void set_plot(string filename, double* x, double* y, long long number_of_points, string color_rgb);
    void set_plot_straight_line(double coef_y, double coef_x, double b, int color_gnuplot=0); //coefs of y=x+b
    void set_plot_straight_line(double coef_y, double coef_x, double b, string color_rgb); //coefs of y=x+b
    void set_xyaxes(int xaxis, int yaxis);
};


/* -----------------------------------------------------------------------------------------*/

/* -----------------------------------------------------------------------------------------*/

/* -----------------------------------------------------------------------------------------*/

//CLASS PLOTSTRING3D_SINGLE

class plotstring3d_single : public plotbase {

private:
    bool _plane_bool;
    string _plane_str;
    plotstring3d_single(void); //private constructor
    string plotstring (void);

public:

    friend class gnup3D; //allows gnup3D to access this class private data (access its constructor)

    void set_plot(string filename, int col1, int col2, int col3, int color_gnup=0);
    void set_plot(string filename, int col1, int col2, int col3, int col4, int col5, int col6, int color_gnup=0); //for ploting vectors
    void set_plot(string filename, int col1, int col2, int col3, string color_rgb);
    void set_plot(string filename, int col1, int col2, int col3, int col4, int col5, int col6, string color_rgb); //for ploting vectors
    void set_plot(string filename, double* x, double* y, double* z, long long number_of_points, int color_gnup=0);
    void set_plot(string filename, double* x, double* y, double* z, long long number_of_points, string color_rgb);
    void set_plot_plane(double x, double y, double z, double a, int color_gnup=0);
    void set_plot_plane(double x, double y, double z, double a, string color_rgb);
};


//CLASS HEADER_GNUPLOT

class header_gnuplot {
    private:
    static int _cont_plots;

protected:
    string _terminal;
    double _linewidth;
    string _font;
    int _font_size;
    bool _font_size_changed;
    int _term_code;
    double _graph_size_pdflatex[2];

    void set_terminal (int term1);
    string terminal_gnuplot (void);

    bool _added_latex_packages;
    string _latex_packages;
    
    
    string _output_filename;
    header_gnuplot(void); //protected constructor

    string header (void);
    void set_term_code (int terminal1);

public:

    void set_terminal_custom (string terminal);

    void set_term_aqua (void);
    void set_term_x11 (void);
    void set_term_eps (void);
    void set_term_windows (void);
    void set_term_wxt (void);
    void set_term_qt (void);
    void set_term_pdflatex_eps(void);
    void set_term_pdflatex_cairo(void);

    void set_output_filename (string output_filename);

    void set_font (string font);
    void set_font_size (int font_size);
    void set_linewidth (double linewidth);

    void set_graph_size_pdflatex (double widht_in_cm, double height_in_cm);
    int get_terminal (void);
    void add_latex_package (string latex_package);
    
};


//CLASS CONTROL_GNUPLOT

class control_gnuplot {
protected:
	FILE* _file;
	bool _file_init;
	control_gnuplot (void); //protected constructor
    ~control_gnuplot (void); //protected destructor

    void send_command (string& script);
    void send_command_replot (void);
    void send_command_plot (string scrp);
    void plot_ctr_gnuplot(string& filenam);

public:

    friend class Gnuplot2D; ///allows Gnuplot2D to access this class private data (access its constructor)
    friend class Gnuplot3D; //allows Gnuplot3D to access this class private data (access its constructor)
};


/* -----------------------------------------------------------------------------------------*/

/* -----------------------------------------------------------------------------------------*/

/* -----------------------------------------------------------------------------------------*/

//CLASS GNUP2D

class gnup2D {

protected:
    bool _grid;
    bool _sizeratio_bool;
    double _sizeratio;
    bool _sizesquare;
    bool _xtics_bool;
    double _xtics;
    bool _ytics_bool;
    double _ytics;
    bool _xrange_bool;
    bool _yrange_bool;
    double _xrange[2];
    double _yrange[2];
    bool _title_bool;
    string _title;
    bool _xlabel_bool;
    string _xlabel;
    bool _ylabel_bool;
    string _ylabel;
    bool _cbrange_bool;
    double _cbrange[2];
    int _n_plots;

    bool _parametric;
    bool _trange_bool;
    double _trange[2];

    string generate_plot2d (void);
    bool get_parametric(void);

    bool _key_bool;
    string _key_string[2];

    bool _add_line_bool;
    string _added_line;
    
    gnup2D (int number_of_curves=1); //protected constructor
    ~gnup2D (void); //protected destructor

    void set_number_of_curves (int number_of_curves);
    //void set_parametric (void);

public:
    plotstring2d_single *curve;//*plot;

    void set_xrange (double xmin, double xmax);
    void set_yrange (double ymin, double ymax);
    void set_xyrange(double xmin, double xmax, double ymin, double ymax);
    void set_xtics(double xtics);
    void set_ytics(double ytics);
    void set_xytics (double xtics, double ytics);
    void set_title (string title);
    void set_xlabel (string xlabel);
    void set_ylabel (string ylabel);
    void set_xylabel (string xlabel, string ylabel);
    void unset_grid (void);
    void set_sizeratio (double sizeratio=-1.0);
    void set_sizesquare (void);
    void set_trange (double tmin, double tmax);
    void set_cbrange (double cbmin, double cbmax);
    void set_key (string left_center_right, string top_center_bottom);
    void add_string (string line);

};


/* -----------------------------------------------------------------------------------------*/

/* -----------------------------------------------------------------------------------------*/

/* -----------------------------------------------------------------------------------------*/

//CLASS GNUPLOT2D

class Gnuplot2D : public header_gnuplot, public gnup2D {

private:
    control_gnuplot _process;
    static int _n;
    string _scriptname;
    void generate_script (void);
    bool _plotted;

    #if WINDOWS_OS
    #else
	bool *_realtime_bool;
	#endif

    void bundle_files_exec (void);
    string _bundle_folder_path;
    bool _bundle_files_bool;

public:
    Gnuplot2D (int number_of_curves = 1);
    ~Gnuplot2D (void);

    void set_scriptname (string scriptname);
    void bundle_files (string folder_path = "");
    void plot_graph (void);
    void replot_graph (void);
    void plot_realtime (int t_milisec=100);

};






/* -----------------------------------------------------------------------------------------*/

/* -----------------------------------------------------------------------------------------*/

/* -----------------------------------------------------------------------------------------*/

//CLASS GNUP3D

class gnup3D {

protected:
    int _n_plots;
    bool _view_bool;
    int _view[2];
    bool _grid;
    bool _viewequalxy;
    bool _viewequalxyz;
    bool _size_bool;
    double _size[2];
    bool _xtics_bool;
    double _xtics;
    bool _ytics_bool;
    double _ytics;
    bool _ztics_bool;
    double _ztics;
    bool _xrange_bool;
    bool _yrange_bool;
    bool _zrange_bool;
    double _xrange[2];
    double _yrange[2];
    double _zrange[2];
    bool _title_bool;
    string _title;
    bool _xlabel_bool;
    string _xlabel;
    bool _ylabel_bool;
    string _ylabel;
    bool _zlabel_bool;
    string _zlabel;
    bool _cbrange_bool;
    double _cbrange[2];
    bool _viewmap;

    bool _parametric;
    bool _isosample_bool;
    int _isosample;
    bool _urange_bool;
    double _urange[2];
    bool _vrange_bool;
    double _vrange[2];

    bool _key_bool;
    string _key_string[2];
    
    bool _add_line_bool;
    string _added_line;


    string generate_plot3d (void);
    void unset_view (void);
    bool get_parametric (void);

    gnup3D (int number_of_curves=1); //protected constructor
    ~gnup3D (void); //protected destructor

    void set_number_of_curves (int number_of_curves);
    void set_parametric (void);


public:
    plotstring3d_single *curve;

    void set_view (int angle_inclination, int angle_rotation);
    void unset_grid (void);
    void set_viewequalxy (void);
    void set_viewequalxyz (void);
    void set_size (double xy_length, double z_length);
    void set_xtics(double xtics);
    void set_ytics(double ytics);
    void set_ztics(double ztics);
    void set_xytics (double xtics, double ytics);
    void set_xyztics (double xtics, double ytics, double ztics);
    void set_xrange (double xmin, double xmax);
    void set_yrange (double ymin, double ymax);
    void set_zrange (double zmin, double zmax);
    void set_xyrange(double xmin, double xmax,double ymin, double ymax);
    void set_xyzrange(double xmin, double xmax,double ymin, double ymax, double zmin, double zmax);
    void set_title (string title);
    void set_xlabel (string xlabel);
    void set_ylabel (string ylabel);
    void set_zlabel (string zlabel);
    void set_xylabel (string xlabel, string ylabel);
    void set_xyzlabel (string xlabel, string ylabel, string zlabel);
    void set_urange (double umin, double umax);
    void set_vrange (double vmin, double vmax);
    void set_uvrange(double umin, double umax,double vmin, double vmax);
    void set_cbrange (double cbmin, double cbmax);
    void set_viewmap (void);
    void set_isosample (int isosamp);
    void set_key (string left_center_right, string top_center_bottom);
    void add_string (string line);


};

/* -----------------------------------------------------------------------------------------*/

/* -----------------------------------------------------------------------------------------*/

/* -----------------------------------------------------------------------------------------*/

//CLASS GNUPLOT3D


class Gnuplot3D : public header_gnuplot, public gnup3D {

private:
    control_gnuplot _process;
    static int _n;
    string _scriptname;
    bool _plotted;

    #if WINDOWS_OS
    #else
	bool *_realtime_bool;
    #endif
    void generate_script (void);

    string _bundle_folder_path;
    bool _bundle_files_bool;
    void bundle_files_exec (void);

public:
    Gnuplot3D (int number_of_curves = 1);
    ~Gnuplot3D (void);

    void set_scriptname (string str);
    void bundle_files (string folder_path = "");
    void plot_graph (void);
    void replot_graph (void);
    void plot_realtime (int t_milisec=100);

};


string int_to_color_rgb (int c);



#endif
