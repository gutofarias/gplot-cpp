//
//  gplot.cpp
//
//  Source file of the library 'gplot'
//
//  Created by João Gutemberg Barbosa de Farias Filho
//  See https://github.com/gutofarias/gplot
//


#include "gplot.h"


/* -----------------------------------------------------------------------------------------*/

/* -----------------------------------------------------------------------------------------*/

/* -----------------------------------------------------------------------------------------*/



//FUNCTION TO FIND GNUPLOT PATH
#if WINDOWS_OS
const int GNUPLOT_PATH_NOT_FOUND = 0;
const int GNUPLOT_PATH_CUSTOM = 1;
const int GNUPLOT_PATH_WINDOWSX86 = 2;
const int GNUPLOT_PATH_WINDOWSX64 = 3;
int GNUPLOT_PATH_CODE = GNUPLOT_PATH_NOT_FOUND;
string GNUPLOT_PATH;
void test_path (void) //FOR WINDOWS
{
	static bool first = true;
    static bool CUSTOM_GNUPLOT_PATH_BOOL2 = true;
    if(first)
    {
        first = false;
        if(CUSTOM_GNUPLOT_PATH_BOOL && CUSTOM_GNUPLOT_PATH_BOOL2)
        {
            string test_string = "if exist \"" + CUSTOM_GNUPLOT_PATH +  "\" (echo sim)  else (echo nao)";
            FILE* test = _popen(test_string.c_str(),"r");
            char resp[4];
            string str;
            fgets(resp, 4, test);
            str = resp;
            _pclose(test);
            if (str=="sim")
            {
                GNUPLOT_PATH_CODE = GNUPLOT_PATH_CUSTOM;//true;
                GNUPLOT_PATH = CUSTOM_GNUPLOT_PATH;
            }
            else
            {
                first = true;
                CUSTOM_GNUPLOT_PATH_BOOL2 = false;
                cout << "CUSTOM GNUPLOT PATH NOT FOUND. TRYING AGAIN WITH THE REGULAR PATH" << endl;
                test_path();
            }
        }
        else
        {
            FILE* test = _popen("if exist \"C:\\Program Files\\gnuplot\\bin\\gnuplot.exe\" (echo sim)  else (echo nao)","r");
            char resp[4];
            string str;
            fgets(resp, 4, test);
            str = resp;
            _pclose(test);
            //cout << str << endl;
            if (str=="sim")
            {
                //PATH_BOOL = true;
                GNUPLOT_PATH_CODE = GNUPLOT_PATH_WINDOWSX64;
                GNUPLOT_PATH = "C:\\Program Files\\gnuplot\\bin\\gnuplot.exe";
            }
            else
            {
                test = _popen("if exist \"C:\\Program Files (x86)\\gnuplot\\bin\\gnuplot.exe\" (echo sim)  else (echo nao)","r");
                fgets(resp, 4, test);
                str = resp;
                _pclose(test);
                //cout << str << endl;
                if(str=="sim")
                {
                    //PATH_BOOL = true;
                    GNUPLOT_PATH_CODE = GNUPLOT_PATH_WINDOWSX86;
                    GNUPLOT_PATH = "C:\\Program Files (x86)\\gnuplot\\bin\\gnuplot.exe";
                }
                else
                {
                    cout << "ERROR: GNUPLOT PATH NOT FOUND" << endl;
                    //PATH_BOOL = true;
                    GNUPLOT_PATH_CODE = GNUPLOT_PATH_NOT_FOUND;
                    GNUPLOT_PATH = "C:\\Program Files\\gnuplot\\bin\\gnuplot.exe";
                }
            }
        }
    }
}
#else
const int GNUPLOT_PATH_NOT_FOUND = 0;
const int GNUPLOT_PATH_CUSTOM = 1;
const int GNUPLOT_PATH_JUST_GNUPLOT = 2;
const int GNUPLOT_PATH_OPT_LOCAL_BIN_GNUPLOT = 3;
int GNUPLOT_PATH_CODE = GNUPLOT_PATH_NOT_FOUND;
//bool PATH_BOOL=false;
string GNUPLOT_PATH;
void test_path (void) //FOR MAC AND LINUX
{
    static bool first = true;
    static bool CUSTOM_GNUPLOT_PATH_BOOL2 = true;
    if(first)
    {
        first = false;
        if(CUSTOM_GNUPLOT_PATH_BOOL && CUSTOM_GNUPLOT_PATH_BOOL2)
        {
            //string test_string = "type " + CUSTOM_GNUPLOT_PATH +  " 2>&1>/dev/null && echo sim || echo nao";
            string test_string = "type " + CUSTOM_GNUPLOT_PATH +  " 2>&1 && echo sim || echo nao";
            FILE* test = popen(test_string.c_str(), "r");
            char resp[200];
            string str = "";
            bool teste_str = false;
            
            while(fgets(resp, sizeof(resp), test)!=NULL && teste_str == false)
            {
                str = resp;
                if(str.find("sim")!=string::npos || str.find("nao")!=string::npos)
                {
                    teste_str = true;
                }
            }
            pclose(test);
            if (str.find("sim")!=string::npos)
            {
                //PATH_BOOL = true;
                GNUPLOT_PATH_CODE = GNUPLOT_PATH_CUSTOM;
                GNUPLOT_PATH = CUSTOM_GNUPLOT_PATH;
            }
            else
            {
                first = true;
                CUSTOM_GNUPLOT_PATH_BOOL2 = false;
                cout << "CUSTOM GNUPLOT PATH NOT FOUND. TRYING AGAIN WITH THE REGULAR PATH" << endl;
                test_path();
            }
        }
        else
        {
            //FILE* test = popen("type gnuplot 2>&1>/dev/null && echo \"sim\" || echo \"nao\"", "r");
            FILE* test = popen("type gnuplot 2>&1 && echo \"sim\" || echo \"nao\"", "r");
            char resp[200];
            string str = "";
            bool teste_str = false;
            while(fgets(resp, sizeof(resp), test)!=NULL && teste_str == false)
            {
                str = resp;
                if(str.find("sim")!=string::npos || str.find("nao")!=string::npos)
                {
                    teste_str = true;
                }
            }
            pclose(test);
            if (str.find("sim")!=string::npos)
            {
                //PATH_BOOL = true;
                GNUPLOT_PATH_CODE = GNUPLOT_PATH_JUST_GNUPLOT;
                GNUPLOT_PATH = "gnuplot";
            }
            else
            {
                //test = popen("type /opt/local/bin/gnuplot 2>&1>/dev/null && echo sim || echo nao", "r");
                test = popen("type /opt/local/bin/gnuplot 2>&1 && echo sim || echo nao", "r");
                teste_str = false;
                while(fgets(resp, sizeof(resp), test)!=NULL && teste_str == false)
                {
                    str = resp;
                    if(str.find("sim")!=string::npos || str.find("nao")!=string::npos)
                    {
                        teste_str = true;
                    }
                }
                pclose(test);
                if (str.find("sim")!=string::npos)
                {
                    //PATH_BOOL = true;
                    GNUPLOT_PATH_CODE = GNUPLOT_PATH_OPT_LOCAL_BIN_GNUPLOT;
                    GNUPLOT_PATH = "/opt/local/bin/gnuplot";
                }
                else
                {
                    cout << "ERROR: GNUPLOT PATH NOT FOUND" << endl;
                    //PATH_BOOL = false;
                    GNUPLOT_PATH_CODE = GNUPLOT_PATH_NOT_FOUND;
                    GNUPLOT_PATH = "gnuplot";
                }
            }
        }
    }
}
#endif


//FUNCTION THAT EXECUTES THE SCRIPT (PLOT THE GRAPH) IN CASE IT WAS NOT PLOTTED BY USING THE Gnuplot2D::plot_graph() or Gnuplot3D::plot_graph() FUNCTIONS. THIS FUNCTION IS EXECUTED WHEN THE Gnuplot2D OBJECT or Gnuplot3D OBJECT DIES.

void execute_script_gnuplot (string scriptname, int& pid)
{
#if WINDOWS_OS
    spawnl( P_NOWAIT, GNUPLOT_PATH.c_str(), "gnuplot","-persist",scriptname.c_str(), NULL);
#else
    if ((pid=fork())==0)  //if(fork()==0)
    {
        //if(!PATH_BOOL)
        if(GNUPLOT_PATH_CODE == GNUPLOT_PATH_JUST_GNUPLOT)
        {
            execlp(GNUPLOT_PATH.c_str(),"gnuplot","-persist",scriptname.c_str(),NULL);//FOR MAC AND LINUX IN MOST OF THE CASES, RUNNING JUST THE COMMAND "gnuplot" WITHOUT AND ABSOLUTE PATH BEING NEEDED
        }
        else
        {
            execl(GNUPLOT_PATH.c_str(),"gnuplot","-persist",scriptname.c_str(), NULL); //FOR MAC WHEN GNUPLOT IS INSTALED THROUGH MACPORTS, OR WHEN RUNNING AN ABSOLUTE PATH TO GNUPLOT
        }

        //IF IT FAILS TO EXECUTE
        cout << "PLOT " << scriptname << " FAILS TO EXECUTE" << endl;
         _exit(1);
    }

    //int status;
    //while (-1 == waitpid(pid, &status, 0))
    //{}
    //cout << "teste" << endl;
    //pid = -100;
#endif
}

/*
void print_line_once (void)
{
    static bool printed = false;
    if(!printed){ cout << endl; printed = true;}
}
*/

std::string ReplaceAll(std::string str, const std::string& from, const std::string& to) {
    size_t start_pos = 0;
    while((start_pos = str.find(from, start_pos)) != std::string::npos) {
        str.replace(start_pos, from.length(), to);
        start_pos += to.length(); // Handles case where 'to' is a substring of 'from'
    }
    return str;
}

