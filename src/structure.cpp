#include "structure.h"

FA::FA(std::string FAname)
{
    name= FAname;
    determinized=minimized=complete= false;
}

FA::FA() {
    name="Finite Automata";
    determinized=minimized=complete= false;
}
