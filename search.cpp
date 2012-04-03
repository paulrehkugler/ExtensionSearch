/*
 * search.cpp
 *
 *  Created on: Feb 25, 2011
 *      Author: Paul
 */

#include <unistd.h>
#include <iostream>
#include <dirent.h>
#include <vector>

std::vector<std::string> results;				// holds search results

// recursive search algorithm
void search(std::string curr_directory, std::string extension){
	DIR* dir_point = opendir(curr_directory.c_str());
	dirent* entry = readdir(dir_point);
	while (entry){									// if !entry then end of directory
		if (entry->d_type == DT_DIR){				// if entry is a directory
			std::string fname = entry->d_name;
			if (fname != "." && fname != "..")
				search(entry->d_name, extension);	// search through it
		}
		else if (entry->d_type == DT_REG){		// if entry is a regular file
			std::string fname = entry->d_name;	// filename
												// if filename's last characters are extension
			if (fname.find(extension, (fname.length() - extension.length())) != std::string::npos)
				results.push_back(fname);		// add filename to results vector
		}
		entry = readdir(dir_point);
	}
	return;
}

int main(int argc, char* argv[]){				// accepts command line arguments
	// obtain user input, file type to search for
	std::string extension;						// type of file to search for
	if (argc < 2){								// if user did not provide command line arguments
		std::cout << "Please enter the extension you would like to search for." << std::endl;
		std::cin >> extension;
	}
	else										// if user did provide command line arguments
		extension = argv[1];

	// setup search parameters
	std::string curr_directory = get_current_dir_name();

	search(curr_directory, extension);

	// output results
	if (results.size()){
		std::cout << results.size() << " files were found:" << std::endl;
		for (unsigned int i = 0; i < results.size(); ++i)	// used unsigned to appease compiler warnings
			std::cout << "- \t" <<  results[i] << std::endl;
	}
	else{
		std::cout << "No files ending in '" << extension << "' were found." << std::endl;
	}
	
	// return
	return 0;
}
