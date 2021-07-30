#include "Gear.h"
#include "RefPool.h"
#include "Gear.h"
#include "RefPool.h"
#include "Singleton.h"

#define DEFAULT_FRAME_RATE 60
namespace gear {

Gear::Gear()
: frame_(0)
, frame_rate_(DEFAULT_FRAME_RATE)
, frame_msec_(1000 / DEFAULT_FRAME_RATE)
, valid_(false)
, begine_time_(0)
, wait_time_(0)
{
}

Gear::~Gear()
{
}

bool Gear::baseInit()
{
    return true;
}

void Gear::logic()
{
    update();
}

void Gear::begin()
{
    DBG("[Gear](start) begin_time:%d frame_msec_:%d", begine_time_, frame_msec_);

    valid_ = true;
}

void Gear::stop()
{
    valid_ = false;
}

void Gear::end()
{
    Singleton<RefPoolManager>::destroyInstance();
}

void Gear::mainLoop()
{
}

void Gear::setFrameRate(unsigned int rate)
{
    frame_rate_ = rate;
    frame_msec_ = (1000 / frame_rate_);
}

} // namespace gear