//FUNCTION THAT EXECUTES THE LATEX TO PDF CONVERSION IN THE PDFLATEX TERMINAL
void pdflatex_exec (string output_filename, int pid=-100)
{
    int status;
    if(pid != -100)
    {
    	#if WINDOWS_OS
    	#else
        while (-1 == waitpid(pid, &status, 0))
        {}
        #endif
    }
    #if WINDOWS_OS
    else{Sleep(1000);}
    #else
    else{sleep(1);}
    #endif
	

	
    unsigned long p = output_filename.rfind(".");
    if (p>0)
    {
        output_filename = output_filename.substr(0,p);
    }
    
    #if WINDOWS_OS
    output_filename = ReplaceAll(output_filename,"/", "\\");
    #endif
    
    bool folder_name_bool = false;
    string folder_name = "";
    p = output_filename.rfind("/");
    unsigned long p2 = output_filename.rfind("\\");
    if(p != string::npos)
    {
        folder_name_bool = true;
        folder_name = output_filename.substr(0,p+1);
    }
    else if(p2 != string::npos)
    {
        folder_name_bool = true;
    	folder_name = output_filename.substr(0,p2+1);
	}
	

    string scriptex = output_filename + ".tex";

    #if WINDOWS_OS
    string deletefiles = "del " + output_filename + ".log " + output_filename + ".aux " + output_filename + "-inc.eps " + output_filename + "-inc-eps-converted-to.pdf " + scriptex + " 2>&1";
    #else
    string deletefiles = "rm " + output_filename + ".log " + output_filename + ".aux " + output_filename + "-inc.eps " + output_filename + "-inc-eps-converted-to.pdf " + scriptex + " 2>&1";
    #endif

    //print_line_once();
    cout << "Generating " << output_filename << ".pdf ... ";
    bool ERROR_BOOL = false;

    char buff[512];
    char error_char = '!';


    if(PDFLATEX_MANUAL_PATH_BOOL)
    {
    	#if WINDOWS_OS
    	string LATEX2PDFCOMPILER_PATH2 = "\"" + LATEX2PDFCOMPILER_PATH + "\"";
    	string EPSTOPDF_PATH2 = "\"" + EPSTOPDF_PATH + "\"";
    	string compare;
    	string LATEX2PDFCOMPILER_PATH_compare = "'" + LATEX2PDFCOMPILER_PATH2 + "'";
    	string EPSTOPDF_PATH_compare = "'" + EPSTOPDF_PATH2 + "'";
    	#endif

    	#if WINDOWS_OS
		string pdflatex_manual_str = EPSTOPDF_PATH2 + " --outfile=" + output_filename + "-inc-eps-converted-to.pdf " + output_filename + "-inc.eps" + " 2>&1";
		#else
		string pdflatex_manual_str = EPSTOPDF_PATH + " --gscmd=" + GHOSTSCRIPT_PATH + " --outfile=" + output_filename + "-inc-eps-converted-to.pdf " + output_filename + "-inc.eps" + " 2>&1";
        #endif

        FILE* pdflatex_manual;
        #if WINDOWS_OS
        pdflatex_manual = _popen(pdflatex_manual_str.c_str(), "r");
        #else
        pdflatex_manual = popen(pdflatex_manual_str.c_str(), "r");
        #endif

		while(fgets(buff, sizeof(buff), pdflatex_manual)!=NULL)
        {
        	if(DEBUG_MANUAL_PATH)
        	{cout << buff << endl;}
			#if WINDOWS_OS
			compare = string(buff).substr(0,EPSTOPDF_PATH_compare.length());
        	if(buff[0] == error_char || EPSTOPDF_PATH_compare == compare)
        	#else
            if(buff[0] == error_char || (buff[0] == 's' && buff[1] == 'h'))
            #endif
            {
				if(!ERROR_BOOL)
                {
                    cout << endl;
                    ERROR_BOOL = true;
                }
                cout << "ERROR EPSTOPDF: ";
                cout << buff;
            }
            #if WINDOWS_OS
            else if ( buff[0] == '\'')
            {
            	if(!ERROR_BOOL)
                {
                    cout << endl;
                    ERROR_BOOL = true;
                }
                cout << "ERROR EPSTOPDF: " << EPSTOPDF_PATH << " NOT FOUND!" << endl;
			}
            #endif
        }
        #if WINDOWS_OS
        _pclose(pdflatex_manual);
        #else
        pclose(pdflatex_manual);
        #endif

        string pdflatex_str;
        #if WINDOWS_OS
        if(folder_name_bool)
        {
            pdflatex_str = LATEX2PDFCOMPILER_PATH2 + " --interaction=nonstopmode --output-directory=" + folder_name + " " + scriptex + " 2>&1";
        }
        else
        {
            pdflatex_str = LATEX2PDFCOMPILER_PATH2 + " --interaction=nonstopmode " + scriptex + " 2>&1";
        }
        #else
        if(folder_name_bool)
        {
            pdflatex_str = LATEX2PDFCOMPILER_PATH + " --interaction=nonstopmode --output-directory=" + folder_name + " " + scriptex + " 2>&1";
        }
        else
        {
            pdflatex_str = LATEX2PDFCOMPILER_PATH + " --interaction=nonstopmode " + scriptex + " 2>&1";
        }
        #endif

        FILE* comp_tex;
        #if WINDOWS_OS
        comp_tex = _popen(pdflatex_str.c_str(), "r");
        #else
        comp_tex = popen(pdflatex_str.c_str(), "r");
        #endif
        while(fgets(buff, sizeof(buff), comp_tex)!=NULL)
        {
        	if(DEBUG_MANUAL_PATH)
        	{cout << buff << endl;}
        	#if WINDOWS_OS
			compare = string(buff).substr(0,LATEX2PDFCOMPILER_PATH_compare.length());
        	if(buff[0] == error_char || LATEX2PDFCOMPILER_PATH_compare == compare)
        	#else
            if(buff[0] == error_char || (buff[0] == 's' && buff[1] == 'h'))
            #endif
            {
                if(!ERROR_BOOL)
                {
                    cout << endl;
                    ERROR_BOOL = true;
                }
                cout << "ERROR PDFLATEX: ";
                cout << buff;
            }
            #if WINDOWS_OS
            else if ( buff[0] == '\'')
            {
            	if(!ERROR_BOOL)
                {
                    cout << endl;
                    ERROR_BOOL = true;
                }
                cout << "ERROR PDFLATEX: " << LATEX2PDFCOMPILER_PATH << " NOT FOUND!" << endl;
			}
            #endif
        }
        #if WINDOWS_OS
        _pclose(comp_tex);
        #else
        pclose(comp_tex);
        #endif
        
    }
    else
    {
    	#if WINDOWS_OS
    	string LATEX2PDFCOMPILER2 = "\"" + LATEX2PDFCOMPILER + "\"";
    	string compare;
    	string LATEX2PDFCOMPILER_compare = "'" + LATEX2PDFCOMPILER2 + "'";
    	#endif

        string pdflatex_str;
    	#if WINDOWS_OS
        if(folder_name_bool)
        {
            pdflatex_str = LATEX2PDFCOMPILER2 + " --interaction=nonstopmode --output-directory=" + folder_name + " " + scriptex + " 2>&1";
        }
        else
        {
            pdflatex_str = LATEX2PDFCOMPILER2 + " --interaction=nonstopmode " + scriptex + " 2>&1";
        }
        #else
        if(folder_name_bool)
        {
            pdflatex_str = LATEX2PDFCOMPILER + " --interaction=nonstopmode --output-directory=" + folder_name + " " + scriptex + " 2>&1";
        }
        else
        {
            pdflatex_str = LATEX2PDFCOMPILER + " --interaction=nonstopmode " + scriptex + " 2>&1";
        }
        #endif

        FILE* comp_tex;
        #if WINDOWS_OS
        comp_tex = _popen(pdflatex_str.c_str(), "r");
        #else
        comp_tex = popen(pdflatex_str.c_str(), "r");
        #endif
        while(fgets(buff, sizeof(buff), comp_tex)!=NULL)
        {
        	if(DEBUG_MANUAL_PATH)
        	{cout << buff << endl;}
        	#if WINDOWS_OS
			compare = string(buff).substr(0,LATEX2PDFCOMPILER_compare.length());
        	if(buff[0] == error_char || LATEX2PDFCOMPILER_compare == compare)
        	#else
            if(buff[0] == error_char || (buff[0] == 's' && buff[1] == 'h'))
            #endif
            {
                if(!ERROR_BOOL)
                {
                    cout << endl;
                    ERROR_BOOL = true;
                }
                cout << "ERROR PDFLATEX: ";
                cout << buff;
            }
            #if WINDOWS_OS
            else if ( buff[0] == '\'')
            {
            	if(!ERROR_BOOL)
                {
                    cout << endl;
                    ERROR_BOOL = true;
                }
                cout << "ERROR PDFLATEX: " << LATEX2PDFCOMPILER << " NOT FOUND!" << endl;
			}
            #endif
        }
        #if WINDOWS_OS
        _pclose(comp_tex);
        #else
        pclose(comp_tex);
        #endif

         //cout << endl << pdflatex_str << endl;
    }

    FILE* delete_files = popen(deletefiles.c_str(), "r");
    #if WINDOWS_OS
    _pclose(delete_files);
    #else
    pclose(delete_files);
    #endif

    if(!ERROR_BOOL)
    {
        cout << "OK!" << endl;
    }
    else
    {
        cout << "Failed to generate " << output_filename << ".pdf!\n\n";
    }


    //cout << deletefiles << endl;
}



//#if WINDOWS_OS

