#include <limits>
#include "Color.hpp"
#include "MathHelper.hpp"
#include "Vector4.hpp"
#include "Vector3.hpp"

using std::numeric_limits;

//Constructors
namespace Xna {
	Color::Color(){}

	Color::Color(uint32_t packedValue) :
		_packedValue(packedValue) {}    

    Color::Color(Vector4 color) :
        _packedValue(toPackedValue(
            static_cast<int32_t>(color.X * 255), 
            static_cast<int32_t>(color.Y * 255),
            static_cast<int32_t>(color.Z * 255), 
            static_cast<int32_t>(color.W * 255))){}

    Color::Color(Vector3 color) :
        _packedValue(toPackedValue(
            static_cast<int32_t>(color.X * 255),
            static_cast<int32_t>(color.Y * 255),
            static_cast<int32_t>(color.Z * 255))) {}

    Color::Color(Color color, int32_t alpha) :
        _packedValue(toPackedValue(color, alpha)) {}

    Color::Color(Color color, float alpha) :
        _packedValue(toPackedValue(color, static_cast<int32_t>(alpha * 255))) {}

    Color::Color(float r, float g, float b) :
        _packedValue(toPackedValue(
            static_cast<int32_t>(r * 255),
            static_cast<int32_t>(g * 255),
            static_cast<int32_t>(b * 255))) {}

    Color::Color(float r, float g, float b, float alpha) :
        _packedValue(toPackedValue(
            static_cast<int32_t>(r * 255),
            static_cast<int32_t>(g * 255),
            static_cast<int32_t>(b * 255),
            static_cast<int32_t>(alpha * 255))) {}

    Color::Color(int32_t r, int32_t g, int32_t b) :
        _packedValue(toPackedValue(r, g, b)) {}

    Color::Color(int32_t r, int32_t g, int32_t b, int32_t alpha) :
        _packedValue(toPackedValue(r, g, b, alpha)) {}

    Color::Color(uint8_t r, uint8_t g, uint8_t b, uint8_t alpha) :
        _packedValue(
            (static_cast<uint32_t>(alpha) << 24) 
            | (static_cast<uint32_t>(b) << 16) 
            | (static_cast<uint32_t>(g) << 8) 
            | r) {}	
}

//Operators
namespace Xna {
    bool operator ==(Color const& a, Color const& b) {
        return a.Equals(b);
    }

    bool operator !=(Color const& a, Color const& b) {
        return !a.Equals(b);
    }

    Color operator* (Color const& value, float scale) {
        return Color::Multiply(value, scale);
    }

    Color operator* (float scale, Color const& value) {
        return Color::Multiply(value, scale);
    }
}

//Static
namespace Xna {
    Color Color::Lerp(Color const& value1, Color const& value2, int16_t amount) {
        
        amount = MathHelper::Clamp(amount, 0, 1);
        
        return Color(
            static_cast<int32_t>(MathHelper::Lerp(value1.R(), value2.R(), amount)),
            static_cast<int32_t>(MathHelper::Lerp(value1.G(), value2.G(), amount)),
            static_cast<int32_t>(MathHelper::Lerp(value1.B(), value2.B(), amount)),
            static_cast<int32_t>(MathHelper::Lerp(value1.A(), value2.A(), amount)));
    }

    Color Color::Multiply(Color const& value, float scale) {
        return Color(
            static_cast<int32_t>(value.R() * scale),
            static_cast<int32_t>(value.G() * scale),
            static_cast<int32_t>(value.B() * scale),
            static_cast<int32_t>(value.A() * scale));
    }

    Color Color::FromNonPremultiplied(Vector4 const& vector) {
        return Color(
            vector.X * vector.W,
            vector.Y * vector.W,
            vector.Z * vector.W,
            vector.W);
    }

    Color Color::FromNonPremultiplied(int32_t r, int32_t g, int32_t b, int32_t a) {
        return Color(
            r * a / 255,
            g * a / 255,
            b * a / 255,
            a);
    }
}

//Fields
namespace Xna {
    uint8_t Color::B() const {
        return static_cast<int8_t>(_packedValue >> 16);
    }

    uint8_t Color::G() const {
        return static_cast<int8_t>(_packedValue >> 8);
    }

    uint8_t Color::R() const {
        return static_cast<int8_t>(_packedValue);
    }

    uint8_t Color::A() const {
        return static_cast<int8_t>(_packedValue >> 24);
    }

