
/* Copyright (c) 2006-2012, Stefan Eilemann <eile@equalizergraphics.com> 
 *
 * This library is free software; you can redistribute it and/or modify it under
 * the terms of the GNU Lesser General Public License version 2.1 as published
 * by the Free Software Foundation.
 *  
 * This library is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more
 * details.
 * 
 * You should have received a copy of the GNU Lesser General Public License
 * along with this library; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */

#include "frame.h"

#include "frameData.h"
#include "image.h"
#include <eq/util/objectManager.h>

namespace eq
{
Frame::Frame()
        : _frameData( 0 )
        , _zoomFilter( FILTER_LINEAR )
{
}

Frame::~Frame()
{
    if( _frameData )
        LBINFO << "FrameData attached to frame during deletion" << std::endl;
}

uint32_t Frame::getBuffers() const
{
    LBASSERT( _frameData );
    return _frameData->getBuffers();
}

const Pixel& Frame::getPixel() const
{
    LBASSERT( _frameData );
    return _frameData->getPixel();
}

const SubPixel& Frame::getSubPixel() const
{
    LBASSERT( _frameData );
    return _frameData->getSubPixel();
}

const Range& Frame::getRange() const
{
    LBASSERT( _frameData );
    return _frameData->getRange();
}

uint32_t Frame::getPeriod() const
{
    LBASSERT( _frameData );
    return _frameData->getPeriod();
}

uint32_t Frame::getPhase() const
{
    LBASSERT( _frameData );
    return _frameData->getPhase();
}

const Images& Frame::getImages() const
{
    LBASSERT( _frameData );
    return _frameData->getImages();
}

void Frame::clear()
{
    LBASSERT( _frameData );
    _frameData->clear();
}

void Frame::flush()
{
    if( _frameData )
        _frameData->flush();
}

void Frame::setAlphaUsage( const bool useAlpha )
{
    if( _frameData )
        _frameData->setAlphaUsage( useAlpha );
}

void Frame::setQuality( const Frame::Buffer buffer, const float quality )
{
    if( _frameData )
        _frameData->setQuality( buffer, quality );
}

void Frame::useCompressor( const Frame::Buffer buffer, const uint32_t name )
{
    if( _frameData )
        _frameData->useCompressor( buffer, name );
}

void Frame::readback( ObjectManager* glObjects, const DrawableConfig& config )
{
    LBASSERT( _frameData );
    const PixelViewport& pvp = _frameData->getPixelViewport();
    const Images& images = _frameData->startReadback( *this, glObjects, config,
                                                      PixelViewports( 1, pvp ));
    for( ImagesCIter i = images.begin(); i != images.end(); ++i )
        (*i)->finishReadback( getZoom(), glObjects->glewGetContext( ));
}

void Frame::readback( ObjectManager* glObjects, const DrawableConfig& config,
                      const PixelViewports& regions )
{
    LBASSERT( _frameData );
    const Images& images = _frameData->startReadback( *this, glObjects, config,
                                                      regions );
    for( ImagesCIter i = images.begin(); i != images.end(); ++i )
        (*i)->finishReadback( getZoom(), glObjects->glewGetContext( ));
}

Images Frame::startReadback( ObjectManager* glObjects,
                           const DrawableConfig& config,
                           const PixelViewports& regions )
{
    LBASSERT( _frameData );
    return _frameData->startReadback(  *this, glObjects, config, regions );
}

void Frame::setReady()
{
    LBASSERT( _frameData );
    _frameData->setReady();
}

bool Frame::isReady() const
{
    LBASSERT( _frameData );
    return _frameData->isReady();
}

void Frame::waitReady( const uint32_t timeout ) const
{
    LBASSERT( _frameData );
    _frameData->waitReady( timeout );
}

void Frame::disableBuffer( const Buffer buffer )
{
    LBASSERT( _frameData );
    _frameData->disableBuffer( buffer );
}

void Frame::addListener( lunchbox::Monitor<uint32_t>& listener )
{
    LBASSERT( _frameData );
    _frameData->addListener( listener );
}

void Frame::removeListener( lunchbox::Monitor<uint32_t>& listener )
{
    LBASSERT( _frameData );
    _frameData->removeListener( listener );
}

}
