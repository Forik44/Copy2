
#include <fstream>
#include <iostream>
using namespace std;

#define Data char
int count1 = 0;
int sizef = 0;
struct Node
{
	Data *data = nullptr;
	Node* next = nullptr;
};

struct BytesList
{
	Node* last = nullptr;
	Node *first = nullptr;
	size_t size = 0;
};

int k = 5;

void AddBytes(BytesList* list, char* bytes, int l)
{
	if (list->size == 0)
	{
		Node* tmp = new Node;
		
		
	    tmp->data = bytes;
		tmp->next = nullptr;
		list->first = tmp;
		list->last = list->first;
		list->size += 1;
		
	}
	else
	{
		Node* tmp = new Node;
		tmp->data = bytes;
		tmp->next = nullptr;
		list->size += 1;
		list->last->next = tmp;
		list->last = tmp;
		
		
	}
	
}
char* getData(Node* marker)
{
	return marker->data;
}
Node* moveNext(Node* marker)
{
	 return marker->next;
	
}
bool canMoveNext(Node* marker)
{
	return marker->next != nullptr;
}

void WriteBytes(const BytesList* array, const char* next)
{
	fstream dstfs;
	dstfs.open(next, ios_base::app | ios_base::binary);
	if (dstfs.is_open())
	{
		Node* marker = array->first;
		while(1)
		{
			if (canMoveNext(marker))
				dstfs.write(getData(marker), k);
			else
				dstfs.write(getData(marker), sizef - count1 + k);
			if (canMoveNext(marker))
				marker = moveNext(marker);
			else
				break;
		}
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
		BytesList* arr = new BytesList;
		arr->first = nullptr;
		arr->last = nullptr;
		arr->size = 0;
				
		srcfs.seekg(0, ios_base::end);
		sizef = srcfs.tellg();
		srcfs.seekg(0);
		count1 = 0;
		while (!srcfs.eof())
		{
			char* buffer = new char[k];
			if (0 <= sizef - count1 && sizef - count1 < k)
			{
				srcfs.read(buffer, sizef - count1	+ 1);
				AddBytes(arr, buffer, sizef - count1);
			}
			else
			{
				srcfs.read(buffer, k);
				AddBytes(arr, buffer, k);
			}
			
			count1 += k;
		}
		WriteBytes(arr, next);
	
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
