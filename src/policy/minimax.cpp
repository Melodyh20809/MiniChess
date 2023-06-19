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

// if minmax = 1 -> want max;
// if minmax = 0 -> want min;
int Minimax::minimax_value(int depth, State* state, int minmax) {
    int next_value, value;
    //printf("%d\n", depth);
    if (depth <= 0 || !state->legal_actions.size() ) {
        
        value = state->evaluate();
        //printf("!!!!!!!!!!!!!!!!!%d\n", value);
        return value;
    }
    int dep;
    dep = depth - 1;
    Move best_move;
    if (minmax == 1) {   // max
        value = -1000;
        //printf("?????????????????\n");
        for (auto it : state->legal_actions) {
            State* nextstate = state->next_state(it);
            nextstate->get_legal_actions();
            
            next_value = minimax_value(dep, nextstate, 0);
            if (next_value > value) {
                value = next_value;
            }
        }
        //printf("%d max\n", value);
        return value;
    }
    else {   // min
        value = 1000;
        //printf(">>>>>>>>>>>\n");
        for (auto it : state->legal_actions) {
            State* nextstate = state->next_state(it);
            nextstate->get_legal_actions();
            next_value = minimax_value(dep, nextstate, 1);
            if (next_value < value) {
                value = next_value;
            }
        }
        //printf("%d min\n", value);
        return value;
    }
    

}   



Move Minimax::get_move(State *state, int depth){

    if(!state->legal_actions.size())
        state->get_legal_actions();
    
    Move best_move;
    auto actions = state->legal_actions;
    int best_value = -10000, curr_value;

    for (int i = 0; i < state->legal_actions.size(); i++) {
        curr_value = minimax_value(depth--, state, 0);
        if (curr_value >= best_value) {
            best_value = curr_value;
            best_move = actions[i];
        }
    }
    return best_move;
} 