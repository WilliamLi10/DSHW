
#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include <algorithm>
/*for each line inside the vector of lines, it will replace the old character with the new character using the replace algorithm
once it is done replacing, it will then write all the lines into the output file*/
void replace(char oldc, char newc, std::vector<std::string>& lines,std::ofstream& outFile)
{
	for(int i = 0; i != lines.size(); ++i )
	{
	std::replace(lines[i].begin(),lines[i].end(),oldc,newc);
	outFile << lines[i];
	outFile << '\n';
	}
}
/*for each line it will check each character if it is a candidate pixel. If it is, it will then check the left, right, top, and right of the character
inside the 2d array. If one of those positions contains an erosion character, the current character is replaced with an r.
After going through the vector, it will then call the replace function on the rs changing them to a background pixel*/
void erosion(std::vector<std::string>& lines, char c, char e, std::ofstream& outFile)
{
	for(int i = 0; i !=lines.size(); ++i)
		 {
		 	for(int j = 0; j != lines[i].size()-1;++j)
		 	{
				if(lines[i][j] == c)
				{
					if(lines[i-1][j] == e)
			 		{
			 			lines[i][j] = 'r';
			 		}
			 		
			 		if(lines[i+1][j] == e)
			 		{
			 			lines[i][j] = 'r';
			 		}
			 		if(lines[i][j-1] == e)
			 		{
			 			lines[i][j] = 'r';
			 		}
			 		if(lines[i][j+1] == e)
			 		{
			 			lines[i][j] = 'r';
			 		}
		 		}	
		 	}

		 }
		 replace('r',e,lines,outFile);
}
/*for each line it will check each character if it is a candidate pixel. If it is, it will then check the left, right, top, and right of the character
inside the 2d array. If one of those positions is not a candidate pixel, that position is replaced with an r.
After going through the vector, it will then call the replace function on the rs and replace them with a candidate pixel*/
void dilation(std::vector<std::string>& lines, char d, std::ofstream& outFile)
{
	for(int i = 0; i !=lines.size(); ++i)
		 {
		 	for(int j = 0; j != lines[i].size()-1;++j)
		 	{
				if(lines[i][j] == d)
				{
					if(lines[i-1][j] == '.')
			 		{
			 			lines[i-1][j] = 'r';
			 		}
			 		
			 		if(lines[i+1][j] == '.')
			 		{
			 			lines[i+1][j] = 'r';
			 		}
			 		if(lines[i][j-1] == '.')
			 		{
			 			lines[i][j-1] = 'r';
			 		}
			 		if(lines[i][j+1] == '.')
			 		{
			 			lines[i][j+1] = 'r';
			 		}
		 		}	
		 	}

		 }
		 replace('r',d,lines,outFile);
}
int main(int argc, char* argv[])
{
	if (argc <= 4)
	{
		std::cerr << "ERROR: Argument Missing" << std::endl;
		return 1;
	}
	else 
	{
	//Creates variables that will be used in program
	std::ifstream inFile;
	std::vector<std::string> lines;
	std::string line = "";
	inFile.open(argv[1]);
	//uses the in file to create a vector of strings 
	while(inFile >> line)
	{
		lines.push_back(line);
	}
	//creates the output file
	std::ofstream outFile;
	outFile.open(argv[2]);
	//based on the given input, perform the correct operation
	if (std::string(argv[3]) == std::string("replace"))
	{
		replace(*argv[4],*argv[5],lines,outFile);
	}
	else if (std::string(argv[3]) == std::string("erosion"))
	{
		erosion(lines,*argv[4],*argv[5],outFile);
	}
	else if (std::string(argv[3]) == std::string("dilation"))
	{
		dilation(lines,*argv[4],outFile);
	}
	else if (std::string(argv[3]) == std::string("opening"))
	{
		dilation(lines,*argv[4],outFile);
	}
	return 0;
	}

}