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
#include "pathfinding.hpp"

std::vector<std::string> fileToArray (std::string filepath);

class Pacman : public AGameModule {
    public:
        typedef struct enemy {
            int color; // 0 = red, 1 = blue, 2 = pink, 3 = orange
            float x;
            float y;
            int direction;
            bool avlive;
        } enemy_t;

        typedef struct pos {
            float x;
            float y;
        } pos_t;

        Pacman();
        ~Pacman();
        void update(std::string key);
        const std::string &getName() const{return _name;};
        void resetGame(void);

    protected:
        void move(void);
        void dataToEntity(void);
        void enemyMove(void);
        void getInfoMap (std::vector<std::string> map);
        void pacmanPart(void);
        int chooseenemySprite (int color, int direction);
        void enemyPart(enemy_t enemy, int i, int row);
        bool eventAfterMoving(int x, int y);
        int checkIfPacmanTouchenemy(void);
        std::vector<std::string> getTextures(void);
        void fillGumsRemain(void);
        bool isValidPosition(int x, int y) const;
        t_myopen nextPositionPacman(void);

        float _pos_x = 0;
        float _pos_y = 0;
        int _score = 0;
        int _nbr_gums_remain = 0;
        int _lives = 3;
        int _invincible = 0;
        bool _isMoving = false;
        bool _second_sprite = false;
        bool _isAlive = true;
        DIRECTION _next_direction = DIRECTION::RIGHT;
        std::vector<enemy_t> _enemy;
        std::string _name = "Pacman";
        int _decal_y = 1;
        // std::string _map_file = "lib/games/pacman/map1.txt";
        int _level = 1;
};

#endif /* !PACMAN_HPP_ */
