#include "gx_opn2.h"
#include <cstring>

#include "gx/gx_ym2612.h"

GXOPN2::GXOPN2()
    : m_chip(YM2612GXAlloc()),
      m_framecount(0)
{
    YM2612GXInit(m_chip);
    YM2612GXConfig(m_chip, YM2612_DISCRETE);
}

GXOPN2::~GXOPN2()
{
    YM2612GXFree(m_chip);
}

void GXOPN2::setRate(uint32_t rate, uint32_t clock)
{
    OPNChipBaseT::setRate(rate, clock);
    YM2612GXResetChip(m_chip);
}

void GXOPN2::reset()
{
    OPNChipBaseT::reset();
    YM2612GXResetChip(m_chip);
}

void GXOPN2::writeReg(uint32_t port, uint16_t addr, uint8_t data)
{
    YM2612GXWrite(m_chip, 0 + port * 2, addr);
    YM2612GXWrite(m_chip, 1 + port * 2, data);
}

void GXOPN2::nativePreGenerate()
{
    YM2612GXPreGenerate(m_chip);
    m_framecount = 0;
}

void GXOPN2::nativePostGenerate()
{
    YM2612GXPostGenerate(m_chip, m_framecount);
}

void GXOPN2::nativeGenerate(int16_t *frame)
{
    YM2612GXGenerateOneNative(m_chip, frame);
    ++m_framecount;
}

const char *GXOPN2::emulatorName()
{
    return "Genesis Plus GX";
}