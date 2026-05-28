#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<fstream>
#include<string>
#include<sstream>	//string stream
#include<map>
#include<list>
#include<ctime>
using std::cin;
using std::cout;
using std::endl;

#define tab			"\t"
#define delimiter	"\n--------------------------------------------\n"

const std::map<int, std::string> OFFENCES =
{
	std::pair<int, std::string>(0, "N/A"),
	std::pair<int, std::string>(1, "Парковка в неположенном месте"),
	std::pair<int, std::string>(2, "Непристегнутый ремень безопасности"),
	std::pair<int, std::string>(3, "Превышение скорости"),
	std::pair<int, std::string>(4, "Пересеченте сплошной"),
	std::pair<int, std::string>(5, "Вождение в нетрезвом состоянии"),
	std::pair<int, std::string>(6, "Оскоробление сотрудника полиции"),
	std::pair<int, std::string>(7, "Проезд на красный")
};

class Offence
{
	std::string location;
	tm time;
	int offence;
public:
	const std::string& get_location()const
	{
		return location;
	}
	std::string get_time()const
	{
		return std::asctime(&this->time);
	}
	time_t get_timestamp()const
	{
		tm time = this->time;
		tm* p_time = &time;
		return mktime(p_time);
	}
	int get_offence()const
	{
		return offence;
	}

	//			Constructors:
	Offence(const std::string& location, const char* time, int offence)
	{
		char time_buffer[32] = {};
		strcpy(time_buffer, time);
		this->location = location;
		this->time = {};
		this->get_time_from_string(time_buffer);
		this->offence = offence;
	}
	explicit Offence(const std::string& location = "N/A", time_t timestamp = 0, int offence = 0)
	{
		this->location = location;
		this->time = *localtime(&timestamp);
		this->offence = offence;
	}

	//			Methods:
	tm get_time_from_string(char* str)
	{
		const char delimiters[] = "./ -:";
		char* dateparts[5] = {};
		int i = 0;
		for (char* pch = strtok(str, delimiters); pch; pch = strtok(NULL, delimiters))
			dateparts[i++] = pch;
		this->time.tm_year = std::atoi(dateparts[0]) - 1900;
		this->time.tm_mon = std::atoi(dateparts[1]) - 1;
		this->time.tm_mday = std::atoi(dateparts[2]);	
		this->time.tm_hour = std::atoi(dateparts[3]);
		this->time.tm_min = std::atoi(dateparts[4]);
		time_t timestamp = mktime(&this->time);
		this->time = *localtime(&timestamp);
		return this->time;
	}
};
std::ostream& operator<<(std::ostream& os, const Offence& obj)
{
	std::string offence_time = obj.get_time();
	offence_time[offence_time.size() - 1] = 0;
	return	os << offence_time << tab
		<< obj.get_location() << tab
		<< OFFENCES.at(obj.get_offence());
}
std::ofstream& operator<<(std::ofstream& ofs, const Offence& obj)
{
	ofs << obj.get_timestamp() << " " << obj.get_offence() << " " << obj.get_location();
	return ofs;
}
std::istream& operator>>(std::istream& is, Offence& obj)
{
	time_t timestamp;
	int offence_id;
	std::string location;

	is >> timestamp >> offence_id;
	std::getline(is, location);
	location[location.size() - 1] = 0;
	obj = Offence(location, timestamp, offence_id);
	return is;
}

void Print(const std::map<std::string, std::list<Offence>>& base);
void Save(const std::map<std::string, std::list<Offence>>& base, const std::string& filename);
std::map<std::string, std::list<Offence>> Load(const std::string& filename);

//#define PRINT_AND_SAVE_CHECK

void main()
{
	setlocale(LC_ALL, "");

#ifdef PRINT_AND_SAVE_CHECK
	std::map<std::string, std::list<Offence>> base =
	{
		std::pair<std::string, std::list<Offence>>("a123bb", {Offence("Ул. Жирная ", "2023.04.29 12:31", 1), Offence("Красный проспект ", "2016.11.16 17:30",2) }),
		std::pair<std::string, std::list<Offence>>("a777bb", {Offence("Ул. Жирная ", "2023.06.29 18:31", 3), Offence("Ул. Терияки ", "2023.06.29 18:31",5), Offence("Ул. Терияки ", "2023.06.29 18:45",6) }),
		std::pair<std::string, std::list<Offence>>("a304bb", {Offence("Ул. 25 лет Октября ", "2015.06.16 18:31", 3), Offence("Ул. 25 лет Октября ", "2015.06.29 18:31",4)}),
	};

	Print(base);
	Save(base, "base.txt");
#endif // PRINT_AND_SAVE_CHECK

	std::map<std::string, std::list<Offence>> base = Load("base.txt");
	cout << "\n=============================================\n";
	Print(base);
	cout << base.size() << endl;
}

void Print(const std::map<std::string, std::list<Offence>>& base)
{
	for (
		std::map<std::string, std::list<Offence>>::const_iterator it = base.begin();
		it != base.end();
		++it
		)
	{
		cout << it->first << ":\n";
		for (
			std::list<Offence>::const_iterator of_it = it->second.begin();
			of_it != it->second.end();
			++of_it
			)
		{
			cout << tab << *of_it << endl;
		}
		cout << delimiter << endl;
	}
}
void Save(const std::map<std::string, std::list<Offence>>& base, const std::string& filename)
{
	std::ofstream fout(filename);
	for (
		std::map<std::string, std::list<Offence>>::const_iterator it = base.begin();
		it != base.end();
		++it
		)
	{
		fout << it->first << ":";
		for (
			std::list<Offence>::const_iterator of_it = it->second.begin();
			of_it != it->second.end();
			++of_it
			)
		{
			fout << *of_it << ",";
		}
		fout.seekp(-1, std::ios::cur);
		fout << ";" << endl;;
	}
	fout.close();
	std::string cmd = "notepad ";
	cmd += filename;
	system(cmd.c_str());
}
std::map<std::string, std::list<Offence>> Load(const std::string& filename)
{
	std::map<std::string, std::list<Offence>> base;
	std::ifstream fin(filename);
	if (fin.is_open())
	{
		while (!fin.eof())
		{
			//std::string license_plate;
			//std::getline(fin, license_plate, ':');
			char all_violations[1024] = {};
			fin.getline(all_violations, 1024, ';');
			if (strlen(all_violations) < 10)continue;
			//cout << license_plate << endl;
			//cout << all_violations << endl;
			char delimiters[] = ":,;\n";
			char* pch = strtok(all_violations, delimiters);
			std::string license_plate = pch;
			for (pch = strtok(NULL, delimiters); pch; pch = strtok(NULL, delimiters))
			{
				std::stringstream s_stream;
				Offence violation;
				s_stream << pch;
				s_stream >> violation;
				base[license_plate].push_back(violation);
			}
			cout << delimiter << endl;
		}
	}
	else
	{
		std::cerr << "Error: File not found" << endl;
	}
	fin.close();
	return base;
}