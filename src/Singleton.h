#ifndef SINGLETON_H_
#define SINGLETON_H_

template <class T>
class Singleton
{
private:
	Singleton();
	~Singleton();
	Singleton(Singleton const &);
	Singleton &operator=(Singleton const &);

public:
	static T *getInstance()
	{
		static T instance;
		return &instance;
	}
};

#endif /* SINGLETON_H_ */
