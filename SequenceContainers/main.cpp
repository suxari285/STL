#include<iostream>
#include<array>
#include<vector>
#include<deque>
#include<list>
#include<iterator>
#include<forward_list>
using std::cin;
using std::cout;
using std::endl;

#define tab "\t"
#define delimiter "\n-----------------------------------\n"

template<typename T>void vector_properties(const std::vector<T>& vec)
{
	cout << "Size:    " << vec.size() << endl;		//фактический размер
	cout << "Capacity:" << vec.capacity() << endl;	//вместительность
	cout << "MaxSize: " << vec.max_size() << endl;	//максимально-возможный размер
}
bool less_then_10(const int value)
{
	return value < 10;
}

//#define STL_ARRAY
//#define STL_VECTOR
//#define STL_DEQUE
//#define STL_LIST
#define STL_FORWARD_LIST

void main()
{
	setlocale(LC_ALL, "");

#ifdef STL_ARRAY
	//array - это контейнер, который хранит данные в виде статического массива.
	std::array<int, 5> arr = { 3, 5, 8, 13, 21 };
	for (int i = 0; i < arr.size(); i++)
	{
		cout << arr[i] << tab;
	}
	cout << endl;
#endif // STL_ARRAY

#ifdef STL_VECTOR
	std::vector<int> i_vec = { 0, 1, 1, 2, 3, 5, 8, 13, 21, 34 };
	vector_properties(i_vec);
	i_vec.push_back(55);
	i_vec.push_back(89);
	vector_properties(i_vec);
	i_vec.reserve(25);
	i_vec.shrink_to_fit();
	//i_vec.resize(5);
	//i_vec.resize(15);
	vector_properties(i_vec);
	for (int i = 0; i < i_vec.size(); i++)
	{
		//cout << i_vec[i] << tab;
		cout << i_vec.at(i) << tab;
	}
	cout << endl;
	cout << "Front:\t" << i_vec.front() << endl;
	cout << "Back:\t" << i_vec.back() << endl;
	i_vec.data();
	//std::vector<double> d_vec;
	//vector_properties(d_vec);

	double index;
	int value;
	cout << "Введите индекс добавляемого элемента: "; cin >> index;
	cout << "Введите значение добавляемого элемента: "; cin >> value;
	if (index <= i_vec.size())
		i_vec.insert(i_vec.begin() + index, value);

	for (std::vector<int>::iterator it = i_vec.begin(); it != i_vec.end(); ++it)
	{
		cout << *it << tab;
	}
	cout << endl;
#endif // STL_VECTOR

#ifdef STL_DEQUE
	std::deque<int> i_deque = { 3, 5, 8, 13, 21 };
	for (int i = 0; i < i_deque.size(); i++)
	{
		cout << i_deque[i] << tab;
	}
	cout << endl;
	i_deque.push_front(1);
	i_deque.push_front(1);
	i_deque.push_front(0);
	i_deque.push_back(34);
	i_deque.push_back(55);
	i_deque.push_back(89);
	for (std::deque<int>::iterator it = i_deque.begin(); it != i_deque.end(); ++it)
	{
		cout << *it << tab;
	}
	cout << endl;
#endif // STL_DEQUE

#ifdef STL_LIST
	std::list<int> i_list = { 3, 5, 8, 13, 21 };
	/*for (int i = 0; i < i_list.size(); i++)
	{
		cout << i_list[i] << tab;
	}
	cout << endl;*/
	for (std::list<int>::iterator it = i_list.begin(); it != i_list.end(); ++it)
	{
		cout << *it << tab;
	}
	cout << endl;
	i_list.push_front(1);
	i_list.push_front(1);
	i_list.push_front(0);

	i_list.push_back(34);
	i_list.push_back(55);
	i_list.push_back(89);

	int index;
	int value;
	cout << "Введите индекс добавляемого элемента: "; cin >> index;
	cout << "Введите значение добавляемого элемента: "; cin >> value;
	std::list<int>::iterator position = i_list.begin();
	//for (int i = 0; i < index; i++)position++;
	std::advance(position, index);
	i_list.insert(position, value);

	for (int i : i_list)
	{
		cout << i << tab;
	}
	cout << endl;

	for (std::list<int>::reverse_iterator it = i_list.rbegin(); it != i_list.rend(); ++it)
	{
		cout << *it << tab;
	}
	cout << endl;
#endif // STL_LIST

#ifdef STL_FORWARD_LIST

	std::forward_list<int> i_flist = { 3, 5, 8, 13, 21 };
	for (int x : i_flist) 
	{
		cout << x << '\t';
	}

	cout << endl;
	cout << "Размер списка: " << std::distance(i_flist.begin(), i_flist.end()) << endl;

	int index, value;
	cout << "Введите индекс добавляемого элемента: "; cin >> index;
	cout << "Введите значение добавляемого элемента: "; cin >> value;

	std::forward_list<int>::iterator position = i_flist.before_begin();
	if (index >= 0 && index <= std::distance(i_flist.begin(), i_flist.end())) 
	{
		std::advance(position, index);
		i_flist.insert_after(position, value);
	}
	else {
		cout << "Некорректный индекс для вставки!" << endl;
	}

	//i_flist.remove(13);
	//i_flist.remove_if(less_then_10);
	//i_flist.remove_if([](const int v) { return v % 2 == 0; });
	cout << "Список после изменений:" << endl;
	for (int x : i_flist) {
		cout << x << '\t';
	}
	cout << endl;

	cout << "Введите индекс удаляемого элемента: "; cin >> index;
	position = i_flist.before_begin();
	std::forward_list<int>::iterator to_remove = i_flist.begin();

	if (index >= 0 && index < std::distance(i_flist.begin(), i_flist.end())) 
	{
		std::advance(position, index);
		i_flist.erase_after(position);
		cout << "Элемент удалён." << endl;
	}

	cout << "Финальный список:" << endl;
	for (int x : i_flist) {
		cout << x << '\t';
	}
	cout << endl;

#endif // STL_FORWARD_LIST


}
