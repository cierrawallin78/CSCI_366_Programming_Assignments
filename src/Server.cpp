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
#include "Server.hpp"


/**
 * Calculate the length of a file (helper function)
 *
 * @param file - the file whose length we want to query
 * @return length of the file in bytes
 */
int get_file_length(ifstream *file){
}


void Server::initialize(unsigned int board_size,
                        string p1_setup_board,
                        string p2_setup_board){
Server::board_size = board_size;
    if(board_size != BOARD_SIZE){
       throw ServerException("Improper Board Size");
    }

    if(p1_setup_board.empty()){
        throw ServerException("Incorrect File Name");

    }
    if(p2_setup_board.empty()){
        throw ServerException("Incorrect File name");
    }

}



int Server::evaluate_shot(unsigned int player, unsigned int x, unsigned int y) {


    if (x>board_size){
        return OUT_OF_BOUNDS ;
    }
    if (y>board_size){
        return OUT_OF_BOUNDS;
    }
    string name = "player_" + to_string(player) + ".setup_board.txt";


    using namespace std;
        fstream newfile;
        newfile.open(name,ios::in);
        string theone;
        string tp;

        if (newfile.is_open()){

            while(getline(newfile,tp)){
                theone.append(tp);

            }
            newfile.close();

        }

        char arr1[board_size][board_size];

        int m = 0;
        for(int i = 0; i<board_size; i++){
            for(int j = 0; j<board_size;j++){
                arr1[i][j] =theone[m];

                m++;

            }
        }


    if(arr1[x][y] == '_'){
        MISS;
    }
    else{
         HIT;
    }









    if ((player != 1) || (player != 2)) {
        throw ServerException("Must be player 1 or 2");
    }





}


int Server::process_shot(unsigned int player) {
    string name = "player_" + to_string(player) + ".shot.json";
    int x;
    int y;
    ifstream file;
    file.open(name);
    if (file) {
        {
            cereal::JSONInputArchive arc(file);
            arc(x);
            arc(y);

        }
        file.close();
    }
    //remove(fNarme.c_str());
    string n1 = "player_" + to_string(player) + ".result.json";
    int result = evaluate_shot(player, x ,y);
    ofstream f;

    f.open(n1);
    if (f){
        {
            cereal ::JSONOutputArchive arc (f);
            arc(CEREAL_NVP(result));

        }
        f.close();
    }








    if ((player != 1) || (player != 2)) {
        throw ServerException("Must be player 1 or 2");
    }

    return NO_SHOT_FILE;
    }