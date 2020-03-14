//    Battleship game assignment for MSU CSCI 366
//    Copyright (C) 2020    Mike P. Wittie
//
//    This program is free software: you can redistribute it and/or modify
//    it under the terms of the GNU General Public License as published by
//    the Free Software Foundation, either version 3 of the License, or
//    (at your option) any later version.
//
//    This program is distributed in the hope that it will be useful,
//    but WITHOUT ANY WARRANTY; without even the implied warranty of
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//    GNU General Public License for more details.
//
//    You should have received a copy of the GNU General Public License
//    along with this program.  If not, see <https://www.gnu.org/licenses/>.

#include "common.hpp"
#include "Client.hpp"

Client::~Client() {
}


void Client::initialize(unsigned int player, unsigned int board_size){

    string name = "player_" + to_string(player) + ".action_board.json";
    vector <int> v(board_size);
    vector<vector<int>>board(board_size,v);
    ofstream file;
    file.open(name, ofstream::out);
    if (file){
        {
            cereal::JSONOutputArchive arc(file);
            arc(CEREAL_NVP(board));
        }
        file.close();
        initialized = true;

    }
    else{
        cout << "File could not be found."<<endl;
    }
}


void Client::fire(unsigned int x, unsigned int y) {
    string name = "player_" + to_string(player) + ".shot.json";
    ofstream file;
    file.open(name);
    if (file) {
        {
            cereal::JSONOutputArchive arc(file);
            arc(CEREAL_NVP(x));
            arc(CEREAL_NVP(y));
        }
        file.close();
    }

}


bool Client::result_available() {
    if(HIT | MISS) {


        return true;

    }

}


int Client::get_result() {
    string name = "player_" + to_string(player) + ".result.json";
    int result;

    ifstream file;
    file.open(name);
    if(file){
        {
            cereal:: JSONInputArchive arc(file);
            arc(result);
        }
        file.close();
    }



    if (result>board_size){
        result = OUT_OF_BOUNDS ;
    }


    return result;


}



void Client::update_action_board(int result, unsigned int x, unsigned int y) {


    string name = "player_" + to_string(player) + ".action_board.json";
    int n[x][y];

    ifstream file;
    file.open(name);
    if (file){
        {
            cereal::JSONInputArchive arc(file);
            arc(n[x][y]);


        }
    file.close();


    }

    ofstream f;
    f.open(name);
    if(f){
        {
            cereal::JSONOutputArchive arc(f);
            arc(CEREAL_NVP(n[x][y]));


        }
    f.close();

    }






}
string Client::render_action_board(){

}