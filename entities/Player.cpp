#include <string>
#include <array>
#include "Player.h"
#include "../states/State.h" // enum MoveType
#include "../Game.h"
#include "../Logger.h"

#define PLAYER_TEXTURE Game::instance().texture_holder().get("player")
#define PLAYER_TEXTURE_GRID_SIZE 128

using sf::Keyboard;

Player::Player() {
	m_physics   = PhysicsPtr(new PhysicsComponent(this));
	m_animation = AnimationPtr(new AnimationComponent(this));
	m_state     = StatePtr(new StateComponent(this));
	m_input     = InputPtr(new InputComponent(this));

    set_dir(D_RIGHT);
	set_width(70);
	set_height(115);

    /* Animations */
    std::string s, dir_str;
    int gs = PLAYER_TEXTURE_GRID_SIZE;
	m_animation->set_offset({0,height()-PLAYER_TEXTURE_GRID_SIZE});

    for (bool is_right : {true,false})
    {
        dir_str = (is_right)? ":right":":left";

        s = "wall-slide"; s += dir_str;
        m_animation->add_animation(s, PLAYER_TEXTURE, sf::seconds(10), AnimationType::LOOP, !is_right);
            m_animation->animation(s)->add_frame({4,6, gs,gs}, {0,0,gs,gs});
            m_animation->animation(s)->add_frame({4,6, gs,gs}, {0,0,gs,gs});

        s = "roll"; s += dir_str;
        m_animation->add_animation(s, PLAYER_TEXTURE, sf::seconds(0.02), AnimationType::ONCE, !is_right);
        for (int i = 0; i < 10; ++i)
            m_animation->animation(s)->add_frame({i,7, gs,gs}, {0,0,gs,gs});

        s = "dive"; s += dir_str;
        m_animation->add_animation(s, PLAYER_TEXTURE, sf::seconds(0.1), AnimationType::LOOP, !is_right);
        for (int i = 0; i < 3; ++i)
            m_animation->animation(s)->add_frame({i,8, gs,gs}, {0,0,gs,gs});

        s = "turn-around"; s += dir_str;
        m_animation->add_animation(s, PLAYER_TEXTURE, sf::seconds(0.025), AnimationType::ONCE, !is_right);
            m_animation->animation(s)->add_frame({2,4, gs,gs}, {0,0,gs,gs});
            m_animation->animation(s)->add_frame({0,3, gs,gs}, {0,0,gs,gs});
            m_animation->animation(s)->add_frame({0,3, gs,gs}, {0,0,gs,gs});

        s = "edge-lean"; s += dir_str;
        m_animation->add_animation(s, PLAYER_TEXTURE, sf::seconds(0.3), AnimationType::LOOP, !is_right);
            m_animation->animation(s)->add_frame({1,2, gs,gs}, {0,0,gs,gs});
            m_animation->animation(s)->add_frame({2,2, gs,gs}, {0,0,gs,gs});
            m_animation->animation(s)->add_frame({3,2, gs,gs}, {0,0,gs,gs});

        s = "idle"; s += dir_str;
        m_animation->add_animation(s, PLAYER_TEXTURE, sf::seconds(0.2), AnimationType::LOOP, !is_right);
            m_animation->animation(s)->add_frame({1,4, gs,gs}, {0,0,gs,gs});
            m_animation->animation(s)->add_frame({2,4, gs,gs}, {0,0,gs,gs});

        s = "turn-to-prep-jump"; s += dir_str;
        m_animation->add_animation(s, PLAYER_TEXTURE, sf::seconds(0.025), AnimationType::ONCE, !is_right);
            m_animation->animation(s)->add_frame({5,6, gs,gs}, {0,0,gs,gs});

        s = "land"; s += dir_str;
        m_animation->add_animation(s, PLAYER_TEXTURE, sf::seconds(0.1), AnimationType::ONCE, !is_right);
            m_animation->animation(s)->add_frame({1,7, gs,gs}, {0,0,gs,gs});
            m_animation->animation(s)->add_frame({0,7, gs,gs}, {0,0,gs,gs});

        s = "prep-jump"; s += dir_str;
        m_animation->add_animation(s, PLAYER_TEXTURE, sf::seconds(0.05), AnimationType::ONCE, !is_right);
            m_animation->animation(s)->add_frame({0,7, gs,gs}, {0,0,gs,gs});
            m_animation->animation(s)->add_frame({1,7, gs,gs}, {0,0,gs,gs});

        s = "jump"; s += dir_str;
        m_animation->add_animation(s, PLAYER_TEXTURE, sf::seconds(0.1), AnimationType::ONCE, !is_right);
        for (int i = 3; i < 5; ++i)
            m_animation->animation(s)->add_frame({i,5, gs,gs}, {0,0,gs,gs});

        s = "in-air"; s += dir_str;
        m_animation->add_animation(s, PLAYER_TEXTURE, sf::seconds(0.1), AnimationType::LOOP, !is_right);
        for (int i = 0; i < 3; ++i)
            m_animation->animation(s)->add_frame({i,5, gs,gs}, {0,0,gs,gs});

        s = "skid"; s += dir_str;
        m_animation->add_animation(s, PLAYER_TEXTURE, sf::seconds(0.2), AnimationType::LOOP, !is_right);
            m_animation->animation(s)->add_frame({0,2, gs,gs}, {0,0,gs,gs});
            m_animation->animation(s)->add_frame({0,2, gs,gs}, {0,0,gs,gs});

        float walk_frame_speed = 0.0165; // 0.0175
        s = "init-walk"; s += dir_str;
        m_animation->add_animation(s, PLAYER_TEXTURE, sf::seconds(walk_frame_speed), AnimationType::ONCE, !is_right);
        for (int i = 0; i < 10; ++i)
            m_animation->animation(s)->add_frame({i,0, gs,gs}, {0,0,gs,gs});

        s = "walk"; s += dir_str;
        m_animation->add_animation(s, PLAYER_TEXTURE, sf::seconds(walk_frame_speed), AnimationType::LOOP, !is_right);
        for (int i = 0; i < 10; ++i)
            m_animation->animation(s)->add_frame({i,1, gs,gs}, {0,0,gs,gs});

        s = "run"; s += dir_str;
        m_animation->add_animation(s, PLAYER_TEXTURE, sf::seconds(0.012), AnimationType::LOOP, !is_right);
        for (int i = 0; i < 10; ++i)
            m_animation->animation(s)->add_frame({i,1, gs,gs}, {0,0,gs,gs});

    }

	m_animation->play_animation("idle:right");

}

void Player::update(float dt) {
    m_state->handle_input();

	m_input->update(dt);
    m_state->update(dt);
	m_physics->update(dt);
	m_animation->update(dt);
}

void Player::render(sf::RenderWindow &window) {
	m_animation->render(window);
}
