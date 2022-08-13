#ifndef HOLORSP2TOUCHSTONE_H_
#define HOLORSP2TOUCHSTONE_H_
#include <iostream>
#include <string>
#include <iomanip> 
#include <sstream>
#include <vector>
#include <fstream>
#include <cmath>
#include <algorithm>
#include <set>
#include <filesystem>
#include <regex>
using std::endl;
using std::cout;
using std::string;
using std::regex;
using std::ifstream;
using std::ofstream;
using std::set;
using std::filesystem::directory_iterator;
using std::filesystem::current_path;
struct inputsparam {

	double frequency;
	double Decibel;
	double Angle_rd;
	//inputsparam() {};
   // inputsparam(double f, double d, double a) :frequency(f), Decibel(d), Angle_rd(a) {};
};

double holor_convert_radian_to_degree(double ang_rd);
void holor_read_sparam_file_and_convert(int n, string *infilename, const char* outfilename, string* missing_files, size_t missing_file_count, double* frequency_list, size_t line_count, const char* mode = "DB");
double holor_convert_dB_to_magnitude(double dB);
double holor_convert_magnitute_angle_to_real_part(double mng, double ang);
double holor_convert_magnitute_angle_to_imaginary_part(double mng, double ang);
void holor_generate_total_filenames(int n, string* filenames_t, string dir_path = current_path().string());
size_t holor_generate_missing_filenames(int n, string* infilename, size_t infilecount, string* filenames_t, string* missing_filenames, bool debug = false);
size_t holor_extract_files_from_directory(string* filenames, bool debug = false, string dir_path = current_path().string());
void holor_frequency_list(string* infilename, double* frequency_list);
size_t holor_line_count(string* infilename);
#endif