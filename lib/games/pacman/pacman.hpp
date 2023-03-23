/*
**  ______   ______     ______     __    __     ______     __   __
** /\  == \ /\  __ \   /\  ___\   /\ "-./  \   /\  __ \   /\ "-.\ \
** \ \  _-/ \ \  __ \  \ \ \____  \ \ \-./\ \  \ \  __ \  \ \ \-.  \
**  \ \_\    \ \_\ \_\  \ \_____\  \ \_\ \ \_\  \ \_\ \_\  \ \_\\"\_\
**   \/_/     \/_/\/_/   \/_____/   \/_/  \/_/   \/_/\/_/   \/_/ \/_/
**
*/

#ifndef PACMAN_HPP_
#define PACMAN_HPP_
#include "AGameModule.hpp"

class Pacman : public AGameModule {
    public:
        typedef struct ennemy {
            int color; // 0 = red, 1 = blue, 2 = pink, 3 = orange
            float x;
            float y;
            int direction;
            bool avlive;
        } ennemy_t;

        Pacman();
        ~Pacman();
        void update(std::string key);
        const std::string &getName() const{return _name;};

    protected:
        void move(void);
        void dataToEntity(void);
        void getInfoMap (std::vector<std::string> map);
        void pacmanPart(void);
        int chooseEnnemySprite (int color, int direction);
        void ennemyPart(ennemy_t ennemy, int i, int row);
        void positionToThisValue(int value);
        bool eventAfterMoving(int x, int y);
        int checkIfPacmanTouchEnnemy(void);
        std::vector<std::string> getTextures(void);

        float _pos_x = 0;
        float _pos_y = 0;
        int _score = 0;
        int _lives = 3;
        int _invincible = 0;
        bool _isMoving = false;
        bool _second_sprite = false;
        bool _isAlive = true;
        DIRECTION _next_direction = DIRECTION::RIGHT;
        std::vector<ennemy_t> _ennemy;
        std::string _name = "Pacman";
};

#endif /* !PACMAN_HPP_ */
