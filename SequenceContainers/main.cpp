#include <iostream>
//#include <array>
#include <vector>
using std::cin;
using std::cout;
using std::endl;

#define tab "\t"
#define delimetr "\n-----------------------------\n"

template<typename T>void print_vector(const std::vector<T>& vec)
{
    for (const auto& el : vec)cout << el << tab;
    cout << endl;
}
template<typename T>void vector_properties(std::vector<T>& vec)
{
	cout << "Size:\t\t" << vec.size() << endl;
	cout << "Capacity:\t" << vec.capacity() << endl;
	cout << "MaxSize:\t" << vec.max_size() << endl;
}

//#define STL_ARRAY
#define STL_VECTOR

void main()
{
	setlocale(LC_ALL, "");
#ifdef STL_ARRAY
	std::array<int, 5> arr = {3,5,8,13,21};
	for (int i = 0; i < arr.size(); i++)
	{
		cout << arr[i] << tab;
	}
	cout << endl;
#endif
#ifdef STL_VECTOR
	std::vector<int> i_vec = {0,1,1,2,3,5,8,13,21,34};
	vector_properties(i_vec);
	i_vec.push_back(55);
	vector_properties(i_vec);

    int index, value;
    cout << "Введите индекс для вставки: ";
    cin >> index;
    cout << "Введите значение для вставки: ";
    cin >> value;
    if (index >= 0 && index <= i_vec.size()) {
        i_vec.insert(i_vec.begin() + index, value);
    }
    vector_properties(i_vec);
    print_vector(i_vec);

    cout << "Введите индекс для удаления: ";
    cin >> index;
    if (index >= 0 && index < i_vec.size()) {
        i_vec.erase(i_vec.begin() + index);
    }

    vector_properties(i_vec);
    print_vector(i_vec);
#endif

}