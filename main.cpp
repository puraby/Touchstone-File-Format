#include "holorSP2TouchStone.h"
int main(int argc, char** argv) {
    if (argc < 6) {
        fprintf(stderr, "wrong arguments\n");
        fprintf(stderr, "Usage: -n <numPorts> [-d <dir>] -o <output touchstone file>  [-m DB | MA | RI] [-v]"  );
        return 1;
    }
    int i;
    string dir = current_path().string();
    int numOfPorts = 0;
    const char* outfilename = NULL;
    const char* mode = "DB";
    bool debug = false;
    for (i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-n") == 0)
            numOfPorts = atoi(argv[i + 1]);    
        if (strcmp(argv[i], "-d") == 0)
            dir = argv[i + 1];
        if (strcmp(argv[i], "-o") == 0)
            outfilename = argv[i + 1];
        if (strcmp(argv[i], "-m") == 0)
            mode = argv[i + 1];   
        if (strcmp(argv[i], "-v") == 0)
            debug = true;
    }
    if (numOfPorts == 0)
    {
        fprintf(stderr, "Number of port should be specified.\n");
        fprintf(stderr, "Usage: -n <numPorts>\n");
        exit(-1);
    }
    if (outfilename == NULL)
    {
        fprintf(stderr, "Output file name should be specified.\n");
        fprintf(stderr, "Usage: -o <output touchstone file>\n");
        exit(-1);
    }
    string* infilename = new string[sizeof(string) * numOfPorts];
    string* total_filenames = new string[sizeof(string) * numOfPorts];
    string* missing_files = new string[sizeof(string) * numOfPorts];
    size_t missing_file_count;
    size_t num_of_line;
    size_t infile_count;
    infile_count = holor_extract_files_from_directory(infilename, debug ,dir);
    num_of_line = holor_line_count(infilename);
    cout << "number of line : " << num_of_line << endl;
    double* frequency = new double[sizeof(double) + num_of_line];
    holor_frequency_list(infilename, frequency);
    holor_generate_total_filenames(numOfPorts,total_filenames,dir);
    missing_file_count = holor_generate_missing_filenames(numOfPorts, infilename, infile_count, total_filenames, missing_files, debug);
    holor_read_sparam_file_and_convert(numOfPorts, total_filenames, outfilename, missing_files, missing_file_count,frequency, num_of_line, mode);
   delete[] infilename;
   delete[] total_filenames;
   delete[] missing_files;
   delete[] frequency;

   return 0;

    
}
