#include<iostream>
#include<fstream>
#include<string>
#include<vector>

void get_colnume(std::ofstream& output_csv_file)
{
	output_csv_file <<"Select,"
		            <<"CRN,"
		            <<"Subj,"
		            <<"Crse,"
		            <<"Sec,"
		            <<"Cmp,"
		            <<"Cred,"	
		            <<"Title,"
		            <<"Days,"
		            <<"Time,"
		            <<"Cap,"
		            <<"Act,"
		            <<"Rem," << std::endl;
}

int main(int argc, char* argv[])
{
	std::ifstream input_csv_file;
	std::ofstream output_csv_file;
	std::string temp_buffer = "";

	//open input file
	input_csv_file.open(argv[1],std::ios::in);
	if(!input_csv_file.good())
	{
		std::cerr << "cannot open input file" << std::endl;
	}
	output_csv_file.open("fall-2022.csv");
	if (!output_csv_file)
	{
		std::cerr << "cannot open output file" << std::endl;
	}
	get_colnume(output_csv_file);

	int idx = 0;
	int double_deli = 0;
	std::vector<std::string> line_buffer;

	char delim = ',';
	
	//while(getline(input_csv_file, temp_buffer))
	while (getline(input_csv_file, temp_buffer))
	{
		//tmp = tmp.replace("\uFEFF", "");
		if (0>temp_buffer[0] ||255< temp_buffer[0])
		{
			temp_buffer = temp_buffer.substr(3,3+temp_buffer.size());
		}
		//subject skip ex) Administrative Courses, Aerospace Studies...
		if (check_skip_line(temp_buffer))
		{
			line_buffer.clear();
			continue;
		}
		//split the catalog section
		tokenize(temp_buffer, delim, line_buffer);
		if (line_buffer.size() == 0)
		{
			continue;
		}
		else
		{
			print(output_csv_file,line_buffer);
			line_buffer.clear();
		}
	}
}