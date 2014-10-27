#include <iostream>
#include <vector>

using namespace std;

class VectorInit {

private:
    vector<int>		m_ints;
    vector<int*>	m_pints;

public:
	VectorInit()
		: m_ints(4, 3)
		, m_pints(0, nullptr){
	}

	void print(){
		for(auto iter : m_ints){
			cout << iter << "\n";
		}
		for(auto iter : m_pints){
			cout << *iter << "\n";
		}
	}
};

int main()
{
	VectorInit vi;
	vi.print();

	return 0;
}
// Output:
// 3
// 3
// 3
// 3