    void Color::B(uint8_t value) {
        _packedValue = (_packedValue & 0xff00ffff) | (static_cast<uint32_t>(value) << 16);
    }

    void Color::G(uint8_t value) {
        _packedValue = (_packedValue & 0xffff00ff) | ((static_cast<uint32_t>(value) << 8));
    }

    void Color::R(uint8_t value) {
        _packedValue = (_packedValue & 0xffffff00) | value;
    }

    void Color::A(uint8_t value) {
        _packedValue = (_packedValue & 0x00ffffff) | (static_cast<uint32_t>(value) << 24);
    }

    bool Color::Equals(Color other) const {
        return _packedValue == other._packedValue;
    }

    Vector3 Color::ToVector3() const {
        return Vector3(R() / 255.0F, G() / 255.0F, B() / 255.0F);
    }

    Vector4 Color::ToVector4() const {
        return Vector4(R() / 255.0F, G() / 255.0F, B() / 255.0F, A() / 255.0F);
    }
    
    uint32_t Color::PackedValue() {
        return _packedValue;
    }

    void Color::Deconstruct(uint8_t& r, uint8_t& g, uint8_t& b) const {
        r = R();
        g = G();
        b = B();
    }

    void Color::Deconstruct(float& r, float& g, float& b) const {
        r = R() / 255.F;
        g = G() / 255.F;
        b = B() / 255.F;
    }

    void Color::Deconstruct(uint8_t& r, uint8_t& g, uint8_t& b, uint8_t& a) const {
        r = R();
        g = G();
        b = B();
        a = A();
    }

    void Color::Deconstruct(float& r, float& g, float& b, float& a) const {
        r = R() / 255.F;
        g = G() / 255.F;
        b = B() / 255.F;
        a = A() / 255.F;
    }
}

//Private
namespace Xna {
    uint32_t Color::toPackedValue(Color color, int32_t alpha) {
        if ((alpha & 0xFFFFFF00) != 0) {

            auto constexpr byteMin = numeric_limits<uint8_t>::min();
            auto constexpr byteMax = numeric_limits<uint8_t>::max();
            auto clamp = MathHelper::Clamp(alpha, byteMin, byteMax);

            auto clampedA = static_cast<uint32_t>(clamp);

            return (color._packedValue & 0x00FFFFFF) | (clampedA << 24);
        }

        return (color._packedValue & 0x00FFFFFF) | (static_cast<uint32_t>(alpha) << 24);
    }

    uint32_t Color::toPackedValue(int32_t r, int32_t g, int32_t b) {
        int32_t _packedValue = 0xFF000000;

        if (((r | g | b) & 0xFFFFFF00) != 0)
        {
            auto constexpr byteMin = numeric_limits<uint8_t>::min();
            auto constexpr byteMax = numeric_limits<uint8_t>::max();

            auto clampedR = static_cast<uint32_t>(MathHelper::Clamp(r, byteMin, byteMax));
            auto clampedG = static_cast<uint32_t>(MathHelper::Clamp(g, byteMin, byteMax));
            auto clampedB = static_cast<uint32_t>(MathHelper::Clamp(b, byteMin, byteMax));

            return _packedValue |= (clampedB << 16) | (clampedG << 8) | (clampedR);
        }

        return _packedValue
            |= (static_cast<uint32_t>(b) << 16)
            | (static_cast<uint32_t>(g) << 8)
            | (static_cast<uint32_t>(r));
    }

    uint32_t Color::toPackedValue(int32_t r, int32_t g, int32_t b, int32_t alpha) {

        if (((r | g | b | alpha) & 0xFFFFFF00) != 0)
        {
            auto constexpr byteMin = numeric_limits<uint8_t>::min();
            auto constexpr byteMax = numeric_limits<uint8_t>::max();

            auto clampedR = static_cast<uint32_t>(MathHelper::Clamp(r, byteMin, byteMax));
            auto clampedG = static_cast<uint32_t>(MathHelper::Clamp(g, byteMin, byteMax));
            auto clampedB = static_cast<uint32_t>(MathHelper::Clamp(b, byteMin, byteMax));
            auto clampedA = static_cast<uint32_t>(MathHelper::Clamp(alpha, byteMin, byteMax));

            return (clampedA << 24) | (clampedB << 16) | (clampedG << 8) | (clampedR);
        }

        return (static_cast<uint32_t>(alpha) << 24)
            | (static_cast<uint32_t>(b) << 16)
            | (static_cast<uint32_t>(g) << 8)
            | (static_cast<uint32_t>(r));
    }
}

