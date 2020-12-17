#ifndef PLUGIN_API_HPP
#define PLUGIN_API_HPP
/*============================================================================*/

#include <cstdint>
#include <string>
#include <unordered_map>

/*============================================================================*/

namespace PluginAPI {

/*  Структура используется для передачи плагину доступа к вашему
 *  канвасу в момент применения плагина. Не храните в ней владеющий
 *  указатель на массив пикселей.
 */
struct Canvas {
    uint8_t* pixels;

    size_t height;
    size_t width;
};

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

struct Position {
    int64_t x;
    int64_t y;
};

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

struct Property {
    /* если вашему плагину требуются собственные свойства, то вы
       должны нумеровать их начиная с COUNT, в противном случае,
       поведение не определено */

    enum DISPLAY_TYPE { COLOR_PICKER, SLIDER, INPUTBOX, CHECKBOX };

    DISPLAY_TYPE display_type;

    const char* label;

    union {
        int32_t int_value;
        double double_value;
        void* pointer_value;
    };
};

/* Такая конструкция позволяет расширять enum,
 * не теряя при этом определенность передаваемых данных */

namespace TYPE {
struct Type {
   private:
    const int32_t value;

   public:
    explicit constexpr Type(int32_t value) : value(value) {}

    constexpr operator int32_t() const noexcept { return value; }

    constexpr bool operator==(const Type& other) const noexcept {
        return other.value == value;
    }

    friend struct std::hash<PluginAPI::TYPE::Type>;
};

constexpr Type PRIMARY_COLOR = Type(0);
constexpr Type SECONDARY_COLOR = Type(1);
constexpr Type THICKNESS = Type(2);
constexpr Type COUNT = Type(3);
};  // namespace TYPE

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

struct PluginInfo {
    uint16_t version;
    std::string name;
};
}  // namespace PluginAPI

namespace std {
template <>
struct hash<PluginAPI::TYPE::Type> {
    size_t operator()(const PluginAPI::TYPE::Type& property_type) const {
        std::hash<int32_t> type_value_hash;

        return type_value_hash(property_type.value);
    }
};
}

namespace PluginAPI {
class Plugin {
   public:
    /* init() вызывается в момент подгрузки плагина,
     * в ней нужно добавить в properties все свойства,
     * которые в дальнейшем потребуются плагину для настройки */
    virtual bool init() = 0;

    /* deinit() вызывается при закрытии редактора, чтобы плагин
     * освободил ресурсы в случае, если он захватил их в init() */
    virtual bool deinit() = 0;

    /* start_apply() вызывается, когда Canvas, с которым работает плагин,
     * получает событие -- нажатие кнопки мыши */
    virtual void start_apply(Canvas canvas, Position pos) = 0;

    /* apply() вызывается, когда Canvas, с которым работает плагин,
     * получает событие -- перемещение нажатой мыши */
    virtual void apply(Canvas canvas, Position pos) = 0;

    /* apply() вызывается, когда Canvas, с которым работает плагин,
     * получает событие -- отжатие кнопки мыши */
    virtual void stop_apply(Canvas canvas, Position pos) = 0;

    virtual ~Plugin() = default;

    using PropertyMap = std::unordered_map<TYPE::Type, Property>;

    PropertyMap properties;
};

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/* Функция для создания в статической области памяти объекта плагина.
 * Удобно использовать для определения функции get()
 */
template <typename SomePlugin>
PluginAPI::Plugin* get_instance() {
    static SomePlugin PLUGIN;
    return &PLUGIN;
}

}  // namespace PluginAPI

/*============================================================================*/
////////////////////////////////////////////////////////////////////////////////

/* Функция, которую следует определить разработчику плагина
 * для доступа к объекту плагина */
extern "C" PluginAPI::Plugin* get_plugin();

////////////////////////////////////////////////////////////////////////////////
/*============================================================================*/

/*~~~~~~~~~~~~~~~~~~MISC~~~~~~~~~~~~~~~~~~~~~*/
#endif
