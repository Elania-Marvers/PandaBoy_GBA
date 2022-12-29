#include "dma.hpp"

using namespace pandaboygba;

pbg_dma::pbg_dma(pbg_context *ctx)
  : _context_ptr(ctx), active(false)
{
  
}

void pbg_dma::dma_start(uint8_t start)
{
  this->active = true;
  this->byte = 0;
  this->start_delay = 2;
  this->value = start;
}

void pbg_dma::dma_tick()
{
    if (!this->active)
      return;
    if (this->start_delay)
      {
        this->start_delay--;
        return;
    }
    this->_context_ptr->_ppu_ptr->ppu_oam_write(this->byte, this->_context_ptr->_bus_ptr->bus_read((this->value * 0x100) + this->byte));
    this->byte++;
    this->active = this->byte < 0xA0;
}

bool pbg_dma::dma_transferring()
{
    return this->active;
}
