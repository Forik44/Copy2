
#include <fstream>
#include <iostream>
using namespace std;

#define Data char
struct Node
{
	Data *data = nullptr;
	Node* next = nullptr;
};

struct BytesArray
{
	Node* last = nullptr;
	Node *first = nullptr;
	size_t size = 0;
};

int k = 100000;

void AddBytes(BytesArray* list, char* bytes, int l)
{
	if (list->size == 0)
	{
		Node* tmp = new Node;
		
		
	    tmp->data = bytes;
		tmp->next = nullptr;
		list->first = tmp;
		list->last = list->first;
		list->size += l;
		
	}
	else
	{
		Node* tmp = new Node;
		tmp->data = bytes;
		tmp->next = nullptr;
		list->size += l;
		list->last->next = tmp;
		list->last = tmp;
		
		
	}
	
}
void WriteBytes(Node* data, int size, char* next)
{
	fstream dstfs;
	dstfs.open(next, ios_base::app | ios_base::binary);
	if (dstfs.is_open())
	{
		int count = 0;
		Node* marker = data;
		do
		{

			if (marker->next->next == nullptr)
				dstfs.write(marker->data, size - count);
			else
				dstfs.write(marker->data, k);
			marker = marker->next;
			count += k;
		} while (marker->next != nullptr);
	}
	else
	{
		cout << "File isnt open";
	}
}
int main(int argc, char* argv[])
{
	setlocale(LC_ALL, "Russian");
	if (argc < 3)
	{
		cout << "Недостаточно аргументов!";
		exit(1);
	}
	char* cur;
	char* next;
	cur = argv[1];
	next = argv[2];
	fstream srcfs;
	srcfs.open(cur, ios_base::in | ios_base::binary);
	fstream dstfs;
	dstfs.open(next, ios_base::out | ios_base::trunc | ios_base::binary);
	dstfs.close();
	if (srcfs.is_open())
	{
		BytesArray* arr = new BytesArray;
		arr->first = nullptr;
		arr->last = nullptr;
		arr->size = 0;
		
		int count = 0;
		srcfs.seekg(0, ios_base::end);
		int sizef = srcfs.tellg();
		srcfs.seekg(0);
		while (!srcfs.eof())
		{
			char* buffer = new char[k];
			if (0 < sizef - count && sizef - count < k)
			{
				srcfs.read(buffer, sizef - count + 1);
				AddBytes(arr, buffer, sizef - count);
			}
			else
			{
				srcfs.read(buffer, k);
				AddBytes(arr, buffer, k);
			}
			
			count += k;
		}
		WriteBytes(arr->first, arr->size, next);
	
		delete arr;
		srcfs.close();
		dstfs.close();

		return 0;
	}
	else
	{
		cout << "File isnt open";
	}
	return 1;
}
