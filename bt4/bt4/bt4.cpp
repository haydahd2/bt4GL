// bt4.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <stdio.h>
using namespace std;

class Door 
{
	class State *current;
public:
	Door();
	void setCurrent(State *s)
	{
		current = s;
	}
	void lock();
	void unlock();
	void close();
	void open();
};
class State
{
public:
	virtual void lock(Door *d) 
	{
		cout << "Already lock\n";
	}
	virtual void unlock(Door *d)
	{
		cout << "Already unlock\n";
	}
	virtual void close(Door *d)
	{
		cout << "Already close\n";
	}
	virtual void open(Door *d)
	{
		cout << "Already open\n";
	}
};
//----------------------------------------------------------------------------------------------------
void Door::lock()
{
	current->lock(this);
}
void Door::unlock()
{
	current->unlock(this);
}
void Door::close()
{
	current->close(this);
}
void Door::open()
{
	current->open(this);
}
//---------------------------------------------------------------------------------------------------
class LOCK :public State
{
public:
	LOCK()
	{
		cout << " LOCK-ctor ";
	};
	~LOCK()
	{
		cout << " dtor-LOCK\n";
	};
	void unlock(Door *d);
};
class UNLOCK :public State
{
public:
	UNLOCK()
	{
		cout << " UNLOCK-ctor ";
	};
	~UNLOCK()
	{
		cout << " dtor-UNLOCK\n";
	};
	void lock(Door *d)
	{
		cout << "   going from UNLOCK to LOCK";
		d->setCurrent(new LOCK());
		delete this;
	}
	void close(Door *d);
};
class CLOSE :public State
{
public:
	CLOSE()
	{
		cout << " CLOSE-ctor ";
	};
	~CLOSE()
	{
		cout << " dtor-CLOSE\n";
	};
	void unlock(Door *d)
	{
		cout << "   going from CLOSE to UNLOCK";
		d->setCurrent(new UNLOCK());
		delete this;
	}
	void open(Door *d);
};
class OPEN :public State
{
public:
	OPEN()
	{
		cout << " OPEN-ctor ";
	};
	~OPEN()
	{
		cout << " dtor-OPEN\n";
	};
	void open(Door *d)
	{
		cout << "   going from OPEN to CLOSE";
		d->setCurrent(new CLOSE());
		delete this;
	}
};
//------------------------------------------------------------
void LOCK::unlock(Door *d)
{
	cout << "   going from LOCK to UNLOCK";
	d->setCurrent(new UNLOCK());
	delete this;
}
void UNLOCK::close(Door *d)
{
	cout << "   going from UNLOCK to CLOSE";
	d->setCurrent(new CLOSE());
	delete this;
}
void CLOSE::open(Door *d)
{
	cout << "   going from CLOSE to OPEN";
	d->setCurrent(new OPEN());
	delete this;
}
//--------------------------------------------------------------------------------
Door::Door()
{
	current = new LOCK();
	cout << '\n';
}
int main()
{
	void(Door::*ptrs[])() =
	{
	  &Door::lock, &Door::unlock, &Door::close, &Door::open
	};
	Door fsm;
	int num;
	while (3)
	{
		cout << "Enter 0/1/2/3: ";
		cin >> num;
		(fsm.*ptrs[num])();
	}
}
