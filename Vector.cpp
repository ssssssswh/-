#include<iostream>
#include"Vector.h"
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
//插入
template<typename T>
Rank Vector<T>::insert(Rank r, T const& e) { //0 <= r <= size
    expand(); //如必要，先扩容
    for (Rank i = _size; r < i; i--) //自后向前，后继元素
        _elem[i] = _elem[i - 1]; //顺次后移一个单元
    _elem[r] = e; _size++; //置入新元素并更新容量
    return r; //返回秩
}
//无序去重
template<typename T>
Rank Vector<T>::deduplicate() {
    int oldSize = _size;
    Rank i = 0;
    while (i < _size - 1) {
        Rank j;
        j = i + 1;
        while (j < _size) {
            if ((_elem[i].getreal() == _elem[j].getreal()) && (_elem[i].getimag() == _elem[j].getimag())) {
                remove(j, j + 1);
            }
            else {
                j++;
            }
        }
        i++;
    }
    return oldSize - _size; //被删除元素总数
}
//有序去重
template <typename T> Rank Vector<T>::uniquify() { 
    Rank i = 0, j = 0; //各对互异“相邻”元素的秩
    while (++j < _size) 
        if (_elem[i] != _elem[j]) //跳过雷同者
            _elem[++i] = _elem[j]; //发现不同元素时，向前移至紧邻于前者右侧
    _size = ++i; shrink(); //
    return j - i; //向量规模变化量，即被删除元素总数
}
//删除在[lo,hi]之间元素
template <typename T> Rank Vector<T>::remove(Rank lo, Rank hi) { //0 <= lo <= hi <= n
    if (lo == hi) return 0; //出于效率考虑，单独处理退化情况
    while (hi < _size) _elem[lo++] = _elem[hi++]; //后缀[hi, _size)顺次前移hi-lo位
    _size = lo; shrink(); //更新规模，lo=_size之后的内容无需清零；如必要，则缩容
    //若有必要，则缩容
    return hi - lo; //返回被删除元素的数目
}
//对[lo.hi]置乱
template <typename T> void Vector<T>::unsort(Rank lo, Rank hi) {
    T* V = _elem + lo; //将子向量_elem[lo, hi)视作另一向量V[0, hi - lo)
    for (Rank i = hi - lo; i > 0; i--) //自后向前
        swap(V[i - 1], V[rand() % i]); //将V[i - 1]与V[0, i)中某一元素随机交换
}




