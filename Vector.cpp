//复制数组区间A[lo,hi}
template <typename T>//模板名称定义
void Vector<T>::copyFrom(T const* A, Rank lo, Rank hi)
{
	_elem = new T[_capacity = 2 * (hi - lo)];
	_size = 0;
	while (lo < hi)
	{
		_elem[_size++] = A[lo++];
	}
}
//空间不足kuorong
template<typename T>
void Vector<T>::expand()
{
	if (_size < _capacity) return;//条件不扩容 
	if (_capacity < DEFAULT_CAPACITY)_capacity = DEFAULT_CAPACITY;  
	T* oldElem = _elem; _elem = new T[_capacity <<= 1];
	for (int i = 0; i < _size; i++)
		_elem[i] = oldElem[i];
	delete[]oldElem;//释放原空间 
}
//压缩
template<typename T>
void Vector<T>::shrink()
{
	if (_capacity < DEFAULT_CAPACITY << 1)return;//条件
	if (_size << 2 > _capacity)return;
	T* oldElem = _elem; _elem = new T[_capacity >>= 1];
	for (int i = 0; i < _size; i++)_elem[i] = oldElem[i];
	delete[]oldElem;
}
