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
		            <<"Rem," 
		            <<"Instructor"
					<<"Date (MM/DD)"
					<<"Attribute"
					<<"Location"<< std::endl;
}

bool check_skip_line(std::string& buffer)
{
	for (int i = 0; i < (int)buffer.size(); i++)
	{
		if (buffer[i] == ',' && buffer[i+1] == ',')
		{
			return true;
		}
	}
	return false;
}

void tokenize(std::string const& buffer, char delim,std::vector<std::string>& out)
{
	size_t start = 0;
	size_t end = 0;

	int cnt = 0;

	while ((start = buffer.find_first_not_of(delim, end)) != std::string::npos)
	{
		end = buffer.find(delim, start);
		if (cnt == 13 || cnt == 14 || cnt == 15 || cnt == 16 || cnt == 17 || cnt == 18)
		{
			cnt++;
			continue;
		}
		out.push_back(buffer.substr(start, end - start));
		cnt++;
		if (out[0] == "Select")
		{
			out.clear();
			return;
		}
	}
}


void print(std::ofstream& output_csv_file,std::vector<std::string>& line_buffer)
{
	for (int i = 0; i < (int)line_buffer.size(); i++)
	{
		if (i == line_buffer.size() - 1)
		{
			output_csv_file << line_buffer[i] << std::endl;
		}
		else
		{
			output_csv_file << line_buffer[i] << ",";
		}
	}
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