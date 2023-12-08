#include "Board.h"

class Controller {
    private:
        Board board;
        
    public:
        Controller();
        ~Controller();

        void init();
        void LaunchGame();
};