//#else
void exec_bundle_files (string *files_copy, int n_files_copy, string *files_move, int n_files_move, string folder_path)
{
    list<string> files_copy_list(files_copy, files_copy + n_files_copy);
    files_copy_list.sort();
    files_copy_list.unique();

    list<string> files_move_list(files_move, files_move + n_files_move);
    files_move_list.sort();
    files_move_list.unique();
    //cout << endl << endl;

    unsigned long p = folder_path.rfind("/");
    unsigned long p2 = folder_path.rfind("\\");
    if(p == folder_path.length()-1)
    {
        folder_path = folder_path.substr(0,p);
    }
    else if(p2 == folder_path.length()-1)
    {
    	folder_path = folder_path.substr(0,p2);
	}

    string new_folder = "mkdir " + folder_path + " 2>&1";
    FILE* commands;
    #if WINDOWS_OS
    commands = _popen(new_folder.c_str(), "r");
    #else
    commands = popen(new_folder.c_str(), "r");
    #endif

    #if WINDOWS_OS
    _pclose(commands);
    #else
    pclose(commands);
    #endif


    #if WINDOWS_OS
    string copy_files = "";
    #else
    string copy_files = "cp -p ";
    #endif

    for (list<string>::iterator it=files_copy_list.begin(); it!=files_copy_list.end(); ++it)
    {
        if((*it) == PLOT_FILENAME_DEFAULT)
        {continue;}

        #if WINDOWS_OS
		copy_files = "copy /Y " + ReplaceAll((*it),"/", "\\") + " " + ReplaceAll(folder_path, "/", "\\");
		commands = _popen(copy_files.c_str(), "r");
		_pclose(commands);
		#else
        copy_files += (*it) + " ";
        #endif
    }

    #if WINDOWS_OS
    #else
    copy_files += folder_path;
    // copy_files += folder_path + "2>/dev/null";
    commands = popen(copy_files.c_str(), "r");
    pclose(commands);
    #endif

    #if WINDOWS_OS
    string move_files = "";
    #else
    string move_files = "mv ";
    #endif
    for (list<string>::iterator it=files_move_list.begin(); it!=files_move_list.end(); ++it)
    {
    	#if WINDOWS_OS
		move_files = "move /Y " + ReplaceAll((*it),"/", "\\") + " " + ReplaceAll(folder_path, "/", "\\");
		commands = _popen(move_files.c_str(), "r");
		_pclose(commands);
		#else
        move_files += (*it) + " ";
        #endif
    }
    move_files += folder_path;

    #if WINDOWS_OS
    #else
    commands = popen(move_files.c_str(), "r");
    pclose(commands);
    #endif
}
//#endif


/* -----------------------------------------------------------------------------------------*/

/* -----------------------------------------------------------------------------------------*/

/* -----------------------------------------------------------------------------------------*/

//FUNCTION TO CONVERT A VARIABLE OUTPUT STRINGSTREAM TO A STRING
template <typename T> string conv_string(T var)
{
    stringstream ss;
    ss << var;
    return ss.str();
}












/* -----------------------------------------------------------------------------------------*/

/* -----------------------------------------------------------------------------------------*/

/* -----------------------------------------------------------------------------------------*/

//CLASS HEADER_GNUPLOT

int header_gnuplot::_cont_plots = 0;

/* -----------------------------------------------------------------------------------------*/

/* -----------------------------------------------------------------------------------------*/

/* -----------------------------------------------------------------------------------------*/






/* -----------------------------------------------------------------------------------------*/

/* -----------------------------------------------------------------------------------------*/

/* -----------------------------------------------------------------------------------------*/

//CLASS GNUP2D




/* -----------------------------------------------------------------------------------------*/

/* -----------------------------------------------------------------------------------------*/

/* -----------------------------------------------------------------------------------------*/

//CLASS GNUPLOT2D



int Gnuplot2D::_n=0;





/* -----------------------------------------------------------------------------------------*/

/* -----------------------------------------------------------------------------------------*/

/* -----------------------------------------------------------------------------------------*/

//CLASS GNUP3D



/* -----------------------------------------------------------------------------------------*/

/* -----------------------------------------------------------------------------------------*/

/* -----------------------------------------------------------------------------------------*/

//CLASS GNUPLOT3D




int Gnuplot3D::_n=0;


/* -----------------------------------------------------------------------------------------*/

/* -----------------------------------------------------------------------------------------*/

/* -----------------------------------------------------------------------------------------*/

/* -----------------------------------------------------------------------------------------*/

/* -----------------------------------------------------------------------------------------*/

//FUNCTIONS DEFINITION

/* -----------------------------------------------------------------------------------------*/

/* -----------------------------------------------------------------------------------------*/

/* -----------------------------------------------------------------------------------------*/

/* -----------------------------------------------------------------------------------------*/

/* -----------------------------------------------------------------------------------------*/




//PLOTBASE FUNCTIONS

plotbase::plotbase(int color_gnu)
{
    _title_bool = false;
    _lines = true;
    _points = false;
    _color_gnuplot = color_gnu;
    _color_rgb_bool = false;
    _parametric = false;
    _type_or_style = 1;
    _size_width = 1.0;
    _palette = false;
    _palette_column = 2;
    _pm3d = false;
    _dashtype_string_bool = false;
    _dashtype_int = 1;
    _dashtype_string = "";
    _plotstring_custom_bool = false;
    _vectors = false;
    _vector_headsize[0] = 0.1;
    _vector_headsize[1] = 20.0;
    _vector_headfilled = true;
}
void plotbase::set_filename (string filename)
{
    _filename = filename;
}
void plotbase::set_columns (int col1, int col2, int col3, int col4, int col5, int col6)
{
    _columns[0]=col1;
    _columns[1]=col2;
    _columns[2]=col3;
    _columns[3]=col4;
    _columns[4]=col5;
    _columns[5]=col6;
}

/*
void plotbase::set_one_column (int column_index, int column_value)
{
    if(column_index <= 0)
    { column_index = 1; }
    _columns[column_index - 1] = column_value;
}
*/

void plotbase::set_color_gnuplot(int color_gnuplot)
{
    _palette = false;
    _pm3d = false;
    _color_rgb_bool = false;
    _color_gnuplot = color_gnuplot;
}

void plotbase::set_color_rgb (string color_rgb)
{
    _palette = false;
    _pm3d = false;
    _color_rgb_bool = true;
    _color_rgb = color_rgb;
}
void plotbase::set_title (string title)
{
    _title_bool = true;
    _title = title;
}
void plotbase::set_with_points (double point_size, int point_type)
{
    _lines = false;
    _points = true;
    _vectors = false;
    set_type_or_style(point_type);
    set_size_or_width(point_size);
}
void plotbase::set_with_lines (double line_width, int line_style)
{
    _lines = true;
    _points = false;
    _vectors = false;
    set_type_or_style(line_style);
    set_size_or_width(line_width);
}

void plotbase::set_with_vectors(double line_width, int line_style)
{
    _lines = false;
    _points = false;
    _vectors = true;
    set_type_or_style(line_style);
    set_size_or_width(line_width);
}
void plotbase::set_vector_headsize(double length, double angle)
{
    _vector_headsize[0] = length;
    _vector_headsize[1] = angle;
}
void plotbase::set_vector_headfilled(bool filled)
{
    _vector_headfilled = filled;
}

void plotbase::set_dashtype (int dash_pattern)
{
    _dashtype_string_bool = false;
    if(dash_pattern>0)
    {
        _dashtype_int = dash_pattern;
        if(_lines)
        {set_type_or_style(1);}
    }
    else
    {
        cout << "ERROR: DASH TYPE INVALID, DASH TYPE MUST BE > 0" << endl;
    }
}

void plotbase::set_dashtype (string custom_dash_pattern)
{
    _dashtype_string_bool = true;
    _dashtype_string = custom_dash_pattern;
    if(_lines)
    {set_type_or_style(1);}
}

void plotbase::set_parametric (void)
{
    _parametric = true;
}
bool plotbase::get_parametric (void)
{
    return _parametric;
}

string plotbase::get_filename (void)
{
    return _filename;
}

void plotbase::set_type_or_style (int point_type_or_line_style)
{
    _type_or_style = point_type_or_line_style;
}

void plotbase::set_size_or_width (double point_size_or_line_width)
{
    _size_width = point_size_or_line_width;
}

void plotbase::set_palette (int function_column)
{
    _palette_column = function_column;
    _color_rgb_bool = false;
    _pm3d = false;
    _palette = true;
}

void plotbase::set_pm3d (int function_column)
{
    _palette_column = function_column;
    _color_rgb_bool = false;
    _palette = false;
    _pm3d = true;
}

void plotbase::set_plot_custom(string plotstring_custom)
{
    _plotstring_custom_bool = true;
    _plotstring_custom = plotstring_custom;
}

void plotbase::set_color_rgb_or_option (string opt)
{
    if (opt == "palette")
    {set_palette(_palette_column);}
    else if(opt == "pm3d")
    {set_pm3d(_palette_column);}
    else{set_color_rgb(opt);}
}


string plotbase::end_of_plot (void)
{
    string plotstr = "";

    if(_title_bool)
    {plotstr += "title '" + _title + "' ";}
    else{plotstr += "notitle ";}


    if(_pm3d)
    {
        plotstr += "w pm3d";
        return plotstr;
    }
    else if(_lines)
    {
        plotstr += "w l lt " + conv_string(_type_or_style) + " lw " + conv_string(_size_width) + " ";
        if(_dashtype_string_bool)
        {
            plotstr += "dt '" + _dashtype_string + "' ";
        }
        else
        {
            plotstr += "dt " + conv_string(_dashtype_int) + " ";
        }
    }
    else if(_points)
    {
        plotstr += "w p pt " + conv_string(_type_or_style) + " ps " + conv_string(_size_width) + " ";
    }
    else if(_vectors)
    {
        plotstr += "with vectors";
        plotstr += " head size " + conv_string(_vector_headsize[0]) + "," + conv_string(_vector_headsize[1]) + " ";
        if(_vector_headfilled)
        {
            plotstr += "filled ";
        }
        else
        {
            plotstr += "nofilled ";
        }
        plotstr += "lt " + conv_string(_type_or_style) + " lw " + conv_string(_size_width) + " ";
        if(_dashtype_string_bool)
        {
            plotstr += "dt '" + _dashtype_string + "' ";
        }
        else
        {
            plotstr += "dt " + conv_string(_dashtype_int) + " ";
        }
    }


    if (_palette)
    {plotstr += "lc palette";}
    else if(_color_rgb_bool)
    {plotstr += "lc rgb '" + _color_rgb + "'";}
    else {plotstr += "lc " + conv_string(_color_gnuplot);}
    
    return plotstr;
}




/* -----------------------------------------------------------------------------------------*/

/* -----------------------------------------------------------------------------------------*/

/* -----------------------------------------------------------------------------------------*/




//PLOTSTRONG2D_SINGLE FUNCTIONS

plotstring2d_single::plotstring2d_single(void) : plotbase(0)
{
    //_filename = PLOT_FILENAME_DEFAULT;
    set_filename(PLOT_FILENAME_DEFAULT);
    set_columns(1,2);
    _straight_line_bool = false;
    _straight_line = "";
    _palette_column = 2;
    
    _x2y2bool = false;
    _xyaxes[0] = 1;
    _xyaxes[1] = 1;
}
void plotstring2d_single::set_plot(string filename, int col1, int col2, int color_gnuplot)
{
    set_filename(filename);
    set_columns(col1,col2);
    set_color_gnuplot(color_gnuplot);
}

