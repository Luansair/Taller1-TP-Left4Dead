#include <exception>
#include <SDL2pp/SDL2pp.hh>
#include "yaml-cpp/yaml.h"
#include "../include/client.h"
#include "../../Common/include/Information/Actions/shoot_start.h"
#include "../../Common/include/Information/Actions/game_join.h"
#include "../../Common/include/Information/Actions/game_create.h"
#include "../../Common/include/Information/information_code.h"
#include "../include/Animations/animation_manager.h"
#include "../include/Drawer/drawer_manager.h"
#include "../include/visual_game.h"
#include "../../Common/include/Information/Actions/moving_right_start.h"
#include "../../Common/include/Information/Actions/moving_left_start.h"
#include "../../Common/include/Information/Actions/moving_right_stop.h"
#include "../../Common/include/Information/Actions/moving_left_stop.h"


Client::Client(const char *hostname, const char *servname) :
    socket(hostname, servname) ,
    protocol(socket),
    actions_to_send(5000),
    feedback_received(10000),
    sender(actions_to_send, socket),
    receiver(feedback_received, socket) {
}

void Client::processEvent(std::uint32_t event_type, int key_code, bool *quit)
{
    if (event_type == SDL_KEYDOWN)
    {
        switch (key_code)
        {
        case SDLK_ESCAPE:
            *quit = true;
            break;

        case SDLK_z:
            protocol.sendAction(StartShootAction());
            break;

        default:
            break;
        }
    }
}

// Crear clases: texture manager q tenga dicc mapa etc para mapear. No crear
// la textura en cada game loop.
// jugadores, animaciones, mapa
// Es responsabilidad del cliente transformar lo q reciba a pixeles. No va a
// recibir pixeles directamente
// Poder cambiar parametros in game para probar
void Client::start() {
    using SDL2pp::NullOpt;
    using SDL2pp::Rect;
    using SDL2pp::Renderer;
    using SDL2pp::SDL;
    using SDL2pp::Texture;
    using SDL2pp::Window;

    using YAML::LoadFile;
    using YAML::Node;

    using std::make_shared;
    using std::shared_ptr;

    sender.start();
    receiver.start();
    // crear clase lobby
    bool joined = false;
    std::cout << "Waiting input. Use 'create' or 'join <code>' to join a "
                 "game."
              << std::endl;
    while (!joined)
    {
        std::string action;
        std::cin >> action;
        if (action == "join")
        {
            std::uint32_t game_code;
            std::cin >> game_code;
            actions_to_send.push(
                    make_shared<JoinGameAction>(game_code));
            joined = true;
        }
        else if (action == "create")
        {
            actions_to_send.push(make_shared<CreateGameAction>());
            const std::shared_ptr<Information>& create_feed =
                    feedback_received.pop();

            if (create_feed == nullptr)
            {
                throw std::runtime_error("Client::start. CreateFeedback is "
                                         "null.\n");
            }
            std::cout << dynamic_cast<CreateGameFeedback *>(create_feed.get())
                             ->game_code
                      << std::endl;
            joined = true;
        }
    }

    Node window_config = LoadFile(CLIENT_CONFIG_PATH "/config.yaml")["window"];

    const auto window_width =
        window_config["width"].as<std::uint16_t>();
    const auto window_height =
        window_config["height"].as<std::uint16_t>();

    GameVisual game_visual(window_width, window_height);
    /*
    std::uint16_t player_id = 0x1234;

    // Big part of this logic has to be done by the Server
    double position = 0.0;
    bool is_running_right = false;
    bool is_running_left = false;
    bool last_input_right = false;
    bool last_input_left = false;

    std::int8_t direction = DrawDirection::DRAW_RIGHT;
    */
    std::shared_ptr<Information> information_ptr = nullptr;
    bool quit = false;
    while (!quit)
    {
        unsigned int frame_ticks = SDL_GetTicks();

        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            processEvent(event.type, event.key.keysym.sym, &quit);
            if (event.type == SDL_QUIT)
            {
                quit = true;
            }
            else if (event.type == SDL_KEYDOWN)
            {
                switch (event.key.keysym.sym)
                {
                case SDLK_ESCAPE:
                    quit = true;
                    break;

                case SDLK_RIGHT:
                    actions_to_send.push(
                            make_shared<StartMovingRightAction>());
                    break;

                case SDLK_LEFT:
                    actions_to_send.push(
                            make_shared<StartMovingLeftAction>());
                    break;
                }
                // Parseamos y definimos valores
            }
            else if (event.type == SDL_KEYUP)
            {
                switch (event.key.keysym.sym)
                {
                case SDLK_RIGHT:
                    actions_to_send.push(
                            make_shared<StopMovingRightAction>());
                    break;

                case SDLK_LEFT:
                    actions_to_send.push(
                            make_shared<StopMovingLeftAction>());
                    break;
                }
            }
        }
        /*
        if (is_running_right && is_running_left)
        {
            if (last_input_right)
            {
                direction = DrawDirection::DRAW_RIGHT;
                position += frame_delta * 0.27;
            }
            else if (last_input_left)
            {
                direction = DrawDirection::DRAW_LEFT;
                position -= frame_delta * 0.27;
            }
        }
        else if (is_running_right)
        {
            direction = DrawDirection::DRAW_RIGHT;
            position += frame_delta * 0.27;
        }
        else if (is_running_left)
        {
            direction = DrawDirection::DRAW_LEFT;
            position -= frame_delta * 0.27;
        }

        int src_width = 128;
        int src_height = 128;

        if (position > window_width)
            position = -src_width;

        if (position < -src_width)
            position = window_width;

        int vcenter = window_height / 2;



        uint8_t type = ElementType::SOLDIER_1;
        uint8_t action = SoldierOneActionID::SOLDIER_1_IDLE;
        if (is_running_right || is_running_left)
        {
            action = SoldierOneActionID::SOLDIER_1_RUN;
        }
        if (frame_ticks > 10000)
        {
            action = SoldierOneActionID::SOLDIER_1_DEAD;
            position = (window_width / 2) - src_width;
            direction = DrawDirection::DRAW_RIGHT;
        }
         */
        game_visual.clear();

        feedback_received.try_pop(information_ptr);
        if (information_ptr != nullptr) {
            game_visual.updateInfo(dynamic_cast<GameStateFeedback&>
                                   (*information_ptr));
        }

        /*
        ElementStateDTO player_state = {type, action,
                                        direction,
                                        static_cast<int>(position),
                                        vcenter - src_height};
        ElementStateDTO zombie1_state = {
            ZOMBIE, ZOMBIE_IDLE, DRAW_RIGHT, window_width / 4, window_height / 4};
        std::vector<std::pair<std::uint16_t, ElementStateDTO>> actors;
        actors.emplace_back(player_id, player_state);
        actors.emplace_back(0x5678, zombie1_state);
        GameStateFeedback game_state(std::move(actors));
        game_visual.updateInfo(game_state);
         */
        game_visual.draw(frame_ticks);

        game_visual.present();

        SDL_Delay(1);
    }
}

Client::~Client() {

    if (!receiver.isDead()) {
        receiver.stop();
    }
    if(!sender.isDead()) {
        sender.stop();
    }
    receiver.join();
    sender.join();
}
