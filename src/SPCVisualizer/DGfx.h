#pragma once

#include "IGfx.h"

class DCore;

class DGfx : public G::IGfx {
  public:
    DGfx();
    virtual ~DGfx();

    // Interface implementation : IGfx
    virtual std::unique_ptr<G::IRender>   CreateRender() override;
    virtual std::unique_ptr<G::ISolidBox> CreateSolidBox(const G::RectF& rRect,
                                                         const G::Color& rColor) override;

    virtual void FillRect(const G::RectF& rRect, const G::Color& rColor) override;

    // Other methods
    bool Init();
    void Release();

  private:
    bool m_init = false;

    std::unique_ptr<DCore> m_pCore;
};