void plotstring2d_single::set_plot(string filename, int col1, int col2, int col3, int col4, int color_gnuplot)
{
    set_filename(filename);
    set_columns(col1,col2,col3,col4);
    set_color_gnuplot(color_gnuplot);
}

void plotstring2d_single::set_plot(string filename, int col1, int col2, string color_rgb)
{
    set_filename(filename);
    set_columns(col1,col2);
    //if (color_rgb == "palette")
    //{set_palette();}
    //else{set_color_rgb(color_rgb);}
    set_color_rgb_or_option(color_rgb);
}

void plotstring2d_single::set_plot(string filename, int col1, int col2, int col3, int col4, string color_rgb)
{
    set_filename(filename);
    set_columns(col1,col2,col3,col4);
    //if (color_rgb == "palette")
    //{set_palette();}
    //else{set_color_rgb(color_rgb);}
    set_color_rgb_or_option(color_rgb);
}

void plotstring2d_single::set_plot(string filename, double* x, double* y, long long number_of_points, int color_gnuplot)
{
    set_filename(filename);
    set_columns(1,2);
    set_color_gnuplot(color_gnuplot);

    fstream vet;
    vet.open(_filename.c_str(),ios::out|ios::trunc);
    vet << "# x   y" << endl;

    for(long long i=0; i<number_of_points; i++)
    {
        vet << x[i] << "   " << y[i] << endl;
    }
    vet.close();
}

void plotstring2d_single::set_plot(string filename, double* x, double* y, long long number_of_points, string color_rgb)
{
    set_filename(filename);
    set_columns(1,2);
    set_color_rgb_or_option(color_rgb);

    fstream vet;
    vet.open(_filename.c_str(),ios::out|ios::trunc);
    vet << "# x   y" << endl;

    for(long long i=0; i<number_of_points; i++)
    {
        vet << x[i] << "   " << y[i] << endl;
    }
    vet.close();
}


void plotstring2d_single::set_plot_straight_line(double coef_y, double coef_x, double b, int color_gnup)
{
    _straight_line_bool=true;
    set_filename(PLOT_FILENAME_DEFAULT);
    set_parametric();
    set_with_lines();
    set_color_gnuplot(color_gnup);
    stringstream ss;


    if (coef_y==0.0)
    {
        _straight_line = conv_string(-b) + "/(" + conv_string(coef_x) + "),t ";
    }
    else
    {
        _straight_line = "t,((t*(" + conv_string(coef_x) + ")+(" + conv_string(b) + "))/(" + conv_string(coef_y) + ")) ";
    }
}

void plotstring2d_single::set_plot_straight_line(double coef_y, double coef_x, double b, string color_rgb)
{
    _straight_line_bool=true;
    set_filename(PLOT_FILENAME_DEFAULT);
    set_parametric();
    set_with_lines();
    set_color_rgb_or_option(color_rgb);

    if (coef_y==0.0)
    {
        _straight_line = conv_string(-b) + "/(" + conv_string(coef_x) + "),t ";
    }
    else
    {
        _straight_line = "t,((t*(" + conv_string(coef_x) + ")+(" + conv_string(b) + "))/(" + conv_string(coef_y) + ")) ";
    }
}

void plotstring2d_single::set_xyaxes(int xaxis, int yaxis)
{
    if(xaxis > 2 || xaxis <1)
    {
        xaxis = 1;
    }
    
    if(yaxis > 2 || yaxis <1)
    {
        yaxis = 1;
    }
    
    _x2y2bool = true;
    _xyaxes[0] = xaxis;
    _xyaxes[1] = yaxis;
}

string plotstring2d_single::plotstring (void)
{
    if(_plotstring_custom_bool)
    {
        return _plotstring_custom;
    }
    
    string plotstr;
    
    if(_straight_line_bool)
    {
        plotstr = _straight_line;
        plotstr += plotbase::end_of_plot();
    }
    else
    {
        plotstr = "'" + _filename + "' ";
        if(_vectors)
        {
            plotstr += "using " + conv_string(_columns[0]) + ":" + conv_string(_columns[1]) + ":" + conv_string(_columns[2]) + ":" + conv_string(_columns[3]);// + " ";
        }
        else
        {
            plotstr += "using " + conv_string(_columns[0]) + ":" + conv_string(_columns[1]);// + " ";
        }
        if(_palette)
        {plotstr += ":" + conv_string(_palette_column);}
        plotstr += " ";

        plotstr += plotbase::end_of_plot();
    }
    
    if(_x2y2bool)
    {
        plotstr += " axes x" + conv_string(_xyaxes[0]) + "y" + conv_string(_xyaxes[1]);
    }
    
    return plotstr;
}



/* -----------------------------------------------------------------------------------------*/

/* -----------------------------------------------------------------------------------------*/

/* -----------------------------------------------------------------------------------------*/




//PLOTSTRING3D_SINGLE FUNCTIONS

plotstring3d_single::plotstring3d_single(void) : plotbase(0)
{
    //_filename = "You need to set the plots";
    set_filename(PLOT_FILENAME_DEFAULT);
    set_columns(1,2,3);
    _plane_bool=false;
    _plane_str = "";
    _palette_column = 3;
}

void plotstring3d_single::set_plot(string filename, int col1, int col2, int col3, int color_gnup)
{
    set_filename(filename);
    set_columns(col1,col2,col3);
    set_color_gnuplot(color_gnup);
}

void plotstring3d_single::set_plot(string filename, int col1, int col2, int col3, int col4, int col5, int col6, int color_gnup)
{
    set_filename(filename);
    set_columns(col1,col2,col3,col4,col5,col6);
    set_color_gnuplot(color_gnup);
}

void plotstring3d_single::set_plot(string filename, int col1, int col2, int col3, string color_rgb)
{
    set_filename(filename);
    set_columns(col1,col2,col3);
    set_color_rgb_or_option(color_rgb);
}

void plotstring3d_single::set_plot(string filename, int col1, int col2, int col3, int col4, int col5, int col6, string color_rgb)
{
    set_filename(filename);
    set_columns(col1,col2,col3,col4,col5,col6);
    set_color_rgb_or_option(color_rgb);
}

void plotstring3d_single::set_plot(string filename, double* x, double* y, double* z, long long number_of_points, int color_gnup)
{
    set_filename(filename);
    set_columns(1,2,3);
    set_color_gnuplot(color_gnup);

    fstream vet;
    vet.open(_filename.c_str(),ios::out|ios::trunc);
    vet << "# x   y   z" << endl;

    for(long long i=0; i<number_of_points; i++)
    {
        vet << x[i] << "   " << y[i] << "   " << z[i] << endl;
    }
    vet.close();
}

void plotstring3d_single::set_plot(string filename, double* x, double* y, double* z, long long number_of_points, string color_rgb)
{
    set_filename(filename);
    set_columns(1,2,3);
    set_color_rgb_or_option(color_rgb);

    fstream vet;
    vet.open(_filename.c_str(),ios::out|ios::trunc);
    vet << "# x   y   z" << endl;

    for(long long i=0; i<number_of_points; i++)
    {
        vet << x[i] << "   " << y[i] << "   " << z[i] << endl;
    }
    vet.close();
}

void plotstring3d_single::set_plot_plane(double coef_x, double coef_y, double coef_z, double b, int color_gnup)
{
    _plane_bool = true;
    set_filename(PLOT_FILENAME_DEFAULT);
    set_parametric();
    set_with_lines();
    set_color_gnuplot(color_gnup);
    double mult = 1.0;

    if(coef_z!=0.0)
    {
        if(fabs(coef_x)>=fabs(coef_y) && fabs(coef_x)>=mult*fabs(coef_z))
        {
            _plane_str = "((-u*(" + conv_string(coef_y) + ") - v*(" + conv_string(coef_z) + ") + (" + conv_string(b) + "))/(" + conv_string(coef_x) + ")),u,v ";
        }
        else if (fabs(coef_y) >= mult*fabs(coef_z))
        {
            _plane_str = "u,((-u*(" + conv_string(coef_x) + ") - v*(" + conv_string(coef_z) + ") + (" + conv_string(b) + "))/(" + conv_string(coef_y) + ")),v ";
        }
        else
        {
            _plane_str = "u,v,((-u*(" + conv_string(coef_x) + ") - v*(" + conv_string(coef_y) + ") + (" + conv_string(b) + "))/(" + conv_string(coef_z) + ")) ";
        }
    }
    else if (coef_y!=0.0)
    {
        if(fabs(coef_x) >= mult*fabs(coef_y))
        {
            _plane_str = "((-u*(" + conv_string(coef_y) + ") + (" + conv_string(b) + "))/(" + conv_string(coef_x) + ")),u,v ";
        }
        else
        {
            _plane_str = "u,((-u*(" + conv_string(coef_x) + ") + (" + conv_string(b) + "))/(" + conv_string(coef_y) + ")),v ";
        }
    }
    else
    {
        _plane_str = "((" + conv_string(b) + ")/(" + conv_string(coef_x) + ")),u,v ";
    }
}

void plotstring3d_single::set_plot_plane(double coef_x, double coef_y, double coef_z, double b, string color_rgb)
{
    _plane_bool = true;
    set_filename(PLOT_FILENAME_DEFAULT);
    set_parametric();
    set_with_lines();
    set_color_rgb_or_option(color_rgb);
    double mult = 1.0;

    if(coef_z!=0.0)
    {
        if(fabs(coef_x)>=fabs(coef_y) && fabs(coef_x)>=mult*fabs(coef_z))
        {
            _plane_str = "((-u*(" + conv_string(coef_y) + ") - v*(" + conv_string(coef_z) + ") + (" + conv_string(b) + "))/(" + conv_string(coef_x) + ")),u,v ";
        }
        else if (fabs(coef_y) >= mult*fabs(coef_z))
        {
            _plane_str = "u,((-u*(" + conv_string(coef_x) + ") - v*(" + conv_string(coef_z) + ") + (" + conv_string(b) + "))/(" + conv_string(coef_y) + ")),v ";
        }
        else
        {
            _plane_str = "u,v,((-u*(" + conv_string(coef_x) + ") - v*(" + conv_string(coef_y) + ") + (" + conv_string(b) + "))/(" + conv_string(coef_z) + ")) ";
        }
    }
    else if (coef_y!=0.0)
    {
        if(fabs(coef_x) >= mult*fabs(coef_y))
        {
            _plane_str = "((-u*(" + conv_string(coef_y) + ") + (" + conv_string(b) + "))/(" + conv_string(coef_x) + ")),u,v ";
        }
        else
        {
            _plane_str = "u,((-u*(" + conv_string(coef_x) + ") + (" + conv_string(b) + "))/(" + conv_string(coef_y) + ")),v ";
        }
    }
    else
    {
        _plane_str = "((" + conv_string(b) + ")/(" + conv_string(coef_x) + ")),u,v ";
    }
}


