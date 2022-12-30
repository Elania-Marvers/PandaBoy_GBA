#include "dbg.hpp"

using namespace pandaboygba;

static char dbg_msg[1024] = {0};
static int msg_size = 0;

pbg_dbg::pbg_dbg(pbg_context *ctx)
  : _context_ptr(ctx)
{
std::cout << "🎮 " << RED << "[" << ORANGE << "Running DBG!" << RED << "]" << DEFAULT << " 🎮" << std::endl;  
}

void pbg_dbg::dbg_update() {
    if (this->_context_ptr->_bus_ptr->bus_read(0xFF02) == 0x81) {
        char c = this->_context_ptr->_bus_ptr->bus_read(0xFF01);
        dbg_msg[msg_size++] = c;
        this->_context_ptr->_bus_ptr->bus_write(0xFF02, 0);
    }
}

void pbg_dbg::dbg_print() {
    if (dbg_msg[0]) {
        //printf("DBG: %s\n", dbg_msg);
    }
}
