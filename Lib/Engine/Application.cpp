#include "Application.hpp"
#include "../Window/Window.hpp"
#include "../GUIElems/Scroll.hpp"
#include <SFML/Graphics/Color.hpp>

AbstractWindow* AIWM::Application::root_window = nullptr;

void AIWM::Application::start(){
    /*
    Application::root_window = new Slider({100, 100}, {100, 100}, {100, 300});
    Application::root_window = new TextView({100, 300}, {200, 300}, R"(Давай ронять слова,
Как сад — янтарь и цедру,
Рассеянно и щедро,
Едва, едва, едва.

Не надо толковать,
Зачем так церемонно
Мареной и лимоном
Обрызнута листва.

Кто иглы заслезил
И хлынул через жерди
На ноты, к этажерке
Сквозь шлюзы жалюзи.

Кто коврик за дверьми
Рябиной иссурьмил,
Рядном сквозных, красивых
Трепещущих курсивов.

Ты спросишь, кто велит,
Чтоб август был велик,
Кому ничто не мелко,
Кто погружен в отделку

Кленового листа
И с дней Экклезиаста
Не покидал поста
За теской алебастра?

Ты спросишь, кто велит,
Чтоб губы астр и далий
Сентябрьские страдали?
Чтоб мелкий лист ракит
С седых кариатид
Слетал на сырость плит
Осенних госпиталей?

Ты спросишь, кто велит?
— Всесильный бог деталей,
Всесильный бог любви,
Ягайлов и Ядвиг.

Не знаю, решена ль
Загадка зги загробной,
Но жизнь, как тишина
Осенняя, — подробна.)"); 
*/

    GraphicSystem::start();
    EventSystem::start();

}

void AIWM::Application::stop(){
    delete Application::root_window;
    GraphicSystem::stop();
    EventSystem::stop();
}

void AIWM::Application::run(){
    while (GraphicSystem::is_running()){

        root_window->handle_event(EventSystem::poll_event());
        root_window->handle_event(RedrawEvent());
        GraphicSystem::display_desktop();
    }
}