string plotstring3d_single::plotstring (void)
{
    if(_plotstring_custom_bool)
    {
        return _plotstring_custom;
    }
    
    string plotstr;

    if(_plane_bool)
    {
        plotstr = _plane_str;
        plotstr += plotbase::end_of_plot();
    }
    else
    {
        plotstr = "'" + _filename + "' ";
        if(_vectors)
        {
            plotstr += "using " + conv_string(_columns[0]) + ":" + conv_string(_columns[1]) + ":" + conv_string(_columns[2]) + ":" + conv_string(_columns[3]) + ":" + conv_string(_columns[4]) + ":" + conv_string(_columns[5]);// + " ";
        }
        else
        {
            plotstr += "using " + conv_string(_columns[0]) + ":" + conv_string(_columns[1]) + ":" + conv_string(_columns[2]);// + " ";
        }
        if(_palette || _pm3d)
        {plotstr += ":" + conv_string(_palette_column);}

        plotstr += " ";

        plotstr += plotbase::end_of_plot();
    }


    return plotstr;
}



/* -----------------------------------------------------------------------------------------*/

/* -----------------------------------------------------------------------------------------*/

/* -----------------------------------------------------------------------------------------*/



//HEADER_GNUPLOT FUNCTIONS

header_gnuplot::header_gnuplot (void)
{
    test_path();
    _cont_plots++;

    set_term_code(TERM_DEFAULT);
    _linewidth = 1.0;
    _font = FONT_DEFAULT;
    _font_size = FONT_SIZE_DEFAULT;
    _font_size_changed = false;

    _graph_size_pdflatex[0] = GRAPH_SIZE_DEFAULT_PDFLATEX[0];
    _graph_size_pdflatex[1] = GRAPH_SIZE_DEFAULT_PDFLATEX[1];
    
    bool _added_latex_packages = false;
    string _latex_packages = "";
}

void header_gnuplot::set_terminal (int term1)
{
    string termin = "";
    switch (term1) {
        case TERM_EPS:
            termin = "postscript eps color dashed";
            _term_code = TERM_EPS;
            break;

        case TERM_X11:
            termin = "x11 dashed";
            _term_code = TERM_X11;
            break;

        case TERM_AQUA:
            termin = "aqua dashed";
            _term_code = TERM_AQUA;
            break;

        case TERM_WXT:
            termin = "wxt dashed persist";
            _term_code = TERM_WXT;
            break;

        case TERM_QT:
            termin = "qt dashed";
            _term_code = TERM_QT;
            break;

        case TERM_WINDOWS:
            termin = "windows dashed";
            _term_code = TERM_WINDOWS;
            break;

        case TERM_PDFLATEX_EPS:
//            termin = "epslatex standalone color dashed colortext size " + conv_string(_graph_size_pdflatex[0]) + "cm," + conv_string(_graph_size_pdflatex[1]) + "cm header \\\n\"\\\\usepackage[T1]{fontenc} \\\\usepackage[utf8]{inputenc} \\\\usepackage{epstopdf} \\\\nonstopmode";
            termin = "epslatex standalone color dashed colortext size " + conv_string(_graph_size_pdflatex[0]) + "cm," + conv_string(_graph_size_pdflatex[1]) + "cm header \\\n\" \\\\usepackage{epstopdf} \\\\nonstopmode";
            
            if(_added_latex_packages)
            {
                termin += " " + _latex_packages;
            }
            termin += "\"";
            
            _term_code = TERM_PDFLATEX_EPS;
            break;

        case TERM_PDFLATEX_CAIRO:
//            termin = "cairolatex standalone color dashed colortext size " + conv_string(_graph_size_pdflatex[0]) + "cm," + conv_string(_graph_size_pdflatex[1]) + "cm header \\\n\"\\\\usepackage[T1]{fontenc} \\\\usepackage[utf8]{inputenc} \\\\usepackage{epstopdf} \\\\nonstopmode";
            termin = "cairolatex standalone color dashed colortext size " + conv_string(_graph_size_pdflatex[0]) + "cm," + conv_string(_graph_size_pdflatex[1]) + "cm header \\\n\" \\\\usepackage{epstopdf} \\\\nonstopmode";
            
            if(_added_latex_packages)
            {
                termin += " " + _latex_packages;
            }
            termin += "\"";
            
            _term_code = TERM_PDFLATEX_CAIRO;
            break;

        default:
            termin = "postscript eps color dashed";
            _term_code = TERM_EPS;
            break;
    }

    _terminal = termin;
    //set_terminal_custom(termin);
}

void header_gnuplot::set_terminal_custom (string terminal)
{
    _terminal = terminal;
}

void header_gnuplot::set_font (string font)
{
    _font = font;
}

void header_gnuplot::set_linewidth (double linewidth)
{
    _linewidth = linewidth;
}

void header_gnuplot::set_font_size (int font_size)
{
    _font_size_changed = true;
    _font_size = font_size;
}

string header_gnuplot::terminal_gnuplot (void)
{
    string str;
    str = "set term " + _terminal + "; \n";
    int tam_final = _font_size;
    if((_term_code == TERM_PDFLATEX_EPS) || (_term_code == TERM_PDFLATEX_CAIRO))
    {
        if(!_font_size_changed)
        {
            tam_final = FONT_SIZE_DEFAULT_PDFLATEX;
        }
    }
    str += "set termoption font '" + _font + "," + conv_string(tam_final) + "'; \n";
    str += "set termoption enhanced; \n";

    return str;
}


void header_gnuplot::set_term_code (int terminal1)
{
    switch (terminal1) {
        case TERM_EPS:
            set_term_eps();
            break;

        case TERM_X11:
            set_term_x11();
            break;

        case TERM_AQUA:
            set_term_aqua();
            break;

        case TERM_WXT:
            set_term_wxt();
            break;

        case TERM_QT:
            set_term_qt();
            break;

        case TERM_WINDOWS:
            set_term_windows();
            break;

        case TERM_PDFLATEX_EPS:
            set_term_pdflatex_eps();
            break;

        case TERM_PDFLATEX_CAIRO:
            set_term_pdflatex_cairo();
            break;

        default:
            set_term_eps();
            break;
    }
}

string header_gnuplot::header (void)
{
    string str;

    str = terminal_gnuplot() + "\n";

    if(_term_code == TERM_EPS)
    {
        str += "set output '" + _output_filename + ".eps';";
    }
    else if((_term_code == TERM_PDFLATEX_EPS) || (_term_code == TERM_PDFLATEX_CAIRO))
    {
        str += "set output '" + ReplaceAll(_output_filename,"\\", "/") + ".tex';";
        //LATEX does not work with \ as path divider
    }

    str += "\n";
    //str += "set termoption enhanced;\n";
    //str += "set termoption font " + fon
    str += "set encoding utf8;\n";
    str += "\n\n";

    return str;
}

void header_gnuplot::set_graph_size_pdflatex (double widht_in_cm, double height_in_cm)
{
    _graph_size_pdflatex[0] = widht_in_cm;
    _graph_size_pdflatex[1] = height_in_cm;
    set_term_code(_term_code);
}

void header_gnuplot::set_term_aqua (void)
{
    set_terminal(TERM_AQUA);
}

void header_gnuplot::set_term_x11 (void)
{
    set_terminal(TERM_X11);
}

void header_gnuplot::set_term_eps (void)
{
    set_terminal(TERM_EPS);
}

void header_gnuplot::set_term_windows (void)
{
    set_terminal(TERM_WINDOWS);
}

void header_gnuplot::set_term_wxt (void)
{
    set_terminal(TERM_WXT);
}

void header_gnuplot::set_term_qt (void)
{
    set_terminal(TERM_QT);
}

void header_gnuplot::set_term_pdflatex_eps(void)
{
    set_terminal(TERM_PDFLATEX_EPS);
}

void header_gnuplot::set_term_pdflatex_cairo(void)
{
    set_terminal(TERM_PDFLATEX_CAIRO);
}

void header_gnuplot::set_output_filename (string output_filename)
{
    #if WINDOWS_OS
    #else
    output_filename = ReplaceAll(output_filename,"\\", "/");
    #endif

    _output_filename = output_filename;
}

int header_gnuplot::get_terminal(void)
{
    return _term_code;
}

void header_gnuplot::add_latex_package (string latex_package)
{
    _added_latex_packages = true;
    _latex_packages += "\\" + latex_package + " ";
}


/* -----------------------------------------------------------------------------------------*/

/* -----------------------------------------------------------------------------------------*/

/* -----------------------------------------------------------------------------------------*/

//CONTROL_GNUPLOT FUNCTIONS

control_gnuplot::control_gnuplot (void)
{
    _file_init = false;
}
control_gnuplot::~control_gnuplot (void)
{
    if(_file_init)
    {
#if WINDOWS_OS
        //fprintf(_file, "quit\n");
#else
        fprintf(_file, "exit\n");
#endif

        fflush(_file);

#if WINDOWS_OS
        _pclose(_file);
#else
        pclose(_file);
#endif
    }
}
void control_gnuplot::send_command (string& script)
{
    if(_file_init)
    {
        fprintf(_file, script.c_str());
        fflush(_file);
    }
}

void control_gnuplot::send_command_replot (void)
{
    if(_file_init)
    {
        fprintf(_file, "\nreplot;\n");
        fflush(_file);
    }
}

void control_gnuplot::send_command_plot (string scrp)
{
    scrp = "load '" + scrp + "';\n";
    send_command(scrp);
}

