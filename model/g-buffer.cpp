/**
 *
 * @file g-buffer.cpp
 * @author Thomas R. Carrel
 *
 * @brief Defines functions for the G_Buffer class.
 */




#include "g-buffer.h"
#include "../app/window.h"

#include<cstdio>

namespace Model
{

    /** Ctor
     * @param w The window is needed for the aspect ratio.
     */
    G_Buffer::G_Buffer( App::Window* w )
    {
        GLint width   =   w->w();
        GLint height  =   w->h();
        glGenFramebuffers( 1, &g.Buffer );
        glBindFramebuffer( GL_FRAMEBUFFER, g.Buffer );

        glGenTextures( 1, &g.Position );
        glBindTexture( GL_TEXTURE_2D, g.Position );
        glTexImage2D(
                GL_TEXTURE_2D,
                0,
                GL_RGB16F,
                width,
                height,
                0,
                GL_RGB,
                GL_FLOAT,
                NULL );
        glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST );
        glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST );
        glFramebufferTexture2D(
                GL_FRAMEBUFFER,
                GL_COLOR_ATTACHMENT0,
                GL_TEXTURE_2D,
                g.Position,
                0 );

        glGenTextures( 1, &g.Normal );
        glBindTexture( GL_TEXTURE_2D, g.Normal );
        glTexImage2D(
                GL_TEXTURE_2D,
                0,
                GL_RGB16F,
                width,
                height,
                0,
                GL_RGB,
                GL_FLOAT,
                NULL );
        glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST );
        glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST );
        glFramebufferTexture2D(
                GL_FRAMEBUFFER,
                GL_COLOR_ATTACHMENT1,
                GL_TEXTURE_2D,
                g.Normal,
                0 );

        glGenTextures( 1, &g.Albedo_Spec );
        glBindTexture( GL_TEXTURE_2D, g.Albedo_Spec );
        glTexImage2D(
                GL_TEXTURE_2D,
                0,
                GL_RGBA,
                width,
                height,
                0,
                GL_RGBA,
                GL_UNSIGNED_BYTE,
                NULL );
        glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST );
        glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST );
        glFramebufferTexture2D(
                GL_FRAMEBUFFER,
                GL_COLOR_ATTACHMENT2,
                GL_TEXTURE_2D,
                g.Albedo_Spec,
                0 );
        GLuint attachments[3] = {
            GL_COLOR_ATTACHMENT0,
            GL_COLOR_ATTACHMENT1,
            GL_COLOR_ATTACHMENT2
        };

        glDrawBuffers( 3, attachments );

        glGenRenderbuffers( 1, &rbo_depth_ );
        glBindRenderbuffer( 1, rbo_depth_ );
        glRenderbufferStorage( GL_RENDERBUFFER, GL_DEPTH_COMPONENT, width, height );
        glFramebufferRenderbuffer(
                GL_FRAMEBUFFER,
                GL_DEPTH_ATTACHMENT,
                GL_RENDERBUFFER,
                rbo_depth_ );

        //Check for errors
        if( glCheckFramebufferStatus( GL_FRAMEBUFFER ) != GL_FRAMEBUFFER_COMPLETE )
        {
            fprintf(
                    stderr,
                    "Incomplete g-buffer.\n" );
        }
        //Load shaders.
    }

} //Model namespace.
