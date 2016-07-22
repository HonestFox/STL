#pragma once

struct InputIteratorTag {};
struct OutputIteratorTag {};
struct ForwardIteratorTag : public InputIteratorTag {};
struct BidirectionalIteratorTag : public ForwardIteratorTag {};
struct RandomAccessIteratorTag : public BidirectionalIteratorTag {};

template<class T> 
struct InputIterator
{
	//typedef T                  ValueType;
	//typedef Distance           DifferenceType;
	//typedef T*                 Pointer;
	//typedef T&                 Reference;
	typedef InputIteratorTag IteratorCategory;	//迭代器的类型 （ 包括上面那5个struct ）
};

template<class Iterator>
struct IteratorTraits
{
	//typedef typename Iterator::ValueType ValueType;
	//typedef typename Iterator::DifferenceType DifferenceType;
	//typedef typename Iterator::Pointer Pointer;
	//typedef typename Iterator::Reference Reference;
	typedef typename InputIterator<Iterator>::IteratorCategory IteratorCategory;
};

template<class T>
struct IteratorTraits<T*>		//内置类型的特化版本
{
	typedef RandomAccessIteratorTag IteratorCategory;
};

template <class InputIterator>
inline size_t Distance(InputIterator first, InputIterator last)
{
	return _Distance(first, last, IteratorTraits<InputIterator>::IteratorCategory() );  //这里第三个参数 并没有实际意义，不过正是它的存在，让_Distance实现重载
}

template <class InputIterator>
inline size_t _Distance(InputIterator first, InputIterator last, RandomAccessIteratorTag)
{
	return last - first;
}

template <class InputIterator>
inline size_t _Distance(InputIterator first, InputIterator last, InputIteratorTag)
{
	size_t n = 0;
	while (first != last)
	{
		++first;
		++n;
	}
	return n;
}