void control_gnuplot::plot_ctr_gnuplot(string& filenam)
{
    if(_file_init)
    {
        send_command_plot(filenam);
    }
    else
    {
        _file_init = true;

#if WINDOWS_OS
        string str = "\"" + GNUPLOT_PATH + "\"" + " -persist";
        _file = _popen(str.c_str(),"w");
#else
        string str = GNUPLOT_PATH + " -persist";
        _file = popen(str.c_str(),"w");
#endif

        send_command_plot(filenam);
    }
}


/* -----------------------------------------------------------------------------------------*/

/* -----------------------------------------------------------------------------------------*/

/* -----------------------------------------------------------------------------------------*/

//GNUP2D FUNCTIONS

gnup2D::gnup2D (int number_of_curves)
{
    _grid = true;
    _sizeratio_bool = false;
    _sizeratio = -1.0;
    _sizesquare = false;
    _xtics_bool = false;
    _xtics = 0.1;
    _ytics_bool = false;
    _ytics = 0.1;
    _xrange_bool = false;
    _xrange[0]=-1.0;
    _xrange[1]=1.0;
    _yrange_bool = false;
    _yrange[0]=-1.0;
    _yrange[1]=1.0;
    _title_bool = false;
    _title = "graph title";
    _xlabel_bool = false;
    _xlabel = "x axis";
    _ylabel_bool = false;
    _ylabel = "y axis";

    _cbrange_bool = false;
    _cbrange[0]=-1.0;
    _cbrange[1]= 1.0;

    _parametric = false;
    _trange_bool = false;
    _trange[0]=-1.0;
    _trange[1]=1.0;

    _key_bool = false;
    _key_string[0] = "right"; //left, center or right
    _key_string[1] = "top"; //top, center or bottom
    
    _add_line_bool = false;
    _added_line = "";

    if(number_of_curves < 1)
    { number_of_curves = 1; }
    _n_plots = number_of_curves;
    curve = new plotstring2d_single[_n_plots];
}

gnup2D::~gnup2D (void)
{
    delete[] curve;
}

string gnup2D::generate_plot2d (void)
{
    string str="";

    if (!_grid) {str += "#";}
    str += "set style line 1 lt 1 dt 3 lc rgb \'black\'; \n";
    if (!_grid) {str += "#";}
    str += "set grid ls 1; \n"; //lt 1 dt 3 lc 0;\n";
    str += "\n";

    if(!_sizeratio_bool){str += "#";}
    str += "set size ratio " + conv_string(_sizeratio) + ";\n";
    if(!_sizesquare){str += "#";}
    str += "set size square;\n";
    str += "\n";

    if (!_xtics_bool) {str += "#";}
    str += "set xtics " + conv_string(_xtics) + ";\n";
    if (!_ytics_bool) {str += "#";}
    str += "set ytics " + conv_string(_ytics) + ";\n";
    str += "\n";

    if (!_xrange_bool) {str += "#";}
    str += "set xrange [" + conv_string(_xrange[0]) + ":" + conv_string(_xrange[1]) + "];\n";
    if (!_yrange_bool) {str += "#";}
    str += "set yrange [" + conv_string(_yrange[0]) + ":" + conv_string(_yrange[1]) + "];\n";
    str += "\n";

    if (!_cbrange_bool) {str += "#";}
    str += "set cbrange [" + conv_string(_cbrange[0]) + ":" + conv_string(_cbrange[1]) + "];\n";
    str += "set palette rgbformulae 33,13,10;\n";

    str += "\n";
    if (!_title_bool) {str += "#";}
    str += "set title '" + _title + "';\n";

    if(!_key_bool) {str += "#";}
    str += "set key " + _key_string[0] + " " + _key_string[1] + ";\n\n";

    if (!_xlabel_bool) {str += "#";}
    str += "set xlabel '" + _xlabel + "';\n";

    if (!_ylabel_bool) {str += "#";}
    str += "set ylabel '" + _ylabel + "';\n";
    str += "\n";

    if(_parametric || get_parametric())
    {
        str += "set parametric;\n";
        if (!_trange_bool) {str += "#";}
        str += "set trange [" + conv_string(_trange[0]) + ":" + conv_string(_trange[1]) + "];\n\n";
    }
    
    if (_add_line_bool)
    {
        str += "#ADDED LINES:";
        str += _added_line + "\n\n";
    }
    
    str += "\n";
    str += "plot ";

    for(int i=0; i<_n_plots-1; i++)
    {
        str += curve[i].plotstring();
        str += ", \\\n";
    }
    str += curve[_n_plots-1].plotstring();
    str += ";";

    return str;
}

void gnup2D::set_number_of_curves (int number_of_curves)
{
    delete[] curve;
    _n_plots = number_of_curves;
    curve = new plotstring2d_single[_n_plots];
}

void gnup2D::unset_grid (void)
{
    _grid = false;
}

void gnup2D::set_sizeratio(double sratio)
{
    _sizeratio_bool = true;
    _sizeratio = sratio;
}

void gnup2D::set_sizesquare (void)
{
    _sizesquare = true;
}

void gnup2D::set_xtics(double xtics)
{
    _xtics_bool = true;
    _xtics = xtics;
}
void gnup2D::set_ytics(double ytics)
{
    _ytics_bool = true;
    _ytics = ytics;
}
void gnup2D::set_xytics (double xtics, double ytics)
{
    set_xtics(xtics);
    set_ytics(ytics);
}
void gnup2D::set_xrange (double x1, double x2)
{
    _xrange_bool = true;
    _xrange[0]=x1;
    _xrange[1]=x2;
}
void gnup2D::set_yrange (double y1, double y2)
{
    _yrange_bool = true;
    _yrange[0]=y1;
    _yrange[1]=y2;
}

void gnup2D::set_xyrange(double x1, double x2,double y1, double y2)
{
    set_xrange(x1, x2);
    set_yrange(y1, y2);
}

void gnup2D::set_title (string tit)
{
    _title_bool = true;
    _title = tit;
}

void gnup2D::set_xlabel (string xlab)
{
    _xlabel_bool=true;
    _xlabel = xlab;
}

void gnup2D::set_ylabel (string ylab)
{
    _ylabel_bool=true;
    _ylabel = ylab;
}

void gnup2D::set_xylabel (string xlab, string ylab)
{
    set_xlabel(xlab);
    set_ylabel(ylab);
}

bool gnup2D::get_parametric (void)
{
    bool ret = false;

    for(int i=0; i<_n_plots; i++)
    {
        if (curve[i].get_parametric())
        {
            ret = true;
            break;
        }
    }

    return ret;
}

//void gnup2D::set_parametric (void)
//{
//    _parametric = true;
//}

void gnup2D::set_trange (double t1, double t2)
{
    _trange_bool = true;
    _trange[0] = t1;
    _trange[1] = t2;
}

void gnup2D::set_cbrange (double cbmin, double cbmax)
{
    _cbrange_bool = true;
    _cbrange[0]=cbmin;
    _cbrange[1]=cbmax;
}

void gnup2D::set_key (string left_center_right, string top_center_bottom)
{
    _key_bool = true;
    _key_string[0] = left_center_right;
    _key_string[1] = top_center_bottom;
}

void gnup2D::add_string (string line)
{
    _add_line_bool = true;
    _added_line += "\n" + line;
}


/* -----------------------------------------------------------------------------------------*/

/* -----------------------------------------------------------------------------------------*/

/* -----------------------------------------------------------------------------------------*/

//GNUPLOT2D FUNCTIONS

Gnuplot2D::Gnuplot2D (int number_of_curves) : gnup2D(number_of_curves),header_gnuplot()
{
    _n++;
    _scriptname = "gnuplot2d_" + conv_string(_n) + ".txt";
    string ofi = "gnuplot2d_" + conv_string(_n);
    set_output_filename(ofi);
    _plotted = false;
    #if WINDOWS_OS
    //*_realtime_bool = false;
    #else
    _realtime_bool = (bool*) mmap(NULL, sizeof(*_realtime_bool), PROT_READ | PROT_WRITE,
                                 MAP_SHARED | MAP_ANON, -1, 0);
    *_realtime_bool = false;
    #endif

    _bundle_files_bool = false;
    _bundle_folder_path = "";
}

Gnuplot2D::~Gnuplot2D (void)
{
	#if WINDOWS_OS
	#else
    if(*_realtime_bool)
    {
        *_realtime_bool = false;
        if(!WINDOWS)
        {
            if(_term_code == TERM_WXT)
            {
                set_term_code(TERM_DEFAULT);
                plot_graph();
            }
        }
    }
    #endif

    //EXECUTES GNUPLOT AND PLOTS THE GRAPH
    if(!_plotted)
    {
        generate_script();
        int pid=-100;
        execute_script_gnuplot (_scriptname,pid);
        if((_term_code == TERM_PDFLATEX_EPS) || (_term_code == TERM_PDFLATEX_CAIRO))
        {
            pdflatex_exec(_output_filename,pid);
        }
    }

    if(_bundle_files_bool)
    {
        if(_term_code != TERM_PDFLATEX_EPS && _term_code != TERM_PDFLATEX_CAIRO)
        {
            #if WINDOWS_OS
            Sleep(1000);
            #else
            sleep(1);
            #endif
        }
        bundle_files_exec();
    }
}

void Gnuplot2D::generate_script (void)
{
    ofstream script;
    script.open(_scriptname.c_str(),ios::out|ios::trunc);
    script << "#Execute the 'cd' command on gnuplot to change the current directory to the directory the script is in" << endl << "#Execute the command: load '" << _scriptname << "'" << endl;

    script << "\n\n";
    script << "reset;" << endl;
    script << "\n\n";

    script << header();
    script << generate_plot2d();

    script << "\n\n" << endl;

    /*
    if(!WINDOWS)
    {
        script << "pause -1;" << endl; //Pause -1 allows for rotating the graph in x11 terminal
    }
    //*/
    script << "set output;";
    script.close();
}

void Gnuplot2D::set_scriptname (string scriptname)
{
    _scriptname = scriptname;
    
    #if WINDOWS_OS
    #else
    _scriptname = ReplaceAll(scriptname,"\\", "/");
    #endif
    
    unsigned long p = scriptname.rfind(".");
    if (p>0)
    {
        scriptname = scriptname.substr(0,p);
    }

    set_output_filename(scriptname);
}

