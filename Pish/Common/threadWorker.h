#ifndef THREADWORKER_H
#define THREADWORKER_H

#include "wx/thread.h"

class threadWorker : public wxThread
{
    private:

    public:
        threadWorker();
        ~threadWorker();
};

#endif // THREADWORKER_H
