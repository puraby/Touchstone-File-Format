#include "holorSP2TouchStone.h"
/**
 *  holorz_read_from_file_and_convert takes number of ports, input filenames and output filename as input. Reads and extracts data from the file. Converts the input data as per mode and writes output data on the output file. 
 *
 * @param[in] n Number of ports.
 * @param[in] infilename Input files of S-Parameter. The frequency line data should have dB Angle format. Data is saparated by single or multiple spaces.
 * @param[in] outfilename Output file name, in which data would be written.
 * @param[in] mode Mode of conversion. Optional parameter. Conversion mode can be real-imaginary(RI), magnitute-angle(MA) or dB-angle(DB). Default value is dB-angle(DB).
 * @return Nothing
 */
void holor_read_sparam_file_and_convert(int n, string *infilename, const char* outfilename, string* missing_files, size_t missing_file_count, double* frequency_list, size_t line_count, const char* mode ) {
	inputsparam** input_list = new inputsparam* [sizeof(inputsparam) + line_count];
	for (int i = 0; i < sizeof(inputsparam) + line_count; ++i)
		input_list[i] = new inputsparam[sizeof(inputsparam)*n*n];
	int i = 0; // number of lines in file
	int j = 0; // number of files
	ofstream ofp(outfilename);
	if (!ofp.is_open()) {
		cout << "unable to open output file";
		exit(-1);
	}
	while (!infilename[j].empty()) {
		bool flag = false;
		for (int k = 0; k < missing_file_count; k++) {
			if (infilename[j] == missing_files[k]) {
				flag = true;
				break;
			}
		}
		if (flag) {
			for (int i = 0; i < line_count; i++) {
				input_list[i][j] = {frequency_list[i], 0, 0};
			}
			j++;
		}
		else {
			i = 0;
			ifstream ifp(infilename[j]);
			ifp >> std::fixed >> std::setprecision(6) >> std::scientific >> std::setiosflags(std::ios::uppercase);
			if (!ifp.is_open()) {
				cout << "unable to open input file ";
				exit(-1);
			}
			double step_no, mng, ang_rd, freq, db;
			while (ifp >> step_no >> mng >> ang_rd >> freq >> db) {
				input_list[i][j] = { freq, db, ang_rd };
				i++;
			}
			ifp.close();
			j++;
		}
	}
	ofp << std::fixed << std::setprecision(6) << std::scientific << std::setiosflags(std::ios::uppercase);
	if ((strcmp(mode, "DB") == 0)) {
		ofp << "# Hz S DB 50" << endl;
		for (int p = 0; p < i; p++) {
			ofp << input_list[p][0].frequency << "\t\t";
			for (int q = 0; q < j; q++) {
				if (n > 2 && n < 5) {
					if ((q % n == 0) && (q != 0))
						ofp << endl << "\t\t";
				}
				if (n >= 5) {
					if ((q % 4 == 0) && (q != 0))
						ofp << endl << "\t\t";
				}
				ofp << input_list[p][q].Decibel << "\t" << holor_convert_radian_to_degree(input_list[p][q].Angle_rd) << "\t\t";
			}
			ofp << endl;
			if (n > 2)
				ofp << endl;
		}
	}
	if ((strcmp(mode, "MA") == 0)) {
		ofp << "# Hz S MA 50" << endl;
		for (int p = 0; p < i; p++) {
			ofp << input_list[p][0].frequency << "\t\t";
			for (int q = 0; q < j; q++) {
				if (n > 2 && n < 5) {
					if ((q % n == 0) && (q != 0))
						ofp << endl << "\t\t";
				}
				if (n >= 5) {
					if ((q % 4 == 0) && (q != 0))
						ofp << endl << "\t\t";
				}
				ofp << holor_convert_dB_to_magnitude(input_list[p][q].Decibel) << "\t" << holor_convert_radian_to_degree(input_list[p][q].Angle_rd) << "\t\t";

			}
			ofp << endl;
			if (n > 2 )
				ofp << endl;
		}
	}
	if ((strcmp(mode, "RI") == 0)) {
		ofp << "# Hz S RI 50" << endl;
		for (int p = 0; p < i; p++) {
			ofp << input_list[p][0].frequency << "\t\t";
			for (int q = 0; q < j; q++) {
				double mng = holor_convert_dB_to_magnitude(input_list[p][q].Decibel);
				double real = holor_convert_magnitute_angle_to_real_part(mng, input_list[p][q].Angle_rd);
				double imaginary = holor_convert_magnitute_angle_to_imaginary_part(mng, input_list[p][q].Angle_rd);
				if (n > 2 && n < 5) {
					if ((q % n == 0) && (q != 0))
						ofp << endl << "\t\t";
				}
				if (n >= 5) {
					if ((q % 4 == 0) && (q != 0))
						ofp << endl << "\t\t";
				}
				ofp << real << "\t" << imaginary << "\t\t";
			}
			ofp << endl;
			if (n > 2 )
				ofp << endl;
		}
	}
	ofp.close();
	for (int i = 0; i < sizeof(inputsparam); ++i) {
		delete[] input_list[i];
	}
	delete[] input_list;

}