void Gnuplot2D::bundle_files (string folder_path)
{
    #if WINDOWS_OS
    #else
    folder_path = ReplaceAll(folder_path,"\\", "/");
    #endif
    
    _bundle_files_bool = true;
    if(folder_path == "")
    {
        unsigned long p = _scriptname.rfind(".");
        if (p>0)
        {
            _bundle_folder_path = _scriptname.substr(0,p);
        }
    }
    else
    {
        _bundle_folder_path = folder_path;
    }
}

void Gnuplot2D::bundle_files_exec (void)
{
    int n_files_copy = _n_plots;
    int n_files_move = 1;
    string *files_copy;
    string *files_move;
    if(_term_code == TERM_EPS || _term_code == TERM_PDFLATEX_EPS || _term_code == TERM_PDFLATEX_CAIRO)
    {
        n_files_move = 2;
        string output_filename_and_extension = _output_filename;
        if(_term_code == TERM_EPS)
        {
            output_filename_and_extension += ".eps";
        }
        else
        {
            output_filename_and_extension += ".pdf";
        }

        files_move = new string[n_files_move];
        files_move[0] = _scriptname;
        files_move[1] = output_filename_and_extension;
    }
    else
    {
        files_move = new string[n_files_move];
        files_move[0] = _scriptname;
    }

    files_copy = new string[n_files_copy];
    for(int i=0; i<_n_plots; i++)
    {
        files_copy[i] = curve[i].get_filename();
    }

    exec_bundle_files(files_copy, n_files_copy, files_move, n_files_move, _bundle_folder_path);

    delete[] files_copy;
    delete[] files_move;
}

void Gnuplot2D::plot_graph (void)
{
    _plotted = true;
    generate_script();
    _process.plot_ctr_gnuplot(_scriptname);
    if((_term_code == TERM_PDFLATEX_EPS) || (_term_code == TERM_PDFLATEX_CAIRO))
    {
        pdflatex_exec(_output_filename);
    }
}

void Gnuplot2D::replot_graph (void)
{
    if(_plotted)
    {
        _process.send_command_replot();
    }
    else
    {
        plot_graph();
    }
}

void Gnuplot2D::plot_realtime (int t_milisec)
{
#if WINDOWS_OS
    cout << "plot_realtime NOT AVAILABLE TO WINDOWS" << endl;
#else
    if(t_milisec < 100)
    {
        t_milisec = 100;
    }

    unsigned int t = 1000*t_milisec;
    *_realtime_bool = true; //funcao desativada no momento

    plot_graph(); //se deixar so o replot dentro do fork, quando mudar o status de _plotted para true, nao vai fazer efeito fora do fork.
    if(fork()==0)
    {
        while (*_realtime_bool)
        {
            usleep(t);
            replot_graph();
        }
         _exit(0);
    }
#endif
}



/* -----------------------------------------------------------------------------------------*/

/* -----------------------------------------------------------------------------------------*/

/* -----------------------------------------------------------------------------------------*/

//GNUP3D FUNCTIONS

gnup3D::gnup3D (int number_of_curves)
{
    _view_bool = true;
    _view[0]=45;
    _view[1]=45;
    _grid = true;
    _viewequalxy = false;
    _viewequalxyz = false;
    _size_bool = false;
    _size[0] = 1.0;
    _size[1] = 1.0;
    _xtics_bool = false;
    _xtics = 0.1;
    _ytics_bool = false;
    _ytics = 0.1;
    _ztics_bool = false;
    _ztics = 0.1;
    _xrange_bool = false;
    _xrange[0] = -1.0;
    _xrange[1] = 1.0;
    _yrange_bool = false;
    _yrange[0] = -1.0;
    _yrange[1] = 1.0;
    _zrange_bool = false;
    _zrange[0] = -1.0;
    _zrange[1] = 1.0;
    _title_bool = false;
    _title = "graph title";
    _xlabel_bool = false;
    _xlabel = "x axis";
    _ylabel_bool = false;
    _ylabel = "y axis";
    _zlabel_bool = false;
    _zlabel = "z axis";

    _parametric = false;
    _urange_bool = false;
    _urange[0]=-1.0;
    _urange[1]= 1.0;
    _vrange_bool = false;
    _vrange[0]=-1.0;
    _vrange[1]= 1.0;
    _isosample_bool=false;
    _isosample = 50;

    _cbrange_bool = false;
    _cbrange[0]=-1.0;
    _cbrange[1]= 1.0;
    _viewmap = false;

    _key_bool = false;
    _key_string[0] = "right"; //left, center or right
    _key_string[1] = "top"; //top, center or bottom
    
    _add_line_bool = false;
    _added_line = "";

    if(number_of_curves < 1)
    { number_of_curves = 1; }
    _n_plots = number_of_curves;
    curve = new plotstring3d_single[_n_plots];
}


gnup3D::~gnup3D (void)
{
    delete[] curve;
}

void gnup3D::set_number_of_curves (int number_of_curves)
{
    delete[] curve;
    _n_plots = number_of_curves;
    curve = new plotstring3d_single[_n_plots];
}

void gnup3D::set_view (int angle_inclination, int angle_rotation)
{
    _view[0] = angle_inclination;
    _view[1] = angle_rotation;
}

void gnup3D::unset_view (void)
{
    _view_bool = false;
}

void gnup3D::unset_grid (void)
{
    _grid = false;
}

void gnup3D::set_viewequalxy (void)
{
    _viewequalxy = true;
}

void gnup3D::set_viewequalxyz (void)
{
    _viewequalxyz = true;
}

void gnup3D::set_size (double xy_length, double z_length)
{
    _size_bool = true;
    _size[0] = xy_length;
    _size[1] = z_length;
}

void gnup3D::set_xtics(double xtics)
{
    _xtics_bool = true;
    _xtics = xtics;
}

void gnup3D::set_ytics(double ytics)
{
    _ytics_bool = true;
    _ytics = ytics;
}

void gnup3D::set_ztics(double ztics)
{
    _ztics_bool = true;
    _ztics = ztics;
}

void gnup3D::set_xytics (double xtics, double ytics)
{
    set_xtics(xtics);
    set_ytics(ytics);
}

void gnup3D::set_xyztics (double xtics, double ytics, double ztics)
{
    set_xtics(xtics);
    set_ytics(ytics);
    set_ztics(ztics);
}

void gnup3D::set_xrange (double xmin, double xmax)
{
    _xrange_bool = true;
    _xrange[0]=xmin;
    _xrange[1]=xmax;
}

void gnup3D::set_yrange (double ymin, double ymax)
{
    _yrange_bool = true;
    _yrange[0]=ymin;
    _yrange[1]=ymax;
}

void gnup3D::set_zrange (double zmin, double zmax)
{
    _zrange_bool = true;
    _zrange[0]=zmin;
    _zrange[1]=zmax;
}

void gnup3D::set_xyrange(double xmin, double xmax, double ymin, double ymax)
{
    set_xrange(xmin, xmax);
    set_yrange(ymin, ymax);
}

void gnup3D::set_xyzrange(double xmin, double xmax, double ymin, double ymax, double zmin, double zmax)
{
    set_xrange(xmin, xmax);
    set_yrange(ymin, ymax);
    set_zrange(zmin, zmax);
}

void gnup3D::set_title (string title)
{
    _title_bool = true;
    _title = title;
}

void gnup3D::set_xlabel (string xlabel)
{
    _xlabel_bool=true;
    _xlabel = xlabel;
}

void gnup3D::set_ylabel (string ylabel)
{
    _ylabel_bool=true;
    _ylabel = ylabel;
}

void gnup3D::set_zlabel (string zlabel)
{
    _zlabel_bool=true;
    _zlabel = zlabel;
}

void gnup3D::set_xylabel (string xlabel, string ylabel)
{
    set_xlabel(xlabel);
    set_ylabel(ylabel);
}

void gnup3D::set_xyzlabel (string xlabel, string ylabel, string zlabel)
{
    set_xlabel(xlabel);
    set_ylabel(ylabel);
    set_zlabel(zlabel);
}


bool gnup3D::get_parametric (void)
{
    bool ret = false;

    for(int i=0; i<_n_plots; i++)
    {
        if (curve[i].get_parametric())
        {
            ret = true;
            break;
        }
    }

    return ret;
}

void gnup3D::set_parametric (void)
{
    _parametric = true;
}

void gnup3D::set_isosample (int isosamp)
{
    _isosample_bool = true;
    _isosample = isosamp;
}

void gnup3D::set_urange (double umin, double umax)
{
    _urange_bool = true;
    _urange[0]=umin;
    _urange[1]=umax;
}
void gnup3D::set_vrange (double vmin, double vmax)
{
    _vrange_bool = true;
    _vrange[0]=vmin;
    _vrange[1]=vmax;
}
void gnup3D::set_uvrange(double umin, double umax,double vmin, double vmax)
{
    set_urange(umin,umax);
    set_vrange(vmin,vmax);
}
void gnup3D::set_cbrange (double cbmin, double cbmax)
{
    _cbrange_bool = true;
    _cbrange[0]=cbmin;
    _cbrange[1]=cbmax;
}

void gnup3D::set_viewmap (void)
{
    _viewmap = true;
}

void gnup3D::set_key (string left_center_right, string top_center_bottom)
{
    _key_bool = true;
    _key_string[0] = left_center_right;
    _key_string[1] = top_center_bottom;
}

void gnup3D::add_string (string line)
{
    _add_line_bool = true;
    _added_line += "\n" + line;
}


