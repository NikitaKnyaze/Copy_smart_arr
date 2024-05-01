#include <iostream>
class arr_error : public std::exception
{
	std::string message;
public:
	arr_error(const std::string& message) : message{ message } {}
	const char* what() const noexcept override
	{
		return message.c_str();
	}
};
class smart_array
{
	int num_of_arr;
	int* arr = nullptr;
	int count{ 0 };
public:
	smart_array(int c)
	{
		num_of_arr = c;
		int* arr_some = new int[num_of_arr] {};
		delete[] arr;
		arr = arr_some;
	}
	~smart_array() { delete[] arr; }

	void add_element(int c)
	{
		if (count >= num_of_arr)
		{
			throw arr_error("Array out of bonds");
			return;
		}
		arr[count] = c;
		count++;
	}
	int get_element(int c)
	{
		if (c > num_of_arr || c <= 0)
		{
			throw arr_error("Wrong index");
			return -1 ;
		}
		c--;
		return arr[c];
	}
	smart_array& operator=(const smart_array& other)
	{
		if (this != &other)
		{
			delete[] arr;
			num_of_arr = other.num_of_arr;
			arr = new int[num_of_arr];
			for(int i=0; i< num_of_arr; ++i)
			{
				arr[i] = other.arr[i];
			}
		}
		return *this;
	}
};

int main()
{
	try {
		smart_array arr(5);
		arr.add_element(1);
		arr.add_element(4);
		arr.add_element(155);
		arr.add_element(14);
		arr.add_element(15);

		std::cout << arr.get_element(1) << std::endl;

		smart_array new_array(2);
		new_array.add_element(100);
		new_array.add_element(200);
		std::cout << new_array.get_element(1) << std::endl;

		arr = new_array;
		std::cout << arr.get_element(2) << std::endl;
	}
	catch (const std::exception& ex) {
		std::cout << ex.what() << std::endl;
	}
}