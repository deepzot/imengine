// Created 05-Apr-2011 by David Kirkby (University of California, Irvine) <dkirkby@uci.edu>

#ifndef IMENGINE_OBSERVER
#define IMENGINE_OBSERVER

namespace imengine {
	class Observer {
	public:
		Observer();
        ~Observer();
        bool hasChanged() const;
        void setChanged(bool status);
	private:
        bool _changed;
	}; // Observer
	
	inline Observer::Observer() : _changed(true) { }
	inline Observer::~Observer() { }
    inline bool Observer::hasChanged() const { return _changed; }
    inline void Observer::setChanged(bool status) { _changed = status; }
    
} // imengine

#endif // IMENGINE_OBSERVER
