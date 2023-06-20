#include <cstdlib>

#include <limits.h>

#include "../state/state.hpp"
#include "./submission.hpp"


/**
 * @brief Randomly get a legal action
 * 
 * @param state Now state
 * @param depth You may need this for other policy
 * @return Move 
 */

// if minmax = 1 -> want max;
// if minmax = 0 -> want min;

int player = 0;

int Submission::alphabeta_value(int depth, State* state, int minmax, int a, int b) {
    int next_value, value;
    if (depth <= 0) {
        value = state->evaluate(player);
        return value;
    }
    
    else if (minmax) {   // max
        value = INT_MIN;
        state->get_legal_actions();
        for (auto it : state->legal_actions) {
            State* nextstate = state->next_state(it);
            next_value = alphabeta_value(depth - 1, nextstate, 0, a, b);
            value = std::max(value, next_value);
            a = std::max(a, value);
            if (a >= b) break;
        }
        return value;
    }
    else {   // min
        value = INT_MAX;
        state->get_legal_actions();
        for (auto it : state->legal_actions) {
            State* nextstate = state->next_state(it);
            next_value = alphabeta_value(depth - 1, nextstate, 1, a, b);
            value = std::min(value, next_value);
            b = std::min(b, value);
            if (b <= a) break;
        }
        return value;
    }
    
}   

Move Submission::get_move(State *state, int depth){

    if(!state->legal_actions.size())
        state->get_legal_actions();
    
    Move best_move;
    int best_value = -1000, curr_value;
    int a = -10000, b = 10000;

    player = state->player;
    for (auto it : state->legal_actions) {
        State* nextstate = state->next_state(it);
        curr_value = alphabeta_value(depth -1, nextstate, 0, a, b);
        if (curr_value >= best_value) {
            best_value = curr_value;
            best_move = it;
        }
    }
    return best_move;
} 