#include "opener.h"

class Anealling
{
 private:
    double temperature;
    int count;

    std::vector<std::shared_ptr<Node>> current;
    double Lcurrent;

    std::vector<std::shared_ptr<Node>> best;
    double Lbest;

    double pathL(const std::vector<std::shared_ptr<Node>>& nodes);

 public:
    Anealling(std::vector<std::shared_ptr<Node>> current, double temperature);
    
    std::vector<std::shared_ptr<Node>> try_new();

    double get_temp();
    double get_len();
    bool get_ended();
};
