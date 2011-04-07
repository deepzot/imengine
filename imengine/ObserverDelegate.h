// Created 05-Apr-2011 by David Kirkby (University of California, Irvine) <dkirkby@uci.edu>

#ifndef IMENGINE_OBSERVER_DELEGATE
#define IMENGINE_OBSERVER_DELEGATE

#include "imengine/Observer.h"
#include "imengine/ptr_types.h"

namespace imengine {
	class ObserverDelegate {
	public:
		ObserverDelegate();
        ~ObserverDelegate();
        // Sets the observer we are delegated to update.
        void setObserver(ObserverPtr observer);
        // Registers that our result has changed.
        void setChanged();
	private:
        ObserverPtr _observer;
	}; // ObserverDelegate
	
	inline ObserverDelegate::ObserverDelegate() { }
	inline ObserverDelegate::~ObserverDelegate() { }

    inline void ObserverDelegate::setObserver(ObserverPtr observer) {
        _observer = observer;
    }
    inline void ObserverDelegate::setChanged() {
        if(0 != _observer.get()) _observer->setChanged(true);
    }
	
} // imengine

#endif // IMENGINE_OBSERVER_DELEGATE
