struct flag_t {
  bool n, v, p, b, h, i, z, c;

  inline operator unsigned() const {
    return ((n ? 1 : 0) << 7) | ((v ? 1 : 0) << 6) | ((p ? 1 : 0) << 5) | ((b ? 1 : 0) << 4)
         | ((h ? 1 : 0) << 3) | ((i ? 1 : 0) << 2) | ((z ? 1 : 0) << 1) | ((c ? 1 : 0) << 0);
  }

  inline unsigned operator=(uint8 data) {
    n = (data & 0x80) ? true:false; v = (data & 0x40) ? true : false; p = (data & 0x20) ? true : false; b = (data & 0x10) ? true : false;
    h = (data & 0x08) ? true : false; i = (data & 0x04) ? true : false; z = (data & 0x02) ? true : false; c = (data & 0x01) ? true : false;
    return data;
  }

  inline unsigned operator|=(uint8 data) { return operator=(operator unsigned() | data); }
  inline unsigned operator^=(uint8 data) { return operator=(operator unsigned() ^ data); }
  inline unsigned operator&=(uint8 data) { return operator=(operator unsigned() & data); }
};

struct word_t {
  union {
    uint16 w;
    struct { uint8 l, h; };
  };

  inline operator unsigned() const { return w; }
  inline unsigned operator=(unsigned data) { return w = data; }

  inline unsigned operator++() { return ++w; }
  inline unsigned operator--() { return --w; }

  inline unsigned operator++(int) { unsigned data = w++; return data; }
  inline unsigned operator--(int) { unsigned data = w--; return data; }

  inline unsigned operator+=(unsigned data) { return w += data;; }
  inline unsigned operator-=(unsigned data) { return w -= data;; }

  inline unsigned operator|=(unsigned data) { return w |= data; }
  inline unsigned operator^=(unsigned data) { return w ^= data; }
  inline unsigned operator&=(unsigned data) { return w &= data; }
};

struct regs_t {
  word_t pc;
  union {
    uint16 ya;
    struct { uint8 a, y; };
  };
  uint8 x, s;
  flag_t p;
};
