// https://blog.csdn.net/bible_reader/article/details/80386882

// https://blog.csdn.net/weixin_44503157/article/details/118240982

// HashTable.cpp : 定义控制台应用程序的入口点。
//

#include <iostream>
#include <vector>
#include <list>
#include <string>
 
using namespace std;
 
// hash 函数（根据字符串长度映射到哈希表中）
static unsigned int hashFunc(const string& str, unsigned int bucketSize)
{
 	return (str.size() % bucketSize);
}
 
template<typename V>
struct NODE
{
	string key;
	V value;
	NODE* next;
	NODE()
	{
		next = NULL;
	}
};
 
template<typename V>
class hashTable
{
public:
	hashTable()
	{
	}
	~hashTable()
	{
		destroyBuckets();
	}
 
public:
	hashTable(unsigned int size)
	{
		pFunc = hashFunc;
		m_buckets.clear();
		m_bucketSize = size;
		initialBuckets();
	}
 
private:
	unsigned int (*pFunc)(const string& str, unsigned int bucketSize);   // 哈希函数指针
	unsigned int m_bucketSize;                                              // 哈希函数中的桶的数量
    vector<NODE <V>* > m_buckets;                                   // 存储指针
	void initialBuckets();
	void destroyBuckets();
 
public:
	void put(const string& key, V value)
	{
		NODE<V> *node = new NODE<V>();
		node->key = key;
		node->value = value;
		node->next = NULL;
 
		unsigned int index = (*pFunc)(key, m_bucketSize);
		NODE<V> *pCur = m_buckets[index];
		NODE<V> *pPre = pCur;
 
		while(pCur->next != NULL)
		{
			pPre = pCur->next;
			pCur = pCur->next;
		}
 
		pCur->next = node;
	}
 
	bool get(const string& key, V& value)
	{
		unsigned int index = (*pFunc)(key, m_bucketSize);
		NODE<V> *pCur = m_buckets[index];
		while(pCur->next != NULL)
		{
			if(key == pCur->next->key)
			{
				value = pCur->next->value;
				return true;
			}
 
			pCur = pCur->next;
		}
 
		return false;
	}
};
 
template<typename V>
void hashTable<V>::initialBuckets()
{
	for(unsigned int i = 0; i < m_bucketSize; i++)
	{
		NODE <V>* pHead = new NODE<V>();
		pHead->next = NULL;
 
		m_buckets.push_back(pHead);  // 保存头指针
	}
}
 
template<typename V>
void hashTable<V>::destroyBuckets()
{
	vector<NODE <V>* >::iterator iter = m_buckets.begin();
	for(; iter != m_buckets.end(); iter++)
	{
		NODE<V>* pHead = *iter;
 
		while(pHead != NULL)  // 从vector中的第一个元素才是释放
		{
			NODE<V>* pCur = pHead;
			pHead = pHead->next;
 
			delete pCur;
		}
	}
}
 
int _tmain(int argc, _TCHAR* argv[])
{
	// 创建一个带10个桶的hash对象
	hashTable<int> hash(10);
	hash.put("zhangsan", 101);
	hash.put("lisi", 110);
	hash.put("wangwu", 90);  
 
	int score1, score2, score3;
	hash.get("zhangsan", score1);
	hash.get("lisi", score2);
	hash.get("wangwu", score3);
 
	cout<<"zhangsan' score is:"<<score1<<endl;
	cout<<"lisi' score is:"<<score2<<endl;
	cout<<"wangwu's score is:"<<score3<<endl;
 
	system("pause");
	return 0;
}