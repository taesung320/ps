#include<iostream>
#include<string>
using namespace std;

int main()
{
	const int noA = 26;
	int arr[noA] = {};
	string word;
	cin >> word;
	for (size_t i = 0; i < word.size(); i++)
	{
		if(word[i]>='a')
        {
            arr[int(word[i]-'a')]++;
        }
        else
        {
            arr[int(word[i]-'A')]++;
        }
	}
	int m = arr[0];
	int I = 0;
	for (size_t i = 1; i < noA; i++)
	{
		if (m < arr[i])
		{
			m = arr[i];
			I = i;
		}
	}
    int cnt=0;
    for(int i=0;i<noA;i++)
    {
        if(arr[i]==m)
            cnt++;
        if(cnt>1)
        {
            cout<<'?';
            return 0;
        }
    }
    cout<<char(I+65);
	return 0;
}