string gnup3D::generate_plot3d (void)
{
    string str = "";
    if(!_view_bool){str += "#";}
    str += "set view " + conv_string(_view[0]) + "," + conv_string(_view[1]) + ";\n";

    if(!_grid){str += "#";}
    str += "set grid xtics ytics ztics;\n";
    str += "\n";

    if(!_viewequalxy){str += "#";}
    str += "set view equal xy;\n";
    if(!_viewequalxyz){str += "#";}
    str += "set view equal xyz;\n";
    if(!_size_bool){str += "#";}
    str += "set size " + conv_string(_size[0]) + "," + conv_string(_size[1]) + ";\n";
    str += "\n";

    if (!_xtics_bool) {str += "#";}
    str += "set xtics " + conv_string(_xtics) + ";\n";
    if (!_ytics_bool) {str += "#";}
    str += "set ytics " + conv_string(_ytics) + ";\n";
    if (!_ztics_bool) {str += "#";}
    str += "set ztics " + conv_string(_ztics) + ";\n";
    str += "\n";

    if (!_xrange_bool) {str += "#";}
    str += "set xrange [" + conv_string(_xrange[0]) + ":" + conv_string(_xrange[1]) + "];\n";
    if (!_yrange_bool) {str += "#";}
    str += "set yrange [" + conv_string(_yrange[0]) + ":" + conv_string(_yrange[1]) + "];\n";
    if (!_zrange_bool) {str += "#";}
    str += "set zrange [" + conv_string(_zrange[0]) + ":" + conv_string(_zrange[1]) + "];\n";
    str += "\n";

    if (!_viewmap){str += "#";}
    str += "set view map;\n";
    if (!_cbrange_bool) {str += "#";}
    str += "set cbrange [" + conv_string(_cbrange[0]) + ":" + conv_string(_cbrange[1]) + "];\n";
    str += "set palette rgbformulae 33,13,10;\n";

    str += "\n";
    if (!_title_bool) {str += "#";}
    str += "set title '" + _title + "';\n";
    str += "\n";

    if(!_key_bool) {str += "#";}
    str += "set key " + _key_string[0] + " " + _key_string[1] + ";\n\n";

    if (!_xlabel_bool) {str += "#";}
    str += "set xlabel '" + _xlabel + "';\n";
    if (!_ylabel_bool) {str += "#";}
    str += "set ylabel '" + _ylabel + "';\n";
    if (!_zlabel_bool) {str += "#";}
    str += "set zlabel '" + _zlabel + "';\n";
    str += "\n";

    if (_parametric || get_parametric())
    {
        str += "set parametric;\n";

        if (!_urange_bool) {str += "#";}
        str += "set urange [" + conv_string(_urange[0]) + ":" + conv_string(_urange[1]) + "];\n";
        if (!_vrange_bool) {str += "#";}
        str += "set vrange [" + conv_string(_vrange[0]) + ":" + conv_string(_vrange[1]) + "];\n";

        if(!_isosample_bool){str += "#";}
        str += "set isosample " + conv_string(_isosample) + ";\n\n";
    }
    
    if (_add_line_bool)
    {
        str += "#ADDED LINES:";
        str += _added_line + "\n\n";
    }

    str += "\n";

    str += "splot ";

    for(int i=0; i<_n_plots-1; i++)
    {
        str += curve[i].plotstring();
        str += ", \\\n";
    }
    str += curve[_n_plots-1].plotstring();
    str += ";";

    return str;
}




/* -----------------------------------------------------------------------------------------*/

/* -----------------------------------------------------------------------------------------*/

/* -----------------------------------------------------------------------------------------*/

//FUNCOES DE GNUPLOT3D

Gnuplot3D::Gnuplot3D (int number_of_curves) : gnup3D(number_of_curves), header_gnuplot()
{
	_n++;
    _scriptname = "gnuplot3d_" + conv_string(_n) + ".txt";
    string ofi = "gnuplot3d_" + conv_string(_n);
    set_output_filename(ofi);
    _plotted = false;


    #if WINDOWS_OS
    //*_realtime_bool = false;
    #else
    _realtime_bool = (bool*) mmap(NULL, sizeof(*_realtime_bool), PROT_READ | PROT_WRITE,
                                 MAP_SHARED | MAP_ANON, -1, 0);
    *_realtime_bool = false;
    #endif

    _bundle_files_bool = false;
    _bundle_folder_path = "";
}

Gnuplot3D::~Gnuplot3D (void)
{
	#if WINDOWS_OS
	#else
    if(*_realtime_bool)
    {
        *_realtime_bool = false;
        if(!WINDOWS)
        {
            if(_term_code == TERM_X11)
            {
                _plotted = false;
            }
            if(_term_code == TERM_WXT)
            {
                if(TERM_DEFAULT != TERM_WXT)
                {
                    _plotted = false;
                    set_term_code(TERM_DEFAULT);
                }
            }
        }
    }
    #endif

    //EXECUTES GNUPLOT AND PLOTS THE GRAPH
    if(!_plotted)
    {
        generate_script();
        int pid=-100;
        execute_script_gnuplot (_scriptname,pid);
        if((_term_code == TERM_PDFLATEX_EPS) || (_term_code == TERM_PDFLATEX_CAIRO))
        {
            //sleep(1);
            pdflatex_exec(_output_filename,pid);
        }
    }

    if(_bundle_files_bool)
    {
        if(_term_code != TERM_PDFLATEX_EPS && _term_code != TERM_PDFLATEX_CAIRO)
        {
            #if WINDOWS_OS
            Sleep(1000);
            #else
            sleep(1);
            #endif
        }
        bundle_files_exec();
    }
}

void Gnuplot3D::set_scriptname (string scriptname)
{
    _scriptname = scriptname;
    
    #if WINDOWS_OS
    #else
    _scriptname = ReplaceAll(scriptname,"\\", "/");
    #endif
    
    unsigned long p = scriptname.rfind(".");
    if (p>0)
    {
        scriptname = scriptname.substr(0,p);
    }

    set_output_filename(scriptname);
}

void Gnuplot3D::bundle_files (string folder_path)
{
    #if WINDOWS_OS
    #else
    folder_path = ReplaceAll(folder_path,"\\", "/");
    #endif
    
    _bundle_files_bool = true;
    if(folder_path == "")
    {
        unsigned long p = _scriptname.rfind(".");
        if (p>0)
        {
            _bundle_folder_path = _scriptname.substr(0,p);
        }
    }
    else
    {
        _bundle_folder_path = folder_path;
    }
}

void Gnuplot3D::bundle_files_exec (void)
{
    int n_files_copy = _n_plots;
    int n_files_move = 1;
    string *files_copy;
    string *files_move;
    if(_term_code == TERM_EPS || _term_code == TERM_PDFLATEX_EPS || _term_code == TERM_PDFLATEX_CAIRO)
    {
        n_files_move = 2;
        string output_filename_and_extension = _output_filename;
        if(_term_code == TERM_EPS)
        {
            output_filename_and_extension += ".eps";
        }
        else
        {
            output_filename_and_extension += ".pdf";
        }

        files_move = new string[n_files_move];
        files_move[0] = _scriptname;
        files_move[1] = output_filename_and_extension;
    }
    else
    {
        files_move = new string[n_files_move];
        files_move[0] = _scriptname;
    }

    files_copy = new string[n_files_copy];
    for(int i=0; i<_n_plots; i++)
    {
        files_copy[i] = curve[i].get_filename();
    }

    exec_bundle_files(files_copy, n_files_copy, files_move, n_files_move, _bundle_folder_path);

    delete[] files_copy;
    delete[] files_move;
}


void Gnuplot3D::generate_script (void)
{
    ofstream script;
    script.open(_scriptname.c_str(),ios::out|ios::trunc);

    script << "#Execute the 'cd' command on gnuplot to change the current directory to the directory the script is in" << endl << "#Execute the command: load '" << _scriptname << "'" << endl;

    script << "\n\n";
    script << "reset;" << endl;
    script << "\n\n";

    script << header();
    script << generate_plot3d();

    script << "\n\n";
    //*
     if(!WINDOWS && _term_code == TERM_X11)
     {
     script << "pause -1;" << endl; //Pause -1 allows for rotating the graph in x11 terminal
     }
     //*/
	script << "set output;";
    script.close();
}


void Gnuplot3D::plot_graph (void)
{
    _plotted = true;
    generate_script();
    _process.plot_ctr_gnuplot(_scriptname);
}
void Gnuplot3D::replot_graph (void)
{
    if(_plotted)
    {
        _process.send_command_replot();
    }
    else
    {
        plot_graph();
    }
}
void Gnuplot3D::plot_realtime (int t_milisec)
{
#if WINDOWS_OS
    cout << "plot_realtime NOT AVAILABLE FOR WINDOWS" << endl;
#else
    if(t_milisec < 100)
    {
        t_milisec = 100;
    }

    unsigned int t = 1000*t_milisec;
    *_realtime_bool = true; //deactivated function (for now)

    plot_graph(); //if I let the replot inside the fork, when _plotted status changes to true it wont be seen outside the fork
    if(fork()==0)
    {
        while (*_realtime_bool)
        {
            replot_graph();
            usleep(t);
        }
         _exit(0);
    }
#endif
}


/* -----------------------------------------------------------------------------------------*/

/* -----------------------------------------------------------------------------------------*/

/* -----------------------------------------------------------------------------------------*/


//AUXILIAR FUNCTIONS

//TRANSLATE AN INT TO A RGB COLOR, USEFUL WHEN USING A FOR TO PLOT VARIOUS CURVES WITH DIFFERENT COLORS
string int_to_color_rgb (int c)
{
    string ret;
    //*
    if(c>=0)
    {
        c = c%26;
    }
    else
    {
        c = -1;
    }
    //*/
    switch (c) {
        case -1:
            ret = "white";
            break;
        case 0:
            ret = "black";
            break;
        case 1:
            ret = "red";
            break;
        case 2:
            ret = "dark-grey";
            break;
        case 3:
            ret = "web-green";
            break;
        case 4:
            ret = "web-blue";
            break;
        case 5:
            ret = "dark-magenta";
            break;
        case 6:
            ret = "dark-cyan";
            break;
        case 7:
            ret = "dark-orange";
            break;
        case 8:
            ret = "dark-yellow";
            break;
        case 9:
            ret = "royalblue";
            break;
        case 10:
            ret = "goldenrod";
            break;
        case 11:
            ret = "dark-spring-green";
            break;
        case 12:
            ret = "purple";
            break;
        case 13:
            ret = "steelblue";
            break;
        case 14:
            ret = "dark-red";
            break;
        case 15:
            ret = "dark-chartreuse";
            break;
        case 16:
            ret = "orchid";
            break;
        case 17:
            ret = "aquamarine";
            break;
        case 18:
            ret = "brown";
            break;
        case 19:
            ret = "yellow";
            break;
        case 20:
            ret = "green";
            break;
        case 21:
            ret = "blue";
            break;
        case 22:
            ret = "navy";
            break;
        case 23:
            ret = "skyblue";
            break;
        case 24:
            ret = "dark-pink";
            break;
        case 25:
            ret = "dark-khaki";
            break;

        default:
            ret = "red";
            break;
    }

    return ret;
}


