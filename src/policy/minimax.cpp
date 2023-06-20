#include <cstdlib>

#include "../state/state.hpp"
#include "./minimax.hpp"


/**
 * @brief Randomly get a legal action
 * 
 * @param state Now state
 * @param depth You may need this for other policy
 * @return Move 
 */
int player = 0;

// if minmax = 1 -> want max;
// if minmax = 0 -> want min;

int Minimax::minimax_value(int depth, State* state, int minmax) {
    int next_value, value;
    if (depth <= 0 || !state->legal_actions.size() ) {
        
        value = state->evaluate(player);
        return value;
    }
    int dep;
    dep = depth - 1;
    if (minmax == 1) {   // max
        value = -1000;
        for (auto it : state->legal_actions) {
            State* nextstate = state->next_state(it);
            nextstate->get_legal_actions();
            
            next_value = minimax_value(dep, nextstate, 0);
            if (next_value > value) {
                value = next_value;
            }
        }
        return value;
    }
    else {   // min
        value = 1000;
        for (auto it : state->legal_actions) {
            State* nextstate = state->next_state(it);
            nextstate->get_legal_actions();
            next_value = minimax_value(dep, nextstate, 1);
            if (next_value < value) {
                value = next_value;
            }
        }
        return value;
    }
    

}   



Move Minimax::get_move(State *state, int depth){

    if(!state->legal_actions.size())
        state->get_legal_actions();
    
    Move best_move;
    int best_value = -10000, curr_value;
    player = state->player;
    
    for (auto it : state->legal_actions) {
        State* nextstate = state->next_state(it);
        curr_value = minimax_value(depth - 1, nextstate, 0);
        if (curr_value >= best_value) {
            best_value = curr_value;
            best_move = it;
        }
    }
    return best_move;
} 