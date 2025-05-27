#ifndef GENERAL_HPP
#define GENERAL_HPP
#include "Player.hpp"
using namespace std;
namespace coup {
    class General: public Player {;
    private:
        /* data */
    public:
    General(Game &game, const string &name): Player(game, name) {
        _role = "General";
    }
        string role() const{
            return _role;
        };
        string getName(){
            return _name;
        };
        void undo(const Player &player){}
        ~General(){}
        bool is_active() const{
            return _is_active;
        } 
        
    void set_active(bool is_active, bool using_gui=false){
        
        if(coins()>=5&&is_active==false){

            if(using_gui==false){
                
                cout<<"do you want to save yourself?"<<endl;
                string ans;
                cin>>ans;
                if(ans=="yes"){
                    _is_active = true;
                    _coinNum -= 5;
                    cout<<_name<<" saved "<<endl;
                    return;
                }else{
                    _is_active = false;
                    cout<<_name<<" is dead"<<endl;
                    return;
                }
                _is_active = is_active;
            }else{
            bool save = askToStayAlive();
            if(save==true){
                _is_active = true;
                _coinNum -= 5;
                cout<<_name<<" saved "<<endl;
                return;
            }
            else{
                _is_active = false;
                cout<<_name<<" is dead"<<endl;
                return;
            }
            
        }
        
        }
        else{
            _is_active=is_active;
        }
    }


        // /
    //  * @brief Use this method to set the alive status of the player when using GUI.
    //  * @param alive The alive status to set.
    //  */
    // void General::setIsAlivedGui(bool alive) {
    //     if (alive == false && coinsNum >= 5) {
    //         bool check = askToStayAlive(); // Ask the player if they want to pay 5 coins to stay alive
    //         if (check == false) {
    //             Alive = alive;
    //             return;
    //         } else {
    //             coinsNum -= 5;
    //             std::cout << "General paid 5 coins to stay alive" << std::endl;
    //             return;
    //         }
    //     }
    //     Alive = alive;
        
    // }

     bool askToStayAlive();

    //     void set_active(bool is_active, bool live=false){
    //         if(live==false){
    //         if(coins()>=5&&is_active==false){
    //             cout<<"do you want to save yourself?"<<endl;
    //             string ans;
    //             cin>>ans;
    //             if(ans=="yes"){

    //                 _is_active = true;
    //                 cout<<_name<<" saved "<<endl;
    //                 return;
    //             }else{
    //                 _is_active = false;
    //                 cout<<_name<<" is dead"<<endl;
    //                 return;
    //             }
    //         }
    //     }
    //         _is_active = is_active;

    // }
        int coins() const{
            return _coinNum;
        }
        void set_coins(int coins){
            _coinNum = coins;
        }
        void add_coins(int coins){
            _coinNum += coins;
        }
        void remove_coins(int coins){
            _coinNum -= coins;
        }
        void undo_coup( Player &player);
        // Destructor
};
    
}
#endif // GENERAL_HPP