//Colors
namespace Xna {
    const Color Color::Transparent = 0;
    const Color Color::AliceBlue = 0xfffff8f0;
    const Color Color::AntiqueWhite = 0xffd7ebfa;    
    const Color Color::Aqua = 0xffffff00;
    const Color Color::Aquamarine = 0xffd4ff7f;
    const Color Color::Azure = 0xfffffff0;
    const Color Color::Beige = 0xffdcf5f5;
    const Color Color::Bisque = 0xffc4e4ff;
    const Color Color::Black = 0xff000000;
    const Color Color::BlanchedAlmond = 0xffcdebff;
    const Color Color::Blue = 0xffff0000;
    const Color Color::BlueViolet = 0xffe22b8a;
    const Color Color::Brown = 0xff2a2aa5;
    const Color Color::BurlyWood = 0xff2a2aa5;
    const Color Color::CadetBlue = 0xffa09e5f;
    const Color Color::Chartreuse = 0xff00ff7f;
    const Color Color::Chocolate = 0xff1e69d2;
    const Color Color::Coral = 0xff507fff;
    const Color Color::CornflowerBlue = 0xffed9564;
    const Color Color::Cornsilk = 0xffdcf8ff;
    const Color Color::Crimson = 0xff3c14dc;
    const Color Color::Cyan = 0xffffff00;
    const Color Color::DarkBlue = 0xff8b0000;
    const Color Color::DarkCyan = 0xff8b8b00;
    const Color Color::DarkGoldenrod = 0xff0b86b8;
    const Color Color::DarkGray = 0xffa9a9a9;
    const Color Color::DarkGreen = 0xff006400;
    const Color Color::DarkKhaki = 0xff6bb7bd;
    const Color Color::DarkMagenta = 0xff8b008b;
    const Color Color::DarkOliveGreen = 0xff2f6b55;
    const Color Color::DarkOrange = 0xff008cff;
    const Color Color::DarkOrchid = 0xffcc3299;
    const Color Color::DarkRed = 0xff00008b;
    const Color Color::DarkSalmon = 0xff7a96e9;
    const Color Color::DarkSeaGreen = 0xff8bbc8f;
    const Color Color::DarkSlateBlue = 0xff8b3d48;
    const Color Color::DarkSlateGray = 0xff4f4f2f;
    const Color Color::DarkTurquoise = 0xffd1ce00;
    const Color Color::DarkViolet = 0xffd30094;
    const Color Color::DeepPink = 0xff9314ff;
    const Color Color::DeepSkyBlue = 0xffffbf00;
    const Color Color::DimGray = 0xff696969;
    const Color Color::DodgerBlue = 0xffff901e;
    const Color Color::Firebrick = 0xff2222b2;
    const Color Color::FloralWhite = 0xfff0faff;
    const Color Color::ForestGreen = 0xff228b22;
    const Color Color::Fuchsia = 0xffff00ff;
    const Color Color::Gainsboro = 0xffdcdcdc;
    const Color Color::GhostWhite = 0xfffff8f8;
    const Color Color::Gold = 0xff00d7ff;
    const Color Color::Goldenrod = 0xff20a5da;
    const Color Color::Gray = 0xff808080;
    const Color Color::Green = 0xff008000;
    const Color Color::GreenYellow = 0xff2fffad;
    const Color Color::Honeydew = 0xfff0fff0;
    const Color Color::HotPink = 0xffb469ff;
    const Color Color::IndianRed = 0xff5c5ccd;
    const Color Color::Indigo = 0xff82004b;
    const Color Color::Ivory = 0xfff0ffff;
    const Color Color::Khaki = 0xff8ce6f0;
    const Color Color::Lavender = 0xfffae6e6;
    const Color Color::LavenderBlush = 0xfff5f0ff;
    const Color Color::LawnGreen = 0xff00fc7c;
    const Color Color::LemonChiffon = 0xffcdfaff;
    const Color Color::LightBlue = 0xffe6d8ad;
    const Color Color::LightCoral = 0xff8080f0;
    const Color Color::LightCyan = 0xffffffe0;
    const Color Color::LightGoldenrodYellow = 0xffd2fafa;
    const Color Color::LightGray = 0xffd3d3d3;
    const Color Color::LightGreen = 0xff90ee90;
    const Color Color::LightPink = 0xffc1b6ff;
    const Color Color::LightSalmon = 0xff7aa0ff;
    const Color Color::LightSeaGreen = 0xffaab220;
    const Color Color::LightSkyBlue = 0xffface87;
    const Color Color::LightSlateGray = 0xff998877;
    const Color Color::LightSteelBlue = 0xffdec4b0;
    const Color Color::LightYellow = 0xffe0ffff;
    const Color Color::Lime = 0xff00ff00;
    const Color Color::LimeGreen = 0xff32cd32;
    const Color Color::Linen = 0xffe6f0fa;
    const Color Color::Magenta = 0xffff00ff;
    const Color Color::Maroon = 0xff000080;
    const Color Color::MediumAquamarine = 0xffaacd66;
    const Color Color::MediumBlue = 0xffcd0000;
    const Color Color::MediumOrchid = 0xffd355ba;
    const Color Color::MediumPurple = 0xffdb7093;
    const Color Color::MediumSeaGreen = 0xff71b33c;
    const Color Color::MediumSlateBlue = 0xffee687b;
    const Color Color::MediumSpringGreen = 0xff9afa00;
    const Color Color::MediumTurquoise = 0xffccd148;
    const Color Color::MediumVioletRed = 0xff8515c7;
    const Color Color::MidnightBlue = 0xff701919;
    const Color Color::MintCream = 0xfffafff5;
    const Color Color::MistyRose = 0xffe1e4ff;
    const Color Color::Moccasin = 0xffb5e4ff;
    const Color Color::MonoGameOrange = 0xff003ce7;
    const Color Color::NavajoWhite = 0xffaddeff;
    const Color Color::Navy = 0xff800000;
    const Color Color::OldLace = 0xffe6f5fd;
    const Color Color::Olive = 0xff008080;
    const Color Color::OliveDrab = 0xff238e6b;
    const Color Color::Orange = 0xff00a5ff;
    const Color Color::OrangeRed = 0xff0045ff;
    const Color Color::Orchid = 0xffd670da;
    const Color Color::PaleGoldenrod = 0xffaae8ee;
    const Color Color::PaleGreen = 0xff98fb98;
    const Color Color::PaleTurquoise = 0xffeeeeaf;
    const Color Color::PaleVioletRed = 0xff9370db;
    const Color Color::PapayaWhip = 0xffd5efff;
    const Color Color::PeachPuff = 0xffb9daff;
    const Color Color::Peru = 0xff3f85cd;
    const Color Color::Pink = 0xffcbc0ff;
    const Color Color::Plum = 0xffdda0dd;
    const Color Color::PowderBlue = 0xffe6e0b0;
    const Color Color::Purple = 0xff800080;
    const Color Color::Red = 0xff0000ff;
    const Color Color::RosyBrown = 0xff8f8fbc;
    const Color Color::RoyalBlue = 0xffe16941;
    const Color Color::SaddleBrown = 0xff13458b;
    const Color Color::Salmon = 0xff7280fa;
    const Color Color::SandyBrown = 0xff60a4f4;
    const Color Color::SeaGreen = 0xff578b2e;
    const Color Color::SeaShell = 0xffeef5ff;
    const Color Color::Sienna = 0xff2d52a0;
    const Color Color::Silver = 0xffc0c0c0;
    const Color Color::SkyBlue = 0xffebce87;
    const Color Color::SlateBlue = 0xffcd5a6a;
    const Color Color::SlateGray = 0xff908070;
    const Color Color::Snow = 0xfffafaff;
    const Color Color::SpringGreen = 0xff7fff00;
    const Color Color::SteelBlue = 0xffb48246;
    const Color Color::Tan = 0xff8cb4d2;
    const Color Color::Teal = 0xff808000;
    const Color Color::Thistle = 0xffd8bfd8;
    const Color Color::Tomato = 0xff4763ff;
    const Color Color::Turquoise = 0xffd0e040;
    const Color Color::Violet = 0xffee82ee;
    const Color Color::Wheat = 0xffb3def5;
    const Color Color::White = 0xffffffff;
    const Color Color::WhiteSmoke = 0xfff5f5f5;
    const Color Color::Yellow = 0xff00ffff;
    const Color Color::YellowGreen = 0xff32cd9a;
}