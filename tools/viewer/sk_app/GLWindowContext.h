
/*
 * Copyright 2016 Google Inc.
 *
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */
#ifndef GLWindowContext_DEFINED
#define GLWindowContext_DEFINED


#include "gl/GrGLInterface.h"

#include "SkRefCnt.h"
#include "GrRenderTarget.h"
#include "SkSurface.h"

#include "WindowContext.h"

class GrContext;

namespace sk_app {

class GLWindowContext : public WindowContext {
public:
    sk_sp<SkSurface> getBackbufferSurface() override;

    bool isValid() override { return SkToBool(fBackendContext.get()); }

    void resize(int w, int h) override;
    void swapBuffers() override;

    void setDisplayParams(const DisplayParams& params) override;

    GrBackendContext getBackendContext() override {
        return (GrBackendContext) fBackendContext.get();
    }

protected:
    GLWindowContext(const DisplayParams&);
    // This should be called by subclass constructor. It is also called when window/display
    // parameters change. This will in turn call onInitializeContext().
    void initializeContext();
    virtual void onInitializeContext() = 0;

    // This should be called by subclass destructor. It is also called when window/display
    // parameters change prior to initializing a new GL context. This will in turn call
    // onDestroyContext().
    void destroyContext();
    virtual void onDestroyContext() = 0;

    virtual void onSwapBuffers() = 0;

    SkAutoTUnref<const GrGLInterface> fBackendContext;
    sk_sp<GrRenderTarget>             fRenderTarget;
    sk_sp<SkSurface>                  fSurface;

    // parameters obtained from the native window
    // Note that the platform .cpp file is responsible for
    // initializing fSampleCount, fStencilBits, and fColorBits!
    int                               fSampleCount;
    int                               fStencilBits;
    int                               fColorBits;
    int                               fActualColorBits;
};

}   // namespace sk_app

#endif