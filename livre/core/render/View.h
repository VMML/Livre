/* Copyright (c) 2011-2015, EPFL/Blue Brain Project
 *                          Ahmet Bilgili <ahmet.bilgili@epfl.ch>
 *
 * This file is part of Livre <https://github.com/BlueBrain/Livre>
 *
 * This library is free software; you can redistribute it and/or modify it under
 * the terms of the GNU Lesser General Public License version 3.0 as published
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

#ifndef _View_h_
#define _View_h_

#include <livre/core/api.h>
#include <livre/core/dashTypes.h>
#include <livre/core/mathTypes.h>
#include <livre/core/lunchboxTypes.h>

namespace livre
{

/** A viewport on the rendering widgets frame buffer. */
class View
{
public:
    LIVRECORE_API View();

    LIVRECORE_API virtual ~View();

    /**
     * @param rendererPtr Sets the renderer.
     */
    LIVRECORE_API void setRenderer( RendererPtr rendererPtr );

    /**
     * @param viewport Sets the viewport in the ( 0.f, 0.f, 1.f, 1.f ) normalized coordinates.
     */
    LIVRECORE_API void setViewport( const Viewport& viewport );

    /**
     * @return The renderer.
     */
    LIVRECORE_API RendererPtr getRenderer() const;

    /**
     * @return The normalized viewport.
     */
    LIVRECORE_API const Viewport& getViewport() const;

    /**
     * Renders the viewport on widget, using the renderer, using the list generated by
     * render list generator.
     * @param widget The framebuffer widget to render to.
     * @param renderSetGenerator The renderlist generator.
     */
    LIVRECORE_API void render( const FrameInfo& frameInfo,
                               const RenderBricks& renderBricks,
                               const GLWidget& widget );

    /**
     * @param frustum Derived class should implement the get frustum method.
     */
    virtual const Frustum& getFrustum() const = 0;

protected:

    /**
     * Is called after the render list generated, and before the rendering.
     * @param widget The widget to render to.
     * @param frameInfo Frame information.
     */
    virtual void onPreRender_( const GLWidget& widget LB_UNUSED,
                               const FrameInfo& frameInfo LB_UNUSED ) {}

    /**
     * Is called after the rendering.
     * @param widget The widget to render to.
     * @param frameInfo Frame information.
     */
    virtual void onPostRender_( const GLWidget& widget,
                                const FrameInfo& frameInfo ) = 0;

    RendererPtr rendererPtr_; //!< Renderer.
    Viewport viewport_; //!< The normalized viewport.

private:
};

}

#endif // _View_h_
