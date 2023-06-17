#include <cstdlib>

#include "../state/state.hpp"
#include "./minimax_1.hpp"

using  DepthAndState = std::pair<int, State*>;
/**
 * @brief Randomly get a legal action
 * 
 * @param state Now state
 * @param depth You may need this for other policy
 * @return Move 
 */

Move Minimax::get_move(State *state, int depth){

  if(!state->legal_actions.size())
    state->get_legal_actions();
  
  auto actions = state->legal_actions;
  int val = 0;
  Move our_next = actions[0];
  if(state->player == 0){
    val = INT_MIN;
    for(unsigned long i=0; i<actions.size(); i++){

      if(val < set_heuristic( DepthAndState(depth, state->next_state(actions[i]))) ){
        val  = set_heuristic( DepthAndState(depth, state->next_state(actions[i])));
        our_next = actions[i];
      }

    }
    
  }
  else{
      
    val = INT_MAX;
    for(unsigned long i=0; i<actions.size(); i++){

      if(val > set_heuristic( DepthAndState(depth, state->next_state(actions[i]))) ){
        val  = set_heuristic( DepthAndState(depth, state->next_state(actions[i])));
        our_next = actions[i];
      }

    }
    
  }

  return our_next;



}

int Minimax::set_heuristic( DepthAndState now ){

  if(now.second->game_state == DRAW){
    return now.second->evaluate();
  }
  else if(now.second->game_state == WIN){
     
     if(now.second->player == 0){
      return INT_MAX;
     }
     else{
      return INT_MIN;
     }

  }
  else if( now.first == 0){

    return now.second->evaluate();

  }
  else{

    now.second->get_legal_actions();
    auto actions = now.second->legal_actions;
    int val = 0;

    if( now.second->player == 0){

      val  = INT_MIN;
      for(unsigned long i=0; i< actions.size(); i++){

        int tmp = set_heuristic( DepthAndState(now.first-1, now.second->next_state(actions[i])));
        if(tmp > val){
          val = tmp;
        }
      }

    }
    else{
      val = INT_MAX;
      for(unsigned long i=0; i< actions.size(); i++){

        int tmp = set_heuristic( DepthAndState(now.first-1, now.second->next_state(actions[i])));
        if(tmp < val){
          val = tmp;
        }
      }
    }


    return val;


  }




}