#ifndef ___C_SWITCHER_H___
#define ___C_SWITCHER_H___

#include "CWindowSwitcher.h"
#include "CObjectCommunicator.h"

class CSwitcher :
    public QWidget,
    public Ui::WindowSwitcher,
    public BTerminal
{
    Q_OBJECT

 public:
    CSwitcher(QWidget *parent = 0);

 protected:
    
};

#endif//___C_SWITCHER_H___