/**
 *  holor_convert_dB_to_magnitude takes decibel value as input. Converts the decibel value in its magnitude.
 *
 * @param[in] dB Input decibel value. 
 * @return Magnitude of the given dB.
 */
double holor_convert_dB_to_magnitude(double dB) {
	
	double mng;
	mng = double(pow(10, dB / 20));
	return mng;
}
/**
 *  holor_convert_radian_to_degree takes radian as input. Converts the radian to degree.
 *
 * @param[in] ang_rd Input radian.
 * @return Degree.
 */

double holor_convert_radian_to_degree(double ang_rd) {
	double deg;
	double pi = 3.14159;
	deg = (ang_rd * (180 / pi));
	return deg;
}
/**
 *  holor_convert_magnitude_angle_to_real_part takes magnitute and angle value as input. Converts the degree value of angle in radian. Returns real part of complex number.
 *
 * @param[in] mng Input magnitude value.
 * @param[in] ang Input angle value in degree.
 * @return  Real part of the complex number.
 */

double holor_convert_magnitute_angle_to_real_part(double mng, double ang) {
	double rp;
	rp = mng * cos(ang);
	return rp;	

}
/**
 *  holor_convert_magnitute_angle_to_imaginary_part takes magnitute and angle value as input. Converts the degree value of angle in radian. Returns imaginary part of complex number.
 *
  @param[in] mng Input magnitude value.
 * @param[in] ang Input angle value in degree.
 * @return  Imaginary part of the complex number.
 */

double holor_convert_magnitute_angle_to_imaginary_part(double mng, double ang) {

	double ip;
	ip = mng * sin(ang);
	return ip;

}

void holor_generate_total_filenames(int n, string* filenames_t, string dir_path) {
	if (n == 2) {
		filenames_t[0] = dir_path + "\\S1-1.spara";
		filenames_t[1] = dir_path + "\\S2-1.spara";
		filenames_t[2] = dir_path + "\\S1-2.spara";
		filenames_t[3] = dir_path + "\\S2-2.spara";
	//	cout << filenames_t[0] << endl << filenames_t[1] << endl << filenames_t[2] << endl << filenames_t[3];
	}
	else {
		int k = 0;
		for (int i = 1; i <= n; i++)
			for (int j = 1; j <= n; j++) {
				string firstpart = "\\S";
				string stri = std::to_string(i);
				string strj = std::to_string(j);
				string lastpart = ".spara";
				string fullName = dir_path + firstpart + stri + "-" + strj + lastpart;
				filenames_t[k] = fullName;
				// cout << filenames_t[k] << endl;
				k++;
			}
	}
}

size_t holor_generate_missing_filenames(int n, string* infilename, size_t infilecount, string* filenames_t, string* missing_filenames, bool debug) {

	set<string> set_infile_total;
	set<string> set_infile;
	for (int i = 0; i < infilecount; i++) {
		set_infile.insert(infilename[i]);
	}
	for (int i = 0; i < n*n; i++) {
		set_infile_total.insert(filenames_t[i]);
	}
	size_t missing_file_count = set_infile_total.size() - set_infile.size();
    set_difference(set_infile_total.begin(), set_infile_total.end(), set_infile.begin(), set_infile.end(), missing_filenames);
	if (debug) {
		cout << "Number of missing files : " << missing_file_count << endl;
		cout << "Missing files : ";
		for (int i = 0; i < missing_file_count; i++) {
			cout << missing_filenames[i] << " ";

		}
		cout << endl;
	}
	return missing_file_count;
}

size_t holor_extract_files_from_directory(string* filenames, bool debug, string dir_path) {
	size_t infile_count = 0;
	regex p("(.*)(.spara)");
	directory_iterator end_itr;
	if (debug) {
		cout << "Spara files in the directory : " << endl;
	}
	
	for (directory_iterator itr(dir_path); itr != end_itr; ++itr) {
		if (is_regular_file(itr->path())) {
			string file = itr->path().string();
			if (regex_match(file, p)) {
				filenames[infile_count] = file;
				if (debug) {
					cout << filenames[infile_count] << endl;
				}
				infile_count++;
			}
		}
	}
	//cout << "Number of spara files in the directory : " << infile_count << endl;
	return infile_count;
}


void holor_frequency_list(string* infilename, double* frequency_list)
{
	int i = 0;
	double step_no, mng, ang_rd, freq, db;
	ifstream ifp(infilename[0]);
	if (!ifp.is_open()) {
		cout << endl << "unable to open input file." << endl;
		exit(-1);
	}
	while (ifp >> step_no >> mng >> ang_rd >> freq >> db) {
		frequency_list[i] = freq;
		i++;
		
	}
	/**for (int j = 0; j < row_count; j++)
	{
		 cout << frequency_list[j] << endl;
	}
	cout << "Number of rows : " << row_count << endl;
	**/
	
}

size_t holor_line_count(string* infilename) {
	 
	size_t count = 0;
	string line;
	ifstream ifp(infilename[0]);
	while (getline(ifp, line))
		count++;
	return count;
}





